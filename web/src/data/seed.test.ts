import { describe, expect, it } from 'vitest'
import { buildDemoBackup, todayIso } from './seed'
import { CATEGORY_BY_ID } from '@/domain/categories'
import { TRANSACTION_TYPE_BY_ID } from '@/domain/txTypes'
import { convert } from '@/domain/money'
import type { Budget, BudgetPeriod, ProfileBackup } from '@/domain/types'

/**
 * The demo backup is what a first time visitor actually sees, so these
 * checks are less about unit-testing helper functions and more about making
 * sure the data itself is internally consistent: no expense row wearing an
 * income category, no transfer that leaks into an income/expense total, and
 * budgets that land in the states the reports screen is meant to show off.
 */

const backup = buildDemoBackup()

describe('determinism', () => {
  it('produces deeply equal output across calls, since the same demo has to render the same way in every browser and every screenshot', () => {
    const second = buildDemoBackup()
    expect(second).toEqual(backup)
  })

  it('produces deeply equal output for an explicit "today" matching the default', () => {
    const explicit = buildDemoBackup('2026-08-23')
    expect(explicit).toEqual(backup)
  })

  it('does not depend on the wall clock: two independent invocations never differ', () => {
    const a = buildDemoBackup()
    const b = buildDemoBackup()
    expect(JSON.stringify(a)).toBe(JSON.stringify(b))
  })
})

describe('category and type ids are real', () => {
  it('every transaction categoryId and typeId exists in the domain tables', () => {
    for (const tx of backup.transactions) {
      expect(CATEGORY_BY_ID.has(tx.categoryId), `unknown category ${tx.categoryId}`).toBe(true)
      expect(TRANSACTION_TYPE_BY_ID.has(tx.typeId), `unknown type ${tx.typeId}`).toBe(true)
    }
  })

  it('every recurring rule template categoryId and typeId exists in the domain tables', () => {
    for (const rule of backup.recurring) {
      expect(CATEGORY_BY_ID.has(rule.template.categoryId)).toBe(true)
      expect(TRANSACTION_TYPE_BY_ID.has(rule.template.typeId)).toBe(true)
    }
  })
})

describe('direction consistency', () => {
  it('direction agrees with the transaction type direction', () => {
    for (const tx of backup.transactions) {
      const type = TRANSACTION_TYPE_BY_ID.get(tx.typeId)!
      expect(type.direction, `tx ${tx.id} type ${tx.typeId}`).toBe(tx.direction)
    }
  })

  it('direction agrees with the category flow for income and expense rows', () => {
    for (const tx of backup.transactions) {
      if (tx.direction === 'transfer') continue
      const category = CATEGORY_BY_ID.get(tx.categoryId)!
      expect(category.flow, `tx ${tx.id} category ${tx.categoryId}`).toBe(tx.direction)
    }
  })

  it('recurring rule templates agree with the type direction too', () => {
    for (const rule of backup.recurring) {
      const type = TRANSACTION_TYPE_BY_ID.get(rule.template.typeId)!
      expect(type.direction).toBe(rule.template.direction)
    }
  })
})

describe('wallet references', () => {
  const walletIds = new Set(backup.wallets.map((w) => w.id))

  it('every transaction walletId refers to a real wallet', () => {
    for (const tx of backup.transactions) {
      expect(walletIds.has(tx.walletId), `tx ${tx.id} walletId ${tx.walletId}`).toBe(true)
    }
  })

  it('every non-null toWalletId refers to a real wallet', () => {
    for (const tx of backup.transactions) {
      if (tx.toWalletId !== null) {
        expect(walletIds.has(tx.toWalletId), `tx ${tx.id} toWalletId ${tx.toWalletId}`).toBe(true)
      }
    }
  })

  it('recurring rule wallet references are real too', () => {
    for (const rule of backup.recurring) {
      expect(walletIds.has(rule.template.walletId)).toBe(true)
      if (rule.template.toWalletId !== null) {
        expect(walletIds.has(rule.template.toWalletId)).toBe(true)
      }
    }
  })

  it('covers every WalletKind and includes a non-IDR wallet', () => {
    const kinds = new Set(backup.wallets.map((w) => w.kind))
    expect(kinds).toEqual(new Set(['cash', 'bank', 'ewallet', 'savings', 'credit']))
    expect(backup.wallets.some((w) => w.currency !== 'IDR')).toBe(true)
  })
})

