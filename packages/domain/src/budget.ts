/**
 * Budget periods and how close a budget is to its limit.
 */

import { endOfMonth, endOfYear, format, parseISO } from 'date-fns'
import type { CurrencyCode } from './currency'
import type { Budget, IsoDate, Transaction } from './types'
import { money, subtract, sum, type Money } from './money'
import { toBase } from './rates'

/** The calendar span a budget's `periodKey` covers, inclusive on both ends. */
export function budgetPeriodRange(budget: Budget): { start: IsoDate; end: IsoDate } {
  if (budget.period === 'monthly') {
    const start = parseISO(`${budget.periodKey}-01`)
    return { start: format(start, 'yyyy-MM-dd'), end: format(endOfMonth(start), 'yyyy-MM-dd') }
  }

  const start = parseISO(`${budget.periodKey}-01-01`)
  return { start: format(start, 'yyyy-MM-dd'), end: format(endOfYear(start), 'yyyy-MM-dd') }
}

/**
 * Expense transactions that count against this budget: inside its period,
 * and matching its category, or every expense category when `categoryId` is
 * null.
 */
export function transactionsInBudget(
  budget: Budget,
  transactions: readonly Transaction[],
): Transaction[] {
  const { start, end } = budgetPeriodRange(budget)
  return transactions.filter((tx) =>
    tx.direction === 'expense'
    && tx.date >= start
    && tx.date <= end
    && (budget.categoryId === null || tx.categoryId === budget.categoryId),
  )
}

export interface BudgetStatus {
  budget: Budget
  spent: Money
  limit: Money
  remaining: Money
  /** spent / limit. Never Infinity or NaN, even when the limit is zero. */
  fraction: number
  state: 'under' | 'approaching' | 'over'
}

export function evaluateBudget(
  budget: Budget,
  transactions: readonly Transaction[],
  baseCurrency: CurrencyCode,
): BudgetStatus {
  const matches = transactionsInBudget(budget, transactions)
  const spent = sum(matches.map((tx) => toBase(tx, baseCurrency)), baseCurrency)
  const limit = money(budget.limit, baseCurrency)
  const remaining = subtract(limit, spent)

  // A zero limit divides by zero on the natural fraction. Read literally, a
  // limit of zero means "no allowance at all", so any spending at all is
  // already fully over; that is fraction 1, not the Infinity or NaN a raw
  // division would produce.
  const fraction = limit.minor <= 0 ? (spent.minor > 0 ? 1 : 0) : spent.minor / limit.minor

  const state: BudgetStatus['state'] =
    fraction >= 1 ? 'over' : fraction >= budget.alertThreshold ? 'approaching' : 'under'

  return { budget, spent, limit, remaining, fraction, state }
}

/** Budgets with alerts on that are at or past their threshold, worst first. */
export function activeAlerts(
  budgets: readonly Budget[],
  transactions: readonly Transaction[],
  baseCurrency: CurrencyCode,
): BudgetStatus[] {
  return budgets
    .filter((budget) => budget.alertsEnabled)
    .map((budget) => evaluateBudget(budget, transactions, baseCurrency))
    .filter((status) => status.state === 'approaching' || status.state === 'over')
    .sort((a, b) => b.fraction - a.fraction)
}
