/**
 * Reports: spending over time, category breakdown, income against expenses,
 * and a budget burn down, all converted to the profile's base currency.
 *
 * Everything on this page reads from the repository through useAsync rather
 * than caching anything of its own, the same pattern repo.tsx documents: a
 * local IndexedDB read is fast enough that a data fetching layer would only
 * add weight. The four report shapes themselves (spendingOverTime and the
 * rest) are pure functions in src/domain/reports.ts; this file's job is
 * picking the date range and granularity, fetching the rows they need, and
 * handing the results to the chart components in charts.tsx.
 */

import { useMemo, useState } from 'react'
import { endOfMonth, endOfYear, format, startOfMonth, startOfYear, subMonths } from 'date-fns'
import { useI18n } from '@/i18n'
import { useProfile } from '@/app/ProfileProvider'
import { useAsync, useRepository } from '@/app/repo'
import { Card, CardBody, CardHeader, CardTitle, EmptyState, Input, Select, Skeleton, staggerStyle } from '@/ui'
import {
  budgetBurndown, categoryBreakdown, incomeVsExpense, spendingOverTime, type Granularity,
} from '@neraca/domain/reports'
import { budgetPeriodRange } from '@neraca/domain/budget'
import { categoryById } from '@neraca/domain/categories'
import type { Budget, IsoDate } from '@neraca/domain/types'
import { BudgetBurndownChart, CategoryBreakdownChart, IncomeExpenseChart, SpendingOverTimeChart } from './charts'

type RangePreset = 'thisMonth' | 'lastMonth' | 'thisYear' | 'last12Months' | 'custom'

const RANGE_PRESETS: RangePreset[] = ['thisMonth', 'lastMonth', 'thisYear', 'last12Months', 'custom']
const GRANULARITIES: Granularity[] = ['day', 'week', 'month']

function iso(date: Date): IsoDate {
  return format(date, 'yyyy-MM-dd')
}

function presetRange(preset: Exclude<RangePreset, 'custom'>, today: Date): { from: IsoDate; to: IsoDate } {
  switch (preset) {
    case 'thisMonth':
      return { from: iso(startOfMonth(today)), to: iso(endOfMonth(today)) }
    case 'lastMonth': {
      const target = subMonths(today, 1)
      return { from: iso(startOfMonth(target)), to: iso(endOfMonth(target)) }
    }
    case 'thisYear':
      return { from: iso(startOfYear(today)), to: iso(endOfYear(today)) }
    case 'last12Months':
      return { from: iso(startOfMonth(subMonths(today, 11))), to: iso(endOfMonth(today)) }
  }
}

