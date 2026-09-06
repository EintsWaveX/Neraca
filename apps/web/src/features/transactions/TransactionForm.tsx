/**
 * Create and edit form for a single transaction.
 *
 * Type drives category and direction: picking a transaction type sets
 * `direction` to that type's own direction and proposes its
 * `defaultCategoryId`, but the category select is never locked, so a person
 * can still pick something else afterwards. See the doc comment on
 * `Transaction.toAmount` in domain/types.ts for why a cross currency transfer
 * needs its own destination amount field rather than reusing the source
 * amount or `rateToBase`.
 */

import { useMemo, useState, type FormEvent } from 'react'
import { format } from 'date-fns'
import type { CurrencyCode } from '@neraca/domain/currency'
import type { Direction, ExchangeRate, Transaction, Wallet } from '@neraca/domain/types'
import { money, type Money } from '@neraca/domain/money'
import { findRate } from '@neraca/domain/rates'
import { categoriesForFlow } from '@neraca/domain/categories'
import { transactionTypeById, transactionTypesForDirection } from '@neraca/domain/txTypes'
import { newId, nowIso } from '@/data/ids'
import { useRepository } from '@/app/repo'
import { useProfile } from '@/app/ProfileProvider'
import { useI18n } from '@/i18n'
import { Button, Input, MoneyInput, Select } from '@/ui'

export interface TransactionFormProps {
  wallets: readonly Wallet[]
  rates: readonly ExchangeRate[]
  /** Omitted for a brand new transaction. */
  initial?: Transaction
  onSaved: () => void
  onCancel: () => void
}

const DIRECTIONS: readonly Direction[] = ['income', 'expense', 'transfer']

