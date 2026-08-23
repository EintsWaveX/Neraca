import { describe, expect, it } from 'vitest'
import type { Budget, Transaction } from './types'
import { activeAlerts, budgetPeriodRange, evaluateBudget } from './budget'

function budget(overrides: Partial<Budget> = {}): Budget {
  return {
    id: 'b1',
    profileId: 'p1',
    period: 'monthly',
    periodKey: '2026-08',
    categoryId: null,
    limit: 1_000_000,
    target: null,
    description: '',
    alertThreshold: 0.8,
    alertsEnabled: true,
    createdAt: '2026-08-01T00:00:00.000Z',
    ...overrides,
  }
}

function tx(overrides: Partial<Transaction> = {}): Transaction {
  return {
    id: 't1',
    profileId: 'p1',
    walletId: 'w1',
    toWalletId: null,
    date: '2026-08-10',
    direction: 'expense',
    typeId: 'payment-with-card',
    categoryId: 'groceries',
    amount: 10_000,
    currency: 'IDR',
    toAmount: null,
    rateToBase: 1,
    description: '',
    recurringId: null,
    createdAt: '2026-08-10T00:00:00.000Z',
    ...overrides,
  }
}

describe('budgetPeriodRange', () => {
  it('spans the whole month for a monthly period key', () => {
    expect(budgetPeriodRange(budget({ period: 'monthly', periodKey: '2026-08' })))
      .toEqual({ start: '2026-08-01', end: '2026-08-31' })
  })

  it('handles a short month', () => {
    expect(budgetPeriodRange(budget({ period: 'monthly', periodKey: '2026-02' })))
      .toEqual({ start: '2026-02-01', end: '2026-02-28' })
  })

  it('spans the whole year for a yearly period key', () => {
    expect(budgetPeriodRange(budget({ period: 'yearly', periodKey: '2026' })))
      .toEqual({ start: '2026-01-01', end: '2026-12-31' })
  })
})

describe('evaluateBudget', () => {
  it('is under when spending is below the alert threshold', () => {
    const status = evaluateBudget(
      budget({ limit: 1_000_000, alertThreshold: 0.8 }),
      [tx({ amount: 300_000 })],
      'IDR',
    )
    expect(status.spent.minor).toBe(300_000)
    expect(status.remaining.minor).toBe(700_000)
    expect(status.fraction).toBeCloseTo(0.3)
    expect(status.state).toBe('under')
  })

  it('is approaching at or past the alert threshold but not yet over', () => {
    const status = evaluateBudget(
      budget({ limit: 1_000_000, alertThreshold: 0.8 }),
      [tx({ amount: 800_000 })],
      'IDR',
    )
    expect(status.state).toBe('approaching')
  })

  it('is over once spending reaches the limit', () => {
    const status = evaluateBudget(
      budget({ limit: 1_000_000, alertThreshold: 0.8 }),
      [tx({ amount: 1_000_000 })],
      'IDR',
    )
    expect(status.state).toBe('over')
  })

  it('is over past the limit, with remaining going negative', () => {
    const status = evaluateBudget(
      budget({ limit: 1_000_000 }),
      [tx({ amount: 1_500_000 })],
      'IDR',
    )
    expect(status.state).toBe('over')
    expect(status.remaining.minor).toBe(-500_000)
  })

  it('only counts expenses inside the period', () => {
    const rows = [
      tx({ amount: 100_000, date: '2026-07-31' }),
      tx({ amount: 200_000, date: '2026-08-01' }),
      tx({ amount: 300_000, date: '2026-08-31' }),
      tx({ amount: 400_000, date: '2026-09-01' }),
    ]
    const status = evaluateBudget(budget({ periodKey: '2026-08' }), rows, 'IDR')
    expect(status.spent.minor).toBe(500_000)
  })

  it('excludes income and transfers', () => {
    const rows = [
      tx({ direction: 'expense', amount: 100_000 }),
      tx({ direction: 'income', amount: 500_000 }),
      tx({ direction: 'transfer', amount: 500_000, toWalletId: 'w2' }),
    ]
    const status = evaluateBudget(budget(), rows, 'IDR')
    expect(status.spent.minor).toBe(100_000)
  })

  it('a null categoryId counts every category', () => {
    const rows = [
      tx({ categoryId: 'groceries', amount: 100_000 }),
      tx({ categoryId: 'daily-meal', amount: 200_000 }),
    ]
    const status = evaluateBudget(budget({ categoryId: null }), rows, 'IDR')
    expect(status.spent.minor).toBe(300_000)
  })

  it('a set categoryId counts only that category', () => {
    const rows = [
      tx({ categoryId: 'groceries', amount: 100_000 }),
      tx({ categoryId: 'daily-meal', amount: 200_000 }),
    ]
    const status = evaluateBudget(budget({ categoryId: 'groceries' }), rows, 'IDR')
    expect(status.spent.minor).toBe(100_000)
  })

  describe('a zero limit budget', () => {
    it('is under, not NaN or Infinity, when nothing was spent', () => {
      const status = evaluateBudget(budget({ limit: 0 }), [], 'IDR')
      expect(status.fraction).toBe(0)
      expect(Number.isFinite(status.fraction)).toBe(true)
      expect(status.state).toBe('under')
    })

    it('is over, not NaN or Infinity, as soon as anything is spent', () => {
      const status = evaluateBudget(budget({ limit: 0 }), [tx({ amount: 1 })], 'IDR')
      expect(status.fraction).toBe(1)
      expect(Number.isFinite(status.fraction)).toBe(true)
      expect(status.state).toBe('over')
    })
  })
})

describe('activeAlerts', () => {
  it('only includes budgets with alerts enabled', () => {
    const alerts = activeAlerts(
      [budget({ id: 'b1', limit: 100, alertsEnabled: false }), budget({ id: 'b2', limit: 100, alertsEnabled: true })],
      [tx({ amount: 200 })],
      'IDR',
    )
    expect(alerts.map((a) => a.budget.id)).toEqual(['b2'])
  })

  it('excludes budgets that are still under their threshold', () => {
    const alerts = activeAlerts([budget({ limit: 1_000_000, alertThreshold: 0.8 })], [tx({ amount: 100_000 })], 'IDR')
    expect(alerts).toHaveLength(0)
  })

  it('sorts worst first', () => {
    // Separate categories so each budget's spend total is independent: the
    // groceries budget lands at 85 percent (approaching), the daily meal
    // budget at 150 percent (over), so the over budget should sort first.
    const grocery = budget({ id: 'b1', categoryId: 'groceries', limit: 1_000_000, alertThreshold: 0.8 })
    const meal = budget({ id: 'b2', categoryId: 'daily-meal', limit: 1_000_000, alertThreshold: 0.8 })
    const transactions = [
      tx({ categoryId: 'groceries', amount: 850_000 }),
      tx({ categoryId: 'daily-meal', amount: 1_500_000 }),
    ]
    const sorted = activeAlerts([grocery, meal], transactions, 'IDR')
    expect(sorted.map((s) => s.budget.id)).toEqual(['b2', 'b1'])
  })
})
