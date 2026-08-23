/**
 * Create and edit form for a single budget.
 *
 * Renders its own <form> with the Save/Cancel buttons inside it, rather than
 * relying on the Modal's separate footer slot, so the submit button stays a
 * native part of the form and Enter-to-submit keeps working without wiring a
 * form id across two unrelated DOM subtrees.
 */

import { useId, useState, type FormEvent } from 'react'
import type { Budget, BudgetPeriod } from '@/domain/types'
import type { CurrencyCode } from '@/domain/currency'
import { categoriesForFlow } from '@/domain/categories'
import { money } from '@/domain/money'
import { newId, nowIso } from '@/data/ids'
import { useI18n } from '@/i18n'
import { Button, Input, MoneyInput, Select } from '@/ui'

/** `yyyy-MM` for the current month, in the visitor's local calendar. */
export function currentMonthlyKey(): string {
  const now = new Date()
  return `${now.getFullYear()}-${String(now.getMonth() + 1).padStart(2, '0')}`
}

/** `yyyy` for the current year. */
export function currentYearlyKey(): string {
  return String(new Date().getFullYear())
}

export function defaultPeriodKeyFor(period: BudgetPeriod): string {
  return period === 'monthly' ? currentMonthlyKey() : currentYearlyKey()
}

/**
 * A single control for the period key, shaped by which period is selected:
 * a native month picker for `monthly`, a plain year number for `yearly`.
 * Shared between the page's period picker and this form's own period field
 * so the two never drift into different input conventions.
 */
export function PeriodKeyField({
  period,
  value,
  onChange,
  label,
  error,
}: {
  period: BudgetPeriod
  value: string
  onChange: (value: string) => void
  label: string
  error?: string
}) {
  if (period === 'monthly') {
    return (
      <Input
        type="month"
        label={label}
        value={value}
        onChange={(event) => onChange(event.target.value)}
        error={error}
        required
      />
    )
  }
  return (
    <Input
      type="number"
      inputMode="numeric"
      label={label}
      value={value}
      min={1970}
      max={2999}
      step={1}
      onChange={(event) => onChange(event.target.value)}
      error={error}
      required
    />
  )
}

export interface BudgetFormProps {
  profileId: string
  baseCurrency: CurrencyCode
  /** The budget being edited, or null when creating a new one. */
  initial: Budget | null
  /** Seeds a new budget's period from whatever period the page is currently showing. */
  defaultPeriod: BudgetPeriod
  defaultPeriodKey: string
  onSave: (budget: Budget) => void
  onCancel: () => void
}

interface FormErrors {
  periodKey?: string
  limit?: string
  alertThreshold?: string
}

