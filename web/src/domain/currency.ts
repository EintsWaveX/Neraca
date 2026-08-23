/**
 * Currency metadata.
 *
 * Amounts are stored everywhere as integer MINOR UNITS, never as floats, so
 * that adding a thousand transactions cannot drift. The catch is that the
 * number of minor units is not always two: rupiah and yen have none, so
 * `Rp 1.500.000` is stored as the integer 1500000, while `$12.34` is stored as
 * 1234. Anything converting between currencies has to go through `decimals`.
 */

export const CURRENCY_CODES = [
  'IDR', 'USD', 'EUR', 'SGD', 'MYR', 'JPY', 'GBP', 'AUD',
] as const

export type CurrencyCode = (typeof CURRENCY_CODES)[number]

export interface CurrencyMeta {
  code: CurrencyCode
  name: string
  symbol: string
  /** Digits after the decimal separator. Rupiah and yen use zero. */
  decimals: number
  /** Locale whose grouping and separator conventions suit this currency. */
  numberLocale: string
}

export const CURRENCIES: Record<CurrencyCode, CurrencyMeta> = {
  IDR: { code: 'IDR', name: 'Indonesian Rupiah', symbol: 'Rp', decimals: 0, numberLocale: 'id-ID' },
  USD: { code: 'USD', name: 'US Dollar', symbol: '$', decimals: 2, numberLocale: 'en-US' },
  EUR: { code: 'EUR', name: 'Euro', symbol: '€', decimals: 2, numberLocale: 'de-DE' },
  SGD: { code: 'SGD', name: 'Singapore Dollar', symbol: 'S$', decimals: 2, numberLocale: 'en-SG' },
  MYR: { code: 'MYR', name: 'Malaysian Ringgit', symbol: 'RM', decimals: 2, numberLocale: 'ms-MY' },
  JPY: { code: 'JPY', name: 'Japanese Yen', symbol: '¥', decimals: 0, numberLocale: 'ja-JP' },
  GBP: { code: 'GBP', name: 'Pound Sterling', symbol: '£', decimals: 2, numberLocale: 'en-GB' },
  AUD: { code: 'AUD', name: 'Australian Dollar', symbol: 'A$', decimals: 2, numberLocale: 'en-AU' },
}

export function currencyMeta(code: CurrencyCode): CurrencyMeta {
  return CURRENCIES[code]
}

/** 10 raised to the currency's decimal count, as an integer. */
export function minorUnitScale(code: CurrencyCode): number {
  return 10 ** CURRENCIES[code].decimals
}

export function isCurrencyCode(value: string): value is CurrencyCode {
  return (CURRENCY_CODES as readonly string[]).includes(value)
}