export default function ReportsPage() {
  const { t, locale, formatDate } = useI18n()
  const profile = useProfile()
  const repo = useRepository()

  // Captured once on mount rather than read fresh every render, so the
  // computed preset ranges (and the option labels built from them) stay
  // stable for the life of the page instead of drifting at midnight mid
  // session.
  const [today] = useState(() => new Date())

  const [preset, setPreset] = useState<RangePreset>('thisMonth')
  const [granularity, setGranularity] = useState<Granularity>('day')
  const defaultRange = useMemo(() => presetRange('thisMonth', today), [today])
  const [customFrom, setCustomFrom] = useState<IsoDate>(defaultRange.from)
  const [customTo, setCustomTo] = useState<IsoDate>(defaultRange.to)

  const range = preset === 'custom' ? { from: customFrom, to: customTo } : presetRange(preset, today)

  const { data: transactions, loading: transactionsLoading } = useAsync(
    () => repo.listTransactions({ profileId: profile.id, from: range.from, to: range.to }),
    [repo, profile.id, range.from, range.to],
  )

  const { data: budgets, loading: budgetsLoading } = useAsync(
    () => repo.listBudgets(profile.id),
    [repo, profile.id],
  )

  // Only the explicit override is stored in state; the effective selection
  // falls back to the first loaded budget on its own, so there is no need to
  // copy that default into state once the list arrives.
  const [budgetIdOverride, setBudgetIdOverride] = useState<string | null>(null)
  const selectedBudgetId = budgetIdOverride ?? budgets?.[0]?.id ?? null
  const selectedBudget: Budget | null = budgets?.find((b) => b.id === selectedBudgetId) ?? null
  const budgetRange = selectedBudget ? budgetPeriodRange(selectedBudget) : null

  const { data: budgetTransactions, loading: budgetTxLoading } = useAsync(
    () => (selectedBudget && budgetRange
      ? repo.listTransactions({ profileId: profile.id, from: budgetRange.start, to: budgetRange.end })
      : Promise.resolve([])),
    [repo, profile.id, selectedBudget?.id, budgetRange?.start, budgetRange?.end],
  )

  const spendingPoints = useMemo(
    () => (transactions ? spendingOverTime(transactions, profile.baseCurrency, granularity) : []),
    [transactions, profile.baseCurrency, granularity],
  )
  const categoryTotals = useMemo(
    () => (transactions ? categoryBreakdown(transactions, profile.baseCurrency) : []),
    [transactions, profile.baseCurrency],
  )
  const incomeExpensePoints = useMemo(
    () => (transactions ? incomeVsExpense(transactions, profile.baseCurrency, granularity) : []),
    [transactions, profile.baseCurrency, granularity],
  )
  const burndownPoints = useMemo(
    () => (selectedBudget && budgetTransactions
      ? budgetBurndown(selectedBudget, budgetTransactions, profile.baseCurrency)
      : []),
    [selectedBudget, budgetTransactions, profile.baseCurrency],
  )

  const rangeLabel = (option: RangePreset): string => {
    switch (option) {
      case 'thisMonth':
        return t.common.thisMonth
      case 'thisYear':
        return t.common.thisYear
      case 'custom':
        return t.common.custom
      case 'lastMonth':
        return formatDate(subMonths(today, 1), { month: 'short', year: 'numeric' })
      case 'last12Months': {
        const r = presetRange('last12Months', today)
        // "to" is reused as a plain joiner between two month labels rather
        // than its usual role as a field label; no dedicated "X to Y" range
        // phrase exists in the dictionary to build this option text from.
        return `${formatDate(r.from, { month: 'short', year: 'numeric' })} ${t.common.to.toLowerCase()} ${formatDate(r.to, { month: 'short', year: 'numeric' })}`
      }
    }
  }

  const granularityLabel = (option: Granularity): string => {
    switch (option) {
      case 'day': return t.recurring.frequencies.daily
      case 'week': return t.recurring.frequencies.weekly
      case 'month': return t.recurring.frequencies.monthly
    }
  }

  const budgetLabel = (budget: Budget): string => {
    const category = budget.categoryId ? categoryById(budget.categoryId) : null
    const categoryLabel = category ? (locale === 'id' ? category.id_ : category.en) : t.budget.fields.allCategories
    const periodLabel = budget.period === 'monthly'
      ? formatDate(budget.periodKey, { month: 'short', year: 'numeric' })
      : formatDate(budget.periodKey, { year: 'numeric' })
    return `${budget.description || categoryLabel} (${periodLabel})`
  }

  const loading = transactionsLoading
  const hasAnyData = (transactions?.length ?? 0) > 0

  return (
    <div className="flex flex-col gap-4 p-4 sm:p-6">
      <h1 className="text-lg font-semibold text-text">{t.report.title}</h1>

      <Card>
        <CardBody className="flex flex-col gap-4 sm:flex-row sm:flex-wrap sm:items-end">
          <div className="w-full sm:w-56">
            <Select
              label={t.report.dateRange}
              value={preset}
              onChange={(event) => setPreset(event.target.value as RangePreset)}
            >
              {RANGE_PRESETS.map((option) => (
                <option key={option} value={option}>{rangeLabel(option)}</option>
              ))}
            </Select>
          </div>

          {preset === 'custom' && (
            <>
              <div className="w-full sm:w-44">
                <Input
                  type="date"
                  label={t.common.from}
                  value={customFrom}
                  max={customTo}
                  onChange={(event) => setCustomFrom(event.target.value)}
                />
              </div>
              <div className="w-full sm:w-44">
                <Input
                  type="date"
                  label={t.common.to}
                  value={customTo}
                  min={customFrom}
                  onChange={(event) => setCustomTo(event.target.value)}
                />
              </div>
            </>
          )}

          <div className="w-full sm:w-40">
            <Select
              label={t.budget.fields.period}
              value={granularity}
              onChange={(event) => setGranularity(event.target.value as Granularity)}
            >
              {GRANULARITIES.map((option) => (
                <option key={option} value={option}>{granularityLabel(option)}</option>
              ))}
            </Select>
          </div>
        </CardBody>
      </Card>

      <div className="grid grid-cols-1 gap-4 lg:grid-cols-2">
        {loading ? (
          <>
            <Skeleton shape="block" className="h-72 w-full" />
            <Skeleton shape="block" className="h-72 w-full" />
            <Skeleton shape="block" className="h-72 w-full" />
          </>
        ) : !hasAnyData ? (
          <div className="lg:col-span-2">
            <EmptyState title={t.report.noData} description={t.empty.reportsData} />
          </div>
        ) : (
          <>
            <Card className="animate-rise-in" style={staggerStyle(0)}>
              <CardHeader>
                <CardTitle>{t.report.spendingOverTime}</CardTitle>
              </CardHeader>
              <CardBody>
                {spendingPoints.length === 0 ? (
                  <EmptyState title={t.report.noData} />
                ) : (
                  <SpendingOverTimeChart
                    points={spendingPoints}
                    currency={profile.baseCurrency}
                    granularity={granularity}
                    locale={locale}
                    t={t}
                  />
                )}
              </CardBody>
            </Card>

            <Card className="animate-rise-in" style={staggerStyle(1)}>
              <CardHeader>
                <CardTitle>{t.report.categoryBreakdown}</CardTitle>
              </CardHeader>
              <CardBody>
                {categoryTotals.length === 0 ? (
                  <EmptyState title={t.report.noData} />
                ) : (
                  <CategoryBreakdownChart
                    totals={categoryTotals}
                    currency={profile.baseCurrency}
                    locale={locale}
                    t={t}
                  />
                )}
              </CardBody>
            </Card>

            <Card className="animate-rise-in" style={staggerStyle(2)}>
              <CardHeader>
                <CardTitle>{t.report.incomeVsExpense}</CardTitle>
              </CardHeader>
              <CardBody>
                {incomeExpensePoints.length === 0 ? (
                  <EmptyState title={t.report.noData} />
                ) : (
                  <IncomeExpenseChart
                    points={incomeExpensePoints}
                    currency={profile.baseCurrency}
                    granularity={granularity}
                    locale={locale}
                    t={t}
                  />
                )}
              </CardBody>
            </Card>
          </>
        )}

        {/*
          Independent of the range and loading state above: the burn down
          tracks a budget's own period, chosen from its own selector, not the
          date range control at the top of the page. Hiding it behind
          hasAnyData would make a budget with real spending disappear just
          because the unrelated top level range happens to be empty.
        */}
        <Card className="animate-rise-in" style={staggerStyle(3)}>
          <CardHeader className="flex-wrap gap-y-3">
            <CardTitle>{t.report.budgetBurnDown}</CardTitle>
            {budgets && budgets.length > 0 && (
              <div className="w-full sm:w-64">
                <Select
                  label={t.budget.title}
                  value={selectedBudgetId ?? ''}
                  onChange={(event) => setBudgetIdOverride(event.target.value)}
                  className="text-xs"
                >
                  {budgets.map((b) => (
                    <option key={b.id} value={b.id}>{budgetLabel(b)}</option>
                  ))}
                </Select>
              </div>
            )}
          </CardHeader>
          <CardBody>
            {budgetsLoading || budgetTxLoading ? (
              <Skeleton shape="block" className="h-64 w-full" />
            ) : !budgets || budgets.length === 0 ? (
              <EmptyState title={t.empty.budgets} />
            ) : selectedBudget && burndownPoints.length > 0 ? (
              <BudgetBurndownChart
                points={burndownPoints}
                currency={profile.baseCurrency}
                locale={locale}
                t={t}
              />
            ) : (
              <EmptyState title={t.report.noData} />
            )}
          </CardBody>
        </Card>
      </div>
    </div>
  )
}
