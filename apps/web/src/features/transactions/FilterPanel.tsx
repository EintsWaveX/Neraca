/**
 * The transaction search and filter panel.
 *
 * This owns the mapping between what a person clicks and the shape
 * `TransactionQuery` expects. The one rule that matters here: an empty
 * multi-select means "nothing excluded" from the UI's point of view, but
 * `listTransactions` reads an explicit empty array as "match nothing".
 * `buildTransactionQuery` is what keeps those two meanings from colliding,
 * so every caller should build the query through it rather than passing
 * filter state straight to the repository.
 */

import type { CurrencyCode } from '@neraca/domain/currency'
import type { Direction, Wallet } from '@neraca/domain/types'
import type { TransactionQuery } from '@/data/repository'
import { CATEGORY_GROUPS, CATEGORY_GROUP_LABELS, categoriesInGroup } from '@neraca/domain/categories'
import { TRANSACTION_TYPES } from '@neraca/domain/txTypes'
import type { Money } from '@neraca/domain/money'
import { Card, CardBody, CardHeader, CardTitle, Button, Input, MoneyInput } from '@/ui'
import { useI18n } from '@/i18n'

export interface TransactionFiltersState {
  from: string
  to: string
  walletIds: string[]
  categoryIds: string[]
  typeIds: string[]
  directions: Direction[]
  search: string
  /** `null` means no bound is set, matching how MoneyInput represents an empty field. */
  minBaseAmount: Money | null
  maxBaseAmount: Money | null
}

export function createEmptyFilters(): TransactionFiltersState {
  return {
    from: '',
    to: '',
    walletIds: [],
    categoryIds: [],
    typeIds: [],
    directions: [],
    search: '',
    minBaseAmount: null,
    maxBaseAmount: null,
  }
}

export function filtersAreDefault(filters: TransactionFiltersState): boolean {
  return (
    filters.from === '' &&
    filters.to === '' &&
    filters.walletIds.length === 0 &&
    filters.categoryIds.length === 0 &&
    filters.typeIds.length === 0 &&
    filters.directions.length === 0 &&
    filters.search.trim() === '' &&
    filters.minBaseAmount === null &&
    filters.maxBaseAmount === null
  )
}

/** Builds every `TransactionQuery` field the filter panel is responsible for, aside from sort and pagination. */
export function buildTransactionQuery(
  filters: TransactionFiltersState,
  profileId: string,
): Omit<TransactionQuery, 'sort' | 'limit' | 'offset'> {
  return {
    profileId,
    from: filters.from || undefined,
    to: filters.to || undefined,
    // See the module comment: an empty selection has to become `undefined`,
    // never an empty array, or the storage layer would match nothing at all.
    walletIds: filters.walletIds.length > 0 ? filters.walletIds : undefined,
    categoryIds: filters.categoryIds.length > 0 ? filters.categoryIds : undefined,
    typeIds: filters.typeIds.length > 0 ? filters.typeIds : undefined,
    directions: filters.directions.length > 0 ? filters.directions : undefined,
    search: filters.search.trim() || undefined,
    minBaseAmount: filters.minBaseAmount ? filters.minBaseAmount.minor : undefined,
    maxBaseAmount: filters.maxBaseAmount ? filters.maxBaseAmount.minor : undefined,
  }
}

interface CheckboxOption<V extends string> {
  value: V
  label: string
}

function CheckboxGroup<V extends string>({
  legend,
  options,
  selected,
  onChange,
  scroll,
}: {
  legend: string
  options: CheckboxOption<V>[]
  selected: V[]
  onChange: (next: V[]) => void
  scroll?: boolean
}) {
  function toggle(value: V) {
    onChange(selected.includes(value) ? selected.filter((v) => v !== value) : [...selected, value])
  }

  return (
    <fieldset className="flex flex-col gap-1.5">
      <legend className="text-sm font-medium text-text">{legend}</legend>
      <div
        className={`flex flex-col gap-1 rounded-control border border-line p-2 ${
          scroll ? 'max-h-40 overflow-y-auto' : ''
        }`}
      >
        {options.map((opt) => (
          <label key={opt.value} className="flex items-center gap-2 text-sm text-text">
            <input
              type="checkbox"
              checked={selected.includes(opt.value)}
              onChange={() => toggle(opt.value)}
              className="h-4 w-4 shrink-0 rounded border-line accent-[var(--color-accent)]"
            />
            <span>{opt.label}</span>
          </label>
        ))}
      </div>
    </fieldset>
  )
}

