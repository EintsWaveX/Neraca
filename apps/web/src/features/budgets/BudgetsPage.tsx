/**
 * Budgets screen: a period switcher over cards evaluated against the
 * transactions that actually fell in that period, plus create, edit and
 * delete for the budgets themselves.
 */

import { useMemo, useState, type ReactNode } from 'react'
import { useRepository, useAsync } from '@/app/repo'
import { useProfile } from '@/app/ProfileProvider'
import { useI18n } from '@/i18n'
import type { Budget, BudgetPeriod } from '@neraca/domain/types'
import { activeAlerts, budgetPeriodRange, evaluateBudget, type BudgetStatus } from '@neraca/domain/budget'
import { abs, formatMoney } from '@neraca/domain/money'
import { categoryById } from '@neraca/domain/categories'
import { Badge, Button, EmptyState, Modal, ProgressBar, Skeleton, Tabs } from '@/ui'
import { Block, Page, RuledRow } from '@/design/primitives'
import { MoneyFigure } from '@/design/Figure'
import { BudgetForm, defaultPeriodKeyFor, PeriodKeyField } from './BudgetForm'

const STATE_BAR_CLASS: Record<BudgetStatus['state'], string> = {
  under: 'bg-credit',
  approaching: 'bg-stamp',
  over: 'bg-debit',
}

const STATE_TEXT_CLASS: Record<BudgetStatus['state'], string> = {
  under: 'text-credit',
  approaching: 'text-stamp',
  over: 'text-debit',
}

/* The margin rule on an alert note. Filled panels in two alarm colours were
   the loudest thing on a screen whose own rows already say the same thing. */
const STATE_RULE_CLASS: Record<BudgetStatus['state'], string> = {
  under: 'border-credit',
  approaching: 'border-stamp',
  over: 'border-debit',
}

/** 0 to 100, and never Infinity or NaN even when a budget carries a zero limit. */
function clampedPercent(fraction: number): number {
  return Math.max(0, Math.min(100, Math.round(fraction * 100)))
}

