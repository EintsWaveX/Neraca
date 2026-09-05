/**
 * Demo data.
 *
 * A first time visitor never sees an empty app: `buildDemoBackup` produces a
 * full profile, wallets, transactions, budgets, recurring rules and exchange
 * rates that get imported the moment the app boots with nothing in
 * IndexedDB. This is the single most important file for a first impression,
 * so the numbers are deliberately calibrated to an Indonesian student's real
 * life rather than to a generic template.
 *
 * The persona: a final year engineering student in Bandung, living in a kos,
 * who also freelances. Base currency IDR, with one USD wallet holding
 * payments from an overseas client so multi-currency conversion has real
 * data behind it.
 *
 * DETERMINISM. Screenshots, visual review and the test suite all depend on
 * this file producing byte-for-byte the same data on every run, in every
 * browser and in CI. `Math.random()` draws from OS entropy and `Date.now()`
 * reads the wall clock, so either one would make two runs diverge and would
 * make a captured screenshot stop matching the live app the next day. Instead
 * everything below is derived from a small seeded PRNG (mulberry32) seeded
 * with a fixed constant, and from a `today` parameter that itself defaults to
 * a fixed date rather than `new Date()`. Two calls with the same `today`
 * always produce deeply equal output.
 *
 * IDS AND TIMESTAMPS. `src/data/ids.ts` exists for the app's own use once a
 * person is actually editing their data: `newId` mixes in `Date.now()` and
 * `crypto.randomUUID`, and `nowIso` reads the wall clock, both entirely on
 * purpose for that job. Reusing either one here would reintroduce the exact
 * non-determinism this file exists to avoid, so the seed keeps its own tiny
 * id and timestamp generators, built from the same seeded PRNG and the
 * `today` parameter, using the same `prefix_...` id shape purely for
 * readability in DevTools.
 */

import type {
  Budget,
  BudgetPeriod,
  Direction,
  ExchangeRate,
  Frequency,
  IsoDate,
  IsoDateTime,
  Profile,
  ProfileBackup,
  RecurringRule,
  Transaction,
  Wallet,
  WalletKind,
} from '@/domain/types'
import type { CurrencyCode } from '@/domain/currency'
import { CATEGORY_BY_ID } from '@/domain/categories'
import { TRANSACTION_TYPE_BY_ID } from '@/domain/txTypes'
import { convert } from '@/domain/money'

/** Fixed so the generated data never depends on when this code runs. */
const REFERENCE_DATE: IsoDate = '2026-08-23'

/**
 * Today's date, for the app to hand to `buildDemoBackup` at runtime.
 *
 * The determinism note above is about the generator, not about the anchor the
 * caller chooses. Leaving the anchor on REFERENCE_DATE everywhere looked
 * deterministic and was, but it also meant the demo aged: the dashboard reads
 * income, expense and net balance for the current calendar month, so once the
 * wall clock passed August 2026 a first time visitor landed on three cards
 * reading zero while the table below them was full of transactions. The app
 * looked broken when it was working exactly as written.
 *
 * So the wall clock is read here, in one place, and only by the two runtime
 * call sites. Tests and screenshots keep calling `buildDemoBackup()` with no
 * argument, get REFERENCE_DATE, and stay byte for byte reproducible. The PRNG
 * seed does not move either way, so shifting the anchor slides the same
 * fourteen month story forward rather than generating a different one.
 */
export function todayIso(): IsoDate {
  const now = new Date()
  const pad = (n: number) => String(n).padStart(2, '0')
  return `${now.getFullYear()}-${pad(now.getMonth() + 1)}-${pad(now.getDate())}` as IsoDate
}

/** A literal, not a call to any clock. See the determinism note above. */
const SEED = 20260823

// ---------------------------------------------------------------------------
// Seeded PRNG and small helpers built on it.
// ---------------------------------------------------------------------------

/** mulberry32. Small, fast, and good enough for plausible looking demo data. */
function mulberry32(seed: number): () => number {
  let state = seed >>> 0
  return function random(): number {
    state = (state + 0x6d2b79f5) >>> 0
    let t = state
    t = Math.imul(t ^ (t >>> 15), t | 1)
    t ^= t + Math.imul(t ^ (t >>> 7), t | 61)
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296
  }
}

type Rand = () => number

function randInt(rand: Rand, min: number, max: number): number {
  return Math.floor(rand() * (max - min + 1)) + min
}

function chance(rand: Rand, p: number): boolean {
  return rand() < p
}

function pick<T>(rand: Rand, items: readonly T[]): T {
  const idx = Math.min(items.length - 1, Math.floor(rand() * items.length))
  return items[idx]!
}

function weightedPick<T>(rand: Rand, items: readonly (readonly [T, number])[]): T {
  const total = items.reduce((sum, [, w]) => sum + w, 0)
  let roll = rand() * total
  for (const [item, w] of items) {
    if (roll < w) return item
    roll -= w
  }
  return items[items.length - 1]![0]
}

// ---------------------------------------------------------------------------
// Deterministic ids and timestamps. See the top of file comment for why these
// do not come from src/data/ids.ts.
// ---------------------------------------------------------------------------

function makeIdFactory(): (prefix: string) => string {
  const counters = new Map<string, number>()
  return function demoId(prefix: string): string {
    const n = (counters.get(prefix) ?? 0) + 1
    counters.set(prefix, n)
    return `${prefix}_demo_${String(n).padStart(4, '0')}`
  }
}

function stampAt(date: IsoDate, hour: number, minute: number): IsoDateTime {
  return `${date}T${pad(hour)}:${pad(minute)}:00.000Z`
}

// ---------------------------------------------------------------------------
// Plain, timezone free date arithmetic. Every function below works purely
// through Date.UTC and getUTC*, which never consult the host's local
// timezone, so the same seed produces the same calendar on any machine.
// ---------------------------------------------------------------------------

function pad(n: number, len = 2): string {
  return String(n).padStart(len, '0')
}

function ymd(y: number, m: number, d: number): IsoDate {
  return `${y}-${pad(m)}-${pad(d)}`
}

function parseYmd(iso: IsoDate): { y: number; m: number; d: number } {
  const parts = iso.split('-')
  return { y: Number(parts[0]), m: Number(parts[1]), d: Number(parts[2]) }
}

function daysInMonth(y: number, m: number): number {
  return new Date(Date.UTC(y, m, 0)).getUTCDate()
}

