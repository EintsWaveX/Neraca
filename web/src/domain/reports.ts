/**
 * Chart ready aggregates built from a transaction list.
 *
 * Every time series here fills gaps explicitly: a period with no activity is
 * present in the output with a zero value, rather than simply missing. A
 * chart drawn from a gappy series draws a straight line across the missing
 * periods, which reads as unchanging activity instead of none.
 */

import {
  eachDayOfInterval, eachMonthOfInterval, eachWeekOfInterval, format, parseISO,
  startOfDay, startOfMonth, startOfWeek,
} from 'date-fns'
import type { CurrencyCode } from './currency'
import type { Budget, IsoDate, Transaction } from './types'
import { add, money, scale, sum, zero, type Money } from './money'
import { toBase } from './rates'
import { budgetPeriodRange, transactionsInBudget } from './budget'

export type Granularity = 'day' | 'week' | 'month'

function bucketStart(date: Date, granularity: Granularity): Date {
  switch (granularity) {
    case 'day': return startOfDay(date)
    case 'week': return startOfWeek(date)
    case 'month': return startOfMonth(date)
  }
}

function bucketKey(date: Date, granularity: Granularity): IsoDate {
  return format(bucketStart(date, granularity), 'yyyy-MM-dd')
}

function enumerateBuckets(start: Date, end: Date, granularity: Granularity): IsoDate[] {
  const interval = { start: bucketStart(start, granularity), end }
  const dates = granularity === 'day'
    ? eachDayOfInterval(interval)
    : granularity === 'week'
      ? eachWeekOfInterval(interval)
      : eachMonthOfInterval(interval)
  return dates.map((d) => format(d, 'yyyy-MM-dd'))
}

function totalAt(buckets: Map<IsoDate, Money[]>, key: IsoDate, currency: CurrencyCode): Money {
  const items = buckets.get(key)
  return items === undefined ? zero(currency) : sum(items, currency)
}

/** The earliest and latest date among a set of transactions. Assumes at least one row. */
function dateSpan(transactions: readonly Transaction[]): { start: Date; end: Date } {
  const dates = transactions.map((tx) => parseISO(tx.date))
  let start = dates[0]!
  let end = dates[0]!
  for (const d of dates) {
    if (d < start) start = d
    if (d > end) end = d
  }
  return { start, end }
}

export interface SeriesPoint {
  period: IsoDate
  amount: Money
}

/** Total spending per period, with every period between the first and last expense present. */
export function spendingOverTime(
  transactions: readonly Transaction[],
  baseCurrency: CurrencyCode,
  granularity: Granularity,
): SeriesPoint[] {
  const expenses = transactions.filter((tx) => tx.direction === 'expense')
  if (expenses.length === 0) return []

  const { start, end } = dateSpan(expenses)
  const buckets = enumerateBuckets(start, end, granularity)

  const byBucket = new Map<IsoDate, Money[]>()
  for (const tx of expenses) {
    const key = bucketKey(parseISO(tx.date), granularity)
    const list = byBucket.get(key) ?? []
    list.push(toBase(tx, baseCurrency))
    byBucket.set(key, list)
  }

  return buckets.map((period) => ({ period, amount: totalAt(byBucket, period, baseCurrency) }))
}

export interface CategoryTotal {
  categoryId: string
  amount: Money
  /** Share of total expense this category accounts for, 0 to 1. */
  fraction: number
}

/** Expense totals by category, sorted largest first. */
export function categoryBreakdown(
  transactions: readonly Transaction[],
  baseCurrency: CurrencyCode,
): CategoryTotal[] {
  const expenses = transactions.filter((tx) => tx.direction === 'expense')

  const byCategory = new Map<string, Money[]>()
  for (const tx of expenses) {
    const list = byCategory.get(tx.categoryId) ?? []
    list.push(toBase(tx, baseCurrency))
    byCategory.set(tx.categoryId, list)
  }

  const grand = sum(expenses.map((tx) => toBase(tx, baseCurrency)), baseCurrency)

  const rows = Array.from(byCategory.entries()).map(([categoryId, items]) => {
    const amount = sum(items, baseCurrency)
    const fraction = grand.minor === 0 ? 0 : amount.minor / grand.minor
    return { categoryId, amount, fraction }
  })

  return rows.sort((a, b) => b.amount.minor - a.amount.minor)
}

export interface IncomeExpensePoint {
  period: IsoDate
  income: Money
  expense: Money
}

/** Income and expense totals per period, transfers excluded from both. */
export function incomeVsExpense(
  transactions: readonly Transaction[],
  baseCurrency: CurrencyCode,
  granularity: Granularity,
): IncomeExpensePoint[] {
  const flows = transactions.filter((tx) => tx.direction !== 'transfer')
  if (flows.length === 0) return []

  const { start, end } = dateSpan(flows)
  const buckets = enumerateBuckets(start, end, granularity)

  const income = new Map<IsoDate, Money[]>()
  const expense = new Map<IsoDate, Money[]>()
  for (const tx of flows) {
    const key = bucketKey(parseISO(tx.date), granularity)
    const target = tx.direction === 'income' ? income : expense
    const list = target.get(key) ?? []
    list.push(toBase(tx, baseCurrency))
    target.set(key, list)
  }

  return buckets.map((period) => ({
    period,
    income: totalAt(income, period, baseCurrency),
    expense: totalAt(expense, period, baseCurrency),
  }))
}

export interface BurndownPoint {
  date: IsoDate
  /** Total spent from the start of the budget period up to and including this day. */
  cumulative: Money
  /** Where spending would be on this day if the limit were spread evenly across the period. */
  ideal: Money
}

/** Cumulative spend against a budget, day by day across its period, next to an even pace line. */
export function budgetBurndown(
  budget: Budget,
  transactions: readonly Transaction[],
  baseCurrency: CurrencyCode,
): BurndownPoint[] {
  const { start, end } = budgetPeriodRange(budget)
  const days = eachDayOfInterval({ start: parseISO(start), end: parseISO(end) })
    .map((d) => format(d, 'yyyy-MM-dd'))

  const matches = transactionsInBudget(budget, transactions)
  const perDay = new Map<IsoDate, Money[]>()
  for (const tx of matches) {
    const list = perDay.get(tx.date) ?? []
    list.push(toBase(tx, baseCurrency))
    perDay.set(tx.date, list)
  }

  const limit = money(budget.limit, baseCurrency)
  const totalDays = days.length
  let cumulative = zero(baseCurrency)

  return days.map((date, i) => {
    cumulative = add(cumulative, totalAt(perDay, date, baseCurrency))
    const ideal = totalDays === 0 ? zero(baseCurrency) : scale(limit, (i + 1) / totalDays)
    return { date, cumulative, ideal }
  })
}