export function BudgetForm({
  profileId,
  baseCurrency,
  initial,
  defaultPeriod,
  defaultPeriodKey,
  onSave,
  onCancel,
}: BudgetFormProps) {
  const { t, labelFor } = useI18n()
  const thresholdId = useId()

  const [period, setPeriod] = useState<BudgetPeriod>(initial?.period ?? defaultPeriod)
  const [periodKey, setPeriodKey] = useState(initial?.periodKey ?? defaultPeriodKey)
  // '' stands for "all spending" (a null categoryId), since a native <select>
  // option value has to be a string.
  const [categoryId, setCategoryId] = useState(initial?.categoryId ?? '')
  const [limitMinor, setLimitMinor] = useState<number | null>(initial?.limit ?? null)
  const [targetMinor, setTargetMinor] = useState<number | null>(initial?.target ?? null)
  const [description, setDescription] = useState(initial?.description ?? '')
  const [thresholdPercent, setThresholdPercent] = useState(
    initial ? Math.round(initial.alertThreshold * 100) : 80,
  )
  const [alertsEnabled, setAlertsEnabled] = useState(initial?.alertsEnabled ?? true)
  const [errors, setErrors] = useState<FormErrors>({})

  const expenseCategories = categoriesForFlow('expense')

  function handlePeriodChange(nextPeriod: BudgetPeriod) {
    setPeriod(nextPeriod)
    // Switching between a month picker and a year number needs a value in
    // the new shape; carrying over "2026-08" into the year field would just
    // fail validation for no reason a person typing would understand.
    setPeriodKey(defaultPeriodKeyFor(nextPeriod))
  }

  function validate(): FormErrors {
    const next: FormErrors = {}
    const keyPattern = period === 'monthly' ? /^\d{4}-\d{2}$/ : /^\d{4}$/
    if (!keyPattern.test(periodKey)) next.periodKey = t('validation.invalidDate')
    if (limitMinor === null || limitMinor <= 0) next.limit = t('validation.limitMustBePositive')
    if (thresholdPercent < 1 || thresholdPercent > 100) next.alertThreshold = t('validation.thresholdRange')
    return next
  }

  function handleSubmit(event: FormEvent<HTMLFormElement>) {
    event.preventDefault()
    const nextErrors = validate()
    setErrors(nextErrors)
    if (Object.keys(nextErrors).length > 0) return
    // limitMinor is checked above; the assertion here just tells the compiler
    // what validate() already guarantees.
    const budget: Budget = {
      id: initial?.id ?? newId('bud'),
      profileId,
      period,
      periodKey,
      categoryId: categoryId === '' ? null : categoryId,
      limit: limitMinor as number,
      target: targetMinor,
      description: description.trim(),
      alertThreshold: thresholdPercent / 100,
      alertsEnabled,
      createdAt: initial?.createdAt ?? nowIso(),
    }
    onSave(budget)
  }

  return (
    <form onSubmit={handleSubmit} className="flex flex-col gap-4" noValidate>
      <div className="grid grid-cols-2 gap-3">
        <Select
          label={t.budget.fields.period}
          value={period}
          onChange={(event) => handlePeriodChange(event.target.value as BudgetPeriod)}
        >
          <option value="monthly">{t.budget.periods.monthly}</option>
          <option value="yearly">{t.budget.periods.yearly}</option>
        </Select>
        <PeriodKeyField
          period={period}
          value={periodKey}
          onChange={setPeriodKey}
          label={t.budget.fields.periodKey}
          error={errors.periodKey}
        />
      </div>

      <Select
        label={t.budget.fields.category}
        value={categoryId}
        onChange={(event) => setCategoryId(event.target.value)}
      >
        <option value="">{t.budget.fields.allCategories}</option>
        {expenseCategories.map((category) => (
          <option key={category.id} value={category.id}>
            {category.emoji} {labelFor(category)}
          </option>
        ))}
      </Select>

      <MoneyInput
        label={t.budget.fields.limit}
        currency={baseCurrency}
        value={limitMinor !== null ? money(limitMinor, baseCurrency) : null}
        onChange={(value) => setLimitMinor(value ? value.minor : null)}
        error={errors.limit}
        required
      />

      <MoneyInput
        label={t.budget.fields.target}
        hint={t.common.optional}
        currency={baseCurrency}
        value={targetMinor !== null ? money(targetMinor, baseCurrency) : null}
        onChange={(value) => setTargetMinor(value ? value.minor : null)}
      />

      <Input
        label={t.budget.fields.description}
        hint={t.common.optional}
        value={description}
        onChange={(event) => setDescription(event.target.value)}
      />

      <div className="flex flex-col gap-1.5">
        <label htmlFor={thresholdId} className="text-sm font-medium text-text">
          {t.budget.fields.alertThreshold}
        </label>
        <div className="flex items-center gap-3">
          <input
            id={thresholdId}
            type="range"
            min={1}
            max={100}
            step={1}
            value={thresholdPercent}
            aria-valuetext={`${thresholdPercent}%`}
            onChange={(event) => setThresholdPercent(Number(event.target.value))}
            className="h-2 w-full flex-1 cursor-pointer accent-accent"
          />
          <span className="w-12 shrink-0 text-right text-sm tnum text-text">{thresholdPercent}%</span>
        </div>
        <p className="text-xs text-muted">{t('budget.alertAt', { percent: thresholdPercent })}</p>
        {errors.alertThreshold && (
          <p role="alert" className="text-xs text-negative">
            {errors.alertThreshold}
          </p>
        )}
      </div>

      <label className="flex items-center gap-2 text-sm font-medium text-text">
        <input
          type="checkbox"
          checked={alertsEnabled}
          onChange={(event) => setAlertsEnabled(event.target.checked)}
          className="h-4 w-4 rounded border-line accent-accent"
        />
        {t.budget.fields.alertsEnabled}
      </label>

      <div className="mt-1 flex justify-end gap-2 border-t border-line pt-4">
        <Button type="button" variant="secondary" onClick={onCancel}>
          {t.common.cancel}
        </Button>
        <Button type="submit" variant="primary">
          {initial ? t.common.save : t.common.create}
        </Button>
      </div>
    </form>
  )
}
