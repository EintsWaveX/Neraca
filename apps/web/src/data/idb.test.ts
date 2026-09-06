// Registers `indexedDB`, `IDBKeyRange`, `IDBRequest` and the rest of the
// IndexedDB surface on `globalThis`, since Node has none of it natively.
// `idb`'s own wrapper reaches for several of these classes directly (to
// recognise a returned value as a cursor, for instance), not only for the
// factory this file resets per test below, so the auto import has to run
// before anything else touches `openDB`.
import 'fake-indexeddb/auto'
import { beforeEach, describe, expect, it } from 'vitest'
import { IDBFactory } from 'fake-indexeddb'
import type {
  Budget, ExchangeRate, Profile, RecurringRule, Transaction, Wallet,
} from '@neraca/domain/types'
import { IdbRepository } from './idb'

// Each test gets a brand new, empty database rather than sharing the one
// process-wide instance the auto import installs. Reusing a factory across
// tests would let a profile or transaction written by one test leak into the
// next, and the whole point of a repository test is trusting that a fresh
// `listX` call reflects exactly what that test put in.
beforeEach(() => {
  globalThis.indexedDB = new IDBFactory()
})

function makeProfile(overrides: Partial<Profile> = {}): Profile {
  return {
    id: 'prof_1',
    displayName: 'Ada',
    firstName: 'Ada',
    lastName: 'Lovelace',
    email: 'ada@example.com',
    phoneNumber: '000',
    dateOfBirth: null,
    sex: '',
    careerProfiling: '',
    aboutMe: '',
    attendingCollege: '',
    companyWorking: '',
    degreeIn: '',
    baseCurrency: 'USD',
    locale: 'en',
    pinHash: null,
    pinSalt: null,
    createdAt: '2026-01-01T00:00:00.000Z',
    isDemo: false,
    ...overrides,
  }
}

function makeWallet(overrides: Partial<Wallet> = {}): Wallet {
  return {
    id: 'wal_1',
    profileId: 'prof_1',
    name: 'Cash',
    kind: 'cash',
    currency: 'USD',
    openingBalance: 0,
    archived: false,
    createdAt: '2026-01-01T00:00:00.000Z',
    ...overrides,
  }
}

function makeTransaction(overrides: Partial<Transaction> = {}): Transaction {
  return {
    id: 'txn_1',
    profileId: 'prof_1',
    walletId: 'wal_1',
    toWalletId: null,
    date: '2026-01-15',
    direction: 'expense',
    typeId: 'payment-with-card',
    categoryId: 'groceries',
    amount: 1000,
    currency: 'USD',
    toAmount: null,
    rateToBase: 1,
    description: 'Weekly shop',
    recurringId: null,
    createdAt: '2026-01-15T00:00:00.000Z',
    ...overrides,
  }
}

function makeBudget(overrides: Partial<Budget> = {}): Budget {
  return {
    id: 'bud_1',
    profileId: 'prof_1',
    period: 'monthly',
    periodKey: '2026-01',
    categoryId: 'groceries',
    limit: 50000,
    target: null,
    description: '',
    alertThreshold: 0.8,
    alertsEnabled: true,
    createdAt: '2026-01-01T00:00:00.000Z',
    ...overrides,
  }
}

function makeRecurring(overrides: Partial<RecurringRule> = {}): RecurringRule {
  return {
    id: 'rec_1',
    profileId: 'prof_1',
    name: 'Rent',
    frequency: 'monthly',
    interval: 1,
    startDate: '2026-01-01',
    endDate: null,
    lastRunDate: null,
    active: true,
    template: {
      walletId: 'wal_1',
      toWalletId: null,
      direction: 'expense',
      typeId: 'bill-payment',
      categoryId: 'house-and-apartment-rent',
      amount: 500000,
      currency: 'USD',
      description: 'Rent',
    },
    createdAt: '2026-01-01T00:00:00.000Z',
    ...overrides,
  }
}

function makeRate(overrides: Partial<ExchangeRate> = {}): ExchangeRate {
  return {
    id: 'rate_1',
    profileId: 'prof_1',
    currency: 'IDR',
    rate: 0.000061,
    date: '2026-01-01',
    createdAt: '2026-01-01T00:00:00.000Z',
    ...overrides,
  }
}

