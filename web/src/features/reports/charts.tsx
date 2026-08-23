/**
 * Chart components for the reports screen.
 *
 * Every colour drawn here comes from the design tokens in src/index.css,
 * read at runtime with getComputedStyle rather than hardcoded, so a chart
 * painted in light mode still reads correctly the moment the theme flips.
 * useChartColors watches both an explicit theme attribute on <html> (set by
 * ThemeToggle) and the system colour scheme media query (used when no
 * explicit choice has been made), and recomputes whenever either changes.
 *
 * Each chart pairs its canvas with a visually hidden table carrying the same
 * numbers, because a screen reader gets nothing at all from an SVG line or
 * bar. The table is never display:none (that would drop it from the
 * accessibility tree too), it is sr-only: present, readable by assistive
 * tech, invisible on screen.
 */

import { useEffect, useState } from 'react'
import {
  Area, AreaChart, Bar, BarChart, CartesianGrid, Legend, Line, LineChart,
  ResponsiveContainer, Tooltip, XAxis, YAxis,
} from 'recharts'
import type { Granularity, CategoryTotal, IncomeExpensePoint, SeriesPoint, BurndownPoint } from '@/domain/reports'
import { formatMoney, formatMoneyCompact, type Money } from '@/domain/money'
import type { CurrencyCode } from '@/domain/currency'
import { CATEGORY_BY_ID, CATEGORY_GROUP_LABELS } from '@/domain/categories'
import type { Locale } from '@/domain/types'
import { formatDate as formatDateI18n, labelFor as labelForI18n, type T } from '@/i18n'

// ---------------------------------------------------------------------------
// Colour tokens
// ---------------------------------------------------------------------------

export interface ChartColors {
  accent: string
  positive: string
  negative: string
  warning: string
  muted: string
  faint: string
  line: string
}

function readToken(name: string): string {
  const value = getComputedStyle(document.documentElement).getPropertyValue(name).trim()
  // A CSS custom property that fails to resolve reads back as an empty
  // string, never as an error. Falling back to currentColor keeps a chart
  // legible instead of drawing invisible shapes if a token is ever renamed.
  return value === '' ? 'currentColor' : value
}

function readChartColors(): ChartColors {
  return {
    accent: readToken('--accent'),
    positive: readToken('--positive'),
    negative: readToken('--negative'),
    warning: readToken('--warning'),
    muted: readToken('--text-muted'),
    faint: readToken('--text-faint'),
    line: readToken('--border'),
  }
}

/** Tracks the design tokens live, so every chart repaints when the theme changes. */
export function useChartColors(): ChartColors {
  const [colors, setColors] = useState<ChartColors>(readChartColors)

  useEffect(() => {
    const update = () => setColors(readChartColors())
    update()

    // Covers an explicit light/dark choice: ThemeToggle sets data-theme on
    // <html>, which is a plain attribute change no event fires for on its own.
    const observer = new MutationObserver(update)
    observer.observe(document.documentElement, { attributes: true, attributeFilter: ['data-theme'] })

    // Covers "system": no data-theme attribute at all, so the tokens instead
    // follow the OS level preference through the prefers-color-scheme query.
    const media = window.matchMedia('(prefers-color-scheme: dark)')
    media.addEventListener('change', update)

    return () => {
      observer.disconnect()
      media.removeEventListener('change', update)
    }
  }, [])

  return colors
}

// ---------------------------------------------------------------------------
// Chart motion
// ---------------------------------------------------------------------------

export interface ChartMotion {
  /** recharts' own switch for its draw-in animation. */
  isAnimationActive: boolean
  animationDuration: number
}

/** Reads --dur-slow the same way readToken above reads colours, so the chart's draw-in timing stays in step with the rest of the motion system instead of a duration invented just for recharts. Falls back to 320ms (the token's own value) if the property somehow fails to resolve. */
function readAnimationDuration(): number {
  const raw = getComputedStyle(document.documentElement).getPropertyValue('--dur-slow').trim()
  const parsed = Number.parseFloat(raw)
  return Number.isFinite(parsed) ? parsed : 320
}

/**
 * Whether recharts should animate at all, and how long that animation
 * should take. Turned off entirely under reduced motion rather than left to
 * the global CSS rule in index.css, because recharts drives its draw-in
 * with a JS-timed interpolation, not a CSS animation or transition that
 * rule can reach.
 */