/** 0 is Sunday, 6 is Saturday, matching Date#getUTCDay. */
function dayOfWeekUtc(iso: IsoDate): number {
  const { y, m, d } = parseYmd(iso)
  return new Date(Date.UTC(y, m - 1, d)).getUTCDay()
}

interface MonthSpan {
  year: number
  month: number
  /** Last day to generate transactions for. Equal to daysInMonth except in the final, partial month. */
  lastDay: number
  isCurrentMonth: boolean
}

/** Fourteen calendar months ending at `today`'s month, so both a month over month and a year over year view have data. */
function buildMonths(today: IsoDate): MonthSpan[] {
  const { y: ty, m: tm, d: td } = parseYmd(today)
  const months: MonthSpan[] = []
  for (let i = 13; i >= 0; i--) {
    const cursor = new Date(Date.UTC(ty, tm - 1 - i, 1))
    const year = cursor.getUTCFullYear()
    const month = cursor.getUTCMonth() + 1
    const isCurrentMonth = i === 0
    const lastDay = isCurrentMonth ? td : daysInMonth(year, month)
    months.push({ year, month, lastDay, isCurrentMonth })
  }
  return months
}

function monthKey(span: MonthSpan): string {
  return `${span.year}-${pad(span.month)}`
}

// ---------------------------------------------------------------------------
// Consistency guard. Cheap insurance against a typo pairing an expense row
// with an income category, which the rest of the app would trust blindly.
// ---------------------------------------------------------------------------

function assertConsistent(direction: Direction, typeId: string, categoryId: string): void {
  const type = TRANSACTION_TYPE_BY_ID.get(typeId)
  if (!type) throw new Error(`seed: unknown transaction type "${typeId}"`)
  if (type.direction !== direction) {
    throw new Error(`seed: type "${typeId}" implies direction "${type.direction}", got "${direction}"`)
  }
  const category = CATEGORY_BY_ID.get(categoryId)
  if (!category) throw new Error(`seed: unknown category "${categoryId}"`)
  // A transfer moves money between the person's own wallets rather than
  // recording income or an expense, so it has no income/expense flow of its
  // own; only income and expense rows need their category flow checked.
  if (direction !== 'transfer' && category.flow !== direction) {
    throw new Error(`seed: category "${categoryId}" has flow "${category.flow}", expected "${direction}"`)
  }
}

// ---------------------------------------------------------------------------
// The generator itself.
// ---------------------------------------------------------------------------

