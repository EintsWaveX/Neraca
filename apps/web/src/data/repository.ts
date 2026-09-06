/**
 * The storage contract.
 *
 * Nothing above this file knows where data lives. Today the only implementation
 * is IndexedDB in the visitor's browser, which is what lets the app be a static
 * page on GitHub Pages with no server behind it. If it ever needs a real
 * backend, a second implementation of this interface is the whole change: the
 * features, the domain logic and the screens do not move.
 *
 * Every method is async even where IndexedDB could answer synchronously,
 * precisely so that a network backed implementation can drop in without
 * rewriting call sites.
 */

import type {
  Budget, ExchangeRate, IsoDate, Profile, ProfileBackup, RecurringRule, Transaction, Wallet,
} from '@neraca/domain/types'

/** Filter accepted by `listTransactions`. Every field is optional. */
export interface TransactionQuery {
  profileId: string
  from?: IsoDate
  to?: IsoDate
  walletIds?: string[]
  categoryIds?: string[]
  typeIds?: string[]
  directions?: Array<Transaction['direction']>
  /** Matched against description, case insensitively. */
  search?: string
  /** Minor units in the profile's base currency, after conversion. */
  minBaseAmount?: number
  maxBaseAmount?: number
  sort?: 'date-desc' | 'date-asc' | 'amount-desc' | 'amount-asc'
  limit?: number
  offset?: number
}

export interface Repository {
  // Profiles
  listProfiles(): Promise<Profile[]>
  getProfile(id: string): Promise<Profile | undefined>
  putProfile(profile: Profile): Promise<void>
  deleteProfile(id: string): Promise<void>

  // Wallets
  listWallets(profileId: string): Promise<Wallet[]>
  putWallet(wallet: Wallet): Promise<void>
  deleteWallet(id: string): Promise<void>

  // Transactions
  listTransactions(query: TransactionQuery): Promise<Transaction[]>
  countTransactions(query: TransactionQuery): Promise<number>
  getTransaction(id: string): Promise<Transaction | undefined>
  putTransaction(transaction: Transaction): Promise<void>
  putTransactions(transactions: Transaction[]): Promise<void>
  deleteTransaction(id: string): Promise<void>
  deleteTransactions(ids: string[]): Promise<void>

  // Budgets
  listBudgets(profileId: string): Promise<Budget[]>
  putBudget(budget: Budget): Promise<void>
  deleteBudget(id: string): Promise<void>

  // Recurring rules
  listRecurring(profileId: string): Promise<RecurringRule[]>
  putRecurring(rule: RecurringRule): Promise<void>
  deleteRecurring(id: string): Promise<void>

  // Exchange rates
  listRates(profileId: string): Promise<ExchangeRate[]>
  putRate(rate: ExchangeRate): Promise<void>
  deleteRate(id: string): Promise<void>

  // Whole profile transfer
  exportProfile(profileId: string): Promise<ProfileBackup>
  importProfile(backup: ProfileBackup): Promise<string>

  /** Remove every profile and all their data. Used by the demo reset. */
  clearAll(): Promise<void>
}
