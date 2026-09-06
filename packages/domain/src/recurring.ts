/**
 * Turning a recurring rule into the dated occurrences it implies, and those
 * occurrences into transaction rows.
 */

import { addDays, addMonths, addWeeks, addYears, format, parseISO } from 'date-fns'
import type { IsoDate, RecurringRule, Transaction } from './types'

function advance(rule: RecurringRule, n: number): Date {
  const start = parseISO(rule.startDate)
  const count = n * rule.interval
  switch (rule.frequency) {
    case 'daily': return addDays(start, count)
    case 'weekly': return addWeeks(start, count)
    case 'monthly': return addMonths(start, count)
    case 'yearly': return addYears(start, count)
  }
}

/**
 * Every date a rule fires between `from` and `to`, inclusive on both ends. An
 * inactive rule fires on nothing.
 *
 * Each occurrence is computed as `interval * n` periods added to the rule's
 * own `startDate`, never by repeatedly adding one period to the previous
 * occurrence. That distinction matters for monthly rules: date-fns clamps
 * 31 January plus one month down to the 28th or 29th of February, and
 * chaining from that clamped result would add the next month to the 28th,
 * never landing on a 31st again. Adding straight from the original
 * `startDate` each time means March, which does have a 31st, lands on the
 * 31st as it should, and the rule never drifts.
 */
export function occurrencesBetween(rule: RecurringRule, from: IsoDate, to: IsoDate): IsoDate[] {
  if (!rule.active) return []

  const fromDate = parseISO(from)
  const toDate = parseISO(to)
  const startDate = parseISO(rule.startDate)
  const ruleEnd = rule.endDate === null ? null : parseISO(rule.endDate)
  const effectiveEnd = ruleEnd !== null && ruleEnd < toDate ? ruleEnd : toDate

  if (effectiveEnd < startDate || effectiveEnd < fromDate) return []

  const results: IsoDate[] = []
  for (let n = 0; ; n++) {
    const occurrence = advance(rule, n)
    if (occurrence > effectiveEnd) break
    if (occurrence >= fromDate) results.push(format(occurrence, 'yyyy-MM-dd'))
  }
  return results
}

/**
 * Occurrences that still need a transaction generated for them: strictly
 * after the last run, up to and including `asOf`. A rule that has never run
 * starts from its own `startDate`.
 */
export function dueOccurrences(rule: RecurringRule, asOf: IsoDate): IsoDate[] {
  const from = rule.lastRunDate === null
    ? rule.startDate
    : format(addDays(parseISO(rule.lastRunDate), 1), 'yyyy-MM-dd')
  return occurrencesBetween(rule, from, asOf)
}

/**
 * Build transaction rows from a rule's template, one per given date.
 *
 * Materialising has no exchange rate table to consult, only the rule itself,
 * so `rateToBase` is left at 1 here. That is only the correct final value
 * when the rule's own currency already is the profile's base currency; a
 * caller generating rows for a foreign currency wallet is expected to look up
 * the real rate with rates.findRate and overwrite this field before the row
 * is persisted.
 */
export function materialise(
  rule: RecurringRule,
  dates: readonly IsoDate[],
): Array<Omit<Transaction, 'id' | 'createdAt'>> {
  return dates.map((date) => ({
    profileId: rule.profileId,
    walletId: rule.template.walletId,
    toWalletId: rule.template.toWalletId,
    date,
    direction: rule.template.direction,
    typeId: rule.template.typeId,
    categoryId: rule.template.categoryId,
    amount: rule.template.amount,
    currency: rule.template.currency,
    toAmount: null,
    rateToBase: 1,
    description: rule.template.description,
    recurringId: rule.id,
  }))
}
