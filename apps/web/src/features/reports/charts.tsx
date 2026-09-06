/**
 * Chart components for the reports screen.
 *
 * Drawn by hand in SVG rather than by a charting library. The library that
 * used to be here was 114 KB gzipped, more than the whole of the rest of the
 * application put together, for four charts on one screen. It also drew its
 * own visual language: rounded tooltips, its own grid weights, its own
 * animation timing, all of which had to be fought back toward the Passbook
 * before they matched anything else. Four hand drawn charts came to a few
 * kilobytes and take their axes, rules and colours from the same tokens every
 * other screen uses.
 *
 * Every colour comes from the design tokens in src/index.css, read at runtime
 * with getComputedStyle rather than hardcoded, so a chart painted in light
 * mode still reads correctly the moment the theme flips. useChartColors
 * watches both an explicit theme attribute on <html> (set by ThemeToggle) and
 * the system colour scheme media query (used when no explicit choice has been
 * made), and recomputes whenever either changes.
 *
 * Each chart pairs its canvas with a visually hidden table carrying the same
 * numbers, because a screen reader gets nothing at all from an SVG line or
 * bar. The table is never display:none, which would drop it from the
 * accessibility tree as well; it is sr-only, so it is present and readable by
 * assistive technology and invisible on screen.
 *
 * Motion is CSS, never a timer. That is what lets the single reduced motion
 * rule in index.css switch every chart off along with everything else,
 * instead of each chart needing to check the media query itself.
 */

import { useEffect, useRef, useState, type ReactNode } from 'react'
import type { Granularity, CategoryTotal, IncomeExpensePoint, SeriesPoint, BurndownPoint } from '@neraca/domain/reports'
import { formatMoney, toMajor, type Money } from '@neraca/domain/money'
import type { CurrencyCode } from '@neraca/domain/currency'
import { CATEGORY_BY_ID, CATEGORY_GROUP_LABELS } from '@neraca/domain/categories'
import type { Locale } from '@neraca/domain/types'
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
  // A CSS custom property that fails to resolve reads back as an empty string,
  // never as an error. Falling back to currentColor keeps a chart legible
  // instead of drawing invisible shapes if a token is ever renamed.
  return value === '' ? 'currentColor' : value
}

function readChartColors(): ChartColors {
  return {
    accent: readToken('--indigo'),
    positive: readToken('--credit'),
    negative: readToken('--debit'),
    warning: readToken('--stamp'),
    muted: readToken('--ink-muted'),
    faint: readToken('--ink-faint'),
    line: readToken('--rule'),
  }
}

