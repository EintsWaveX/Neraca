import { describe, expect, it } from 'vitest'
import type { ExchangeRate, Transaction } from './types'
import { findRate, signedBase, toBase } from './rates'

function rate(currency: ExchangeRate['currency'], date: string, rate_: number, createdAt = date): ExchangeRate {
  return { id: `${currency}-${date}`, profileId: 'p1', currency, rate: rate_, date, createdAt }
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

describe('findRate', () => {
  it('returns 1 when the currency is already the base currency', () => {
    expect(findRate([], 'IDR', '2026-08-10', 'IDR')).toBe(1)
  })

  it('returns null when no rate exists on or before the date', () => {
    const rates = [rate('USD', '2026-08-15', 16_000)]
    expect(findRate(rates, 'USD', '2026-08-10', 'IDR')).toBeNull()
  })

  it('picks the newest rate dated on or before the target date', () => {
    const rates = [
      rate('USD', '2026-08-01', 16_000),
      rate('USD', '2026-08-10', 16_200),
      rate('USD', '2026-08-20', 16_500),
    ]
    expect(findRate(rates, 'USD', '2026-08-15', 'IDR')).toBe(16_200)
  })

  it('never looks past the target date', () => {
    const rates = [rate('USD', '2026-08-01', 16_000), rate('USD', '2026-08-20', 16_500)]
    expect(findRate(rates, 'USD', '2026-08-10', 'IDR')).toBe(16_000)
  })

  it('uses the rate dated exactly on the target date', () => {
    const rates = [rate('USD', '2026-08-10', 16_100)]
    expect(findRate(rates, 'USD', '2026-08-10', 'IDR')).toBe(16_100)
  })

  it('ignores rates for other currencies', () => {
    const rates = [rate('EUR', '2026-08-10', 17_000)]
    expect(findRate(rates, 'USD', '2026-08-10', 'IDR')).toBeNull()
  })

  it('breaks a same day tie with the row entered later', () => {
    const rates = [
      rate('USD', '2026-08-10', 16_000, '2026-08-10T08:00:00.000Z'),
      rate('USD', '2026-08-10', 16_050, '2026-08-10T20:00:00.000Z'),
    ]
    expect(findRate(rates, 'USD', '2026-08-10', 'IDR')).toBe(16_050)
  })
})

describe('toBase', () => {
  it('uses the rate stored on the row, not a fresh lookup', () => {
    // The row says 1 USD was worth 15,000 IDR on the day it was recorded:
    // 10.00 USD (1,000 minor units) becomes 150,000 IDR. Even if today's true
    // rate is very different, toBase must still use 15,000, because that is
    // what the purchase actually cost at the time.
    const t = tx({ amount: 1_000, currency: 'USD', rateToBase: 15_000 })
    expect(toBase(t, 'IDR')).toEqual({ minor: 150_000, currency: 'IDR' })
  })

  it('is a no-op when the transaction currency already is the base currency', () => {
    const t = tx({ amount: 50_000, currency: 'IDR', rateToBase: 1 })
    expect(toBase(t, 'IDR').minor).toBe(50_000)
  })
})

describe('signedBase', () => {
  it('is negative for an expense', () => {
    const t = tx({ direction: 'expense', amount: 20_000, currency: 'IDR', rateToBase: 1 })
    expect(signedBase(t, 'IDR').minor).toBe(-20_000)
  })

  it('is positive for income', () => {
    const t = tx({ direction: 'income', amount: 20_000, currency: 'IDR', rateToBase: 1 })
    expect(signedBase(t, 'IDR').minor).toBe(20_000)
  })

  it('is zero for a transfer, excluding it from income and expense totals', () => {
    const t = tx({ direction: 'transfer', amount: 20_000, currency: 'IDR', rateToBase: 1, toWalletId: 'w2' })
    expect(signedBase(t, 'IDR').minor).toBe(0)
  })

  it('sums to a correct running total across a mix of directions', () => {
    const rows = [
      tx({ direction: 'income', amount: 100_000, currency: 'IDR', rateToBase: 1 }),
      tx({ direction: 'expense', amount: 30_000, currency: 'IDR', rateToBase: 1 }),
      tx({ direction: 'transfer', amount: 50_000, currency: 'IDR', rateToBase: 1, toWalletId: 'w2' }),
    ]
    const total = rows.reduce((sum, t) => sum + signedBase(t, 'IDR').minor, 0)
    expect(total).toBe(70_000)
  })
})
