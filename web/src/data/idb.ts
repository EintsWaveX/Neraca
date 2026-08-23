/**
 * IndexedDB implementation of the storage contract in `repository.ts`.
 *
 * One `IDBPDatabase` connection is opened lazily and reused for the life of
 * the page; IndexedDB connections are cheap to hold open and expensive to
 * keep reopening, and every method below just borrows it for one request.
 */

import { openDB, type DBSchema, type IDBPDatabase, type StoreNames } from 'idb'
import type {
  Budget, ExchangeRate, IsoDate, Profile, ProfileBackup, RecurringRule, Transaction, Wallet,
} from '@/domain/types'
import type { CurrencyCode } from '@/domain/currency'
import { convert, money } from '@/domain/money'
import type { Repository, TransactionQuery } from './repository'
import { newId, nowIso } from './ids'

const DB_NAME = 'financialam'
const DB_VERSION = 1

interface FinancialAMSchema extends DBSchema {
  profiles: {
    key: string
    value: Profile
  }
  wallets: {
    key: string
    value: Wallet
    indexes: { byProfile: string }
  }
  transactions: {
    key: string
    value: Transaction
    indexes: {
      byProfile: string
      byProfileDate: [string, IsoDate]
      byProfileCategory: [string, string]
      byProfileWallet: [string, string]
    }
  }
  budgets: {
    key: string
    value: Budget
    indexes: { byProfile: string }
  }
  recurring: {
    key: string
    value: RecurringRule
    indexes: { byProfile: string }
  }
  rates: {
    key: string
    value: ExchangeRate
    indexes: { byProfile: string }
  }
}

const ALL_STORES: StoreNames<FinancialAMSchema>[] = [
  'profiles', 'wallets', 'transactions', 'budgets', 'recurring', 'rates',
]

function openDatabase(): Promise<IDBPDatabase<FinancialAMSchema>> {
  return openDB<FinancialAMSchema>(DB_NAME, DB_VERSION, {
    upgrade(db) {
      db.createObjectStore('profiles', { keyPath: 'id' })

      const wallets = db.createObjectStore('wallets', { keyPath: 'id' })
      wallets.createIndex('byProfile', 'profileId')

      // `byProfile` is kept alongside the compound indexes below even though
      // `listTransactions` itself only ever queries through `byProfileDate`
      // (every query has an implicit date range, open ended or not). It
      // exists for the operations that legitimately want every row for a
      // profile with no per-field filtering, such as `exportProfile`, and for
      // whatever screen wants a plain per-category or per-wallet listing
      // without walking the whole date range first.
      const transactions = db.createObjectStore('transactions', { keyPath: 'id' })
      transactions.createIndex('byProfile', 'profileId')
      transactions.createIndex('byProfileDate', ['profileId', 'date'])
      transactions.createIndex('byProfileCategory', ['profileId', 'categoryId'])
      transactions.createIndex('byProfileWallet', ['profileId', 'walletId'])

      const budgets = db.createObjectStore('budgets', { keyPath: 'id' })
      budgets.createIndex('byProfile', 'profileId')

      const recurring = db.createObjectStore('recurring', { keyPath: 'id' })
      recurring.createIndex('byProfile', 'profileId')

      const rates = db.createObjectStore('rates', { keyPath: 'id' })
      rates.createIndex('byProfile', 'profileId')
    },
  })
}

/**
 * `''` and `'\uffff'` stand in for "no lower bound" and "no upper bound" on
 * an `IsoDate`. Every real date string sorts between them under a plain
 * string comparison, which is all a compound IndexedDB key range does, so an
 * open-ended query still becomes one bounded range lookup instead of a scan
 * with a filter bolted on afterwards.
 */
function dateRange(profileId: string, from: IsoDate | undefined, to: IsoDate | undefined): IDBKeyRange {
  return IDBKeyRange.bound([profileId, from ?? ''], [profileId, to ?? '\uffff'])
}

function matchesFilters(row: Transaction, query: TransactionQuery): boolean {
  if (query.walletIds && !query.walletIds.includes(row.walletId)) return false
  if (query.categoryIds && !query.categoryIds.includes(row.categoryId)) return false
  if (query.typeIds && !query.typeIds.includes(row.typeId)) return false
  if (query.directions && !query.directions.includes(row.direction)) return false
  if (query.search) {
    const needle = query.search.toLowerCase()
    if (!row.description.toLowerCase().includes(needle)) return false
  }
  return true
}