export function buildDemoBackup(today: IsoDate = REFERENCE_DATE): ProfileBackup {
  const rand = mulberry32(SEED)
  const mkId = makeIdFactory()
  const months = buildMonths(today)
  const spanStart = ymd(months[0]!.year, months[0]!.month, 1)

  const profileId = mkId('prf')

  // -- Profile ---------------------------------------------------------------
  // A fictional persona, never the repository owner's own details.
  const profile: Profile = {
    id: profileId,
    displayName: 'Raka Wicaksono (Demo Profile)',
    firstName: 'Raka',
    lastName: 'Wicaksono',
    email: 'demo@example.com',
    phoneNumber: '+62 812 0000 0000',
    dateOfBirth: '2004-03-14',
    sex: 'male',
    careerProfiling:
      'Final year electrical engineering student who takes on freelance web projects on the side.',
    aboutMe:
      'Lives in a kos near campus in Bandung. Splits time between coursework, a research assistantship and small freelance web projects for clients abroad.',
    attendingCollege: 'Institut Teknologi Nusantara Bandung',
    companyWorking: 'Freelance web developer',
    degreeIn: 'Teknik Elektro (Electrical Engineering)',
    baseCurrency: 'IDR',
    locale: 'en',
    pinHash: null,
    pinSalt: null,
    createdAt: stampAt(spanStart, 8, 0),
    isDemo: true,
  }

  // -- Wallets -----------------------------------------------------------
  // Five wallets covering every WalletKind as instructed, plus a sixth,
  // explicitly requested USD wallet: an overseas freelance client pays into
  // a Payoneer-style USD account, which is what gives the multi-currency
  // conversion code real data to run against instead of sitting unused.
  function wallet(kind: WalletKind, name: string, currency: CurrencyCode, openingBalance: number): Wallet {
    return {
      id: mkId('wal'),
      profileId,
      name,
      kind,
      currency,
      openingBalance,
      archived: false,
      createdAt: stampAt(spanStart, 8, 5),
    }
  }

  const walCash = wallet('cash', 'Dompet Tunai', 'IDR', 180_000)
  const walBank = wallet('bank', 'BCA Rekening Utama', 'IDR', 850_000)
  const walEwallet = wallet('ewallet', 'GoPay', 'IDR', 95_000)
  const walSavings = wallet('savings', 'BCA Tabungan Masa Depan', 'IDR', 4_500_000)
  const walCredit = wallet('credit', 'Kartu Kredit BCA', 'IDR', 0)
  const walUsd = wallet('bank', 'Payoneer USD Account', 'USD', 0)

  const wallets: Wallet[] = [walCash, walBank, walEwallet, walSavings, walCredit, walUsd]

  // -- Exchange rates ------------------------------------------------------
  // One USD rate per month, drifting slowly in a random walk within a
  // realistic band, so `findRate` has a real series to interpolate against
  // rather than a single flat number.
  const rates: ExchangeRate[] = []
  const monthlyUsdRate = new Map<string, number>()
  let usdRate = 15_850
  for (const span of months) {
    usdRate = Math.min(16_500, Math.max(15_500, usdRate + randInt(rand, -180, 180)))
    monthlyUsdRate.set(monthKey(span), usdRate)
    rates.push({
      id: mkId('rate'),
      profileId,
      currency: 'USD',
      rate: usdRate,
      date: ymd(span.year, span.month, 1),
      createdAt: stampAt(ymd(span.year, span.month, 1), 7, 0),
    })
  }
  function rateForMonth(span: MonthSpan): number {
    return monthlyUsdRate.get(monthKey(span))!
  }

  // -- Transactions --------------------------------------------------------
  const transactions: Transaction[] = []

  function mkTx(params: {
    walletId: string
    toWalletId?: string | null
    date: IsoDate
    direction: Direction
    typeId: string
    categoryId: string
    amount: number
    currency?: CurrencyCode
    /** Credit leg for a transfer whose destination uses another currency. */
    toAmount?: number | null
    rateToBase?: number
    description: string
    recurringId?: string | null
    hour?: number
    minute?: number
  }): Transaction {
    assertConsistent(params.direction, params.typeId, params.categoryId)
    const currency = params.currency ?? 'IDR'
    const hour = params.hour ?? randInt(rand, 7, 21)
    const minute = params.minute ?? randInt(rand, 0, 59)
    // No demo row may be dated in the future. Most generators below already
    // pick their day with Math.min(..., span.lastDay), but roughly a third use
    // a fixed or random day that was safe only because the old reference date
    // sat on the 23rd of its month. Anchoring the demo to the real today
    // exposed them: on the 5th of a month, a standing order written for the
    // 15th landed ten days ahead of the wall clock, and the app showed a
    // person money they had not spent yet. The clamp lives here, at the one
    // place every row passes through, rather than at the thirty call sites
    // that would each have to remember.
    //
    // ISO dates compare correctly as strings, which is why this is a plain
    // comparison and not a Date construction.
    const date = params.date > today ? today : params.date
    const tx: Transaction = {
      id: mkId('txn'),
      profileId,
      walletId: params.walletId,
      toWalletId: params.toWalletId ?? null,
      date,
      direction: params.direction,
      typeId: params.typeId,
      categoryId: params.categoryId,
      amount: Math.max(1, Math.round(params.amount)),
      currency,
      toAmount: params.toAmount ?? null,
      rateToBase: params.rateToBase ?? 1,
      description: params.description,
      recurringId: params.recurringId ?? null,
      createdAt: stampAt(date, hour, minute),
    }
    transactions.push(tx)
    return tx
  }

  // Rule ids are minted up front so the transactions generated below can
  // point back at the rule that "produced" them via recurringId, the same
  // way the real recurring engine would stamp a generated row.
  const ruleStipendId = mkId('rec')
  const ruleKosId = mkId('rec')
  const ruleMobileId = mkId('rec')
  const ruleSavingsId = mkId('rec')

  // -- Regular monthly rhythm ------------------------------------------
  // The kos rent and mobile data rules deliberately skip the current month:
  // their lastRunDate is left one period behind so both rules show up as
  // due and generate their next transaction the moment the demo profile is
  // first opened, instead of the app looking like it has been sitting idle.
  for (const span of months) {
    // Stipend: research assistant pay, day 1, every month including the current one.
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, 1),
      direction: 'income',
      typeId: 'incoming-transfer',
      categoryId: 'salary',
      amount: randInt(rand, 1_400_000, 1_600_000),
      description: 'Stipend asisten riset dosen',
      recurringId: ruleStipendId,
      hour: 9,
      minute: 0,
    })

    // Kos rent, day 5, skipped in the current month so the rule is due.
    if (!span.isCurrentMonth) {
      mkTx({
        walletId: walBank.id,
        date: ymd(span.year, span.month, 5),
        direction: 'expense',
        typeId: 'outgoing-transfer',
        categoryId: 'house-and-apartment-rent',
        amount: randInt(rand, 1_150_000, 1_300_000),
        description: 'Bayar kos bulanan',
        recurringId: ruleKosId,
        hour: 10,
        minute: 0,
      })
    }

    // Mobile data, day 7, skipped in the current month so the rule is due.
    if (!span.isCurrentMonth) {
      mkTx({
        walletId: walEwallet.id,
        date: ymd(span.year, span.month, 7),
        direction: 'expense',
        typeId: 'prepaid-top-up',
        categoryId: 'mobile-and-data',
        amount: randInt(rand, 50_000, 100_000),
        description: 'Paket data bulanan',
        recurringId: ruleMobileId,
        hour: 11,
        minute: 0,
      })
    }

    // Electricity token top up. Not every kos includes it in rent.
    mkTx({
      walletId: weightedPick(rand, [[walCash.id, 40], [walEwallet.id, 60]] as const),
      date: ymd(span.year, span.month, Math.min(10, span.lastDay)),
      direction: 'expense',
      typeId: 'bill-payment',
      categoryId: 'electricity-water-gas',
      amount: randInt(rand, 100_000, 250_000),
      description: 'Token listrik kos',
      hour: 19,
      minute: 30,
    })

    // Bank admin fee, common on Indonesian savings accounts.
    if (span.lastDay >= 25) {
      mkTx({
        walletId: walBank.id,
        date: ymd(span.year, span.month, 25),
        direction: 'expense',
        typeId: 'bank-charge',
        categoryId: 'cost-and-taxes',
        amount: randInt(rand, 5_500, 15_000),
        description: 'Biaya admin bulanan bank',
        hour: 6,
        minute: 0,
      })
    }

    // Automatic transfer into savings, every month including the current one.
    mkTx({
      walletId: walBank.id,
      toWalletId: walSavings.id,
      date: ymd(span.year, span.month, 15),
      direction: 'transfer',
      typeId: 'internal-transfer',
      categoryId: 'savings',
      amount: randInt(rand, 250_000, 350_000),
      description: 'Nabung otomatis ke tabungan',
      recurringId: ruleSavingsId,
      hour: 8,
      minute: 30,
    })

    // Freelance web project, paid in USD into the Payoneer wallet. Not every
    // month has a project land.
    if (chance(rand, 0.7)) {
      const day = Math.min(randInt(rand, 18, 27), span.lastDay)
      const rate = rateForMonth(span)
      const idrTarget = randInt(rand, 2_000_000, 8_000_000)
      const usdMinor = Math.round((idrTarget / rate) * 100)
      mkTx({
        walletId: walUsd.id,
        date: ymd(span.year, span.month, day),
        direction: 'income',
        typeId: 'incoming-transfer',
        categoryId: 'business-profit',
        amount: usdMinor,
        currency: 'USD',
        rateToBase: rate + randInt(rand, -30, 30),
        description: pick(rand, ['Bayaran project website client luar negeri', 'Freelance landing page payment', 'Payment for freelance dev work']),
        hour: 14,
        minute: 0,
      })

      // Payoneer style service fee on some of the same months.
      if (chance(rand, 0.5)) {
        mkTx({
          walletId: walUsd.id,
          date: ymd(span.year, span.month, Math.min(day + 1, span.lastDay)),
          direction: 'expense',
          typeId: 'fee-payment',
          categoryId: 'cost-and-taxes',
          amount: randInt(rand, 300, 1_500),
          currency: 'USD',
          rateToBase: rate + randInt(rand, -30, 30),
          description: 'Payoneer service fee',
          hour: 14,
          minute: 5,
        })
      }
    }

    // Allowance from parents, not every month.
    if (chance(rand, 0.4)) {
      const day = Math.min(randInt(rand, 2, 8), span.lastDay)
      const toCash = chance(rand, 0.5)
      mkTx({
        walletId: toCash ? walCash.id : walBank.id,
        date: ymd(span.year, span.month, day),
        direction: 'income',
        typeId: toCash ? 'incoming-cash' : 'incoming-transfer',
        categoryId: 'allowance',
        amount: randInt(rand, 300_000, 600_000),
        description: 'Uang saku dari orang tua',
        hour: 12,
        minute: 0,
      })
    }

    // Interest on the savings wallet, paid out quarterly.
    if (span.month % 3 === 0) {
      mkTx({
        walletId: walSavings.id,
        date: ymd(span.year, span.month, Math.min(randInt(rand, 25, 28), span.lastDay)),
        direction: 'income',
        typeId: 'interest',
        categoryId: 'interests',
        amount: randInt(rand, 5_000, 25_000),
        description: 'Bunga tabungan',
        hour: 5,
        minute: 0,
      })
    }

    // E-wallet cashback, occasional.
    if (chance(rand, 0.3)) {
      mkTx({
        walletId: walEwallet.id,
        date: ymd(span.year, span.month, Math.min(randInt(rand, 1, span.lastDay), span.lastDay)),
        direction: 'income',
        typeId: 'wallet-cashback',
        categoryId: 'additional-income',
        amount: randInt(rand, 2_000, 15_000),
        description: 'Cashback GoPay',
        hour: 20,
        minute: 0,
      })
    }

    // Occasional refund, small.
    if (chance(rand, 0.15)) {
      mkTx({
        walletId: walEwallet.id,
        date: ymd(span.year, span.month, Math.min(randInt(rand, 1, span.lastDay), span.lastDay)),
        direction: 'income',
        typeId: 'qr-payment-refund',
        categoryId: 'refunds',
        amount: randInt(rand, 10_000, 80_000),
        description: 'Refund pesanan online',
        hour: 16,
        minute: 0,
      })
    }

    // Top up from bank into the e-wallet. A genuine transfer between the
    // person's own wallets, not income or an expense.
    if (chance(rand, 0.55)) {
      mkTx({
        walletId: walBank.id,
        toWalletId: walEwallet.id,
        date: ymd(span.year, span.month, Math.min(randInt(rand, 1, span.lastDay), span.lastDay)),
        direction: 'transfer',
        typeId: 'internal-transfer',
        categoryId: 'top-up-ewallet-cards',
        amount: randInt(rand, 100_000, 300_000),
        description: 'Top up GoPay dari BCA',
        hour: 9,
        minute: 45,
      })
    }
  }

  // -- Daily-ish spending ---------------------------------------------
  const mealWeekdayWallets = [[walCash.id, 50], [walEwallet.id, 35], [walBank.id, 15]] as const
  const diningWeekendWallets = [[walEwallet.id, 50], [walBank.id, 30], [walCash.id, 20]] as const
  const smallSpendWallets = [[walCash.id, 45], [walEwallet.id, 45], [walBank.id, 10]] as const

  const mealDescriptions = ['Nasi padang warteg', 'Makan siang di kantin kampus', 'Nasi goreng dekat kos', 'Sarapan bubur ayam', 'Makan malam warteg', 'Ayam geprek deket kampus']
  const diningDescriptions = ['Nongkrong makan di resto sama temen', 'Dinner sama temen kuliah', 'Weekend brunch', 'Makan bareng anak kos']
  const snackDescriptions = ['Kopi kekinian', 'Es teh dan gorengan', 'Cemilan malam', 'Boba after class']
  const groceryDescriptions = ['Belanja bulanan Indomaret', 'Belanja mingguan Alfamart', 'Beli galon dan sabun']
  const rideDescriptions = ['Ojek online ke kampus', 'Grab ke stasiun', 'Angkot pulang kos']
  const fuelDescriptions = ['Isi bensin motor']
  const parkingDescriptions = ['Parkir kampus', 'Parkir mall']

  function paymentType(): string {
    return chance(rand, 0.65) ? 'qr-payment' : 'payment-with-card'
  }

  for (const span of months) {
    for (let d = 1; d <= span.lastDay; d++) {
      const date = ymd(span.year, span.month, d)
      const dow = dayOfWeekUtc(date)
      const isWeekend = dow === 0 || dow === 6

      if (!isWeekend && chance(rand, 0.88)) {
        mkTx({
          walletId: weightedPick(rand, mealWeekdayWallets),
          date,
          direction: 'expense',
          typeId: paymentType(),
          categoryId: 'daily-meal',
          amount: randInt(rand, 15_000, 35_000),
          description: pick(rand, mealDescriptions),
        })
      }
      if (isWeekend && chance(rand, 0.65)) {
        mkTx({
          walletId: weightedPick(rand, diningWeekendWallets),
          date,
          direction: 'expense',
          typeId: paymentType(),
          categoryId: 'dining-out',
          amount: randInt(rand, 35_000, 90_000),
          description: pick(rand, diningDescriptions),
        })
      }

      const snackChance = isWeekend ? 0.3 : 0.22
      if (chance(rand, snackChance)) {
        mkTx({
          walletId: weightedPick(rand, smallSpendWallets),
          date,
          direction: 'expense',
          typeId: paymentType(),
          categoryId: 'snacks-and-drinks',
          amount: randInt(rand, 10_000, 30_000),
          description: pick(rand, snackDescriptions),
        })
      }

      const rideChance = isWeekend ? 0.18 : 0.5
      if (chance(rand, rideChance)) {
        mkTx({
          walletId: weightedPick(rand, smallSpendWallets),
          date,
          direction: 'expense',
          typeId: paymentType(),
          categoryId: 'daily-transportations',
          amount: randInt(rand, 8_000, 25_000),
          description: pick(rand, rideDescriptions),
        })
      }

      if (chance(rand, 1 / 7)) {
        mkTx({
          walletId: weightedPick(rand, smallSpendWallets),
          date,
          direction: 'expense',
          typeId: paymentType(),
          categoryId: 'gasolines',
          amount: randInt(rand, 20_000, 35_000),
          description: pick(rand, fuelDescriptions),
        })
      }

      if (chance(rand, 0.06)) {
        mkTx({
          walletId: weightedPick(rand, smallSpendWallets),
          date,
          direction: 'expense',
          typeId: paymentType(),
          categoryId: 'parking-and-toll-fee',
          amount: randInt(rand, 2_000, 10_000),
          description: pick(rand, parkingDescriptions),
        })
      }

      if (chance(rand, 1 / 9)) {
        mkTx({
          walletId: weightedPick(rand, [[walCash.id, 30], [walEwallet.id, 40], [walBank.id, 30]] as const),
          date,
          direction: 'expense',
          typeId: paymentType(),
          categoryId: 'groceries',
          amount: randInt(rand, 50_000, 150_000),
          description: pick(rand, groceryDescriptions),
        })
      }
    }
  }

  // -- Small variety pass -----------------------------------------------
  // A handful of extra categories each month, the sort of one-off spending
  // that gives every screen in the app something to render instead of only
  // the same six or seven categories over and over.
  interface ExtraKind {
    categoryId: string
    min: number
    max: number
    wallets: readonly string[]
    descriptions: readonly string[]
  }
  const extraPool: readonly ExtraKind[] = [
    { categoryId: 'books', min: 40_000, max: 150_000, wallets: [walBank.id, walEwallet.id], descriptions: ['Beli buku bekas', 'Buku referensi kuliah'] },
    { categoryId: 'games', min: 20_000, max: 100_000, wallets: [walEwallet.id], descriptions: ['Top up game', 'Beli item game'] },
    { categoryId: 'movies-and-music', min: 25_000, max: 60_000, wallets: [walBank.id, walEwallet.id], descriptions: ['Langganan Spotify', 'Nonton di bioskop'] },
    { categoryId: 'hobby', min: 30_000, max: 150_000, wallets: [walCash.id, walEwallet.id], descriptions: ['Beli alat gambar', 'Peralatan hobi'] },
    { categoryId: 'personal-care', min: 20_000, max: 80_000, wallets: [walCash.id, walEwallet.id], descriptions: ['Potong rambut', 'Skincare'] },
    { categoryId: 'medicines', min: 15_000, max: 60_000, wallets: [walCash.id, walEwallet.id], descriptions: ['Beli obat warung', 'Vitamin'] },
    { categoryId: 'doctor-and-hospital', min: 50_000, max: 300_000, wallets: [walBank.id], descriptions: ['Periksa dokter umum', 'Cek kesehatan klinik kampus'] },
    { categoryId: 'fashions', min: 80_000, max: 300_000, wallets: [walBank.id, walEwallet.id], descriptions: ['Beli baju baru', 'Sepatu baru'] },
    { categoryId: 'home-appliances', min: 50_000, max: 250_000, wallets: [walBank.id], descriptions: ['Beli rice cooker mini', 'Kipas angin kos'] },
    { categoryId: 'gadget-and-electronics', min: 50_000, max: 400_000, wallets: [walBank.id], descriptions: ['Beli mouse baru', 'Charger laptop'] },
    { categoryId: 'sport-activities', min: 15_000, max: 50_000, wallets: [walCash.id, walEwallet.id], descriptions: ['Futsal bareng temen', 'Sewa lapangan badminton'] },
    { categoryId: 'household', min: 20_000, max: 80_000, wallets: [walCash.id, walEwallet.id], descriptions: ['Beli deterjen', 'Perlengkapan kos'] },
    { categoryId: 'classes-and-workshops', min: 50_000, max: 300_000, wallets: [walBank.id], descriptions: ['Kursus online', 'Workshop web development'] },
    { categoryId: 'charity', min: 10_000, max: 50_000, wallets: [walCash.id, walEwallet.id], descriptions: ['Sedekah Jumat', 'Donasi'] },
  ]
  for (const span of months) {
    const count = randInt(rand, 1, 3)
    for (let i = 0; i < count; i++) {
      const kind = pick(rand, extraPool)
      const day = Math.min(randInt(rand, 1, span.lastDay), span.lastDay)
      mkTx({
        walletId: pick(rand, kind.wallets),
        date: ymd(span.year, span.month, day),
        direction: 'expense',
        typeId: paymentType(),
        categoryId: kind.categoryId,
        amount: randInt(rand, kind.min, kind.max),
        description: pick(rand, kind.descriptions),
      })
    }
  }

  // -- Irregular, larger events ------------------------------------------
  // Fixed month indices (0 = fourteen months back, 13 = the current month)
  // chosen so the calendar lines up with an Indonesian academic year: a
  // tuition payment at the start of each semester, Lebaran spending in the
  // month it actually falls in relative to the reference date, and a couple
  // of trips and a laptop repair spread through the middle of the span.
  function monthAt(indexFromStart: number): MonthSpan {
    return months[indexFromStart]!
  }

  // Odd semester tuition, right after the academic year starts.
  {
    const span = monthAt(1)
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, randInt(rand, 10, 20)),
      direction: 'expense',
      typeId: 'outgoing-transfer',
      categoryId: 'tuition-fee',
      amount: randInt(rand, 3_000_000, 5_500_000),
      description: 'Bayar UKT semester ganjil',
      hour: 10,
      minute: 0,
    })
  }

  // Laptop repair.
  {
    const span = monthAt(4)
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, randInt(rand, 5, 25)),
      direction: 'expense',
      typeId: 'payment-with-card',
      categoryId: 'handheld-electric-device',
      amount: randInt(rand, 300_000, 900_000),
      description: 'Servis laptop, ganti keyboard',
      hour: 15,
      minute: 0,
    })
  }

  // Year end holiday trip.
  function trip(index: number, savingsFunded: boolean): void {
    const span = monthAt(index)
    const startDay = randInt(rand, 3, Math.max(4, span.lastDay - 6))
    if (savingsFunded) {
      mkTx({
        walletId: walSavings.id,
        toWalletId: walBank.id,
        date: ymd(span.year, span.month, Math.max(1, startDay - 2)),
        direction: 'transfer',
        typeId: 'internal-transfer',
        categoryId: 'savings',
        amount: randInt(rand, 500_000, 1_500_000),
        description: 'Tarik tabungan buat liburan',
        hour: 9,
        minute: 0,
      })
    }
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, startDay),
      direction: 'expense',
      typeId: 'payment-with-card',
      categoryId: 'transports-on-vacations',
      amount: randInt(rand, 150_000, 600_000),
      description: 'Tiket kereta liburan ke Jogja',
      hour: 6,
      minute: 0,
    })
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, Math.min(startDay + 1, span.lastDay)),
      direction: 'expense',
      typeId: 'payment-with-card',
      categoryId: 'hotel-and-villa',
      amount: randInt(rand, 400_000, 1_200_000),
      description: 'Hotel liburan',
      hour: 14,
      minute: 0,
    })
    mkTx({
      walletId: weightedPick(rand, smallSpendWallets),
      date: ymd(span.year, span.month, Math.min(startDay + 1, span.lastDay)),
      direction: 'expense',
      typeId: paymentType(),
      categoryId: 'attractions-and-tours',
      amount: randInt(rand, 30_000, 150_000),
      description: 'Jajan selama liburan',
      hour: 17,
      minute: 0,
    })
    mkTx({
      walletId: weightedPick(rand, diningWeekendWallets),
      date: ymd(span.year, span.month, Math.min(startDay + 2, span.lastDay)),
      direction: 'expense',
      typeId: paymentType(),
      categoryId: 'dining-out',
      amount: randInt(rand, 60_000, 150_000),
      description: 'Makan enak pas liburan',
      hour: 19,
      minute: 0,
    })
  }
  trip(5, false)
  trip(10, true)

  // Lebaran, the month it actually falls in relative to the reference date.
  {
    const span = monthAt(8)
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, randInt(rand, 5, 10)),
      direction: 'expense',
      typeId: 'outgoing-transfer',
      categoryId: 'gifting',
      amount: randInt(rand, 150_000, 300_000),
      description: 'THR buat adik',
      hour: 10,
      minute: 0,
    })
    mkTx({
      walletId: weightedPick(rand, smallSpendWallets),
      date: ymd(span.year, span.month, randInt(rand, 8, 14)),
      direction: 'expense',
      typeId: paymentType(),
      categoryId: 'fashions',
      amount: randInt(rand, 150_000, 500_000),
      description: 'Baju lebaran baru',
      hour: 16,
      minute: 0,
    })
    mkTx({
      walletId: walEwallet.id,
      date: ymd(span.year, span.month, randInt(rand, 12, 16)),
      direction: 'expense',
      typeId: 'qr-payment',
      categoryId: 'charity',
      amount: randInt(rand, 30_000, 80_000),
      description: 'Zakat fitrah',
      hour: 8,
      minute: 0,
    })
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, randInt(rand, 15, 20)),
      direction: 'expense',
      typeId: 'payment-with-card',
      categoryId: 'transports-on-vacations',
      amount: randInt(rand, 200_000, 500_000),
      description: 'Tiket mudik ke kampung halaman',
      hour: 7,
      minute: 0,
    })
    mkTx({
      walletId: weightedPick(rand, smallSpendWallets),
      date: ymd(span.year, span.month, randInt(rand, 20, Math.min(25, span.lastDay))),
      direction: 'expense',
      typeId: paymentType(),
      categoryId: 'gifting',
      amount: randInt(rand, 50_000, 150_000),
      description: 'Oleh oleh mudik',
      hour: 18,
      minute: 0,
    })
  }

  // Vehicle maintenance, twice across the span.
  for (const index of [3, 11]) {
    const span = monthAt(index)
    mkTx({
      walletId: weightedPick(rand, [[walCash.id, 60], [walBank.id, 40]] as const),
      date: ymd(span.year, span.month, randInt(rand, 5, Math.max(6, span.lastDay - 2))),
      direction: 'expense',
      typeId: 'payment-with-card',
      categoryId: 'vehicle-maintenance',
      amount: randInt(rand, 100_000, 400_000),
      description: 'Servis motor rutin',
      hour: 13,
      minute: 0,
    })
  }

  // Even semester tuition.
  {
    const span = monthAt(7)
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, randInt(rand, 5, 15)),
      direction: 'expense',
      typeId: 'outgoing-transfer',
      categoryId: 'tuition-fee',
      amount: randInt(rand, 3_000_000, 5_500_000),
      description: 'Bayar UKT semester genap',
      hour: 10,
      minute: 0,
    })
  }

  // Thesis defense administration fee, in the current month, since this is a
  // final year student getting close to graduating.
  {
    const span = monthAt(13)
    mkTx({
      walletId: walBank.id,
      date: ymd(span.year, span.month, Math.min(randInt(rand, 1, 20), span.lastDay)),
      direction: 'expense',
      typeId: 'fee-payment',
      categoryId: 'cost-and-taxes',
      amount: randInt(rand, 300_000, 750_000),
      description: 'Biaya sidang skripsi',
      hour: 11,
      minute: 0,
    })
  }

  // -- Recurring rules -----------------------------------------------------
  const lastMonth = months[13]!
  const secondLastMonth = months[12]!

  function recurringRule(params: {
    id: string
    name: string
    walletId: string
    toWalletId: string | null
    direction: Direction
    typeId: string
    categoryId: string
    amount: number
    currency: CurrencyCode
    description: string
    startDay: number
    lastRunDate: IsoDate
  }): RecurringRule {
    return {
      id: params.id,
      profileId,
      name: params.name,
      frequency: 'monthly' as Frequency,
      interval: 1,
      startDate: ymd(months[0]!.year, months[0]!.month, params.startDay),
      endDate: null,
      lastRunDate: params.lastRunDate,
      active: true,
      template: {
        walletId: params.walletId,
        toWalletId: params.toWalletId,
        direction: params.direction,
        typeId: params.typeId,
        categoryId: params.categoryId,
        amount: params.amount,
        currency: params.currency,
        description: params.description,
      },
      createdAt: stampAt(spanStart, 8, 0),
    }
  }

  const recurring: RecurringRule[] = [
    recurringRule({
      id: ruleStipendId,
      name: 'Stipend asisten riset',
      walletId: walBank.id,
      toWalletId: null,
      direction: 'income',
      typeId: 'incoming-transfer',
      categoryId: 'salary',
      amount: 1_500_000,
      currency: 'IDR',
      description: 'Stipend asisten riset dosen',
      startDay: 1,
      // Already ran for the current month, matches the row generated above.
      lastRunDate: ymd(lastMonth.year, lastMonth.month, 1),
    }),
    recurringRule({
      id: ruleKosId,
      name: 'Bayar kos',
      walletId: walBank.id,
      toWalletId: null,
      direction: 'expense',
      typeId: 'outgoing-transfer',
      categoryId: 'house-and-apartment-rent',
      amount: 1_200_000,
      currency: 'IDR',
      description: 'Bayar kos bulanan',
      startDay: 5,
      // Not yet run for the current month: this rule is due on first load.
      lastRunDate: ymd(secondLastMonth.year, secondLastMonth.month, 5),
    }),
    recurringRule({
      id: ruleMobileId,
      name: 'Paket data',
      walletId: walEwallet.id,
      toWalletId: null,
      direction: 'expense',
      typeId: 'prepaid-top-up',
      categoryId: 'mobile-and-data',
      amount: 75_000,
      currency: 'IDR',
      description: 'Paket data bulanan',
      startDay: 7,
      // Not yet run for the current month: this rule is due on first load.
      lastRunDate: ymd(secondLastMonth.year, secondLastMonth.month, 7),
    }),
    recurringRule({
      id: ruleSavingsId,
      name: 'Nabung otomatis',
      walletId: walBank.id,
      toWalletId: walSavings.id,
      direction: 'transfer',
      typeId: 'internal-transfer',
      categoryId: 'savings',
      amount: 300_000,
      currency: 'IDR',
      description: 'Nabung otomatis ke tabungan',
      startDay: 15,
      lastRunDate: ymd(lastMonth.year, lastMonth.month, 15),
    }),
  ]

  // -- Budgets --------------------------------------------------------------
  // Every limit is derived directly from what was actually spent, at a
  // chosen ratio to the limit, so the resulting state (under, approaching or
  // over) is exact by construction instead of hoping hand picked numbers
  // land the right side of a threshold.
  const ALERT_THRESHOLD = 0.8

  function baseMinor(tx: Transaction): number {
    return convert({ minor: tx.amount, currency: tx.currency }, 'IDR', tx.rateToBase).minor
  }

  function spentFor(period: BudgetPeriod, periodKey: string, categoryId: string | null): number {
    return transactions
      .filter((t) => t.direction === 'expense')
      .filter((t) => (period === 'monthly' ? t.date.slice(0, 7) : t.date.slice(0, 4)) === periodKey)
      .filter((t) => categoryId === null || t.categoryId === categoryId)
      .reduce((sum, t) => sum + baseMinor(t), 0)
  }

  function limitForRatio(spent: number, ratio: number): number {
    return Math.max(1, Math.round(spent / ratio))
  }

  const currentMonthKey = monthKey(lastMonth)
  const previousMonthKey = monthKey(secondLastMonth)
  const currentYearKey = String(lastMonth.year)

  function budget(params: {
    period: BudgetPeriod
    periodKey: string
    categoryId: string | null
    ratio: number
    description: string
    target?: number | null
  }): Budget {
    const spent = spentFor(params.period, params.periodKey, params.categoryId)
    return {
      id: mkId('bud'),
      profileId,
      period: params.period,
      periodKey: params.periodKey,
      categoryId: params.categoryId,
      limit: limitForRatio(spent, params.ratio),
      target: params.target ?? null,
      description: params.description,
      alertThreshold: ALERT_THRESHOLD,
      alertsEnabled: true,
      createdAt: stampAt(spanStart, 8, 0),
    }
  }

  const budgets: Budget[] = [
    budget({
      period: 'monthly',
      periodKey: currentMonthKey,
      categoryId: null,
      ratio: 0.9,
      description: 'Overall spending this month',
      target: 500_000,
    }),
    budget({
      period: 'monthly',
      periodKey: currentMonthKey,
      categoryId: 'daily-meal',
      ratio: 0.5,
      description: 'Daily meals this month',
    }),
    budget({
      period: 'monthly',
      periodKey: currentMonthKey,
      categoryId: 'snacks-and-drinks',
      ratio: 1.3,
      description: 'Snacks and drinks this month',
    }),
    budget({
      period: 'monthly',
      periodKey: previousMonthKey,
      categoryId: null,
      ratio: 0.55,
      description: 'Overall spending last month',
    }),
    budget({
      period: 'monthly',
      periodKey: previousMonthKey,
      categoryId: 'daily-transportations',
      ratio: 1.25,
      description: 'Daily transport last month',
    }),
    budget({
      period: 'yearly',
      periodKey: currentYearKey,
      categoryId: null,
      ratio: 0.85,
      description: 'Overall spending this year',
    }),
    budget({
      period: 'yearly',
      periodKey: currentYearKey,
      categoryId: 'hotel-and-villa',
      ratio: 0.4,
      description: 'Hotels and holiday stays this year',
    }),
  ]

  // -- Funding pass ----------------------------------------------------------
  // Income lands where it is actually earned: the stipend and freelance
  // invoices arrive in the bank and Payoneer accounts, while day to day
  // spending leaves from cash and the e-wallet. Generating those two sides
  // independently leaves the spending wallets deeply negative and strands the
  // dollars overseas, which is not a rendering problem, it is the demo showing
  // a life nobody could actually have lived.
  //
  // So money gets moved the way a person moves it. Walking the ledger in date
  // order, whenever a wallet is about to go short it is topped up first: cash
  // and the e-wallet from the bank, and the bank itself from the USD account,
  // which is what a Payoneer withdrawal really is. Top ups are rounded to
  // notes a person would actually withdraw rather than to the exact shortfall.
  fundWallets({
    transactions,
    wallets,
    mkTx,
    rateOn: (date) => monthlyUsdRate.get(date.slice(0, 7)) ?? 16_000,
    cashId: walCash.id,
    ewalletId: walEwallet.id,
    bankId: walBank.id,
    usdId: walUsd.id,
    savingsId: walSavings.id,
  })

  // Routing money around covers most of it, but the opening month has expenses
  // that predate any income at all, and no amount of transferring fixes a
  // ledger that starts at zero. Whatever is still short becomes the wallet's
  // opening balance, which is simply what the persona had on the day the
  // history begins. Deriving it from the lowest point actually reached is more
  // honest than picking a round number and hoping it clears.
  raiseOpeningBalances(wallets, transactions)

  transactions.sort((a, b) => a.date.localeCompare(b.date) || a.createdAt.localeCompare(b.createdAt))

  return {
    version: 1,
    exportedAt: stampAt(today, 8, 0),
    profile,
    wallets,
    transactions,
    budgets,
    recurring,
    rates,
  }
}