describe('transfers', () => {
  it('every transfer row has toWalletId set', () => {
    for (const tx of backup.transactions) {
      if (tx.direction === 'transfer') {
        expect(tx.toWalletId, `transfer tx ${tx.id} should have toWalletId`).not.toBeNull()
      }
    }
  })

  it('no non-transfer row has toWalletId set', () => {
    for (const tx of backup.transactions) {
      if (tx.direction !== 'transfer') {
        expect(tx.toWalletId, `non-transfer tx ${tx.id} should not have toWalletId`).toBeNull()
      }
    }
  })

  it('debits the source in its own currency and credits the destination in its own', () => {
    // A transfer is one row touching two wallets. When both are denominated
    // the same way the single `amount` covers both legs and `toAmount` stays
    // null. When they differ, as with a Payoneer withdrawal from dollars into
    // rupiah, the credited figure is unrelated to the debited one and has to
    // be carried explicitly, which is what `toAmount` is for.
    for (const tx of backup.transactions) {
      if (tx.direction !== 'transfer') continue
      const fromWallet = backup.wallets.find((w) => w.id === tx.walletId)!
      const toWallet = backup.wallets.find((w) => w.id === tx.toWalletId)!
      expect(tx.currency).toBe(fromWallet.currency)

      if (fromWallet.currency === toWallet.currency) {
        expect(tx.toAmount).toBeNull()
      } else {
        expect(tx.toAmount, 'a cross currency transfer must carry its credit leg').not.toBeNull()
        expect(tx.toAmount).toBeGreaterThan(0)
      }
    }
  })
})

describe('amounts', () => {
  it('every amount is a positive integer', () => {
    for (const tx of backup.transactions) {
      expect(Number.isInteger(tx.amount), `tx ${tx.id} amount ${tx.amount}`).toBe(true)
      expect(tx.amount).toBeGreaterThan(0)
    }
  })

  it('IDR amounts have no fractional part, since rupiah has zero minor units', () => {
    for (const tx of backup.transactions) {
      if (tx.currency === 'IDR') {
        expect(Number.isInteger(tx.amount)).toBe(true)
      }
    }
  })

  it('every rateToBase is a finite positive number', () => {
    for (const tx of backup.transactions) {
      expect(Number.isFinite(tx.rateToBase)).toBe(true)
      expect(tx.rateToBase).toBeGreaterThan(0)
    }
  })
})

describe('dates', () => {
  const isoDatePattern = /^\d{4}-\d{2}-\d{2}$/

  it('every transaction date is a valid ISO date within the fourteen month span', () => {
    // The span is fourteen months ending at the reference date used by the
    // default call above: 2025-07-01 up to and including 2026-08-23.
    const spanStart = '2025-07-01'
    const spanEnd = '2026-08-23'
    for (const tx of backup.transactions) {
      expect(tx.date).toMatch(isoDatePattern)
      expect(tx.date >= spanStart, `tx ${tx.id} date ${tx.date} before span start`).toBe(true)
      expect(tx.date <= spanEnd, `tx ${tx.id} date ${tx.date} after reference date`).toBe(true)
      const parsed = new Date(`${tx.date}T00:00:00.000Z`)
      expect(Number.isNaN(parsed.getTime()), `tx ${tx.id} date ${tx.date} does not parse`).toBe(false)
    }
  })

  it('generates enough history to fill the reports without being noise', () => {
    // The upper bound moved once the funding pass started inserting the
    // transfers that keep every wallet solvent. Those are real rows a person
    // would have made, so they count toward the total.
    expect(backup.transactions.length).toBeGreaterThanOrEqual(600)
    expect(backup.transactions.length).toBeLessThanOrEqual(1_200)
  })
})

