import { describe, expect, it } from 'vitest'
import type { Budget, Transaction } from './types'
import {
  budgetBurndown, categoryBreakdown, incomeVsExpense, spendingOverTime,
} from './reports'

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

function budget(overrides: Partial<Budget> = {}): Budget {
  return {
    id: 'b1',
    profileId: 'p1',
    period: 'monthly',
    periodKey: '2026-08',
    categoryId: null,
    limit: 3_100_000, // 100,000 a day across 31 days
    target: null,
    description: '',
    alertThreshold: 0.8,
    alertsEnabled: true,
    createdAt: '2026-08-01T00:00:00.000Z',
    ...overrides,
  }
}

describe('spendingOverTime', () => {
  it('fills a gap between two active days with a zero entry', () => {
    const rows = [
      tx({ date: '2026-08-01', amount: 100_000 }),
      tx({ date: '2026-08-03', amount: 200_000 }),
    ]
    const series = spendingOverTime(rows, 'IDR', 'day')
    expect(series.map((p) => p.period)).toEqual(['2026-08-01', '2026-08-02', '2026-08-03'])
    expect(series.map((p) => p.amount.minor)).toEqual([100_000, 0, 200_000])
  })

  it('returns an empty series when there is no spending at all', () => {
    expect(spendingOverTime([], 'IDR', 'day')).toEqual([])
  })

  it('excludes income and transfers from the totals', () => {
    const rows = [
      tx({ direction: 'expense', date: '2026-08-01', amount: 100_000 }),
      tx({ direction: 'income', date: '2026-08-01', amount: 900_000 }),
      tx({ direction: 'transfer', date: '2026-08-01', amount: 900_000, toWalletId: 'w2' }),
    ]
    const series = spendingOverTime(rows, 'IDR', 'day')
    expect(series).toHaveLength(1)
    expect(series[0]?.amount.minor).toBe(100_000)
  })

  it('groups by month, filling a quiet month with zero', () => {
    const rows = [
      tx({ date: '2026-06-15', amount: 100_000 }),
      tx({ date: '2026-08-15', amount: 200_000 }),
    ]
    const series = spendingOverTime(rows, 'IDR', 'month')
    expect(series.map((p) => p.period)).toEqual(['2026-06-01', '2026-07-01', '2026-08-01'])
    expect(series.map((p) => p.amount.minor)).toEqual([100_000, 0, 200_000])
  })
})

describe('categoryBreakdown', () => {
  it('sorts categories largest first and reports the fraction of the whole', () => {
    const rows = [
      tx({ categoryId: 'groceries', amount: 300_000 }),
      tx({ categoryId: 'daily-meal', amount: 100_000 }),
    ]
    const breakdown = categoryBreakdown(rows, 'IDR')
    expect(breakdown.map((b) => b.categoryId)).toEqual(['groceries', 'daily-meal'])
    expect(breakdown[0]?.fraction).toBeCloseTo(0.75)
    expect(breakdown[1]?.fraction).toBeCloseTo(0.25)
  })

  it('excludes income and transfers', () => {
    const rows = [
      tx({ direction: 'expense', categoryId: 'groceries', amount: 100_000 }),
      tx({ direction: 'income', categoryId: 'salary', amount: 900_000 }),
    ]
    const breakdown = categoryBreakdown(rows, 'IDR')
    expect(breakdown).toHaveLength(1)
    expect(breakdown[0]?.categoryId).toBe('groceries')
  })

  it('returns an empty list with no expenses, rather than dividing by zero', () => {
    expect(categoryBreakdown([], 'IDR')).toEqual([])
  })
})

describe('incomeVsExpense', () => {
  it('reports both income and expense per period, filling gaps', () => {
    const rows = [
      tx({ direction: 'income', date: '2026-08-01', amount: 500_000 }),
      tx({ direction: 'expense', date: '2026-08-03', amount: 200_000 }),
    ]
    const series = incomeVsExpense(rows, 'IDR', 'day')
    expect(series).toEqual([
      { period: '2026-08-01', income: { minor: 500_000, currency: 'IDR' }, expense: { minor: 0, currency: 'IDR' } },
      { period: '2026-08-02', income: { minor: 0, currency: 'IDR' }, expense: { minor: 0, currency: 'IDR' } },
      { period: '2026-08-03', income: { minor: 0, currency: 'IDR' }, expense: { minor: 200_000, currency: 'IDR' } },
    ])
  })

  it('excludes transfers from both sides', () => {
    const rows = [tx({ direction: 'transfer', date: '2026-08-01', amount: 500_000, toWalletId: 'w2' })]
    expect(incomeVsExpense(rows, 'IDR', 'day')).toEqual([])
  })
})

describe('budgetBurndown', () => {
  it('accumulates spend day by day and computes an even pace ideal line', () => {
    const b = budget({ periodKey: '2026-08', limit: 3_100_000 }) // 31 days, 100,000/day ideal
    const rows = [
      tx({ date: '2026-08-01', amount: 200_000 }),
      tx({ date: '2026-08-03', amount: 100_000 }),
    ]
    const points = budgetBurndown(b, rows, 'IDR')
    expect(points).toHaveLength(31)

    const day1 = points[0]!
    expect(day1.date).toBe('2026-08-01')
    expect(day1.cumulative.minor).toBe(200_000)
    expect(day1.ideal.minor).toBe(100_000)

    const day2 = points[1]!
    expect(day2.date).toBe('2026-08-02')
    expect(day2.cumulative.minor).toBe(200_000) // no spend on day 2, cumulative unchanged
    expect(day2.ideal.minor).toBe(200_000)

    const day3 = points[2]!
    expect(day3.cumulative.minor).toBe(300_000)
    expect(day3.ideal.minor).toBe(300_000)
  })

  it('only accumulates spend matching the budget category when one is set', () => {
    const b = budget({ categoryId: 'groceries', periodKey: '2026-08', limit: 3_100_000 })
    const rows = [
      tx({ date: '2026-08-01', categoryId: 'groceries', amount: 100_000 }),
      tx({ date: '2026-08-01', categoryId: 'daily-meal', amount: 900_000 }),
    ]
    const points = budgetBurndown(b, rows, 'IDR')
    expect(points[0]?.cumulative.minor).toBe(100_000)
  })
})