/** Tracks the design tokens live, so every chart repaints when the theme changes. */
export function useChartColors(): ChartColors {
  const [colors, setColors] = useState<ChartColors>(readChartColors)

  useEffect(() => {
    const update = () => setColors(readChartColors())
    update()

    // Covers an explicit light or dark choice: ThemeToggle sets data-theme on
    // <html>, a plain attribute change that fires no event of its own.
    const observer = new MutationObserver(update)
    observer.observe(document.documentElement, { attributes: true, attributeFilter: ['data-theme'] })

    // Covers "system": no data-theme attribute at all, so the tokens follow
    // the operating system preference through the media query instead.
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
// Geometry
// ---------------------------------------------------------------------------

const PAD = { top: 14, right: 10, bottom: 22, left: 58 } as const

/**
 * The drawing width in real pixels.
 *
 * Measured rather than expressed as a scaling viewBox, because a viewBox that
 * stretches scales the type with it: the same axis label would be one size on
 * a phone and another on a desktop, which is exactly the inconsistency the
 * type scale exists to prevent.
 */
function useMeasuredWidth<E extends HTMLElement>(): [React.RefObject<E | null>, number] {
  const ref = useRef<E>(null)
  const [width, setWidth] = useState(640)

  useEffect(() => {
    const el = ref.current
    if (!el) return
    const observer = new ResizeObserver((entries) => {
      const next = entries[0]?.contentRect.width
      if (next && next > 0) setWidth(next)
    })
    observer.observe(el)
    return () => observer.disconnect()
  }, [])

  return [ref, width]
}

/** A rounded scale maximum, so the top gridline lands on a readable number. */
function niceMax(value: number): number {
  if (value <= 0) return 1
  const magnitude = 10 ** Math.floor(Math.log10(value))
  const scaled = value / magnitude
  const step = scaled <= 1 ? 1 : scaled <= 2 ? 2 : scaled <= 5 ? 5 : 10
  return step * magnitude
}

/*
  Axis ticks carry no currency.

  A compact currency format falls back to the ISO code rather than the symbol,
  so the axis read "IDR 750K" five times down the side of a chart whose caption
  already says what the money is. The currency is named once, in the figures
  under the chart, exactly as a ledger names it once at the head of a column.
*/
function axisMoneyTick(minor: number, currency: CurrencyCode, locale: Locale): string {
  const major = toMajor({ minor, currency })
  try {
    return new Intl.NumberFormat(locale === 'id' ? 'id-ID' : 'en-US', {
      notation: 'compact',
      maximumFractionDigits: 1,
    }).format(major)
  } catch {
    return String(Math.round(major))
  }
}

function periodLabel(period: string, granularity: Granularity, locale: Locale): string {
  if (granularity === 'month') return formatDateI18n(period, locale, { month: 'short', year: 'numeric' })
  return formatDateI18n(period, locale, { day: 'numeric', month: 'short' })
}

/**
 * Which x positions get a label.
 *
 * Every period labelled is unreadable past about a dozen columns, and every
 * nth with n fixed drops the last one, which is the one a reader most wants.
 * This always keeps the first and last and thins what is between them.
 */
function labelledIndices(count: number, maxLabels: number): Set<number> {
  if (count <= maxLabels) return new Set(Array.from({ length: count }, (_, i) => i))
  const step = Math.ceil(count / maxLabels)
  const keep = new Set<number>()
  for (let i = 0; i < count; i += step) keep.add(i)
  keep.add(count - 1)
  return keep
}

interface FrameProps {
  label: string
  height: number
  children: (geometry: { width: number; height: number; innerW: number; innerH: number }) => ReactNode
  /** The same numbers as a table, for anybody not looking at the picture. */
  table: ReactNode
}

function ChartFrame({ label, height, children, table }: FrameProps) {
  const [ref, width] = useMeasuredWidth<HTMLDivElement>()
  const innerW = Math.max(1, width - PAD.left - PAD.right)
  const innerH = Math.max(1, height - PAD.top - PAD.bottom)

  return (
    <div ref={ref} className="w-full">
      <svg
        width={width}
        height={height}
        viewBox={`0 0 ${width} ${height}`}
        role="img"
        aria-label={label}
        className="block"
      >
        {children({ width, height, innerW, innerH })}
      </svg>
      {table}
    </div>
  )
}

/** The horizontal rules and their value labels, drawn behind everything else. */
function Gridlines({
  max,
  innerW,
  innerH,
  currency,
  locale,
  colors,
  steps = 4,
}: {
  max: number
  innerW: number
  innerH: number
  currency: CurrencyCode
  locale: Locale
  colors: ChartColors
  steps?: number
}) {
  return (
    <g>
      {Array.from({ length: steps + 1 }, (_, i) => {
        const value = (max / steps) * i
        const y = PAD.top + innerH - (innerH / steps) * i
        return (
          <g key={i}>
            <line
              x1={PAD.left}
              x2={PAD.left + innerW}
              y1={y}
              y2={y}
              stroke={i === 0 ? colors.muted : colors.line}
              strokeWidth={i === 0 ? 1 : 1}
            />
            <text
              x={PAD.left - 8}
              y={y + 4}
              textAnchor="end"
              fontSize={11}
              fill={colors.faint}
              className="figure"
            >
              {axisMoneyTick(value, currency, locale)}
            </text>
          </g>
        )
      })}
    </g>
  )
}

function SrTable({ caption, head, rows }: { caption: string; head: string[]; rows: string[][] }) {
  return (
    <table className="sr-only">
      <caption>{caption}</caption>
      <thead>
        <tr>
          {head.map((h) => (
            <th key={h} scope="col">
              {h}
            </th>
          ))}
        </tr>
      </thead>
      <tbody>
        {rows.map((row) => (
          <tr key={row.join('|')}>
            {row.map((cell, i) =>
              i === 0 ? (
                <th key={i} scope="row">
                  {cell}
                </th>
              ) : (
                <td key={i}>{cell}</td>
              ),
            )}
          </tr>
        ))}
      </tbody>
    </table>
  )
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
  const total = points.reduce((sum, p) => sum + p.amount.minor, 0)
  const peak = points.reduce<SeriesPoint | null>(
    (max, p) => (max === null || p.amount.minor > max.amount.minor ? p : max),
    null,
  )
  const max = niceMax(peak?.amount.minor ?? 0)
  const labelled = labelledIndices(points.length, 8)

  return (
    <figure className="m-0">
      <ChartFrame
        label={t.report.spendingOverTime}
        height={220}
        table={
          <SrTable
            caption={t.report.spendingOverTime}
            head={[t.transaction.fields.date, t.report.totalExpense]}
            rows={points.map((p) => [periodLabel(p.period, granularity, locale), formatMoney(p.amount)])}
          />
        }
      >
        {({ innerW, innerH }) => {
          // A visible gap between columns rather than a fixed bar width, so a
          // year of months and a fortnight of days both fill the same canvas.
          const slot = innerW / Math.max(1, points.length)
          const barW = Math.max(2, slot * 0.62)
          return (
            <>
              <Gridlines
                max={max}
                innerW={innerW}
                innerH={innerH}
                currency={currency}
                locale={locale}
                colors={colors}
              />
              {points.map((p, i) => {
                const h = (p.amount.minor / max) * innerH
                const x = PAD.left + slot * i + (slot - barW) / 2
                return (
                  <rect
                    key={p.period}
                    className="chart-bar chart-bar-up"
                    style={{ '--print-index': i } as React.CSSProperties}
                    x={x}
                    y={PAD.top + innerH - h}
                    width={barW}
                    height={Math.max(0, h)}
                    fill={colors.accent}
                  >
                    <title>{`${periodLabel(p.period, granularity, locale)}: ${formatMoney(p.amount)}`}</title>
                  </rect>
                )
              })}
              {points.map((p, i) =>
                labelled.has(i) ? (
                  <text
                    key={`l-${p.period}`}
                    x={PAD.left + slot * i + slot / 2}
                    y={PAD.top + innerH + 15}
                    textAnchor="middle"
                    fontSize={11}
                    fill={colors.faint}
                  >
                    {periodLabel(p.period, granularity, locale)}
                  </text>
                ) : null,
              )}
            </>
          )
        }}
      </ChartFrame>
      <figcaption className="mt-2 flex flex-wrap gap-x-6 gap-y-1 text-sm text-ink-muted">
        <span>
          {t.report.totalExpense}: <span className="figure">{formatMoney({ minor: total, currency })}</span>
        </span>
        {peak && (
          <span>
            {t.report.topCategory}:{' '}
            <span className="figure">
              {periodLabel(peak.period, granularity, locale)} {formatMoney(peak.amount)}
            </span>
          </span>
        )}
      </figcaption>
    </figure>
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

/**
 * A ranked list of bars rather than a pie.
 *
 * A pie asks you to compare angles, which people are measurably bad at, and it
 * needs a legend because the labels do not fit inside the slices. A ranked bar
 * puts the label, the figure and the share on one ruled row and sorts the
 * answer to "what did I spend most on" into the first line. It is also just a
 * ledger row with a bar behind it, which is what the rest of the app is made
 * of, so it needs no SVG at all.
 */
export function CategoryBreakdownChart({ totals, currency, locale, t }: CategoryBreakdownChartProps) {
  // No dedicated "long tail" bucket string exists in the dictionary; the
  // "Other" category group already carries this exact meaning in both locales,
  // so it is reused here rather than inventing new copy.
  const otherLabel = CATEGORY_GROUP_LABELS.other[locale === 'id' ? 'id_' : 'en']
  const rows = topCategoriesWithOther(totals, currency, otherLabel, locale)
  const largest = rows.reduce((max, row) => Math.max(max, row.amount.minor), 0)

  if (rows.length === 0) return null

  return (
    <figure className="m-0">
      <ul className="m-0 list-none p-0">
        {rows.map((row, index) => (
          <li
            key={row.id}
            className="print-in border-b border-rule py-[var(--row-pad)] last:border-b-0"
            style={{ '--print-index': index } as React.CSSProperties}
          >
            <div className="flex items-baseline justify-between gap-4">
              <span className="min-w-0 truncate text-ink">{row.label}</span>
              <span className="shrink-0 text-sm">
                <span className="figure text-ink">{formatMoney(row.amount)}</span>
                <span className="figure ml-2 text-ink-faint">{Math.round(row.fraction * 100)}%</span>
              </span>
            </div>
            {/* Decorative: the figures on the row above already say this, so a
                second announcement of the same number would be noise. */}
            <div aria-hidden="true" className="mt-1 h-1 w-full bg-paper-sunken">
              <div
                className="bar-fill h-full bg-indigo"
                style={{ width: `${largest === 0 ? 0 : (row.amount.minor / largest) * 100}%` }}
              />
            </div>
          </li>
        ))}
      </ul>
      <figcaption className="sr-only">{t.report.categoryBreakdown}</figcaption>
    </figure>
  )
}

// ---------------------------------------------------------------------------
// c) Income against expense
// ---------------------------------------------------------------------------

export interface IncomeExpenseChartProps {
  points: readonly IncomeExpensePoint[]
  currency: CurrencyCode
  granularity: Granularity
  locale: Locale
  t: T
}

/**
 * Income above the line, expense below it.
 *
 * Two bars side by side make you compare lengths across a gap. Splitting them
 * across a shared zero line means the surplus or shortfall in any period is
 * the difference in how far the page is filled above and below one rule, which
 * is also exactly how a ledger reads: credits one side, debits the other.
 */
export function IncomeExpenseChart({ points, currency, granularity, locale, t }: IncomeExpenseChartProps) {
  const colors = useChartColors()
  const max = niceMax(
    points.reduce((m, p) => Math.max(m, p.income.minor, p.expense.minor), 0),
  )
  const labelled = labelledIndices(points.length, 8)
  const totalIncome = points.reduce((sum, p) => sum + p.income.minor, 0)
  const totalExpense = points.reduce((sum, p) => sum + p.expense.minor, 0)

  return (
    <figure className="m-0">
      <ChartFrame
        label={t.report.incomeVsExpense}
        height={260}
        table={
          <SrTable
            caption={t.report.incomeVsExpense}
            head={[t.transaction.fields.date, t.report.totalIncome, t.report.totalExpense]}
            rows={points.map((p) => [
              periodLabel(p.period, granularity, locale),
              formatMoney(p.income),
              formatMoney(p.expense),
            ])}
          />
        }
      >
        {({ innerW, innerH }) => {
          const half = innerH / 2
          const zeroY = PAD.top + half
          const slot = innerW / Math.max(1, points.length)
          const barW = Math.max(2, slot * 0.5)
          return (
            <>
              {/* Two mirrored scales sharing one zero line. */}
              {[1, 0.5].map((frac) => (
                <g key={frac}>
                  {[-1, 1].map((sign) => (
                    <line
                      key={sign}
                      x1={PAD.left}
                      x2={PAD.left + innerW}
                      y1={zeroY - sign * half * frac}
                      y2={zeroY - sign * half * frac}
                      stroke={colors.line}
                    />
                  ))}
                  <text
                    x={PAD.left - 8}
                    y={zeroY - half * frac + 4}
                    textAnchor="end"
                    fontSize={11}
                    fill={colors.faint}
                    className="figure"
                  >
                    {axisMoneyTick(max * frac, currency, locale)}
                  </text>
                </g>
              ))}
              <line x1={PAD.left} x2={PAD.left + innerW} y1={zeroY} y2={zeroY} stroke={colors.muted} />

              {points.map((p, i) => {
                const x = PAD.left + slot * i + (slot - barW) / 2
                const hIn = (p.income.minor / max) * half
                const hOut = (p.expense.minor / max) * half
                const style = { '--print-index': i } as React.CSSProperties
                return (
                  <g key={p.period}>
                    <rect
                      className="chart-bar chart-bar-up"
                      style={style}
                      x={x}
                      y={zeroY - hIn}
                      width={barW}
                      height={Math.max(0, hIn)}
                      fill={colors.positive}
                    >
                      <title>{`${periodLabel(p.period, granularity, locale)} ${t.report.totalIncome}: ${formatMoney(p.income)}`}</title>
                    </rect>
                    <rect
                      className="chart-bar chart-bar-down"
                      style={style}
                      x={x}
                      y={zeroY}
                      width={barW}
                      height={Math.max(0, hOut)}
                      fill={colors.negative}
                    >
                      <title>{`${periodLabel(p.period, granularity, locale)} ${t.report.totalExpense}: ${formatMoney(p.expense)}`}</title>
                    </rect>
                  </g>
                )
              })}

              {points.map((p, i) =>
                labelled.has(i) ? (
                  <text
                    key={`l-${p.period}`}
                    x={PAD.left + slot * i + slot / 2}
                    y={PAD.top + innerH + 15}
                    textAnchor="middle"
                    fontSize={11}
                    fill={colors.faint}
                  >
                    {periodLabel(p.period, granularity, locale)}
                  </text>
                ) : null,
              )}
            </>
          )
        }}
      </ChartFrame>
      <figcaption className="mt-2 flex flex-wrap gap-x-6 gap-y-1 text-sm text-ink-muted">
        <span className="text-credit">
          {t.report.totalIncome}:{' '}
          <span className="figure">{formatMoney({ minor: totalIncome, currency })}</span>
        </span>
        <span className="text-debit">
          {t.report.totalExpense}:{' '}
          <span className="figure">{formatMoney({ minor: totalExpense, currency })}</span>
        </span>
        <span>
          {t.report.netBalance}:{' '}
          <span className="figure">{formatMoney({ minor: totalIncome - totalExpense, currency })}</span>
        </span>
      </figcaption>
    </figure>
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
  const max = niceMax(points.reduce((m, p) => Math.max(m, p.cumulative.minor, p.ideal.minor), 0))
  const last = points.at(-1)
  const ahead = last ? last.cumulative.minor > last.ideal.minor : false

  return (
    <figure className="m-0">
      <ChartFrame
        label={t.report.budgetBurnDown}
        height={220}
        table={
          <SrTable
            caption={t.report.budgetBurnDown}
            head={[t.transaction.fields.date, t.report.totalExpense, t.budget.onTrack]}
            rows={points.map((p) => [
              formatDateI18n(p.date, locale, { day: 'numeric', month: 'short' }),
              formatMoney(p.cumulative),
              formatMoney(p.ideal),
            ])}
          />
        }
      >
        {({ innerW, innerH }) => {
          const step = innerW / Math.max(1, points.length - 1)
          const pointsFor = (pick: (p: BurndownPoint) => number) =>
            points
              .map((p, i) => `${PAD.left + step * i},${PAD.top + innerH - (pick(p) / max) * innerH}`)
              .join(' ')
          return (
            <>
              <Gridlines
                max={max}
                innerW={innerW}
                innerH={innerH}
                currency={currency}
                locale={locale}
                colors={colors}
              />
              {/* The even pace, drawn faint and dashed because it is a
                  reference rather than something that happened. */}
              <polyline
                points={pointsFor((p) => p.ideal.minor)}
                fill="none"
                stroke={colors.faint}
                strokeWidth={1.5}
                strokeDasharray="4 4"
              />
              <polyline
                className="chart-line"
                pathLength={1}
                points={pointsFor((p) => p.cumulative.minor)}
                fill="none"
                stroke={ahead ? colors.negative : colors.accent}
                strokeWidth={2}
                strokeLinejoin="round"
                strokeLinecap="round"
              />
              {points.length > 0 && (
                <text
                  x={PAD.left}
                  y={PAD.top + innerH + 15}
                  fontSize={11}
                  fill={colors.faint}
                >
                  {formatDateI18n(points[0]!.date, locale, { day: 'numeric', month: 'short' })}
                </text>
              )}
              {last && (
                <text
                  x={PAD.left + innerW}
                  y={PAD.top + innerH + 15}
                  textAnchor="end"
                  fontSize={11}
                  fill={colors.faint}
                >
                  {formatDateI18n(last.date, locale, { day: 'numeric', month: 'short' })}
                </text>
              )}
            </>
          )
        }}
      </ChartFrame>
      {last && (
        <figcaption className="mt-2 text-sm text-ink-muted">
          {t('budget.spentOfLimit', {
            spent: formatMoney(last.cumulative),
            limit: formatMoney(last.ideal),
          })}
        </figcaption>
      )}
    </figure>
  )
}