describe('round tripping every entity kind', () => {
  it('writes and reads back a profile', async () => {
    const repo = new IdbRepository()
    const profile = makeProfile()
    await repo.putProfile(profile)
    expect(await repo.getProfile('prof_1')).toEqual(profile)
    expect(await repo.listProfiles()).toEqual([profile])
  })

  it('writes and reads back a wallet', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    const wallet = makeWallet()
    await repo.putWallet(wallet)
    expect(await repo.listWallets('prof_1')).toEqual([wallet])
  })

  it('writes and reads back a transaction', async () => {
    const repo = new IdbRepository()
    const transaction = makeTransaction()
    await repo.putTransaction(transaction)
    expect(await repo.getTransaction('txn_1')).toEqual(transaction)
  })

  it('writes and reads back a budget', async () => {
    const repo = new IdbRepository()
    const budget = makeBudget()
    await repo.putBudget(budget)
    expect(await repo.listBudgets('prof_1')).toEqual([budget])
  })

  it('writes and reads back a recurring rule', async () => {
    const repo = new IdbRepository()
    const rule = makeRecurring()
    await repo.putRecurring(rule)
    expect(await repo.listRecurring('prof_1')).toEqual([rule])
  })

  it('writes and reads back an exchange rate', async () => {
    const repo = new IdbRepository()
    const rate = makeRate()
    await repo.putRate(rate)
    expect(await repo.listRates('prof_1')).toEqual([rate])
  })

  it('deletes each entity kind', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    await repo.putWallet(makeWallet())
    await repo.putTransaction(makeTransaction())
    await repo.putBudget(makeBudget())
    await repo.putRecurring(makeRecurring())
    await repo.putRate(makeRate())

    await repo.deleteProfile('prof_1')
    await repo.deleteWallet('wal_1')
    await repo.deleteTransaction('txn_1')
    await repo.deleteBudget('bud_1')
    await repo.deleteRecurring('rec_1')
    await repo.deleteRate('rate_1')

    expect(await repo.getProfile('prof_1')).toBeUndefined()
    expect(await repo.listWallets('prof_1')).toEqual([])
    expect(await repo.getTransaction('txn_1')).toBeUndefined()
    expect(await repo.listBudgets('prof_1')).toEqual([])
    expect(await repo.listRecurring('prof_1')).toEqual([])
    expect(await repo.listRates('prof_1')).toEqual([])
  })
})

describe('listTransactions filters', () => {
  async function seed(repo: IdbRepository): Promise<void> {
    await repo.putProfile(makeProfile({ baseCurrency: 'USD' }))
    await repo.putWallet(makeWallet({ id: 'wal_cash', name: 'Cash' }))
    await repo.putWallet(makeWallet({ id: 'wal_bank', name: 'Bank' }))
    await repo.putTransactions([
      makeTransaction({
        id: 'txn_a', walletId: 'wal_cash', date: '2026-01-05', direction: 'expense',
        typeId: 'payment-with-card', categoryId: 'groceries', amount: 1000, currency: 'USD',
        toAmount: null,
        rateToBase: 1, description: 'Supermarket run',
      }),
      makeTransaction({
        id: 'txn_b', walletId: 'wal_bank', date: '2026-01-20', direction: 'income',
        typeId: 'salary-payroll', categoryId: 'salary', amount: 500000, currency: 'USD',
        toAmount: null,
        rateToBase: 1, description: 'Monthly salary',
      }),
      makeTransaction({
        id: 'txn_c', walletId: 'wal_cash', date: '2026-02-10', direction: 'expense',
        typeId: 'qr-payment', categoryId: 'dining-out', amount: 1500000, currency: 'IDR',
        toAmount: null,
        rateToBase: 0.000061, description: 'Dinner out',
      }),
    ])
  }

  it('filters by profileId, leaving out other profiles entirely', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    await repo.putProfile(makeProfile({ id: 'prof_2' }))
    await repo.putTransaction(makeTransaction({ id: 'txn_other', profileId: 'prof_2' }))

    const rows = await repo.listTransactions({ profileId: 'prof_1' })
    expect(rows.map((r) => r.id).sort()).toEqual(['txn_a', 'txn_b', 'txn_c'])
  })

  it('filters by a from/to date range using the compound index', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', from: '2026-01-10', to: '2026-01-31' })
    expect(rows.map((r) => r.id)).toEqual(['txn_b'])
  })

  it('treats an open from with no to as everything from that date onward', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', from: '2026-01-10' })
    expect(rows.map((r) => r.id).sort()).toEqual(['txn_b', 'txn_c'])
  })

  it('filters by walletIds', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', walletIds: ['wal_bank'] })
    expect(rows.map((r) => r.id)).toEqual(['txn_b'])
  })

  it('filters by categoryIds', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', categoryIds: ['dining-out'] })
    expect(rows.map((r) => r.id)).toEqual(['txn_c'])
  })

  it('filters by typeIds', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', typeIds: ['salary-payroll'] })
    expect(rows.map((r) => r.id)).toEqual(['txn_b'])
  })

  it('filters by directions', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', directions: ['income'] })
    expect(rows.map((r) => r.id)).toEqual(['txn_b'])
  })

  it('filters by search, case insensitively over description', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', search: 'SUPERMARKET' })
    expect(rows.map((r) => r.id)).toEqual(['txn_a'])
  })

  it('filters by minBaseAmount and maxBaseAmount, converting IDR through its own stored rate', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    // txn_c is 1,500,000 IDR at rateToBase 0.000061, which is 91.50 USD, so
    // 9150 minor units. A stale rate captured at query time must not affect
    // this: only the rate stored on the row does.
    const rows = await repo.listTransactions({ profileId: 'prof_1', minBaseAmount: 9000, maxBaseAmount: 10000 })
    expect(rows.map((r) => r.id)).toEqual(['txn_c'])
  })

  it('excludes everything when minBaseAmount is set on a profile that has since been deleted', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    await repo.deleteProfile('prof_1')
    const rows = await repo.listTransactions({ profileId: 'prof_1', minBaseAmount: 0 })
    expect(rows).toEqual([])
  })

  it('combines several filters at once', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({
      profileId: 'prof_1', walletIds: ['wal_cash'], directions: ['expense'], from: '2026-02-01',
    })
    expect(rows.map((r) => r.id)).toEqual(['txn_c'])
  })
})