type Sort = NonNullable<TransactionQuery['sort']>

/**
 * Sorting by amount has to compare converted values, not the raw stored ones.
 *
 * `amount` is in the row's own currency and its own minor unit scale, so
 * comparing the integers directly is meaningless across currencies: a hundred
 * dollars is stored as 10000 and a hundred thousand rupiah as 100000, which
 * would sort the smaller amount above the larger one. Each row is converted
 * through the rate it already carries, which is the same value the amount
 * filter compares against, so filtering and sorting agree.
 */
function sortTransactions(
  rows: Transaction[],
  sort: Sort,
  baseCurrency: CurrencyCode | null,
): Transaction[] {
  const sorted = [...rows]
  const baseMinor = (row: Transaction): number =>
    baseCurrency === null
      ? row.amount
      : convert(money(row.amount, row.currency), baseCurrency, row.rateToBase).minor

  switch (sort) {
    case 'date-desc':
      // Ties on `date` (same calendar day) fall back to `createdAt`, so
      // entries do not visibly reorder themselves as more get added on the
      // same day.
      sorted.sort((a, b) => b.date.localeCompare(a.date) || b.createdAt.localeCompare(a.createdAt))
      break
    case 'date-asc':
      sorted.sort((a, b) => a.date.localeCompare(b.date) || a.createdAt.localeCompare(b.createdAt))
      break
    case 'amount-desc':
      sorted.sort((a, b) => baseMinor(b) - baseMinor(a) || b.createdAt.localeCompare(a.createdAt))
      break
    case 'amount-asc':
      sorted.sort((a, b) => baseMinor(a) - baseMinor(b) || a.createdAt.localeCompare(b.createdAt))
      break
  }
  return sorted
}

function page<T>(rows: T[], offset: number | undefined, limit: number | undefined): T[] {
  const start = offset ?? 0
  return limit === undefined ? rows.slice(start) : rows.slice(start, start + limit)
}

export class IdbRepository implements Repository {
  private dbPromise: Promise<IDBPDatabase<FinancialAMSchema>> | undefined

  private db(): Promise<IDBPDatabase<FinancialAMSchema>> {
    if (!this.dbPromise) this.dbPromise = openDatabase()
    return this.dbPromise
  }

  // ---- Profiles ----

  async listProfiles(): Promise<Profile[]> {
    return (await this.db()).getAll('profiles')
  }

  async getProfile(id: string): Promise<Profile | undefined> {
    return (await this.db()).get('profiles', id)
  }

  async putProfile(profile: Profile): Promise<void> {
    await (await this.db()).put('profiles', profile)
  }

  async deleteProfile(id: string): Promise<void> {
    await (await this.db()).delete('profiles', id)
  }

  // ---- Wallets ----

  async listWallets(profileId: string): Promise<Wallet[]> {
    return (await this.db()).getAllFromIndex('wallets', 'byProfile', profileId)
  }

  async putWallet(wallet: Wallet): Promise<void> {
    await (await this.db()).put('wallets', wallet)
  }

  async deleteWallet(id: string): Promise<void> {
    await (await this.db()).delete('wallets', id)
  }

  // ---- Transactions ----

  private async matchingTransactions(query: TransactionQuery): Promise<Transaction[]> {
    const db = await this.db()
    const range = dateRange(query.profileId, query.from, query.to)
    const rows = await db.getAllFromIndex('transactions', 'byProfileDate', range)
    return rows.filter((row) => matchesFilters(row, query))
  }

