/**
 * Wallet balances and net worth.
 *
 * A wallet's balance is derived from its transactions rather than stored, so
 * editing or deleting a row is enough to keep the balance correct with no
 * separate reconciliation step. See types.ts for why the C version's single
 * running total could not answer where the money actually was.
 */

import type { CurrencyCode } from './currency'
import type { ExchangeRate, Transaction, Wallet } from './types'
import { add, convert, money, subtract, zero, type Money } from './money'
import { findRate } from './rates'
import { format } from 'date-fns'

/**
 * A wallet's balance in its own currency: the opening balance plus every
 * income and expense posted to it, plus both legs of any transfer that
 * touches it (a debit on the source wallet, a credit on the destination).
 */
export function walletBalance(wallet: Wallet, transactions: readonly Transaction[]): Money {
  let balance = money(wallet.openingBalance, wallet.currency)

  for (const tx of transactions) {
    const amount = money(tx.amount, tx.currency)

    if (tx.direction === 'transfer') {
      if (tx.walletId === wallet.id) balance = subtract(balance, amount)
      if (tx.toWalletId === wallet.id) {
        // The credit leg is denominated in the destination wallet's currency,
        // which is not always the currency the transfer was debited in. Adding
        // the raw `amount` here would throw on a cross-currency transfer, and
        // would silently credit the wrong figure if the two currencies happened
        // to share a minor unit scale.
        const credited = tx.toAmount ?? tx.amount
        balance = add(balance, money(credited, wallet.currency))
      }
      continue
    }

    if (tx.walletId !== wallet.id) continue
    balance = tx.direction === 'income' ? add(balance, amount) : subtract(balance, amount)
  }

  return balance
}

/**
 * Total value across every wallet, converted into the profile's base currency
 * at today's rate.
 *
 * Each wallet's own balance already nets out both legs of any transfer
 * between the profile's own wallets, so summing wallet balances (rather than
 * summing transactions directly) is what keeps such a transfer from changing
 * net worth.
 */
export function netWorth(
  wallets: readonly Wallet[],
  transactions: readonly Transaction[],
  baseCurrency: CurrencyCode,
  rates: readonly ExchangeRate[],
): Money {
  const today = format(new Date(), 'yyyy-MM-dd')
  let total = zero(baseCurrency)

  for (const wallet of wallets) {
    const balance = walletBalance(wallet, transactions)
    const rate = findRate(rates, wallet.currency, today, baseCurrency)
    if (rate === null) {
      // Silently skipping the wallet would understate net worth without any
      // sign that a number is missing, which is worse than failing loudly.
      throw new Error(
        `No exchange rate available to convert ${wallet.currency} into ${baseCurrency} for wallet "${wallet.name}"`,
      )
    }
    total = add(total, convert(balance, baseCurrency, rate))
  }

  return total
}