describe('sorting', () => {
  async function seed(repo: IdbRepository): Promise<void> {
    await repo.putProfile(makeProfile())
    await repo.putTransactions([
      makeTransaction({ id: 'txn_early_small', date: '2026-01-01', amount: 100 }),
      makeTransaction({ id: 'txn_late_big', date: '2026-01-20', amount: 900 }),
      makeTransaction({ id: 'txn_mid_mid', date: '2026-01-10', amount: 500 }),
    ])
  }

  it('sorts date-desc by default', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1' })
    expect(rows.map((r) => r.id)).toEqual(['txn_late_big', 'txn_mid_mid', 'txn_early_small'])
  })

  it('sorts date-asc', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', sort: 'date-asc' })
    expect(rows.map((r) => r.id)).toEqual(['txn_early_small', 'txn_mid_mid', 'txn_late_big'])
  })

  it('sorts amount-desc', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', sort: 'amount-desc' })
    expect(rows.map((r) => r.id)).toEqual(['txn_late_big', 'txn_mid_mid', 'txn_early_small'])
  })

  it('sorts amount-asc', async () => {
    const repo = new IdbRepository()
    await seed(repo)
    const rows = await repo.listTransactions({ profileId: 'prof_1', sort: 'amount-asc' })
    expect(rows.map((r) => r.id)).toEqual(['txn_early_small', 'txn_mid_mid', 'txn_late_big'])
  })
})

describe('limit and offset', () => {
  it('pages through a sorted result set', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    await repo.putTransactions([
      makeTransaction({ id: 'txn_1', date: '2026-01-01' }),
      makeTransaction({ id: 'txn_2', date: '2026-01-02' }),
      makeTransaction({ id: 'txn_3', date: '2026-01-03' }),
      makeTransaction({ id: 'txn_4', date: '2026-01-04' }),
    ])

    const firstPage = await repo.listTransactions({ profileId: 'prof_1', sort: 'date-asc', limit: 2 })
    expect(firstPage.map((r) => r.id)).toEqual(['txn_1', 'txn_2'])

    const secondPage = await repo.listTransactions({ profileId: 'prof_1', sort: 'date-asc', limit: 2, offset: 2 })
    expect(secondPage.map((r) => r.id)).toEqual(['txn_3', 'txn_4'])

    const tail = await repo.listTransactions({ profileId: 'prof_1', sort: 'date-asc', offset: 3 })
    expect(tail.map((r) => r.id)).toEqual(['txn_4'])
  })

  it('countTransactions ignores limit and offset and reports the total match count', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    await repo.putTransactions([
      makeTransaction({ id: 'txn_1', date: '2026-01-01' }),
      makeTransaction({ id: 'txn_2', date: '2026-01-02' }),
      makeTransaction({ id: 'txn_3', date: '2026-01-03' }),
    ])
    expect(await repo.countTransactions({ profileId: 'prof_1', limit: 1 })).toBe(3)
  })
})