export function useChartMotion(): ChartMotion {
  const [reduced, setReduced] = useState(() => window.matchMedia('(prefers-reduced-motion: reduce)').matches)

  useEffect(() => {
    const media = window.matchMedia('(prefers-reduced-motion: reduce)')
    const update = () => setReduced(media.matches)
    update()
    media.addEventListener('change', update)
    return () => media.removeEventListener('change', update)
  }, [])

  return { isAnimationActive: !reduced, animationDuration: readAnimationDuration() }
}

// ---------------------------------------------------------------------------
// Shared helpers
// ---------------------------------------------------------------------------

function periodLabel(period: string, granularity: Granularity, locale: Locale): string {
  if (granularity === 'month') return formatDateI18n(period, locale, { month: 'short', year: 'numeric' })
  return formatDateI18n(period, locale, { day: 'numeric', month: 'short' })
}

function axisMoneyTick(minor: number, currency: CurrencyCode, locale: Locale): string {
  return formatMoneyCompact({ minor, currency }, locale === 'id' ? 'id-ID' : 'en-GB')
}

/**
 * recharts' Tooltip typings pass every formatter value as `ValueType |
 * undefined` (a union that also covers string and arrays, for charts whose
 * series are not numeric) and every label as `ReactNode`, since the same
 * component serves every chart shape in the library. These two helpers take
 * `unknown` on purpose and narrow at runtime, rather than annotating the
 * inline callbacks with the plain `number` and `string` types this file
 * actually always sees, which is what recharts' own type declares.
 */
function tooltipMoneyValue(value: unknown, currency: CurrencyCode, locale: Locale): string {
  return typeof value === 'number' ? formatMoney({ minor: value, currency }, { locale }) : String(value ?? '')
}

function tooltipDateLabel(label: unknown, format: (date: string) => string): string {
  return typeof label === 'string' ? format(label) : String(label ?? '')
}

/** categoryBreakdown already sorts largest first; this keeps the top N and folds the rest into one "Other" row. */
export function topCategoriesWithOther(
  totals: readonly CategoryTotal[],
  currency: CurrencyCode,
  otherLabel: string,
  locale: Locale,
  limit = 10,
): Array<{ id: string; label: string; amount: Money; fraction: number }> {
  const top = totals.slice(0, limit).map((row) => {
    const category = CATEGORY_BY_ID.get(row.categoryId)
    return {
      id: row.categoryId,
      label: category ? labelForI18n(category, locale) : row.categoryId,
      amount: row.amount,
      fraction: row.fraction,
    }
  })
  const rest = totals.slice(limit)
  if (rest.length === 0) return top
  const restMinor = rest.reduce((sum, row) => sum + row.amount.minor, 0)
  const restFraction = rest.reduce((sum, row) => sum + row.fraction, 0)
  return [...top, { id: 'other', label: otherLabel, amount: { minor: restMinor, currency }, fraction: restFraction }]
}

// ---------------------------------------------------------------------------
// a) Spending over time
// ---------------------------------------------------------------------------

export interface SpendingOverTimeChartProps {
  points: readonly SeriesPoint[]
  currency: CurrencyCode
  granularity: Granularity
  locale: Locale
  t: T
}