describe('budgets', () => {
  // Mirrors the state a reports/alerts screen would compute from a budget
  // and its actual spend: under the alert threshold, at or past it but still
  // under the limit ("approaching"), or at or past the limit itself ("over").
  function baseMinor(tx: ProfileBackup['transactions'][number]): number {
    return convert({ minor: tx.amount, currency: tx.currency }, 'IDR', tx.rateToBase).minor
  }

  function spentFor(period: BudgetPeriod, periodKey: string, categoryId: string | null): number {
    return backup.transactions
      .filter((t) => t.direction === 'expense')
      .filter((t) => (period === 'monthly' ? t.date.slice(0, 7) : t.date.slice(0, 4)) === periodKey)
      .filter((t) => categoryId === null || t.categoryId === categoryId)
      .reduce((sum, t) => sum + baseMinor(t), 0)
  }

  function stateOf(budget: Budget): 'under' | 'approaching' | 'over' {
    const spent = spentFor(budget.period, budget.periodKey, budget.categoryId)
    const ratio = spent / budget.limit
    if (ratio >= 1) return 'over'
    if (ratio >= budget.alertThreshold) return 'approaching'
    return 'under'
  }

  it('has between six and eight budgets', () => {
    expect(backup.budgets.length).toBeGreaterThanOrEqual(6)
    expect(backup.budgets.length).toBeLessThanOrEqual(8)
  })

  it('mixes monthly and yearly periods', () => {
    const periods = new Set(backup.budgets.map((b) => b.period))
    expect(periods.has('monthly')).toBe(true)
    expect(periods.has('yearly')).toBe(true)
  })

  it('covers both the current and the previous month', () => {
    const monthlyKeys = new Set(backup.budgets.filter((b) => b.period === 'monthly').map((b) => b.periodKey))
    expect(monthlyKeys.has('2026-08')).toBe(true)
    expect(monthlyKeys.has('2026-07')).toBe(true)
  })

  it('reaches every alert state: at least one under, one approaching and one over', () => {
    const states = backup.budgets.map(stateOf)
    expect(states).toContain('under')
    expect(states).toContain('approaching')
    expect(states).toContain('over')
  })

  it('every budget categoryId, when set, is a real category', () => {
    for (const b of backup.budgets) {
      if (b.categoryId !== null) {
        expect(CATEGORY_BY_ID.has(b.categoryId)).toBe(true)
      }
    }
  })
})

describe('profile', () => {
  it('is marked as a demo profile with no PIN, English locale and IDR base currency', () => {
    expect(backup.profile.isDemo).toBe(true)
    expect(backup.profile.pinHash).toBeNull()
    expect(backup.profile.pinSalt).toBeNull()
    expect(backup.profile.locale).toBe('en')
    expect(backup.profile.baseCurrency).toBe('IDR')
  })

  it('uses a placeholder identity, not a real person', () => {
    expect(backup.profile.email).toBe('demo@example.com')
    expect(backup.profile.displayName.toLowerCase()).toContain('demo')
  })
})

describe('exchange rates', () => {
  it('has one USD rate per month across the span, drifting rather than constant', () => {
    expect(backup.rates.length).toBeGreaterThanOrEqual(14)
    const values = backup.rates.map((r) => r.rate)
    expect(new Set(values).size).toBeGreaterThan(1)
    for (const r of backup.rates) {
      expect(r.rate).toBeGreaterThanOrEqual(15_000)
      expect(r.rate).toBeLessThanOrEqual(17_000)
    }
  })
})

describe('recurring rules', () => {
  it('has three or four active rules', () => {
    expect(backup.recurring.length).toBeGreaterThanOrEqual(3)
    expect(backup.recurring.length).toBeLessThanOrEqual(4)
    for (const rule of backup.recurring) {
      expect(rule.active).toBe(true)
    }
  })

  it('has at least one rule already run for the current month and at least one still due', () => {
    for (const rule of backup.recurring) {
      expect(rule.lastRunDate).not.toBeNull()
    }
    const dueCount = backup.recurring.filter((r) => (r.lastRunDate ?? '').slice(0, 7) < '2026-08').length
    const notDueCount = backup.recurring.filter((r) => (r.lastRunDate ?? '').slice(0, 7) === '2026-08').length
    expect(dueCount).toBeGreaterThan(0)
    expect(notDueCount).toBeGreaterThan(0)
  })
})