export function TransactionForm({ wallets, rates, initial, onSaved, onCancel }: TransactionFormProps) {
  const { t, labelFor } = useI18n()
  const profile = useProfile()
  const repo = useRepository()

  // A wallet already used on the row being edited stays selectable even if
  // it has since been archived, so opening an old transaction never presents
  // an empty picker. A brand new entry only offers wallets still in use.
  const selectableWallets = useMemo(() => {
    const keep = new Set<string>()
    if (initial) {
      keep.add(initial.walletId)
      if (initial.toWalletId) keep.add(initial.toWalletId)
    }
    return wallets.filter((w) => !w.archived || keep.has(w.id))
  }, [wallets, initial])

  const [direction, setDirection] = useState<Direction>(initial?.direction ?? 'expense')
  const [date, setDate] = useState(initial?.date ?? format(new Date(), 'yyyy-MM-dd'))
  const [typeId, setTypeId] = useState(
    initial?.typeId ?? transactionTypesForDirection(initial?.direction ?? 'expense')[0]?.id ?? '',
  )
  const [categoryId, setCategoryId] = useState(
    initial?.categoryId ?? transactionTypeById(typeId)?.defaultCategoryId ?? '',
  )
  const [walletId, setWalletId] = useState(initial?.walletId ?? selectableWallets[0]?.id ?? '')
  const [toWalletId, setToWalletId] = useState(initial?.toWalletId ?? '')
  const [description, setDescription] = useState(initial?.description ?? '')

  const sourceWallet = selectableWallets.find((w) => w.id === walletId)
  const destWallet = selectableWallets.find((w) => w.id === toWalletId)
  const sourceCurrency: CurrencyCode = sourceWallet?.currency ?? profile.baseCurrency

  const [amount, setAmount] = useState<Money | null>(initial ? money(initial.amount, initial.currency) : null)
  const [toAmount, setToAmount] = useState<Money | null>(() => {
    if (!initial || initial.toAmount === null || !initial.toWalletId) return null
    const toWallet = wallets.find((w) => w.id === initial.toWalletId)
    return toWallet ? money(initial.toAmount, toWallet.currency) : null
  })

  const [errors, setErrors] = useState<Partial<Record<string, string>>>({})
  const [formError, setFormError] = useState<string | undefined>(undefined)
  const [saving, setSaving] = useState(false)

  const availableTypes = transactionTypesForDirection(direction)
  // Categories only carry an income or expense flow. A transfer's default
  // categories (fees, or "other") are both expense-flow ones, so the expense
  // list is what a transfer offers too.
  const availableCategories = direction === 'income' ? categoriesForFlow('income') : categoriesForFlow('expense')

  const crossCurrencyTransfer = Boolean(
    direction === 'transfer' && sourceWallet && destWallet && sourceWallet.currency !== destWallet.currency,
  )

  function handleDirectionChange(next: Direction) {
    setDirection(next)
    const firstType = transactionTypesForDirection(next)[0]
    setTypeId(firstType?.id ?? '')
    setCategoryId(firstType?.defaultCategoryId ?? '')
    if (next !== 'transfer') {
      setToWalletId('')
      setToAmount(null)
    }
  }

  function handleTypeChange(nextId: string) {
    setTypeId(nextId)
    const type = transactionTypeById(nextId)
    if (type) setCategoryId(type.defaultCategoryId)
  }

  async function handleSubmit(event: FormEvent) {
    event.preventDefault()
    const nextErrors: Partial<Record<string, string>> = {}

    if (!date) nextErrors.date = t.validation.required
    if (!typeId) nextErrors.typeId = t.validation.mustSelectType
    if (!categoryId) nextErrors.categoryId = t.validation.mustSelectCategory
    if (!walletId) nextErrors.walletId = t.validation.mustSelectWallet

    if (direction === 'transfer') {
      if (!toWalletId) nextErrors.toWalletId = t.validation.mustSelectDestinationWallet
      else if (toWalletId === walletId) nextErrors.toWalletId = t.validation.sameWalletTransfer
    }

    if (!amount) nextErrors.amount = t.validation.invalidAmount
    else if (amount.minor <= 0) nextErrors.amount = t.validation.amountMustBePositive

    if (crossCurrencyTransfer) {
      if (!toAmount) nextErrors.toAmount = t.validation.invalidAmount
      else if (toAmount.minor <= 0) nextErrors.toAmount = t.validation.amountMustBePositive
    }

    setErrors(nextErrors)
    setFormError(undefined)
    if (Object.keys(nextErrors).length > 0 || !amount || !sourceWallet) return

    // The rate has to be the one in effect on the transaction's own date, not
    // today's: see the doc comment on `rateToBase` in domain/types.ts for why
    // re-pricing an old row at today's rate would quietly rewrite history.
    // findRate already returns 1 when the wallet is already in base currency,
    // so this only ever blocks a genuinely foreign-currency entry.
    const rate = findRate(rates, sourceWallet.currency, date, profile.baseCurrency)
    if (rate === null) {
      setFormError(t.empty.exchangeRates)
      return
    }

    setSaving(true)
    try {
      const record: Transaction = {
        id: initial?.id ?? newId('txn'),
        profileId: profile.id,
        walletId: sourceWallet.id,
        toWalletId: direction === 'transfer' ? toWalletId : null,
        date,
        direction,
        typeId,
        categoryId,
        amount: amount.minor,
        currency: sourceWallet.currency,
        toAmount: direction === 'transfer' && crossCurrencyTransfer ? (toAmount?.minor ?? null) : null,
        rateToBase: rate,
        description: description.trim(),
        recurringId: initial?.recurringId ?? null,
        createdAt: initial?.createdAt ?? nowIso(),
      }
      await repo.putTransaction(record)
      onSaved()
    } finally {
      setSaving(false)
    }
  }

  return (
    <form onSubmit={handleSubmit} className="flex flex-col gap-4" noValidate>
      {formError && (
        <p
          role="alert"
          className="rounded-control border border-negative bg-negative-soft px-3 py-2 text-sm text-negative"
        >
          {formError}
        </p>
      )}

      <fieldset className="flex flex-col gap-1.5">
        <legend className="text-sm font-medium text-text">{t.transaction.fields.direction}</legend>
        <div className="flex gap-2">
          {DIRECTIONS.map((d) => (
            <button
              key={d}
              type="button"
              aria-pressed={direction === d}
              onClick={() => handleDirectionChange(d)}
              className={`flex-1 rounded-control border px-3 py-2 text-sm font-medium transition-colors ${
                direction === d ? 'border-accent bg-accent-soft text-accent' : 'border-line text-muted hover:text-text'
              }`}
            >
              {t.transaction.directions[d]}
            </button>
          ))}
        </div>
      </fieldset>

      <Input
        label={t.transaction.fields.date}
        type="date"
        required
        value={date}
        onChange={(event) => setDate(event.target.value)}
        error={errors.date}
      />

      <Select
        label={t.transaction.fields.type}
        required
        value={typeId}
        onChange={(event) => handleTypeChange(event.target.value)}
        error={errors.typeId}
      >
        <option value="" disabled>
          {t.common.selectPlaceholder}
        </option>
        {availableTypes.map((type) => (
          <option key={type.id} value={type.id}>
            {labelFor(type)}
          </option>
        ))}
      </Select>

      <Select
        label={t.transaction.fields.category}
        required
        value={categoryId}
        onChange={(event) => setCategoryId(event.target.value)}
        error={errors.categoryId}
      >
        <option value="" disabled>
          {t.common.selectPlaceholder}
        </option>
        {availableCategories.map((cat) => (
          <option key={cat.id} value={cat.id}>
            {cat.emoji} {labelFor(cat)}
          </option>
        ))}
      </Select>

      <Select
        label={t.transaction.fields.wallet}
        required
        value={walletId}
        onChange={(event) => setWalletId(event.target.value)}
        error={errors.walletId}
      >
        <option value="" disabled>
          {t.common.selectPlaceholder}
        </option>
        {selectableWallets.map((w) => (
          <option key={w.id} value={w.id}>
            {w.name} ({w.currency})
          </option>
        ))}
      </Select>

      {direction === 'transfer' && (
        <Select
          label={t.transaction.fields.toWallet}
          required
          value={toWalletId}
          onChange={(event) => setToWalletId(event.target.value)}
          error={errors.toWalletId}
        >
          <option value="" disabled>
            {t.common.selectPlaceholder}
          </option>
          {selectableWallets.map((w) => (
            <option key={w.id} value={w.id}>
              {w.name} ({w.currency})
            </option>
          ))}
        </Select>
      )}

      <MoneyInput
        label={t.transaction.fields.amount}
        currency={sourceCurrency}
        value={amount}
        onChange={setAmount}
        error={errors.amount}
      />

      {crossCurrencyTransfer && destWallet && (
        <MoneyInput
          label={`${t.transaction.fields.amount} (${destWallet.currency})`}
          currency={destWallet.currency}
          value={toAmount}
          onChange={setToAmount}
          error={errors.toAmount}
        />
      )}

      <Input
        label={t.transaction.fields.description}
        value={description}
        onChange={(event) => setDescription(event.target.value)}
      />

      <div className="flex justify-end gap-2 pt-2">
        <Button type="button" variant="secondary" onClick={onCancel}>
          {t.common.cancel}
        </Button>
        <Button type="submit" loading={saving}>
          {t.common.save}
        </Button>
      </div>
    </form>
  )
}