export default function BudgetsPage() {
  const repo = useRepository()
  const profile = useProfile()
  const { t, labelFor } = useI18n()

  const [period, setPeriod] = useState<BudgetPeriod>('monthly')
  const [periodKey, setPeriodKey] = useState(() => defaultPeriodKeyFor('monthly'))

  const [formOpen, setFormOpen] = useState(false)
  const [editingBudget, setEditingBudget] = useState<Budget | null>(null)
  const [deleteTarget, setDeleteTarget] = useState<Budget | null>(null)

  const budgetsAsync = useAsync(() => repo.listBudgets(profile.id), [repo, profile.id])
  const budgets = budgetsAsync.data ?? []

  const periodBudgets = useMemo(
    () => budgets.filter((budget) => budget.period === period && budget.periodKey === periodKey),
    [budgets, period, periodKey],
  )

  // budgetPeriodRange only reads `period` and `periodKey` off the budget it is
  // given, so a minimal stand-in lets the transaction range be computed for
  // the period the page is showing even before any budget exists for it.
  const periodRange = useMemo(
    () => budgetPeriodRange({ period, periodKey } as Budget),
    [period, periodKey],
  )

  const transactionsAsync = useAsync(
    () => repo.listTransactions({
      profileId: profile.id,
      from: periodRange.start,
      to: periodRange.end,
      directions: ['expense'],
    }),
    [repo, profile.id, periodRange.start, periodRange.end],
  )
  const transactions = transactionsAsync.data ?? []

  const statuses = useMemo(
    () => periodBudgets.map((budget) => evaluateBudget(budget, transactions, profile.baseCurrency)),
    [periodBudgets, transactions, profile.baseCurrency],
  )

  const alerts = useMemo(
    () => activeAlerts(periodBudgets, transactions, profile.baseCurrency),
    [periodBudgets, transactions, profile.baseCurrency],
  )

  function categoryLabel(categoryId: string | null): string {
    if (categoryId === null) return t.budget.fields.allCategories
    const category = categoryById(categoryId)
    return category ? `${category.emoji} ${labelFor(category)}` : categoryId
  }

  function openCreate() {
    setEditingBudget(null)
    setFormOpen(true)
  }

  function openEdit(budget: Budget) {
    setEditingBudget(budget)
    setFormOpen(true)
  }

  async function handleSave(budget: Budget) {
    await repo.putBudget(budget)
    setFormOpen(false)
    setEditingBudget(null)
    budgetsAsync.reload()
  }

  async function confirmDelete() {
    if (!deleteTarget) return
    await repo.deleteBudget(deleteTarget.id)
    setDeleteTarget(null)
    budgetsAsync.reload()
  }

  const loading = budgetsAsync.loading || transactionsAsync.loading

  return (
    <Page>
      <header className="flex flex-wrap items-center justify-between gap-3">
        <h1 className="text-h2 leading-tight">{t.budget.title}</h1>
        <Button onClick={openCreate}>{t.budget.add}</Button>
      </header>

      {/*
        Alerts stay on this screen even though every row below carries its own
        state, because a budget can be over in a period you are not currently
        looking at. They are marginal notes against a coloured rule rather than
        filled panels: two alarm colours in solid blocks were the loudest thing
        on the page, sitting above the figures they were warning about.
      */}
      {alerts.length > 0 && (
        <div className="mt-6">
          {alerts.map((status, index) => (
            <div
              key={status.budget.id}
              className={`print-in flex flex-wrap items-baseline justify-between gap-2 border-l-2 py-1.5 pl-3 text-sm ${STATE_RULE_CLASS[status.state]}`}
              style={{ '--print-index': index } as React.CSSProperties}
            >
              <span className="text-ink">{categoryLabel(status.budget.categoryId)}</span>
              <span className={STATE_TEXT_CLASS[status.state]}>
                {status.state === 'over'
                  ? t('budget.overLimit', { amount: formatMoney(abs(status.remaining)) })
                  : t.budget.nearLimit}
              </span>
            </div>
          ))}
        </div>
      )}

      <div className="mt-8 flex flex-col gap-3 sm:flex-row sm:items-end sm:justify-between">
        <Tabs
          label={t.budget.fields.period}
          value={period}
          items={[
            { id: 'monthly', label: t.budget.periods.monthly, content: null },
            { id: 'yearly', label: t.budget.periods.yearly, content: null },
          ]}
          onChange={(id) => {
            const nextPeriod = id as BudgetPeriod
            setPeriod(nextPeriod)
            setPeriodKey(defaultPeriodKeyFor(nextPeriod))
          }}
        />
        <div className="max-w-xs">
          <PeriodKeyField
            period={period}
            value={periodKey}
            onChange={setPeriodKey}
            label={t.budget.fields.periodKey}
          />
        </div>
      </div>

      <Block title={periodKey}>
        {loading ? (
          <div className="flex flex-col gap-3 py-2" aria-hidden="true">
            <Skeleton shape="block" className="h-16 w-full" />
            <Skeleton shape="block" className="h-16 w-full" />
          </div>
        ) : periodBudgets.length === 0 ? (
          <EmptyState
            title={t.empty.budgets}
            action={
              <Button size="sm" onClick={openCreate}>
                {t.budget.add}
              </Button>
            }
          />
        ) : (
          statuses.map((status, index) => {
            const percent = clampedPercent(status.fraction)
            const label = categoryLabel(status.budget.categoryId)
            return (
              <RuledRow
                key={status.budget.id}
                index={index}
                label={label}
                {...(status.budget.description ? { note: status.budget.description } : {})}
                value={
                  <span className="flex items-baseline gap-2 text-sm">
                    <MoneyFigure
                      value={status.spent}
                      tone={status.state === 'over' ? 'debit' : 'neutral'}
                      showSymbol={false}
                    />
                    <span className="text-ink-faint">/</span>
                    <MoneyFigure value={status.limit} className="text-ink-muted" showSymbol={false} />
                    <Badge
                      tone={
                        status.state === 'under'
                          ? 'positive'
                          : status.state === 'approaching'
                            ? 'warning'
                            : 'negative'
                      }
                    >
                      {percent}%
                    </Badge>
                  </span>
                }
                below={
                  <div className="flex flex-wrap items-center gap-3">
                    <ProgressBar
                      value={percent}
                      label={label}
                      barClassName={STATE_BAR_CLASS[status.state]}
                      className="min-w-32 flex-1"
                    />
                    <span className={`shrink-0 text-xs ${STATE_TEXT_CLASS[status.state]}`}>
                      {status.state === 'over'
                        ? t('budget.overLimit', { amount: formatMoney(abs(status.remaining)) })
                        : t('budget.remaining', { amount: formatMoney(status.remaining) })}
                    </span>
                    <span className="flex shrink-0 gap-1">
                      <IconButton
                        label={`${t.common.edit}: ${label}`}
                        onClick={() => openEdit(status.budget)}
                      >
                        <PencilIcon />
                      </IconButton>
                      <IconButton
                        label={`${t.common.delete}: ${label}`}
                        onClick={() => setDeleteTarget(status.budget)}
                      >
                        <TrashIcon />
                      </IconButton>
                    </span>
                  </div>
                }
              />
            )
          })
        )}
      </Block>

      <Modal
        open={formOpen}
        onClose={() => {
          setFormOpen(false)
          setEditingBudget(null)
        }}
        title={editingBudget ? t.budget.edit : t.budget.add}
      >
        <BudgetForm
          profileId={profile.id}
          baseCurrency={profile.baseCurrency}
          initial={editingBudget}
          defaultPeriod={period}
          defaultPeriodKey={periodKey}
          onSave={handleSave}
          onCancel={() => {
            setFormOpen(false)
            setEditingBudget(null)
          }}
        />
      </Modal>

      <Modal
        open={deleteTarget !== null}
        onClose={() => setDeleteTarget(null)}
        title={t.budget.delete}
        footer={
          <>
            <Button variant="secondary" onClick={() => setDeleteTarget(null)}>
              {t.common.cancel}
            </Button>
            <Button variant="danger" onClick={confirmDelete}>
              {t.common.delete}
            </Button>
          </>
        }
      >
        <p className="text-sm text-ink-muted">{t.budget.deleteConfirm}</p>
      </Modal>
    </Page>
  )
}

function IconButton({ label, onClick, children }: { label: string; onClick: () => void; children: ReactNode }) {
  return (
    <button
      type="button"
      aria-label={label}
      title={label}
      onClick={onClick}
      className="inline-flex h-7 w-7 items-center justify-center rounded-control text-muted hover:bg-surface-sunken hover:text-text"
    >
      {children}
    </button>
  )
}

function PencilIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true" className="h-4 w-4">
      <path
        d="M13.5 3.5l3 3L6 17H3v-3L13.5 3.5z"
        stroke="currentColor"
        strokeWidth="1.4"
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  )
}

function TrashIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true" className="h-4 w-4">
      <path
        d="M4 6h12M8 6V4.5A1.5 1.5 0 019.5 3h1A1.5 1.5 0 0112 4.5V6m-6.5 0l.6 9.4a1.5 1.5 0 001.5 1.4h3.8a1.5 1.5 0 001.5-1.4L14.5 6"
        stroke="currentColor"
        strokeWidth="1.4"
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  )
}
