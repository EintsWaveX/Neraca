/**
 * Money arithmetic on integer minor units.
 *
 * Every function here is pure and free of React, storage and locale state, so
 * the rules can be unit tested on their own. Rounding happens once, at the
 * boundary where a value crosses into another currency or is shown to a
 * person, and never in the middle of a running total.
 */

import { CURRENCIES, minorUnitScale, type CurrencyCode } from './currency'

/** An amount of money, tagged with the currency it is denominated in. */
export interface Money {
  /** Integer minor units. See currency.ts for why this is not always cents. */
  readonly minor: number
  readonly currency: CurrencyCode
}

export function money(minor: number, currency: CurrencyCode): Money {
  return { minor: Math.round(minor), currency }
}

export function zero(currency: CurrencyCode): Money {
  return { minor: 0, currency }
}

export class CurrencyMismatchError extends Error {
  constructor(a: CurrencyCode, b: CurrencyCode) {
    super(`Cannot combine ${a} and ${b} directly. Convert to a common currency first.`)
    this.name = 'CurrencyMismatchError'
  }
}

export function add(a: Money, b: Money): Money {
  if (a.currency !== b.currency) throw new CurrencyMismatchError(a.currency, b.currency)
  return { minor: a.minor + b.minor, currency: a.currency }
}

export function subtract(a: Money, b: Money): Money {
  if (a.currency !== b.currency) throw new CurrencyMismatchError(a.currency, b.currency)
  return { minor: a.minor - b.minor, currency: a.currency }
}

export function negate(a: Money): Money {
  return { minor: -a.minor, currency: a.currency }
}

export function sum(items: readonly Money[], currency: CurrencyCode): Money {
  let total = 0
  for (const item of items) {
    if (item.currency !== currency) throw new CurrencyMismatchError(currency, item.currency)
    total += item.minor
  }
  return { minor: total, currency }
}

/** Scale by a plain ratio, for example 0.8 to find a budget alert threshold. */
export function scale(a: Money, factor: number): Money {
  return { minor: Math.round(a.minor * factor), currency: a.currency }
}

export function compare(a: Money, b: Money): number {
  if (a.currency !== b.currency) throw new CurrencyMismatchError(a.currency, b.currency)
  return a.minor - b.minor
}

export function isZero(a: Money): boolean {
  return a.minor === 0
}

export function abs(a: Money): Money {
  return { minor: Math.abs(a.minor), currency: a.currency }
}

/**
 * Convert between currencies.
 *
 * `rate` is how many units of `to` one whole unit of `from` buys, in MAJOR
 * units, because that is how an exchange rate is quoted and how the user will
 * type it. The minor unit scales of the two currencies are usually different,
 * so both have to be taken out and put back explicitly. Converting 1500000
 * minor IDR (Rp 1.500.000, zero decimals) at 0.000061 gives 91.5 major USD,
 * which is 9150 minor USD.
 */
export function convert(amount: Money, to: CurrencyCode, rate: number): Money {
  if (amount.currency === to) return amount
  const major = amount.minor / minorUnitScale(amount.currency)
  return { minor: Math.round(major * rate * minorUnitScale(to)), currency: to }
}

/** The value as a plain decimal number. For display and charting only. */
export function toMajor(amount: Money): number {
  return amount.minor / minorUnitScale(amount.currency)
}

export function fromMajor(major: number, currency: CurrencyCode): Money {
  return { minor: Math.round(major * minorUnitScale(currency)), currency }
}

/**
 * Format for display. Falls back to a hand built string if the runtime lacks
 * the currency in its Intl data, which keeps older mobile browsers readable.
 */
export function formatMoney(
  amount: Money,
  opts: { locale?: string; showSymbol?: boolean; signDisplay?: 'auto' | 'never' | 'always' } = {},
): string {
  const meta = CURRENCIES[amount.currency]
  const locale = opts.locale ?? meta.numberLocale
  const showSymbol = opts.showSymbol ?? true
  try {
    return new Intl.NumberFormat(locale, {
      style: showSymbol ? 'currency' : 'decimal',
      currency: amount.currency,
      minimumFractionDigits: meta.decimals,
      maximumFractionDigits: meta.decimals,
      signDisplay: opts.signDisplay ?? 'auto',
    }).format(toMajor(amount))
  } catch {
    const body = toMajor(amount).toFixed(meta.decimals)
    return showSymbol ? `${meta.symbol} ${body}` : body
  }
}

/** A compact form for chart axes and dense tables: Rp 1,5 jt and so on. */
export function formatMoneyCompact(amount: Money, locale?: string): string {
  const meta = CURRENCIES[amount.currency]
  try {
    return new Intl.NumberFormat(locale ?? meta.numberLocale, {
      style: 'currency',
      currency: amount.currency,
      notation: 'compact',
      maximumFractionDigits: 1,
    }).format(toMajor(amount))
  } catch {
    return formatMoney(amount, { locale })
  }
}

/**
 * Read a number the user typed.
 *
 * People type money inconsistently: `1.500.000`, `1,500,000`, `1500000` and
 * `1500000,50` all turn up in the same field. The rule applied here is that
 * the last separator followed by one or two digits is a decimal point, and
 * every other separator is grouping. Currencies with no decimals ignore any
 * fractional part rather than rounding into it.
 */
export function parseMoneyInput(raw: string, currency: CurrencyCode): Money | null {
  const cleaned = raw.replace(/[^\d.,-]/g, '').trim()
  if (cleaned === '' || cleaned === '-') return null

  const negative = cleaned.startsWith('-')
  const body = negative ? cleaned.slice(1) : cleaned
  const decimals = CURRENCIES[currency].decimals

  const lastSep = Math.max(body.lastIndexOf('.'), body.lastIndexOf(','))
  let whole = body
  let fraction = ''

  // Work out which separator was a decimal point BEFORE consulting the
  // currency. A separator trailed by one or two digits is a decimal point in
  // both the Indonesian and the English convention, and anything else is
  // grouping. Only once the fraction is split off does the currency matter:
  // rupiah and yen have no minor units, so their fraction is discarded rather
  // than being folded back into the whole part. Getting this order wrong reads
  // "1.500.000,75" as a hundred and fifty million rupiah.
  if (lastSep !== -1) {
    const tail = body.slice(lastSep + 1)
    if (/^\d{1,2}$/.test(tail)) {
      whole = body.slice(0, lastSep)
      fraction = decimals > 0 ? tail : ''
    }
  }

  whole = whole.replace(/[.,]/g, '')
  if (whole === '') whole = '0'
  if (!/^\d+$/.test(whole)) return null

  const padded = (fraction + '0'.repeat(decimals)).slice(0, decimals)
  const minor = Number(whole) * minorUnitScale(currency) + (decimals > 0 ? Number(padded || 0) : 0)
  if (!Number.isFinite(minor)) return null
  return { minor: negative ? -minor : minor, currency }
}