/** Round up to the next multiple, so top ups look like real withdrawals. */
function roundUpTo(value: number, multiple: number): number {
  return Math.ceil(value / multiple) * multiple
}

interface FundingContext {
  transactions: Transaction[]
  wallets: Wallet[]
  mkTx: (params: {
    walletId: string
    toWalletId?: string | null
    date: IsoDate
    direction: Direction
    typeId: string
    categoryId: string
    amount: number
    currency?: CurrencyCode
    toAmount?: number | null
    rateToBase?: number
    description: string
    recurringId?: string | null
    hour?: number
    minute?: number
  }) => Transaction
  rateOn: (date: IsoDate) => number
  cashId: string
  ewalletId: string
  bankId: string
  usdId: string
  savingsId: string
}

function fundWallets(ctx: FundingContext): void {
  const { transactions, wallets, mkTx, rateOn, cashId, ewalletId, bankId, usdId, savingsId } = ctx

  const balance = new Map<string, number>()
  for (const wallet of wallets) balance.set(wallet.id, wallet.openingBalance)

  const adjust = (id: string, delta: number): void => {
    balance.set(id, (balance.get(id) ?? 0) + delta)
  }

  const apply = (tx: Transaction): void => {
    if (tx.direction === 'transfer') {
      adjust(tx.walletId, -tx.amount)
      if (tx.toWalletId) adjust(tx.toWalletId, tx.toAmount ?? tx.amount)
      return
    }
    adjust(tx.walletId, tx.direction === 'income' ? tx.amount : -tx.amount)
  }

  // Withdraw from the USD account into the bank. The dollars are debited and
  // rupiah credited, so the two legs carry different figures, which is exactly
  // what `toAmount` exists for.
  const withdrawUsd = (date: IsoDate, neededIdr: number): void => {
    const rate = rateOn(date)
    // Both figures are in minor units, and the dollar account keeps cents
    // while rupiah has none, so the scales have to be reconciled explicitly.
    const availableCents = balance.get(usdId) ?? 0
    if (availableCents <= 0) return
    const neededCents = Math.ceil((neededIdr / rate) * 100)
    // Withdraw in round fifty dollar steps, the way a person actually would.
    const wantCents = Math.min(availableCents, roundUpTo(neededCents, 5_000))
    if (wantCents <= 0) return
    const creditIdr = Math.round((wantCents / 100) * rate)
    const tx = mkTx({
      walletId: usdId,
      toWalletId: bankId,
      date,
      direction: 'transfer',
      typeId: 'currency-exchange',
      categoryId: 'others',
      amount: wantCents,
      currency: 'USD',
      toAmount: creditIdr,
      rateToBase: rate,
      description: 'Withdraw Payoneer ke BCA',
      hour: 10,
      minute: 15,
    })
    apply(tx)
  }

  const topUpFromBank = (date: IsoDate, targetId: string, needed: number, label: string): void => {
    const amount = roundUpTo(Math.max(needed, 200_000), 50_000)
    if ((balance.get(bankId) ?? 0) < amount) withdrawUsd(date, amount)
    const tx = mkTx({
      walletId: bankId,
      toWalletId: targetId,
      date,
      direction: 'transfer',
      typeId: 'internal-transfer',
      categoryId: 'others',
      amount,
      description: label,
      hour: 7,
      minute: 30,
    })
    apply(tx)
  }

  // Walk a snapshot in date order. New funding rows are appended to the live
  // array by `mkTx`, so iterating the snapshot avoids processing them twice.
  const ordered = [...transactions].sort(
    (a, b) => a.date.localeCompare(b.date) || a.createdAt.localeCompare(b.createdAt),
  )

  for (const tx of ordered) {
    const spendsFrom = tx.direction === 'transfer' ? tx.walletId : tx.walletId
    const outgoing = tx.direction === 'income' ? 0 : tx.amount

    if (outgoing > 0 && (spendsFrom === cashId || spendsFrom === ewalletId)) {
      const shortfall = outgoing - (balance.get(spendsFrom) ?? 0)
      if (shortfall > 0) {
        topUpFromBank(
          tx.date,
          spendsFrom,
          shortfall,
          spendsFrom === cashId ? 'Tarik tunai dari ATM' : 'Top up GoPay dari BCA',
        )
      }
    }

    if (outgoing > 0 && spendsFrom === bankId && tx.currency === 'IDR') {
      let shortfall = outgoing - (balance.get(bankId) ?? 0)
      if (shortfall > 0) {
        withdrawUsd(tx.date, shortfall)
        shortfall = outgoing - (balance.get(bankId) ?? 0)
      }
      // Early on there are no dollars yet, because the first freelance invoice
      // has not been raised. Dipping into savings is what a person does then,
      // and it is what the savings wallet is there for.
      if (shortfall > 0 && (balance.get(savingsId) ?? 0) > 0) {
        const amount = Math.min(balance.get(savingsId) ?? 0, roundUpTo(shortfall, 100_000))
        if (amount > 0) {
          apply(mkTx({
            walletId: savingsId,
            toWalletId: bankId,
            date: tx.date,
            direction: 'transfer',
            typeId: 'internal-transfer',
            categoryId: 'others',
            amount,
            description: 'Ambil dari tabungan',
            hour: 7,
            minute: 45,
          }))
        }
      }
    }

    apply(tx)
  }
}

/**
 * Lift each wallet's opening balance until its running balance never goes
 * negative. A cash wallet at minus nine million is not a rendering bug, it is
 * the demo describing a life nobody could have lived.
 */
function raiseOpeningBalances(wallets: Wallet[], transactions: readonly Transaction[]): void {
  const ordered = [...transactions].sort(
    (a, b) => a.date.localeCompare(b.date) || a.createdAt.localeCompare(b.createdAt),
  )

  for (const wallet of wallets) {
    let running = wallet.openingBalance
    let lowest = running

    for (const tx of ordered) {
      if (tx.direction === 'transfer') {
        if (tx.walletId === wallet.id) running -= tx.amount
        if (tx.toWalletId === wallet.id) running += tx.toAmount ?? tx.amount
      } else if (tx.walletId === wallet.id) {
        running += tx.direction === 'income' ? tx.amount : -tx.amount
      } else {
        continue
      }
      if (running < lowest) lowest = running
    }

    if (lowest < 0) {
      // Round to a figure a person would recognise as a starting balance.
      const step = wallet.currency === 'IDR' ? 100_000 : 10_000
      wallet.openingBalance += Math.ceil(-lowest / step) * step
    }
  }
}
