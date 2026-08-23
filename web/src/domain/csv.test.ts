import { describe, expect, it } from 'vitest'
import type { ExchangeRate, Transaction } from './types'
import { detectColumns, importRows, parseCsv, transactionsToCsv, type ImportContext } from './csv'

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

describe('transactionsToCsv', () => {
  it('writes a header followed by one row per transaction', () => {
    const csv = transactionsToCsv([tx({ amount: 15_000, description: 'Lunch' })])
    const lines = csv.split('\r\n')
    expect(lines[0]).toBe('date,direction,walletId,toWalletId,categoryId,typeId,amount,currency,description')
    expect(lines[1]).toBe('2026-08-10,expense,w1,,groceries,payment-with-card,15000,IDR,Lunch')
  })

  it('quotes a description containing a comma', () => {
    const csv = transactionsToCsv([tx({ description: 'Coffee, tea and snacks' })])
    expect(csv).toContain('"Coffee, tea and snacks"')
  })

  it('quotes and doubles an embedded quote', () => {
    const csv = transactionsToCsv([tx({ description: 'Said "hello"' })])
    expect(csv).toContain('"Said ""hello"""')
  })

  it('quotes an embedded newline', () => {
    const csv = transactionsToCsv([tx({ description: 'Line one\nLine two' })])
    expect(csv).toContain('"Line one\nLine two"')
  })

  it('can omit the header', () => {
    const csv = transactionsToCsv([tx()], { header: false })
    expect(csv.split('\r\n')).toHaveLength(1)
  })

  it('formats rupiah with no decimal places, since rupiah has none', () => {
    const csv = transactionsToCsv([tx({ amount: 1_500_000, currency: 'IDR' })], { header: false })
    expect(csv).toContain(',1500000,IDR,')
  })
})

describe('parseCsv', () => {
  it('splits a simple row on commas', () => {
    expect(parseCsv('a,b,c\n1,2,3')).toEqual([['a', 'b', 'c'], ['1', '2', '3']])
  })

  it('keeps a comma inside a quoted field', () => {
    expect(parseCsv('a,"b,c",d')).toEqual([['a', 'b,c', 'd']])
  })

  it('unescapes a doubled quote inside a quoted field', () => {
    expect(parseCsv('a,"she said ""hi""",c')).toEqual([['a', 'she said "hi"', 'c']])
  })

  it('keeps a newline inside a quoted field as part of that field', () => {
    expect(parseCsv('a,"line one\nline two",c')).toEqual([['a', 'line one\nline two', 'c']])
  })

  it('accepts CRLF line endings', () => {
    expect(parseCsv('a,b\r\nc,d')).toEqual([['a', 'b'], ['c', 'd']])
  })

  it('accepts bare LF line endings', () => {
    expect(parseCsv('a,b\nc,d')).toEqual([['a', 'b'], ['c', 'd']])
  })

  it('does not produce a phantom row for a trailing newline', () => {
    expect(parseCsv('a,b\nc,d\n')).toEqual([['a', 'b'], ['c', 'd']])
  })

  it('returns nothing for an empty string', () => {
    expect(parseCsv('')).toEqual([])
  })

  it('round trips a quoted field containing a comma and a newline together', () => {
    const rows = parseCsv('date,description,amount\n2026-08-10,"rent, august\nsecond line",5000')
    expect(rows[1]).toEqual(['2026-08-10', 'rent, august\nsecond line', '5000'])
  })
})

describe('detectColumns', () => {
  it('matches English headers', () => {
    const mapping = detectColumns(['Date', 'Description', 'Amount'])
    expect(mapping).toEqual({ date: 0, description: 1, amount: 2 })
  })

  it('matches Indonesian bank export headers', () => {
    const mapping = detectColumns(['Tanggal', 'Keterangan', 'Debet', 'Kredit'])
    expect(mapping).toEqual({ date: 0, description: 1, debit: 2, credit: 3 })
  })

  it('matches Uraian for description and Nominal or Jumlah for amount', () => {
    expect(detectColumns(['Tanggal', 'Uraian', 'Nominal'])).toEqual({ date: 0, description: 1, amount: 2 })
    expect(detectColumns(['Tanggal', 'Uraian', 'Jumlah'])).toEqual({ date: 0, description: 1, amount: 2 })
  })

  it('is case insensitive and trims whitespace', () => {
    expect(detectColumns([' TANGGAL ', 'keterangan'])).toEqual({ date: 0, description: 1 })
  })

  it('leaves unrecognised headers out of the mapping', () => {
    expect(detectColumns(['Reference Number'])).toEqual({})
  })
})

