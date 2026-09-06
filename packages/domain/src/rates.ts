/**
 * Exchange rate lookup and currency conversion for transactions.
 *
 * Pure and free of storage access, like money.ts, so the rules here can be
 * unit tested without a database.
 */

import type { CurrencyCode } from './currency'
import type { ExchangeRate, IsoDate, Transaction } from './types'
import { convert, money, negate, zero, type Money } from './money'

/**
 * The rate for `currency` in effect on `onDate`: the newest rate row dated on
 * or before that day, matching how a person actually enters rates (whenever
 * they think to, not daily). Returns 1 when `currency` already is the base
 * currency, since no rate row is needed to convert a currency into itself.
 */
export function findRate(
  rates: readonly ExchangeRate[],
  currency: CurrencyCode,
  onDate: IsoDate,
  baseCurrency: CurrencyCode,
): number | null {
  if (currency === baseCurrency) return 1

  let best: ExchangeRate | null = null
  for (const candidate of rates) {
    if (candidate.currency !== currency) continue
    // IsoDate strings are fixed width (yyyy-MM-dd), so ordinary string
    // comparison is chronological comparison. No parsing needed.
    if (candidate.date > onDate) continue
    if (best === null || candidate.date > best.date) {
      best = candidate
    } else if (candidate.date === best.date && candidate.createdAt > best.createdAt) {
      // Two rates entered for the same day: the one entered later is the
      // correction, so it wins.
      best = candidate
    }
  }
  return best === null ? null : best.rate
}

/**
 * Convert a transaction into the profile's base currency using the rate that
 * was captured on the row itself, never a fresh lookup against the current
 * rate table.
 *
 * A rate is a fact about a moment: the rate on the day a purchase happened is
 * what that purchase actually cost in base currency terms. Looking the rate
 * up again today would price last year's coffee at today's exchange rate, and
 * every historical report built on it would quietly change each time the
 * rate table changes.
 */
export function toBase(tx: Transaction, baseCurrency: CurrencyCode): Money {
  return convert(money(tx.amount, tx.currency), baseCurrency, tx.rateToBase)
}

/**
 * The base currency value of a transaction, signed so that a plain sum across
 * many rows is already a correct running total: expenses subtract, income
 * adds.
 *
 * A transfer moves money between the profile's own wallets rather than into
 * or out of the profile's finances, so it is reported as zero here. Summing
 * signedBase over a mixed list of transactions therefore already excludes
 * transfers from income and expense totals, with no separate filtering step
 * required at the call site.
 */
export function signedBase(tx: Transaction, baseCurrency: CurrencyCode): Money {
  if (tx.direction === 'transfer') return zero(baseCurrency)
  const base = toBase(tx, baseCurrency)
  return tx.direction === 'expense' ? negate(base) : base
}
