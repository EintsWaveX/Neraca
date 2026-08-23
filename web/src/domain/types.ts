/**
 * The entity model.
 *
 * Every record is flat, serialisable and free of class instances, so it can go
 * into IndexedDB and come back out unchanged, and so the same shapes could be
 * sent to a server later without a translation layer. Money is stored as
 * integer minor units plus a currency code, never as a float. See money.ts.
 */

import type { CurrencyCode } from './currency'

/** ISO date with no time part, for example 2026-08-23. */
export type IsoDate = string
/** Full ISO timestamp. */
export type IsoDateTime = string

export type Locale = 'en' | 'id'

/**
 * A person using the app on this device.
 *
 * The original C program had account registration, login and recovery backed
 * by Caesar ciphered text files. That was never security, and pretending
 * otherwise in a browser would be worse, since all of this lives in the
 * visitor's own IndexedDB. So a profile carries an optional PIN that acts as a
 * convenience lock over shared devices, hashed with PBKDF2 through WebCrypto
 * so the digits are not sitting in the database in the clear, and the README
 * says plainly that this is not encryption of the data itself.
 */
export interface Profile {
  id: string
  displayName: string
  firstName: string
  lastName: string
  email: string
  phoneNumber: string
  dateOfBirth: IsoDate | null
  sex: string
  /** Free text fields carried over from the C registration form. */
  careerProfiling: string
  aboutMe: string
  attendingCollege: string
  companyWorking: string
  degreeIn: string
  /** Everything is reported in this currency. */
  baseCurrency: CurrencyCode
  locale: Locale
  /** PBKDF2 digest and salt, both base64. Null when no PIN is set. */
  pinHash: string | null
  pinSalt: string | null
  createdAt: IsoDateTime
  /** True for the profile seeded so a first time visitor sees a full app. */
  isDemo: boolean
}

export type WalletKind = 'cash' | 'bank' | 'ewallet' | 'savings' | 'credit'

/**
 * A place money sits. The C version tracked a single running balance, which
 * meant it could not answer where the money actually was.
 */
export interface Wallet {
  id: string
  profileId: string
  name: string
  kind: WalletKind
  currency: CurrencyCode
  /** Minor units, in this wallet's own currency. */
  openingBalance: number
  archived: boolean
  createdAt: IsoDateTime
}

export type Direction = 'income' | 'expense' | 'transfer'

/**
 * One movement of money.
 *
 * `rateToBase` is captured when the transaction is written rather than looked
 * up at read time. A rate is a fact about a moment: converting a purchase made
 * last year at today's rate would silently rewrite history, and every report
 * built on it would be wrong. Storing the rate on the row is what keeps old
 * totals stable.
 */
export interface Transaction {
  id: string
  profileId: string
  walletId: string
  /** Destination wallet. Only set when `direction` is `transfer`. */
  toWalletId: string | null
  date: IsoDate
  direction: Direction
  /** One of the transaction types carried over from the C program. */
  typeId: string
  /** One of the categories in categories.ts. */
  categoryId: string
  /** Minor units, denominated in `currency`. Always positive. */
  amount: number
  currency: CurrencyCode
  /**
   * The amount credited to `toWalletId`, in THAT wallet's currency.
   *
   * Only meaningful on a transfer, and only needed when the two wallets are
   * denominated differently: withdrawing from a USD account into a rupiah one
   * debits dollars and credits rupiah, and the two figures are not related by
   * anything the row would otherwise carry. `rateToBase` cannot stand in for
   * it, because that rate converts to the profile's base currency, which is a
   * third currency in the general case. Null means the destination is credited
   * with the same `amount`, which is the ordinary same-currency transfer.
   */
  toAmount: number | null
  /** Units of the profile's base currency per one whole unit of `currency`. */
  rateToBase: number
  description: string
  /** Set when this row was generated from a recurring rule. */
  recurringId: string | null
  createdAt: IsoDateTime
}

export type BudgetPeriod = 'monthly' | 'yearly'

export interface Budget {
  id: string
  profileId: string
  period: BudgetPeriod
  /** `2026-08` for a monthly budget, `2026` for a yearly one. */
  periodKey: string
  /** Null means this budget covers all spending rather than one category. */
  categoryId: string | null
  /** Minor units in the profile's base currency. */
  limit: number
  /** Optional savings target, minor units in base currency. */
  target: number | null
  description: string
  /** Fraction of the limit at which to warn, for example 0.8 for 80 percent. */
  alertThreshold: number
  alertsEnabled: boolean
  createdAt: IsoDateTime
}

export type Frequency = 'daily' | 'weekly' | 'monthly' | 'yearly'

/**
 * A repeating transaction, such as a salary or a rent payment.
 *
 * Rules generate real transactions rather than being summed on the fly, so a
 * generated row can be edited or deleted on its own the way any other row can.
 */
export interface RecurringRule {
  id: string
  profileId: string
  name: string
  frequency: Frequency
  /** Every `interval` periods. 2 with `weekly` means once a fortnight. */
  interval: number
  startDate: IsoDate
  endDate: IsoDate | null
  /** The most recent date a transaction was generated for. */
  lastRunDate: IsoDate | null
  active: boolean
  /** The transaction to create on each occurrence. */
  template: {
    walletId: string
    toWalletId: string | null
    direction: Direction
    typeId: string
    categoryId: string
    amount: number
    currency: CurrencyCode
    description: string
  }
  createdAt: IsoDateTime
}

/**
 * A manually recorded exchange rate.
 *
 * There is no server here and no rate feed, so rates are entered by the person
 * using the app. Lookup picks the newest rate dated on or before the date being
 * converted, which is why a rate is a row with a date rather than a single
 * current value per currency.
 */
export interface ExchangeRate {
  id: string
  profileId: string
  currency: CurrencyCode
  /** Units of base currency per one whole unit of `currency`. */
  rate: number
  date: IsoDate
  createdAt: IsoDateTime
}

/** Everything belonging to one profile, used for export and import. */
export interface ProfileBackup {
  version: 1
  exportedAt: IsoDateTime
  profile: Profile
  wallets: Wallet[]
  transactions: Transaction[]
  budgets: Budget[]
  recurring: RecurringRule[]
  rates: ExchangeRate[]
}