function ctx(overrides: Partial<ImportContext> = {}): ImportContext {
  return {
    profileId: 'p1',
    walletId: 'w1',
    currency: 'IDR',
    baseCurrency: 'IDR',
    rates: [],
    defaultCategoryId: 'uncategorized',
    defaultTypeId: 'payment-with-card',
    ...overrides,
  }
}

describe('importRows', () => {
  it('reads a single amount column, negative as expense and positive as income', () => {
    const mapping = { date: 0, description: 1, amount: 2 }
    const rows = [
      ['2026-08-10', 'Groceries', '-150000'],
      ['2026-08-11', 'Salary', '5000000'],
    ]
    const { transactions, errors } = importRows(rows, mapping, ctx())
    expect(errors).toEqual([])
    expect(transactions).toHaveLength(2)
    expect(transactions[0]).toMatchObject({ direction: 'expense', amount: 150_000, date: '2026-08-10' })
    expect(transactions[1]).toMatchObject({ direction: 'income', amount: 5_000_000, date: '2026-08-11' })
  })

  it('reads separate debit and credit columns', () => {
    const mapping = { date: 0, debit: 1, credit: 2 }
    const rows = [
      ['2026-08-10', '150000', ''],
      ['2026-08-11', '', '5000000'],
    ]
    const { transactions, errors } = importRows(rows, mapping, ctx())
    expect(errors).toEqual([])
    expect(transactions[0]).toMatchObject({ direction: 'expense', amount: 150_000 })
    expect(transactions[1]).toMatchObject({ direction: 'income', amount: 5_000_000 })
  })

  it('records an error for a bad row without aborting the rest of the import', () => {
    const mapping = { date: 0, amount: 1 }
    const rows = [
      ['not a date', '1000'],
      ['2026-08-10', '150000'],
    ]
    const { transactions, errors } = importRows(rows, mapping, ctx())
    expect(transactions).toHaveLength(1)
    expect(transactions[0]?.date).toBe('2026-08-10')
    expect(errors).toHaveLength(1)
    expect(errors[0]).toMatchObject({ row: 1 })
  })

  it('errors a row with neither debit nor credit populated', () => {
    const mapping = { date: 0, debit: 1, credit: 2 }
    const rows = [['2026-08-10', '', '']]
    const { transactions, errors } = importRows(rows, mapping, ctx())
    expect(transactions).toEqual([])
    expect(errors).toHaveLength(1)
  })

  it('errors a row in a foreign currency with no exchange rate available', () => {
    const mapping = { date: 0, amount: 1 }
    const rows = [['2026-08-10', '-100']]
    const { transactions, errors } = importRows(rows, mapping, ctx({ currency: 'USD', baseCurrency: 'IDR', rates: [] }))
    expect(transactions).toEqual([])
    expect(errors[0]?.reason).toMatch(/exchange rate/)
  })

  it('converts using the applicable rate when one is available', () => {
    const mapping = { date: 0, amount: 1 }
    const rates: ExchangeRate[] = [
      { id: 'r1', profileId: 'p1', currency: 'USD', rate: 16_000, date: '2026-08-01', createdAt: '2026-08-01T00:00:00.000Z' },
    ]
    const rows = [['2026-08-10', '-10']]
    const { transactions, errors } = importRows(
      rows, mapping, ctx({ currency: 'USD', baseCurrency: 'IDR', rates }),
    )
    expect(errors).toEqual([])
    expect(transactions[0]?.rateToBase).toBe(16_000)
  })

  it('parses dd/MM/yyyy dates', () => {
    const mapping = { date: 0, amount: 1 }
    const rows = [['10/08/2026', '-1000']]
    const { transactions } = importRows(rows, mapping, ctx())
    expect(transactions[0]?.date).toBe('2026-08-10')
  })
})