  /**
   * `minBaseAmount`/`maxBaseAmount` compare against each row's amount
   * converted with its own stored `rateToBase`, never a freshly looked up
   * rate: a rate is a fact about the moment the transaction happened, and
   * re-converting at today's rate would make the same row cross the
   * threshold on different days for no reason the person entering data
   * caused. The profile is only fetched when one of these is actually set,
   * since it is needed purely to know the base currency's minor unit scale.
   */
  private async filterByBaseAmount(rows: Transaction[], query: TransactionQuery): Promise<Transaction[]> {
    if (query.minBaseAmount === undefined && query.maxBaseAmount === undefined) return rows
    const profile = await this.getProfile(query.profileId)
    // A query against a profile that no longer exists cannot be converted to
    // any base currency, so it matches nothing rather than falling back to
    // comparing raw, differently scaled amounts against a base-currency bound.
    if (!profile) return []
    return rows.filter((row) => {
      const baseMinor = convert(money(row.amount, row.currency), profile.baseCurrency, row.rateToBase).minor
      if (query.minBaseAmount !== undefined && baseMinor < query.minBaseAmount) return false
      if (query.maxBaseAmount !== undefined && baseMinor > query.maxBaseAmount) return false
      return true
    })
  }

  async listTransactions(query: TransactionQuery): Promise<Transaction[]> {
    const matched = await this.matchingTransactions(query)
    const filtered = await this.filterByBaseAmount(matched, query)
    const profile = await this.getProfile(query.profileId)
    const sorted = sortTransactions(filtered, query.sort ?? 'date-desc', profile?.baseCurrency ?? null)
    return page(sorted, query.offset, query.limit)
  }

  async countTransactions(query: TransactionQuery): Promise<number> {
    const matched = await this.matchingTransactions(query)
    const filtered = await this.filterByBaseAmount(matched, query)
    return filtered.length
  }

  async getTransaction(id: string): Promise<Transaction | undefined> {
    return (await this.db()).get('transactions', id)
  }

  async putTransaction(transaction: Transaction): Promise<void> {
    await (await this.db()).put('transactions', transaction)
  }

  async putTransactions(transactions: Transaction[]): Promise<void> {
    const db = await this.db()
    const tx = db.transaction('transactions', 'readwrite')
    // All puts are fired without awaiting each one individually and joined
    // with `tx.done`, which is the pattern `idb` needs to keep one browser
    // transaction alive across the whole batch. Awaiting each put in turn
    // lets the IndexedDB transaction auto-commit between them the moment a
    // microtask boundary is crossed, silently turning "one transaction" into
    // one per row.
    await Promise.all([...transactions.map((t) => tx.store.put(t)), tx.done])
  }

  async deleteTransaction(id: string): Promise<void> {
    await (await this.db()).delete('transactions', id)
  }

  async deleteTransactions(ids: string[]): Promise<void> {
    const db = await this.db()
    const tx = db.transaction('transactions', 'readwrite')
    await Promise.all([...ids.map((id) => tx.store.delete(id)), tx.done])
  }

  // ---- Budgets ----

  async listBudgets(profileId: string): Promise<Budget[]> {
    return (await this.db()).getAllFromIndex('budgets', 'byProfile', profileId)
  }

  async putBudget(budget: Budget): Promise<void> {
    await (await this.db()).put('budgets', budget)
  }

  async deleteBudget(id: string): Promise<void> {
    await (await this.db()).delete('budgets', id)
  }

  // ---- Recurring rules ----

  async listRecurring(profileId: string): Promise<RecurringRule[]> {
    return (await this.db()).getAllFromIndex('recurring', 'byProfile', profileId)
  }

  async putRecurring(rule: RecurringRule): Promise<void> {
    await (await this.db()).put('recurring', rule)
  }

  async deleteRecurring(id: string): Promise<void> {
    await (await this.db()).delete('recurring', id)
  }

  // ---- Exchange rates ----

  async listRates(profileId: string): Promise<ExchangeRate[]> {
    return (await this.db()).getAllFromIndex('rates', 'byProfile', profileId)
  }

  async putRate(rate: ExchangeRate): Promise<void> {
    await (await this.db()).put('rates', rate)
  }

  async deleteRate(id: string): Promise<void> {
    await (await this.db()).delete('rates', id)
  }

  // ---- Whole profile transfer ----

