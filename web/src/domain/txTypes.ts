/**
 * Transaction types.
 *
 * These come from `struct MoneytoryTransactionsRegister` in the original C
 * program, which listed the kinds of banking movement a statement actually
 * shows. A type answers "how did the money move", where a category answers
 * "what was it for". The C version kept them as separate parallel field lists
 * and never linked them, so this rewrite keeps both but records which
 * direction each type implies, which is what lets the entry form pick sensible
 * defaults instead of asking twice.
 *
 * The duplicate `Loan` and `Loans` fields in the C struct are collapsed here.
 */

import type { Direction } from './types'

export interface TransactionType {
  id: string
  /** The direction this type almost always implies. */
  direction: Direction
  en: string
  id_: string
  /** Category suggested when this type is chosen. */
  defaultCategoryId: string
}

const t = (
  id: string,
  direction: Direction,
  en: string,
  id_: string,
  defaultCategoryId: string,
): TransactionType => ({ id, direction, en, id_, defaultCategoryId })

export const TRANSACTION_TYPES: readonly TransactionType[] = [
  t('salary-payroll', 'income', 'Salary or Payroll', 'Gaji atau Penggajian', 'salary'),
  t('incoming-cash', 'income', 'Incoming Cash', 'Kas Masuk', 'incomings'),
  t('incoming-transfer', 'income', 'Incoming Transfer', 'Transfer Masuk', 'incomings'),
  t('interest', 'income', 'Interest Received', 'Bunga Diterima', 'interests'),
  t('wallet-cashback', 'income', 'Wallet Cashback', 'Cashback Dompet', 'additional-income'),
  t('card-refund', 'income', 'Card Refund', 'Pengembalian Kartu', 'refunds'),
  t('qr-payment-refund', 'income', 'QR Payment Refund', 'Pengembalian Pembayaran QR', 'refunds'),
  t('reversal', 'income', 'Reversal', 'Pembalikan Transaksi', 'refunds'),
  t('loan', 'income', 'Loan Received', 'Pinjaman Diterima', 'loan-disbursements'),
  t('principal-repayment', 'income', 'Principal Repayment', 'Pelunasan Pokok', 'investments-withdrawal'),
  t('savings-withdrawal', 'income', 'Savings Withdrawal', 'Penarikan Tabungan', 'investments-withdrawal'),

  t('payment-with-card', 'expense', 'Card Payment', 'Pembayaran Kartu', 'others'),
  t('qr-payment', 'expense', 'QR Payment', 'Pembayaran QR', 'others'),
  t('bill-payment', 'expense', 'Bill Payment', 'Pembayaran Tagihan', 'electricity-water-gas'),
  t('fee-payment', 'expense', 'Fee Payment', 'Pembayaran Biaya', 'cost-and-taxes'),
  t('bank-charge', 'expense', 'Bank Charge', 'Biaya Bank', 'cost-and-taxes'),
  t('tax-on-interest', 'expense', 'Tax on Interest', 'Pajak Bunga', 'cost-and-taxes'),
  t('outgoing-transfer', 'expense', 'Outgoing Transfer', 'Transfer Keluar', 'send-to-personal'),
  t('cash-withdrawal', 'expense', 'Cash Withdrawal', 'Tarik Tunai', 'cash-withdrawal'),
  t('prepaid-top-up', 'expense', 'Prepaid Top Up', 'Isi Ulang Prabayar', 'mobile-and-data'),
  t('card-top-up', 'expense', 'Card Top Up', 'Isi Ulang Kartu', 'top-up-ewallet-cards'),
  t('principal-placement', 'expense', 'Principal Placement', 'Penempatan Pokok', 'investments'),
  t('top-up-savings', 'expense', 'Top Up Savings', 'Menambah Tabungan', 'savings'),

  t('currency-exchange', 'transfer', 'Currency Exchange', 'Penukaran Mata Uang', 'cost-and-taxes'),
  t('internal-transfer', 'transfer', 'Transfer Between Wallets', 'Transfer Antar Dompet', 'others'),
]

export const TRANSACTION_TYPE_BY_ID: ReadonlyMap<string, TransactionType> = new Map(
  TRANSACTION_TYPES.map((type) => [type.id, type]),
)

export function transactionTypeById(id: string): TransactionType | undefined {
  return TRANSACTION_TYPE_BY_ID.get(id)
}

export function transactionTypesForDirection(direction: Direction): readonly TransactionType[] {
  return TRANSACTION_TYPES.filter((type) => type.direction === direction)
}