export interface FilterPanelProps {
  value: TransactionFiltersState
  onChange: (next: TransactionFiltersState) => void
  wallets: readonly Wallet[]
  baseCurrency: CurrencyCode
}

export function FilterPanel({ value, onChange, wallets, baseCurrency }: FilterPanelProps) {
  const { t, labelFor } = useI18n()

  function patch(partial: Partial<TransactionFiltersState>) {
    onChange({ ...value, ...partial })
  }

  const walletOptions: CheckboxOption<string>[] = wallets.map((w) => ({ value: w.id, label: w.name }))
  const directionOptions: CheckboxOption<Direction>[] = (['income', 'expense', 'transfer'] as const).map(
    (d) => ({ value: d, label: t.transaction.directions[d] }),
  )
  const typeOptions: CheckboxOption<string>[] = TRANSACTION_TYPES.map((type) => ({
    value: type.id,
    label: labelFor(type),
  }))

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.transaction.filter.title}</CardTitle>
        <Button variant="ghost" size="sm" onClick={() => onChange(createEmptyFilters())}>
          {t.transaction.filter.reset}
        </Button>
      </CardHeader>
      <CardBody className="grid grid-cols-1 gap-4 sm:grid-cols-2 lg:grid-cols-3">
        <Input
          label={t.common.search}
          placeholder={t.transaction.filter.searchPlaceholder}
          value={value.search}
          onChange={(e) => patch({ search: e.target.value })}
        />

        <Input
          label={t.transaction.filter.dateFrom}
          type="date"
          value={value.from}
          onChange={(e) => patch({ from: e.target.value })}
        />
        <Input
          label={t.transaction.filter.dateTo}
          type="date"
          value={value.to}
          onChange={(e) => patch({ to: e.target.value })}
        />

        <MoneyInput
          label={t.transaction.filter.amountMin}
          currency={baseCurrency}
          value={value.minBaseAmount}
          onChange={(next) => patch({ minBaseAmount: next })}
        />
        <MoneyInput
          label={t.transaction.filter.amountMax}
          currency={baseCurrency}
          value={value.maxBaseAmount}
          onChange={(next) => patch({ maxBaseAmount: next })}
        />

        <CheckboxGroup
          legend={t.transaction.directions.income + ' / ' + t.transaction.directions.expense + ' / ' + t.transaction.directions.transfer}
          options={directionOptions}
          selected={value.directions}
          onChange={(next) => patch({ directions: next })}
        />

        <CheckboxGroup
          legend={t.transaction.filter.wallet}
          options={walletOptions}
          selected={value.walletIds}
          onChange={(next) => patch({ walletIds: next })}
          scroll={walletOptions.length > 5}
        />

        <CheckboxGroup
          legend={t.transaction.filter.type}
          options={typeOptions}
          selected={value.typeIds}
          onChange={(next) => patch({ typeIds: next })}
          scroll
        />

        <fieldset className="flex flex-col gap-1.5 sm:col-span-2 lg:col-span-3">
          <legend className="text-sm font-medium text-text">{t.transaction.filter.category}</legend>
          <div className="flex max-h-48 flex-col gap-2 overflow-y-auto rounded-control border border-line p-2">
            {CATEGORY_GROUPS.map((group) => {
              const cats = categoriesInGroup(group)
              if (cats.length === 0) return null
              return (
                <div key={group} className="flex flex-col gap-1">
                  <p className="text-xs font-semibold uppercase tracking-wide text-faint">
                    {labelFor(CATEGORY_GROUP_LABELS[group])}
                  </p>
                  <div className="flex flex-col gap-1 pl-1 sm:grid sm:grid-cols-2 sm:gap-x-4 lg:grid-cols-3">
                    {cats.map((cat) => (
                      <label key={cat.id} className="flex items-center gap-2 text-sm text-text">
                        <input
                          type="checkbox"
                          checked={value.categoryIds.includes(cat.id)}
                          onChange={() =>
                            patch({
                              categoryIds: value.categoryIds.includes(cat.id)
                                ? value.categoryIds.filter((id) => id !== cat.id)
                                : [...value.categoryIds, cat.id],
                            })
                          }
                          className="h-4 w-4 shrink-0 rounded border-line accent-[var(--color-accent)]"
                        />
                        <span aria-hidden="true">{cat.emoji}</span>
                        <span>{labelFor(cat)}</span>
                      </label>
                    ))}
                  </div>
                </div>
              )
            })}
          </div>
        </fieldset>
      </CardBody>
    </Card>
  )
}