export function SpendingOverTimeChart({ points, currency, granularity, locale, t }: SpendingOverTimeChartProps) {
  const colors = useChartColors()
  const motion = useChartMotion()
  const data = points.map((p) => ({ period: p.period, minor: p.amount.minor }))
  const total = points.reduce((sum, p) => sum + p.amount.minor, 0)
  const peak = points.reduce<SeriesPoint | null>((max, p) => (max === null || p.amount.minor > max.amount.minor ? p : max), null)

  return (
    <div className="flex flex-col gap-2">
      <div className="h-64 w-full" aria-hidden="true">
        <ResponsiveContainer width="100%" height="100%">
          <AreaChart data={data} margin={{ top: 8, right: 8, left: 0, bottom: 0 }}>
            <defs>
              <linearGradient id="spendingFill" x1="0" y1="0" x2="0" y2="1">
                <stop offset="0%" stopColor={colors.accent} stopOpacity={0.35} />
                <stop offset="100%" stopColor={colors.accent} stopOpacity={0.02} />
              </linearGradient>
            </defs>
            <CartesianGrid stroke={colors.line} strokeDasharray="3 3" vertical={false} />
            <XAxis
              dataKey="period"
              tickFormatter={(value: string) => periodLabel(value, granularity, locale)}
              tick={{ fill: colors.muted, fontSize: 12 }}
              stroke={colors.line}
              minTickGap={24}
            />
            <YAxis
              tickFormatter={(value: number) => axisMoneyTick(value, currency, locale)}
              tick={{ fill: colors.muted, fontSize: 12 }}
              stroke={colors.line}
              width={72}
            />
            <Tooltip
              formatter={(value: unknown) => tooltipMoneyValue(value, currency, locale)}
              labelFormatter={(label: unknown) => tooltipDateLabel(label, (d) => periodLabel(d, granularity, locale))}
              contentStyle={{ background: 'var(--surface)', border: '1px solid var(--border)', borderRadius: 8, color: 'var(--text)' }}
            />
            <Area
              type="monotone"
              dataKey="minor"
              stroke={colors.accent}
              strokeWidth={2}
              fill="url(#spendingFill)"
              isAnimationActive={motion.isAnimationActive}
              animationDuration={motion.animationDuration}
            />
          </AreaChart>
        </ResponsiveContainer>
      </div>
      <p className="text-xs text-muted">
        {t.report.totalExpense}: {formatMoney({ minor: total, currency }, { locale })}
        {peak && total > 0 && (
          <>
            {' '}
            {'·'} {periodLabel(peak.period, granularity, locale)}: {formatMoney(peak.amount, { locale })}
          </>
        )}
      </p>
      <table className="sr-only">
        <caption>{t.report.spendingOverTime}</caption>
        <thead>
          <tr>
            <th scope="col">{t.transaction.fields.date}</th>
            <th scope="col">{t.report.totalExpense}</th>
          </tr>
        </thead>
        <tbody>
          {points.map((p) => (
            <tr key={p.period}>
              <td>{periodLabel(p.period, granularity, locale)}</td>
              <td>{formatMoney(p.amount, { locale })}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  )
}

// ---------------------------------------------------------------------------
// b) Category breakdown
// ---------------------------------------------------------------------------

export interface CategoryBreakdownChartProps {
  totals: readonly CategoryTotal[]
  currency: CurrencyCode
  locale: Locale
  t: T
}

export function CategoryBreakdownChart({ totals, currency, locale, t }: CategoryBreakdownChartProps) {
  const colors = useChartColors()
  const motion = useChartMotion()
  // No dedicated "long tail" bucket string exists in the dictionary; the
  // "Other" category group already carries this exact meaning in both
  // locales, so it is reused here rather than inventing new copy.
  const rows = topCategoriesWithOther(totals, currency, labelForI18n(CATEGORY_GROUP_LABELS.other, locale), locale)
  const data = rows.map((row) => ({ label: row.label, minor: row.amount.minor, fraction: row.fraction }))
  const top = rows[0]

  // Horizontal bars: readable at any label length, and it scales to ten plus
  // rows without turning into unreadable pie wedges.
  const height = Math.max(220, rows.length * 36)

  return (
    <div className="flex flex-col gap-2">
      <div className="w-full" style={{ height }} aria-hidden="true">
        <ResponsiveContainer width="100%" height="100%">
          <BarChart data={data} layout="vertical" margin={{ top: 4, right: 24, left: 8, bottom: 4 }}>
            <CartesianGrid stroke={colors.line} strokeDasharray="3 3" horizontal={false} />
            <XAxis
              type="number"
              tickFormatter={(value: number) => axisMoneyTick(value, currency, locale)}
              tick={{ fill: colors.muted, fontSize: 12 }}
              stroke={colors.line}
            />
            <YAxis
              type="category"
              dataKey="label"
              width={128}
              tick={{ fill: colors.muted, fontSize: 12 }}
              stroke={colors.line}
            />
            <Tooltip
              formatter={(value: unknown) => tooltipMoneyValue(value, currency, locale)}
              contentStyle={{ background: 'var(--surface)', border: '1px solid var(--border)', borderRadius: 8, color: 'var(--text)' }}
            />
            <Bar
              dataKey="minor"
              fill={colors.accent}
              radius={[0, 4, 4, 0]}
              isAnimationActive={motion.isAnimationActive}
              animationDuration={motion.animationDuration}
            />
          </BarChart>
        </ResponsiveContainer>
      </div>
      {top && (
        <p className="text-xs text-muted">
          {t.report.topCategory}: {top.label} ({formatMoney(top.amount, { locale })}, {Math.round(top.fraction * 100)}%)
        </p>
      )}
      <table className="sr-only">
        <caption>{t.report.categoryBreakdown}</caption>
        <thead>
          <tr>
            <th scope="col">{t.transaction.fields.category}</th>
            <th scope="col">{t.report.totalExpense}</th>
            <th scope="col">%</th>
          </tr>
        </thead>
        <tbody>
          {rows.map((row) => (
            <tr key={row.id}>
              <td>{row.label}</td>
              <td>{formatMoney(row.amount, { locale })}</td>
              <td>{Math.round(row.fraction * 100)}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  )
}

// ---------------------------------------------------------------------------
// c) Income against expenses
// ---------------------------------------------------------------------------

export interface IncomeExpenseChartProps {
  points: readonly IncomeExpensePoint[]
  currency: CurrencyCode
  granularity: Granularity
  locale: Locale
  t: T
}

export function IncomeExpenseChart({ points, currency, granularity, locale, t }: IncomeExpenseChartProps) {
  const colors = useChartColors()
  const motion = useChartMotion()
  const data = points.map((p) => ({ period: p.period, income: p.income.minor, expense: p.expense.minor }))
  const totalIncome = points.reduce((sum, p) => sum + p.income.minor, 0)
  const totalExpense = points.reduce((sum, p) => sum + p.expense.minor, 0)

  return (
    <div className="flex flex-col gap-2">
      <div className="h-64 w-full" aria-hidden="true">
        <ResponsiveContainer width="100%" height="100%">
          <BarChart data={data} margin={{ top: 8, right: 8, left: 0, bottom: 0 }}>
            <CartesianGrid stroke={colors.line} strokeDasharray="3 3" vertical={false} />
            <XAxis
              dataKey="period"
              tickFormatter={(value: string) => periodLabel(value, granularity, locale)}
              tick={{ fill: colors.muted, fontSize: 12 }}
              stroke={colors.line}
              minTickGap={24}
            />
            <YAxis
              tickFormatter={(value: number) => axisMoneyTick(value, currency, locale)}
              tick={{ fill: colors.muted, fontSize: 12 }}
              stroke={colors.line}
              width={72}
            />
            <Tooltip
              formatter={(value: unknown) => tooltipMoneyValue(value, currency, locale)}
              labelFormatter={(label: unknown) => tooltipDateLabel(label, (d) => periodLabel(d, granularity, locale))}
              contentStyle={{ background: 'var(--surface)', border: '1px solid var(--border)', borderRadius: 8, color: 'var(--text)' }}
            />
            <Legend
              formatter={(value: string) => (value === 'income' ? t.transaction.directions.income : t.transaction.directions.expense)}
              wrapperStyle={{ fontSize: 12, color: colors.muted }}
            />
            <Bar
              dataKey="income"
              name="income"
              fill={colors.positive}
              radius={[3, 3, 0, 0]}
              isAnimationActive={motion.isAnimationActive}
              animationDuration={motion.animationDuration}
            />
            <Bar
              dataKey="expense"
              name="expense"
              fill={colors.negative}
              radius={[3, 3, 0, 0]}
              isAnimationActive={motion.isAnimationActive}
              animationDuration={motion.animationDuration}
            />
          </BarChart>
        </ResponsiveContainer>
      </div>
      <p className="text-xs text-muted">
        {t.report.totalIncome}: {formatMoney({ minor: totalIncome, currency }, { locale })}
        {' · '}
        {t.report.totalExpense}: {formatMoney({ minor: totalExpense, currency }, { locale })}
        {' · '}
        {t.report.netBalance}: {formatMoney({ minor: totalIncome - totalExpense, currency }, { locale })}
      </p>
      <table className="sr-only">
        <caption>{t.report.incomeVsExpense}</caption>
        <thead>
          <tr>
            <th scope="col">{t.transaction.fields.date}</th>
            <th scope="col">{t.transaction.directions.income}</th>
            <th scope="col">{t.transaction.directions.expense}</th>
          </tr>
        </thead>
        <tbody>
          {points.map((p) => (
            <tr key={p.period}>
              <td>{periodLabel(p.period, granularity, locale)}</td>
              <td>{formatMoney(p.income, { locale })}</td>
              <td>{formatMoney(p.expense, { locale })}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  )
}

// ---------------------------------------------------------------------------
// d) Budget burn down
// ---------------------------------------------------------------------------

export interface BudgetBurndownChartProps {
  points: readonly BurndownPoint[]
  currency: CurrencyCode
  locale: Locale
  t: T
}

export function BudgetBurndownChart({ points, currency, locale, t }: BudgetBurndownChartProps) {
  const colors = useChartColors()
  const motion = useChartMotion()
  const data = points.map((p) => ({ date: p.date, cumulative: p.cumulative.minor, ideal: p.ideal.minor }))
  const last = points[points.length - 1]

  return (
    <div className="flex flex-col gap-2">
      <div className="h-64 w-full" aria-hidden="true">
        <ResponsiveContainer width="100%" height="100%">
          <LineChart data={data} margin={{ top: 8, right: 8, left: 0, bottom: 0 }}>
            <CartesianGrid stroke={colors.line} strokeDasharray="3 3" vertical={false} />
            <XAxis
              dataKey="date"
              tickFormatter={(value: string) => formatDateI18n(value, locale, { day: 'numeric', month: 'short' })}
              tick={{ fill: colors.muted, fontSize: 12 }}
              stroke={colors.line}
              minTickGap={24}
            />
            <YAxis
              tickFormatter={(value: number) => axisMoneyTick(value, currency, locale)}
              tick={{ fill: colors.muted, fontSize: 12 }}
              stroke={colors.line}
              width={72}
            />
            <Tooltip
              formatter={(value: unknown) => tooltipMoneyValue(value, currency, locale)}
              labelFormatter={(label: unknown) =>
                tooltipDateLabel(label, (d) => formatDateI18n(d, locale, { day: 'numeric', month: 'short', year: 'numeric' }))}
              contentStyle={{ background: 'var(--surface)', border: '1px solid var(--border)', borderRadius: 8, color: 'var(--text)' }}
            />
            <Legend
              // No standalone "actual spend" / "ideal pace" pair of words
              // exists in the dictionary. The chart's own title reads
              // correctly for the running total line, and "On track" reads
              // correctly for the even pace reference line, so those two
              // existing strings are reused as the series names.
              formatter={(value: string) => (value === 'cumulative' ? t.report.budgetBurnDown : t.budget.onTrack)}
              wrapperStyle={{ fontSize: 12, color: colors.muted }}
            />
            <Line
              type="monotone"
              dataKey="ideal"
              name="ideal"
              stroke={colors.faint}
              strokeWidth={2}
              strokeDasharray="4 4"
              dot={false}
              isAnimationActive={motion.isAnimationActive}
              animationDuration={motion.animationDuration}
            />
            <Line
              type="monotone"
              dataKey="cumulative"
              name="cumulative"
              stroke={colors.accent}
              strokeWidth={2}
              dot={false}
              isAnimationActive={motion.isAnimationActive}
              animationDuration={motion.animationDuration}
            />
          </LineChart>
        </ResponsiveContainer>
      </div>
      {last && (
        // The last point in a burndown series always sits on the final day
        // of the budget's period, where the ideal pace line reaches the
        // full limit. That makes last.ideal exactly the budget limit, so
        // the existing "X of Y spent" sentence applies without distortion.
        <p className="text-xs text-muted">
          {t('budget.spentOfLimit', {
            spent: formatMoney(last.cumulative, { locale }),
            limit: formatMoney(last.ideal, { locale }),
          })}
        </p>
      )}
      <table className="sr-only">
        <caption>{t.report.budgetBurnDown}</caption>
        <thead>
          <tr>
            <th scope="col">{t.transaction.fields.date}</th>
            <th scope="col">{t.report.budgetBurnDown}</th>
            <th scope="col">{t.budget.onTrack}</th>
          </tr>
        </thead>
        <tbody>
          {points.map((p) => (
            <tr key={p.date}>
              <td>{formatDateI18n(p.date, locale, { day: 'numeric', month: 'short' })}</td>
              <td>{formatMoney(p.cumulative, { locale })}</td>
              <td>{formatMoney(p.ideal, { locale })}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  )
}