describe('the demo describes a life that could actually be lived', () => {
  // Regression guard. The first version generated income into the bank and
  // Payoneer accounts while day to day spending left from cash and the
  // e-wallet, with nothing moving between them. Cash finished at minus nine
  // million rupiah, which is not a rendering bug, it is the demo showing
  // something impossible on the first screen a visitor sees.
  it('never lets a wallet go negative at any point in the history', () => {
    const backup = buildDemoBackup()
    const balance = new Map(backup.wallets.map((w) => [w.id, w.openingBalance]))
    const lowest = new Map(backup.wallets.map((w) => [w.id, w.openingBalance]))

    const ordered = [...backup.transactions].sort(
      (a, b) => a.date.localeCompare(b.date) || a.createdAt.localeCompare(b.createdAt),
    )

    const bump = (id: string, delta: number): void => {
      const next = (balance.get(id) ?? 0) + delta
      balance.set(id, next)
      if (next < (lowest.get(id) ?? 0)) lowest.set(id, next)
    }

    for (const tx of ordered) {
      if (tx.direction === 'transfer') {
        bump(tx.walletId, -tx.amount)
        if (tx.toWalletId) bump(tx.toWalletId, tx.toAmount ?? tx.amount)
      } else {
        bump(tx.walletId, tx.direction === 'income' ? tx.amount : -tx.amount)
      }
    }

    for (const wallet of backup.wallets) {
      expect(lowest.get(wallet.id), `${wallet.name} went negative`).toBeGreaterThanOrEqual(0)
    }
  })

  it('moves dollars home through cross currency transfers', () => {
    const backup = buildDemoBackup()
    const crossCurrency = backup.transactions.filter((tx) => tx.toAmount !== null)
    expect(crossCurrency.length).toBeGreaterThan(0)

    for (const tx of crossCurrency) {
      expect(tx.direction).toBe('transfer')
      expect(tx.toWalletId).not.toBeNull()
      const from = backup.wallets.find((w) => w.id === tx.walletId)
      const to = backup.wallets.find((w) => w.id === tx.toWalletId)
      // A destination amount only earns its place when the currencies differ.
      expect(from?.currency).not.toBe(to?.currency)
      expect(tx.toAmount).toBeGreaterThan(0)
    }
  })
})

/**
 * The dashboard reads income, expense and net balance for the current
 * calendar month. The demo is generated from a fixed reference date, so
 * without an anchor the app quietly rotted: every visitor after August 2026
 * met three cards reading zero above a table full of transactions. These pin
 * the fix from both ends, because the whole point is that one of them keeps
 * holding as the wall clock moves.
 */
describe('anchoring to today', () => {
  it('reports today in the yyyy-MM-dd shape an IsoDate requires', () => {
    expect(todayIso()).toMatch(/^\d{4}-\d{2}-\d{2}$/)
  })

  it('puts transactions in the current calendar month, so the dashboard cards are never all zero', () => {
    const backup = buildDemoBackup(todayIso())
    const thisMonth = todayIso().slice(0, 7)
    const inMonth = backup.transactions.filter((tx) => tx.date.startsWith(thisMonth))
    expect(inMonth.length).toBeGreaterThan(0)
  })

  it('carries both an income and an expense into the current month, since the cards show one of each', () => {
    const backup = buildDemoBackup(todayIso())
    const thisMonth = todayIso().slice(0, 7)
    const inMonth = backup.transactions.filter((tx) => tx.date.startsWith(thisMonth))
    expect(inMonth.some((tx) => tx.direction === 'income')).toBe(true)
    expect(inMonth.some((tx) => tx.direction === 'expense')).toBe(true)
  })

  it('still produces identical output for a repeated explicit anchor, so determinism survives the change', () => {
    const anchor = todayIso()
    expect(buildDemoBackup(anchor)).toEqual(buildDemoBackup(anchor))
  })
})

describe('no future dating', () => {
  it('never dates a transaction after the anchor, whatever day of the month it falls on', () => {
    // The 3rd is deliberate: it is early enough that every generator using a
    // fixed mid-month day would overshoot without the clamp in mkTx.
    const backup = buildDemoBackup('2026-09-03')
    const beyond = backup.transactions.filter((tx) => tx.date > '2026-09-03')
    expect(beyond).toEqual([])
  })

  it('holds on the first of a month, the worst case for a fixed-day generator', () => {
    const backup = buildDemoBackup('2026-09-01')
    expect(backup.transactions.filter((tx) => tx.date > '2026-09-01')).toEqual([])
  })

  it('holds for today, which is what a visitor actually loads', () => {
    const anchor = todayIso()
    const backup = buildDemoBackup(anchor)
    expect(backup.transactions.filter((tx) => tx.date > anchor)).toEqual([])
  })

  it('keeps createdAt in step with the clamped date rather than the original', () => {
    const backup = buildDemoBackup('2026-09-03')
    for (const tx of backup.transactions) {
      expect(tx.createdAt.slice(0, 10)).toBe(tx.date)
    }
  })
})
