import { format } from 'date-fns'
import { describe, expect, it } from 'vitest'
import type { ExchangeRate, Transaction, Wallet } from './types'
import { netWorth, walletBalance } from './balances'

function wallet(overrides: Partial<Wallet> = {}): Wallet {
  return {
    id: 'w1',
    profileId: 'p1',
    name: 'Cash',
    kind: 'cash',
    currency: 'IDR',
    openingBalance: 100_000,
    archived: false,
    createdAt: '2026-01-01T00:00:00.000Z',
    ...overrides,
  }
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

describe('walletBalance', () => {
  it('starts from the opening balance with no transactions', () => {
    expect(walletBalance(wallet({ openingBalance: 500_000 }), []).minor).toBe(500_000)
  })

  it('adds income and subtracts expenses posted to the wallet', () => {
    const w = wallet({ openingBalance: 100_000 })
    const rows = [
      tx({ walletId: 'w1', direction: 'income', amount: 50_000 }),
      tx({ walletId: 'w1', direction: 'expense', amount: 20_000 }),
    ]
    expect(walletBalance(w, rows).minor).toBe(130_000)
  })

  it('ignores transactions that belong to a different wallet', () => {
    const w = wallet({ id: 'w1', openingBalance: 100_000 })
    const rows = [tx({ walletId: 'w2', direction: 'income', amount: 50_000 })]
    expect(walletBalance(w, rows).minor).toBe(100_000)
  })

  it('debits the source wallet and credits the destination wallet on a transfer', () => {
    const source = wallet({ id: 'w1', openingBalance: 100_000 })
    const dest = wallet({ id: 'w2', openingBalance: 0 })
    const rows = [tx({ walletId: 'w1', toWalletId: 'w2', direction: 'transfer', amount: 40_000 })]

    expect(walletBalance(source, rows).minor).toBe(60_000)
    expect(walletBalance(dest, rows).minor).toBe(40_000)
  })

  it('nets a transfer to zero change in the total across both wallets', () => {
    const source = wallet({ id: 'w1', openingBalance: 100_000 })
    const dest = wallet({ id: 'w2', openingBalance: 50_000 })
    const rows = [tx({ walletId: 'w1', toWalletId: 'w2', direction: 'transfer', amount: 40_000 })]
    const totalBefore = source.openingBalance + dest.openingBalance
    const totalAfter = walletBalance(source, rows).minor + walletBalance(dest, rows).minor
    expect(totalAfter).toBe(totalBefore)
  })
})

describe('netWorth', () => {
  it('sums wallets already in the base currency with no conversion needed', () => {
    const wallets = [
      wallet({ id: 'w1', currency: 'IDR', openingBalance: 200_000 }),
      wallet({ id: 'w2', currency: 'IDR', openingBalance: 300_000 }),
    ]
    expect(netWorth(wallets, [], 'IDR', []).minor).toBe(500_000)
  })

  it('converts a foreign currency wallet using the newest applicable rate', () => {
    const today = format(new Date(), 'yyyy-MM-dd')
    const wallets = [wallet({ id: 'w1', currency: 'USD', openingBalance: 10_000 })]
    const rates: ExchangeRate[] = [
      { id: 'r1', profileId: 'p1', currency: 'USD', rate: 16_000, date: today, createdAt: today },
    ]
    // 100.00 USD at 16,000 IDR per USD is 1,600,000 IDR.
    expect(netWorth(wallets, [], 'IDR', rates).minor).toBe(1_600_000)
  })

  it('a transfer between two of the profile wallets does not change net worth', () => {
    const wallets = [
      wallet({ id: 'w1', currency: 'IDR', openingBalance: 100_000 }),
      wallet({ id: 'w2', currency: 'IDR', openingBalance: 0 }),
    ]
    const rows = [tx({ walletId: 'w1', toWalletId: 'w2', direction: 'transfer', amount: 30_000 })]
    expect(netWorth(wallets, rows, 'IDR', []).minor).toBe(100_000)
  })

  it('throws rather than silently dropping a wallet with no available rate', () => {
    const wallets = [wallet({ id: 'w1', currency: 'USD', openingBalance: 1_000 })]
    expect(() => netWorth(wallets, [], 'IDR', [])).toThrow()
  })
})