  async exportProfile(profileId: string): Promise<ProfileBackup> {
    const db = await this.db()
    const profile = await this.getProfile(profileId)
    if (!profile) throw new Error(`No profile with id ${profileId}`)

    const [wallets, transactions, budgets, recurring, rates] = await Promise.all([
      db.getAllFromIndex('wallets', 'byProfile', profileId),
      db.getAllFromIndex('transactions', 'byProfile', profileId),
      db.getAllFromIndex('budgets', 'byProfile', profileId),
      db.getAllFromIndex('recurring', 'byProfile', profileId),
      db.getAllFromIndex('rates', 'byProfile', profileId),
    ])

    return {
      version: 1,
      exportedAt: nowIso(),
      profile,
      wallets,
      transactions,
      budgets,
      recurring,
      rates,
    }
  }

  /**
   * Every id in the backup is replaced, including the profile's own id, so
   * importing the same backup twice (or importing it back into the browser
   * it came from) creates a second, independent profile instead of colliding
   * with rows that already exist. The wallet and recurring rule id maps are
   * built up front so every foreign key referencing them, wherever it
   * appears, can be rewritten to point at the new rows rather than the ones
   * left behind in the export.
   */
  async importProfile(backup: ProfileBackup): Promise<string> {
    const db = await this.db()

    const newProfileId = newId('prof')
    const walletIdMap = new Map(backup.wallets.map((w) => [w.id, newId('wal')]))
    const recurringIdMap = new Map(backup.recurring.map((r) => [r.id, newId('rec')]))

    const remapWallet = (id: string): string => {
      const mapped = walletIdMap.get(id)
      if (mapped === undefined) throw new Error(`Backup references unknown wallet ${id}`)
      return mapped
    }
    const remapWalletOrNull = (id: string | null): string | null => (
      id === null ? null : remapWallet(id)
    )
    const remapRecurringOrNull = (id: string | null): string | null => {
      if (id === null) return null
      const mapped = recurringIdMap.get(id)
      if (mapped === undefined) throw new Error(`Backup references unknown recurring rule ${id}`)
      return mapped
    }

    const profile: Profile = { ...backup.profile, id: newProfileId }

    const wallets: Wallet[] = backup.wallets.map((w) => ({
      ...w,
      id: remapWallet(w.id),
      profileId: newProfileId,
    }))

    const recurring: RecurringRule[] = backup.recurring.map((r) => {
      const mappedId = recurringIdMap.get(r.id)
      if (mappedId === undefined) throw new Error(`Backup references unknown recurring rule ${r.id}`)
      return {
        ...r,
        id: mappedId,
        profileId: newProfileId,
        template: {
          ...r.template,
          walletId: remapWallet(r.template.walletId),
          toWalletId: remapWalletOrNull(r.template.toWalletId),
        },
      }
    })

    const transactions: Transaction[] = backup.transactions.map((t) => ({
      ...t,
      id: newId('txn'),
      profileId: newProfileId,
      walletId: remapWallet(t.walletId),
      toWalletId: remapWalletOrNull(t.toWalletId),
      // `categoryId` is left untouched: categories are the static list in
      // categories.ts, not rows this repository owns, so there is nothing to
      // remap it to.
      recurringId: remapRecurringOrNull(t.recurringId),
    }))

    const budgets: Budget[] = backup.budgets.map((b) => ({
      ...b,
      id: newId('bud'),
      profileId: newProfileId,
    }))

    const rates: ExchangeRate[] = backup.rates.map((r) => ({
      ...r,
      id: newId('rate'),
      profileId: newProfileId,
    }))

    const tx = db.transaction(ALL_STORES, 'readwrite')
    await Promise.all([
      tx.objectStore('profiles').put(profile),
      ...wallets.map((w) => tx.objectStore('wallets').put(w)),
      ...transactions.map((t) => tx.objectStore('transactions').put(t)),
      ...budgets.map((b) => tx.objectStore('budgets').put(b)),
      ...recurring.map((r) => tx.objectStore('recurring').put(r)),
      ...rates.map((r) => tx.objectStore('rates').put(r)),
      tx.done,
    ])

    return newProfileId
  }

  async clearAll(): Promise<void> {
    const db = await this.db()
    const tx = db.transaction(ALL_STORES, 'readwrite')
    await Promise.all([...ALL_STORES.map((name) => tx.objectStore(name).clear()), tx.done])
  }
}

let singleton: IdbRepository | undefined

/** The database connection is not opened until the first call reaches it. */
export function getRepository(): Repository {
  if (!singleton) singleton = new IdbRepository()
  return singleton
}