describe('batch operations', () => {
  it('putTransactions writes every row in one call', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    const batch = Array.from({ length: 25 }, (_, i) => makeTransaction({ id: `txn_${i}`, date: '2026-01-01' }))
    await repo.putTransactions(batch)
    expect(await repo.countTransactions({ profileId: 'prof_1' })).toBe(25)
  })

  it('deleteTransactions removes every row in one call', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    const batch = Array.from({ length: 10 }, (_, i) => makeTransaction({ id: `txn_${i}`, date: '2026-01-01' }))
    await repo.putTransactions(batch)
    await repo.deleteTransactions(batch.slice(0, 4).map((t) => t.id))
    const remaining = await repo.listTransactions({ profileId: 'prof_1' })
    expect(remaining).toHaveLength(6)
    expect(remaining.some((t) => t.id === 'txn_0')).toBe(false)
  })
})

describe('export and import', () => {
  it('produces a distinct profile whose rows point at the imported wallets, not the originals', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    await repo.putWallet(makeWallet({ id: 'wal_cash', name: 'Cash' }))
    await repo.putWallet(makeWallet({ id: 'wal_bank', name: 'Bank' }))
    await repo.putRecurring(makeRecurring({
      id: 'rec_rent',
      template: {
        walletId: 'wal_bank', toWalletId: null, direction: 'expense', typeId: 'bill-payment',
        categoryId: 'house-and-apartment-rent', amount: 500000, currency: 'USD', description: 'Rent',
      },
    }))
    await repo.putTransactions([
      makeTransaction({
        id: 'txn_spend', walletId: 'wal_cash', toWalletId: null, recurringId: null,
      }),
      makeTransaction({
        id: 'txn_transfer', walletId: 'wal_cash', toWalletId: 'wal_bank', direction: 'transfer',
        typeId: 'internal-transfer', categoryId: 'others', recurringId: null,
      }),
      makeTransaction({
        id: 'txn_generated', walletId: 'wal_bank', toWalletId: null, recurringId: 'rec_rent',
        categoryId: 'house-and-apartment-rent', typeId: 'bill-payment', amount: 500000,
      }),
    ])
    await repo.putBudget(makeBudget())
    await repo.putRate(makeRate())

    const backup = await repo.exportProfile('prof_1')
    const newProfileId = await repo.importProfile(backup)

    expect(newProfileId).not.toBe('prof_1')
    expect(await repo.getProfile('prof_1')).toBeDefined()
    const importedProfile = await repo.getProfile(newProfileId)
    expect(importedProfile).toBeDefined()
    expect(importedProfile?.id).toBe(newProfileId)

    const originalWalletIds = new Set((await repo.listWallets('prof_1')).map((w) => w.id))
    const importedWallets = await repo.listWallets(newProfileId)
    expect(importedWallets).toHaveLength(2)
    for (const wallet of importedWallets) {
      expect(originalWalletIds.has(wallet.id)).toBe(false)
      expect(wallet.profileId).toBe(newProfileId)
    }

    const importedTransactions = await repo.listTransactions({ profileId: newProfileId })
    expect(importedTransactions).toHaveLength(3)
    const importedWalletIds = new Set(importedWallets.map((w) => w.id))
    for (const txn of importedTransactions) {
      expect(originalWalletIds.has(txn.walletId)).toBe(false)
      expect(importedWalletIds.has(txn.walletId)).toBe(true)
      if (txn.toWalletId !== null) {
        expect(originalWalletIds.has(txn.toWalletId)).toBe(false)
        expect(importedWalletIds.has(txn.toWalletId)).toBe(true)
      }
    }

    const generated = importedTransactions.find((t) => t.amount === 500000 && t.categoryId === 'house-and-apartment-rent')
    expect(generated).toBeDefined()
    expect(generated?.recurringId).not.toBe('rec_rent')
    expect(generated?.recurringId).not.toBeNull()

    const importedRecurring = await repo.listRecurring(newProfileId)
    expect(importedRecurring).toHaveLength(1)
    expect(importedRecurring[0]?.id).not.toBe('rec_rent')
    expect(importedRecurring[0]?.template.walletId).toBe(
      importedWallets.find((w) => w.name === 'Bank')?.id,
    )

    // The original profile's own data must be untouched by the import.
    const originalTransactions = await repo.listTransactions({ profileId: 'prof_1' })
    expect(originalTransactions.map((t) => t.id).sort()).toEqual(['txn_generated', 'txn_spend', 'txn_transfer'])
  })

  it('does not collide with existing rows when importing the same backup twice', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    await repo.putWallet(makeWallet())
    await repo.putTransaction(makeTransaction())

    const backup = await repo.exportProfile('prof_1')
    const firstImportId = await repo.importProfile(backup)
    const secondImportId = await repo.importProfile(backup)

    expect(firstImportId).not.toBe(secondImportId)
    const allProfiles = await repo.listProfiles()
    expect(allProfiles).toHaveLength(3)
    expect(await repo.listWallets(firstImportId)).toHaveLength(1)
    expect(await repo.listWallets(secondImportId)).toHaveLength(1)
  })
})

