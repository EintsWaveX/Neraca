import { describe, expect, it } from 'vitest'
import {
  add, convert, formatMoney, fromMajor, money, parseMoneyInput, scale, subtract, sum, toMajor,
  CurrencyMismatchError,
} from './money'

describe('minor unit handling', () => {
  it('treats rupiah as having no minor units', () => {
    expect(fromMajor(1_500_000, 'IDR').minor).toBe(1_500_000)
    expect(toMajor(money(1_500_000, 'IDR'))).toBe(1_500_000)
  })

  it('treats dollars as having two', () => {
    expect(fromMajor(12.34, 'USD').minor).toBe(1234)
    expect(toMajor(money(1234, 'USD'))).toBe(12.34)
  })

  it('refuses to add two different currencies', () => {
    expect(() => add(money(100, 'IDR'), money(100, 'USD'))).toThrow(CurrencyMismatchError)
  })

  it('sums without floating point drift', () => {
    const cents = Array.from({ length: 1000 }, () => money(10, 'USD'))
    expect(sum(cents, 'USD').minor).toBe(10_000)
  })

  it('adds and subtracts exactly', () => {
    expect(add(money(1234, 'USD'), money(866, 'USD')).minor).toBe(2100)
    expect(subtract(money(1234, 'USD'), money(234, 'USD')).minor).toBe(1000)
  })

  it('scales and rounds once', () => {
    expect(scale(money(1000, 'USD'), 0.8).minor).toBe(800)
    expect(scale(money(1001, 'USD'), 0.5).minor).toBe(501)
  })
})

describe('conversion across differing minor unit scales', () => {
  it('converts rupiah to dollars', () => {
    // Rp 1.500.000 at 0.000061 USD per rupiah is 91.50 dollars.
    expect(convert(money(1_500_000, 'IDR'), 'USD', 0.000061).minor).toBe(9150)
  })

  it('converts dollars back to rupiah', () => {
    expect(convert(money(9150, 'USD'), 'IDR', 16_393).minor).toBe(1_499_960)
  })

  it('is a no-op when the currency already matches', () => {
    const m = money(500, 'USD')
    expect(convert(m, 'USD', 999)).toBe(m)
  })

  it('handles two zero-decimal currencies', () => {
    expect(convert(money(10_000, 'JPY'), 'IDR', 109).minor).toBe(1_090_000)
  })
})

describe('parsing what a person actually types', () => {
  const cases: Array<[string, 'IDR' | 'USD', number | null]> = [
    ['1.500.000', 'IDR', 1_500_000],
    ['1,500,000', 'IDR', 1_500_000],
    ['1500000', 'IDR', 1_500_000],
    ['Rp 1.500.000', 'IDR', 1_500_000],
    ['12.34', 'USD', 1234],
    ['12,34', 'USD', 1234],
    ['1,234.56', 'USD', 123_456],
    ['1.234,56', 'USD', 123_456],
    ['1234', 'USD', 123_400],
    ['-500', 'USD', -50_000],
    ['', 'USD', null],
    ['abc', 'USD', null],
  ]
  it.each(cases)('parses %s as %s', (input, currency, expected) => {
    const parsed = parseMoneyInput(input, currency)
    expect(parsed === null ? null : parsed.minor).toBe(expected)
  })

  it('discards a fractional part on a currency that has none', () => {
    // Rupiah has no minor units, so the 75 is dropped rather than folded into
    // the whole number. Getting this wrong turns Rp 1,5 juta into Rp 150 juta.
    expect(parseMoneyInput('1.500.000,75', 'IDR')?.minor).toBe(1_500_000)
    expect(parseMoneyInput('1500000,75', 'IDR')?.minor).toBe(1_500_000)
    expect(parseMoneyInput('10000,50', 'JPY')?.minor).toBe(10_000)
  })

  it('still reads three trailing digits as grouping, not a fraction', () => {
    expect(parseMoneyInput('1.500', 'IDR')?.minor).toBe(1_500)
    expect(parseMoneyInput('1,500', 'USD')?.minor).toBe(150_000)
  })
})

describe('formatting', () => {
  it('formats rupiah without decimals', () => {
    const out = formatMoney(money(1_500_000, 'IDR'))
    expect(out).toContain('1.500.000')
    expect(out).not.toContain(',00')
  })

  it('formats dollars with two decimals', () => {
    expect(formatMoney(money(1234, 'USD'), { locale: 'en-US' })).toBe('$12.34')
  })
})
