/**
 * Create and edit form for a recurring rule and its transaction template.
 *
 * Like BudgetForm, this renders its own <form> with Save/Cancel inside it
 * rather than using the Modal's separate footer slot.
 */

import { useState, type FormEvent } from 'react'
import type { Direction, Frequency, RecurringRule, Wallet } from '@/domain/types'
import type { CurrencyCode } from '@/domain/currency'
import { CURRENCY_CODES } from '@/domain/currency'
import { categoriesForFlow } from '@/domain/categories'
import { transactionTypeById, transactionTypesForDirection } from '@/domain/txTypes'
import { money } from '@/domain/money'
import { newId, nowIso } from '@/data/ids'
import { useI18n } from '@/i18n'
import { Button, Input, MoneyInput, Select } from '@/ui'

export interface RecurringFormProps {
  profileId: string
  initial: RecurringRule | null
  wallets: Wallet[]
  onSave: (rule: RecurringRule) => void
  onCancel: () => void
}

interface FormErrors {
  name?: string
  startDate?: string
  endDate?: string
  wallet?: string
  toWallet?: string
  type?: string
  category?: string
  amount?: string
}

export function RecurringForm({ profileId, initial, wallets, onSave, onCancel }: RecurringFormProps) {
  const { t, labelFor } = useI18n()

  const [name, setName] = useState(initial?.name ?? '')
  const [frequency, setFrequency] = useState<Frequency>(initial?.frequency ?? 'monthly')
  const [interval, setInterval_] = useState(initial?.interval ?? 1)
  const [startDate, setStartDate] = useState(initial?.startDate ?? nowIso().slice(0, 10))
  const [endDate, setEndDate] = useState(initial?.endDate ?? '')
  const [active, setActive] = useState(initial?.active ?? true)

  const [direction, setDirection] = useState<Direction>(initial?.template.direction ?? 'expense')
  const [walletId, setWalletId] = useState(initial?.template.walletId ?? wallets[0]?.id ?? '')
  const [toWalletId, setToWalletId] = useState(initial?.template.toWalletId ?? '')
  const initialType = initial ? transactionTypeById(initial.template.typeId) : undefined
  const [typeId, setTypeId] = useState(
    initial?.template.typeId ?? transactionTypesForDirection(direction)[0]?.id ?? '',
  )
  const [categoryId, setCategoryId] = useState(
    initial?.template.categoryId ?? initialType?.defaultCategoryId ?? '',
  )
  const [amountMinor, setAmountMinor] = useState<number | null>(initial?.template.amount ?? null)
  const [currency, setCurrency] = useState<CurrencyCode>(initial?.template.currency ?? wallets[0]?.currency ?? 'USD')
  const [description, setDescription] = useState(initial?.template.description ?? '')

  const [errors, setErrors] = useState<FormErrors>({})

  const typeOptions = transactionTypesForDirection(direction)
  const categoryOptions = categoriesForFlow(direction === 'income' ? 'income' : 'expense')

  function handleDirectionChange(nextDirection: Direction) {
    setDirection(nextDirection)
    const firstType = transactionTypesForDirection(nextDirection)[0]
    setTypeId(firstType?.id ?? '')
    setCategoryId(firstType?.defaultCategoryId ?? '')
    if (nextDirection !== 'transfer') setToWalletId('')
  }

  function handleTypeChange(nextTypeId: string) {
    setTypeId(nextTypeId)
    const type = transactionTypeById(nextTypeId)
    if (type) {
      setDirection(type.direction)
      setCategoryId(type.defaultCategoryId)
      if (type.direction !== 'transfer') setToWalletId('')
    }
  }

  function validate(): FormErrors {
    const next: FormErrors = {}
    if (name.trim() === '') next.name = t('validation.required')
    if (startDate === '') next.startDate = t('validation.invalidDate')
    if (endDate !== '' && startDate !== '' && endDate < startDate) next.endDate = t('validation.endDateBeforeStart')
    if (walletId === '') next.wallet = t('validation.mustSelectWallet')
    if (typeId === '') next.type = t('validation.mustSelectType')
    if (categoryId === '') next.category = t('validation.mustSelectCategory')
    if (amountMinor === null || amountMinor <= 0) next.amount = t('validation.amountMustBePositive')
    if (direction === 'transfer') {
      if (toWalletId === '') next.toWallet = t('validation.mustSelectDestinationWallet')
      else if (toWalletId === walletId) next.toWallet = t('validation.sameWalletTransfer')
    }
    return next
  }

  function handleSubmit(event: FormEvent<HTMLFormElement>) {
    event.preventDefault()
    const nextErrors = validate()
    setErrors(nextErrors)
    if (Object.keys(nextErrors).length > 0) return

    const rule: RecurringRule = {
      id: initial?.id ?? newId('rec'),
      profileId,
      name: name.trim(),
      frequency,
      interval,
      startDate,
      endDate: endDate === '' ? null : endDate,
      lastRunDate: initial?.lastRunDate ?? null,
      active,
      template: {
        walletId,
        toWalletId: direction === 'transfer' ? toWalletId : null,
        direction,
        typeId,
        categoryId,
        amount: amountMinor as number,
        currency,
        description: description.trim(),
      },
      createdAt: initial?.createdAt ?? nowIso(),
    }
    onSave(rule)
  }

  return (
    <form onSubmit={handleSubmit} className="flex flex-col gap-4" noValidate>
      <Input
        label={t.recurring.fields.name}
        value={name}
        onChange={(event) => setName(event.target.value)}
        error={errors.name}
        required
      />

      <div className="grid grid-cols-2 gap-3">
        <Select
          label={t.recurring.fields.frequency}
          value={frequency}
          onChange={(event) => setFrequency(event.target.value as Frequency)}
        >
          <option value="daily">{t.recurring.frequencies.daily}</option>
          <option value="weekly">{t.recurring.frequencies.weekly}</option>
          <option value="monthly">{t.recurring.frequencies.monthly}</option>
          <option value="yearly">{t.recurring.frequencies.yearly}</option>
        </Select>
        <Input
          type="number"
          inputMode="numeric"
          label={t.recurring.fields.interval}
          value={interval}
          min={1}
          step={1}
          onChange={(event) => setInterval_(Math.max(1, Math.round(Number(event.target.value) || 1)))}
          required
        />
      </div>

      <div className="grid grid-cols-2 gap-3">
        <Input
          type="date"
          label={t.recurring.fields.startDate}
          value={startDate}
          onChange={(event) => setStartDate(event.target.value)}
          error={errors.startDate}
          required
        />
        <Input
          type="date"
          label={t.recurring.fields.endDate}
          hint={t.common.optional}
          value={endDate}
          onChange={(event) => setEndDate(event.target.value)}
          error={errors.endDate}
        />
      </div>

      <label className="flex items-center gap-2 text-sm font-medium text-text">
        <input
          type="checkbox"
          checked={active}
          onChange={(event) => setActive(event.target.checked)}
          className="h-4 w-4 rounded border-line accent-accent"
        />
        {t.recurring.fields.active}
      </label>

      <div className="border-t border-line pt-4">
        <Select
          label={t.transaction.fields.direction}
          value={direction}
          onChange={(event) => handleDirectionChange(event.target.value as Direction)}
        >
          <option value="income">{t.transaction.directions.income}</option>
          <option value="expense">{t.transaction.directions.expense}</option>
          <option value="transfer">{t.transaction.directions.transfer}</option>
        </Select>
      </div>

      <Select
        label={t.transaction.fields.type}
        value={typeId}
        onChange={(event) => handleTypeChange(event.target.value)}
        error={errors.type}
      >
        <option value="">{t.common.selectPlaceholder}</option>
        {typeOptions.map((type) => (
          <option key={type.id} value={type.id}>
            {labelFor(type)}
          </option>
        ))}
      </Select>

      <Select
        label={t.transaction.fields.category}
        value={categoryId}
        onChange={(event) => setCategoryId(event.target.value)}
        error={errors.category}
      >
        <option value="">{t.common.selectPlaceholder}</option>
        {categoryOptions.map((category) => (
          <option key={category.id} value={category.id}>
            {category.emoji} {labelFor(category)}
          </option>
        ))}
      </Select>

      <div className="grid grid-cols-2 gap-3">
        <Select
          label={t.transaction.fields.wallet}
          value={walletId}
          onChange={(event) => setWalletId(event.target.value)}
          error={errors.wallet}
        >
          <option value="">{t.common.selectPlaceholder}</option>
          {wallets.map((wallet) => (
            <option key={wallet.id} value={wallet.id}>
              {wallet.name} ({wallet.currency})
            </option>
          ))}
        </Select>

        {direction === 'transfer' && (
          <Select
            label={t.transaction.fields.toWallet}
            value={toWalletId}
            onChange={(event) => setToWalletId(event.target.value)}
            error={errors.toWallet}
          >
            <option value="">{t.common.selectPlaceholder}</option>
            {wallets.map((wallet) => (
              <option key={wallet.id} value={wallet.id}>
                {wallet.name} ({wallet.currency})
              </option>
            ))}
          </Select>
        )}
      </div>

      <div className="grid grid-cols-2 gap-3">
        <MoneyInput
          label={t.transaction.fields.amount}
          currency={currency}
          value={amountMinor !== null ? money(amountMinor, currency) : null}
          onChange={(value) => setAmountMinor(value ? value.minor : null)}
          error={errors.amount}
          required
        />
        <Select
          label={t.transaction.fields.currency}
          value={currency}
          onChange={(event) => setCurrency(event.target.value as CurrencyCode)}
        >
          {CURRENCY_CODES.map((code) => (
            <option key={code} value={code}>
              {code}
            </option>
          ))}
        </Select>
      </div>

      <Input
        label={t.transaction.fields.description}
        hint={t.common.optional}
        value={description}
        onChange={(event) => setDescription(event.target.value)}
      />

      {wallets.length === 0 && <p className="text-xs text-warning">{t.empty.wallets}</p>}

      <div className="mt-1 flex justify-end gap-2 border-t border-line pt-4">
        <Button type="button" variant="secondary" onClick={onCancel}>
          {t.common.cancel}
        </Button>
        <Button type="submit" variant="primary" disabled={wallets.length === 0}>
          {initial ? t.common.save : t.common.create}
        </Button>
      </div>
    </form>
  )
}