describe('clearAll', () => {
  it('removes every profile and everything belonging to them', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile())
    await repo.putWallet(makeWallet())
    await repo.putTransaction(makeTransaction())
    await repo.putBudget(makeBudget())
    await repo.putRecurring(makeRecurring())
    await repo.putRate(makeRate())

    await repo.clearAll()

    expect(await repo.listProfiles()).toEqual([])
    expect(await repo.listWallets('prof_1')).toEqual([])
    expect(await repo.listTransactions({ profileId: 'prof_1' })).toEqual([])
    expect(await repo.listBudgets('prof_1')).toEqual([])
    expect(await repo.listRecurring('prof_1')).toEqual([])
    expect(await repo.listRates('prof_1')).toEqual([])
  })
})

describe('sorting by amount across currencies', () => {
  // Regression guard. The first implementation compared the raw stored
  // integers, which are in each row's own minor unit scale. USD 100.00 is
  // stored as 10000 and IDR 100.000 as 100000, so the smaller amount sorted
  // above the larger one. Sorting has to convert first, using the same rate
  // the row already carries.
  it('ranks a larger converted amount above a smaller one', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile({ baseCurrency: 'USD' }))
    await repo.putWallet(makeWallet({ id: 'wal_usd', currency: 'USD' }))
    await repo.putWallet(makeWallet({ id: 'wal_idr', currency: 'IDR' }))

    // One hundred US dollars, stored as 10000 minor units.
    await repo.putTransaction(makeTransaction({
      id: 'txn_usd', walletId: 'wal_usd', amount: 10_000, currency: 'USD', rateToBase: 1,
    }))
    // One hundred thousand rupiah, stored as 100000 minor units, but worth
    // only about six dollars. The raw integer is ten times larger.
    await repo.putTransaction(makeTransaction({
      id: 'txn_idr', walletId: 'wal_idr', amount: 100_000, currency: 'IDR', rateToBase: 0.000061,
    }))

    const desc = await repo.listTransactions({ profileId: 'prof_1', sort: 'amount-desc' })
    expect(desc.map((row) => row.id)).toEqual(['txn_usd', 'txn_idr'])

    const asc = await repo.listTransactions({ profileId: 'prof_1', sort: 'amount-asc' })
    expect(asc.map((row) => row.id)).toEqual(['txn_idr', 'txn_usd'])
  })

  it('agrees with the base amount filter', async () => {
    const repo = new IdbRepository()
    await repo.putProfile(makeProfile({ baseCurrency: 'USD' }))
    await repo.putWallet(makeWallet({ id: 'wal_idr', currency: 'IDR' }))
    await repo.putTransaction(makeTransaction({
      id: 'txn_idr', walletId: 'wal_idr', amount: 100_000, currency: 'IDR', rateToBase: 0.000061,
    }))

    // Roughly six dollars, so a floor of ten dollars must exclude it even
    // though the raw stored integer is 100000.
    const excluded = await repo.listTransactions({ profileId: 'prof_1', minBaseAmount: 1000 })
    expect(excluded).toHaveLength(0)

    const included = await repo.listTransactions({ profileId: 'prof_1', maxBaseAmount: 1000 })
    expect(included.map((row) => row.id)).toEqual(['txn_idr'])
  })
})
