/**
 * CSV export of our own transactions, and a general RFC 4180 reader used to
 * import a bank's own statement export.
 *
 * These two directions are deliberately not mirror images. Our export always
 * knows every field (wallet, category, type); a bank statement never does, so
 * import works from whatever columns are actually present plus a handful of
 * defaults supplied by the caller.
 */

import { format, isValid, parse, parseISO } from 'date-fns'
import type { CurrencyCode } from './currency'
import type { Direction, ExchangeRate, IsoDate, Transaction } from './types'
import { fromMajor, money, toMajor } from './money'
import { findRate } from './rates'

/**
 * Column order written by transactionsToCsv, kept in one place so the file
 * and any future reader of our own exports agree on what column N means.
 */
export const EXPORT_COLUMNS = [
  'date', 'direction', 'walletId', 'toWalletId', 'categoryId', 'typeId', 'amount', 'currency', 'description',
] as const

function escapeField(raw: string): string {
  // RFC 4180: a field containing a comma, a double quote or a line break is
  // wrapped in double quotes, and any double quote inside it is doubled.
  if (/[",\r\n]/.test(raw)) return `"${raw.replace(/"/g, '""')}"`
  return raw
}

export interface CsvExportOptions {
  /** Write a header row naming EXPORT_COLUMNS. Defaults to true. */
  header?: boolean
}

export function transactionsToCsv(
  transactions: readonly Transaction[],
  opts: CsvExportOptions = {},
): string {
  const lines: string[] = []
  if (opts.header ?? true) lines.push(EXPORT_COLUMNS.join(','))

  for (const tx of transactions) {
    const row = [
      tx.date,
      tx.direction,
      tx.walletId,
      tx.toWalletId ?? '',
      tx.categoryId,
      tx.typeId,
      // Major units, not minor: a spreadsheet has no idea rupiah has zero
      // decimal digits and dollars have two, so the file has to already be
      // in the units a person reads.
      String(toMajor(money(tx.amount, tx.currency))),
      tx.currency,
      tx.description,
    ]
    lines.push(row.map(escapeField).join(','))
  }

  return lines.join('\r\n')
}

/**
 * A correct RFC 4180 reader: quoted fields can contain commas, doubled quotes
 * and embedded line breaks, and both CRLF and bare LF line endings are
 * accepted, since real exports mix them depending on what produced the file.
 */
export function parseCsv(text: string): string[][] {
  const rows: string[][] = []
  let row: string[] = []
  let field = ''
  let inQuotes = false
  let i = 0

  const endField = () => { row.push(field); field = '' }
  const endRow = () => { endField(); rows.push(row); row = [] }

  while (i < text.length) {
    const ch = text[i]!

    if (inQuotes) {
      if (ch === '"') {
        if (text[i + 1] === '"') {
          field += '"'
          i += 2
          continue
        }
        inQuotes = false
        i += 1
        continue
      }
      field += ch
      i += 1
      continue
    }

    if (ch === '"') { inQuotes = true; i += 1; continue }
    if (ch === ',') { endField(); i += 1; continue }
    if (ch === '\r') {
      if (text[i + 1] === '\n') i += 1
      endRow()
      i += 1
      continue
    }
    if (ch === '\n') { endRow(); i += 1; continue }
    field += ch
    i += 1
  }

  // A final line with no trailing newline still counts as a row. An input
  // that ends cleanly on a newline should not produce a phantom empty row
  // after it, which is why this check looks at whether anything was actually
  // read since the last row ended.
  if (field !== '' || row.length > 0) endRow()

  return rows
}

export type CsvField = 'date' | 'description' | 'amount' | 'debit' | 'credit'

const FIELD_ALIASES: Record<CsvField, readonly string[]> = {
  date: ['date', 'tanggal', 'tgl', 'transaction date'],
  description: ['description', 'keterangan', 'uraian', 'narasi', 'remark', 'notes'],
  amount: ['amount', 'nominal', 'jumlah', 'value'],
  debit: ['debit', 'debet', 'withdrawal', 'keluar'],
  credit: ['credit', 'kredit', 'deposit', 'masuk'],
}

const CSV_FIELDS = Object.keys(FIELD_ALIASES) as CsvField[]

/** Guess which header column is which, from common English and Indonesian bank export headers. */
export function detectColumns(header: readonly string[]): Partial<Record<CsvField, number>> {
  const result: Partial<Record<CsvField, number>> = {}
  header.forEach((raw, index) => {
    const normalised = raw.trim().toLowerCase()
    for (const field of CSV_FIELDS) {
      if (field in result) continue
      if (FIELD_ALIASES[field].includes(normalised)) result[field] = index
    }
  })
  return result
}

const ROW_DATE_FORMATS = ['dd/MM/yyyy', 'dd-MM-yyyy', 'MM/dd/yyyy', 'yyyy/MM/dd']

function parseRowDate(raw: string): IsoDate | null {
  const trimmed = raw.trim()
  if (/^\d{4}-\d{2}-\d{2}/.test(trimmed)) {
    const iso = parseISO(trimmed)
    if (isValid(iso)) return format(iso, 'yyyy-MM-dd')
  }
  for (const pattern of ROW_DATE_FORMATS) {
    const parsed = parse(trimmed, pattern, new Date())
    if (isValid(parsed)) return format(parsed, 'yyyy-MM-dd')
  }
  return null
}

/**
 * Read a bank statement's amount column. The same rule as money.ts's
 * parseMoneyInput applies: the last separator followed by one or two digits
 * is the decimal point, and every other separator is grouping. Returns a
 * MAJOR unit value, since a raw CSV cell has no idea how many decimal digits
 * the target currency uses.
 */
function parseRowAmount(raw: string): number | null {
  const cleaned = raw.replace(/[^\d.,-]/g, '').trim()
  if (cleaned === '' || cleaned === '-') return null

  const negative = cleaned.startsWith('-')
  const body = negative ? cleaned.slice(1) : cleaned
  const lastSep = Math.max(body.lastIndexOf('.'), body.lastIndexOf(','))
  let whole = body
  let fraction = ''
  if (lastSep !== -1) {
    const tail = body.slice(lastSep + 1)
    if (/^\d{1,2}$/.test(tail)) {
      whole = body.slice(0, lastSep)
      fraction = tail
    }
  }

  whole = whole.replace(/[.,]/g, '')
  if (whole === '') whole = '0'
  if (!/^\d+$/.test(whole)) return null

  const value = Number(`${whole}.${fraction === '' ? '0' : fraction}`)
  if (!Number.isFinite(value)) return null
  return negative ? -value : value
}

export interface ImportContext {
  profileId: string
  walletId: string
  /** Currency every imported row is assumed to be denominated in. */
  currency: CurrencyCode
  baseCurrency: CurrencyCode
  rates: readonly ExchangeRate[]
  defaultCategoryId: string
  defaultTypeId: string
}

export interface ImportError {
  /** 1 based position of the row within the array passed to importRows. */
  row: number
  reason: string
}

/**
 * Turn parsed CSV rows into transaction candidates. A row that cannot be read
 * (a bad date, no usable amount, no exchange rate for the day) is recorded as
 * an error and skipped rather than aborting the whole import, so one damaged
 * line in a thousand row statement does not throw away the other 999.
 */
export function importRows(
  rows: readonly string[][],
  mapping: Partial<Record<CsvField, number>>,
  ctx: ImportContext,
): { transactions: Array<Omit<Transaction, 'id' | 'createdAt'>>; errors: ImportError[] } {
  const transactions: Array<Omit<Transaction, 'id' | 'createdAt'>> = []
  const errors: ImportError[] = []

  rows.forEach((cells, index) => {
    const rowNumber = index + 1
    try {
      if (mapping.date === undefined) {
        errors.push({ row: rowNumber, reason: 'No date column mapped' })
        return
      }
      const rawDate = cells[mapping.date]
      if (rawDate === undefined || rawDate.trim() === '') {
        errors.push({ row: rowNumber, reason: 'Missing date' })
        return
      }
      const date = parseRowDate(rawDate)
      if (date === null) {
        errors.push({ row: rowNumber, reason: `Unrecognised date "${rawDate}"` })
        return
      }

      let direction: Direction
      let major: number

      if (mapping.amount !== undefined) {
        const raw = cells[mapping.amount]
        const parsed = raw === undefined ? null : parseRowAmount(raw)
        if (parsed === null || parsed === 0) {
          errors.push({ row: rowNumber, reason: `Unrecognised amount "${raw ?? ''}"` })
          return
        }
        direction = parsed < 0 ? 'expense' : 'income'
        major = Math.abs(parsed)
      } else if (mapping.debit !== undefined || mapping.credit !== undefined) {
        const debitRaw = mapping.debit === undefined ? undefined : cells[mapping.debit]
        const creditRaw = mapping.credit === undefined ? undefined : cells[mapping.credit]
        const debit = debitRaw ? parseRowAmount(debitRaw) : null
        const credit = creditRaw ? parseRowAmount(creditRaw) : null

        if (debit !== null && debit !== 0) {
          direction = 'expense'
          major = Math.abs(debit)
        } else if (credit !== null && credit !== 0) {
          direction = 'income'
          major = Math.abs(credit)
        } else {
          errors.push({ row: rowNumber, reason: 'No debit or credit amount on this row' })
          return
        }
      } else {
        errors.push({ row: rowNumber, reason: 'No amount column mapped' })
        return
      }

      const rate = findRate(ctx.rates, ctx.currency, date, ctx.baseCurrency)
      if (rate === null) {
        errors.push({ row: rowNumber, reason: `No exchange rate for ${ctx.currency} on ${date}` })
        return
      }

      const description = mapping.description === undefined ? '' : (cells[mapping.description] ?? '')

      transactions.push({
        profileId: ctx.profileId,
        walletId: ctx.walletId,
        toWalletId: null,
        date,
        direction,
        typeId: ctx.defaultTypeId,
        categoryId: ctx.defaultCategoryId,
        amount: fromMajor(major, ctx.currency).minor,
        currency: ctx.currency,
        toAmount: null,
        rateToBase: rate,
        description,
        recurringId: null,
      })
    } catch (err) {
      errors.push({ row: rowNumber, reason: err instanceof Error ? err.message : 'Unknown error' })
    }
  })

  return { transactions, errors }
}
