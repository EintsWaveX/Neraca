/**
 * The small shared pieces every Passbook screen is built from.
 *
 * There is deliberately no Card here. In this system a bordered box with a
 * shadow means a genuinely contained thing, a dialog most often, and a page
 * is divided by ruled headings instead. Keeping the card out of the shared
 * vocabulary is what stops it reappearing screen by screen.
 */

import type { ReactNode } from 'react'

export interface BlockProps {
  title: ReactNode
  /** Usually a link out to the full screen for whatever this block summarises. */
  action?: ReactNode
  children: ReactNode
  className?: string
}

/**
 * A titled division of a page: a heading with the heavier rule under it that
 * a ledger draws beneath a column head.
 */
export function Block({ title, action, children, className }: BlockProps) {
  return (
    <section className={`mt-10 ${className ?? ''}`}>
      <div className="flex items-baseline justify-between gap-3 border-b border-rule-strong pb-2">
        <h2 className="text-h3 leading-snug">{title}</h2>
        {action}
      </div>
      <div className="mt-2">{children}</div>
    </section>
  )
}

export interface RuledRowProps {
  label: ReactNode
  /** A quieter qualifier sitting beside the label: a wallet kind, a period. */
  note?: ReactNode
  value: ReactNode
  /** Position in its list, so the row prints in with the rest. */
  index?: number
  /** A second line under the row, for a progress bar or a longer explanation. */
  below?: ReactNode
  className?: string
}

/**
 * The atom of every list in this app that is not a full table: a label on the
 * left, a figure hard right, a feint rule beneath. The last row in a group
 * drops its rule so a block ends flush rather than with a dangling line.
 */
export function RuledRow({ label, note, value, index = 0, below, className }: RuledRowProps) {
  return (
    <div
      className={`print-in border-b border-rule py-[var(--row-pad)] last:border-b-0 ${className ?? ''}`}
      style={{ '--print-index': index } as React.CSSProperties}
    >
      <div className="flex items-baseline justify-between gap-4">
        <span className="flex min-w-0 flex-wrap items-baseline gap-x-2">
          <span className="truncate text-ink">{label}</span>
          {note && <span className="text-xs text-ink-faint">{note}</span>}
        </span>
        <span className="shrink-0">{value}</span>
      </div>
      {below && <div className="mt-1.5">{below}</div>}
    </div>
  )
}

export interface PageProps {
  children: ReactNode
}

/**
 * The page measure. Wide enough for a four column ledger at a comfortable
 * density, narrow enough that a line of prose never runs past what an eye can
 * track back from.
 */
export function Page({ children }: PageProps) {
  return <div className="mx-auto max-w-5xl px-4 py-6 sm:px-8 sm:py-10">{children}</div>
}

export interface HeroProps {
  label: ReactNode
  value: ReactNode
  meta?: ReactNode
  children?: ReactNode
}

/**
 * The one figure a screen exists to show, set against the book's binding.
 * Only one of these per screen: a page with two heroes has none.
 */
export function Hero({ label, value, meta, children }: HeroProps) {
  return (
    <div className="spine pl-4 sm:pl-6">
      <p className="text-sm text-ink-muted">{label}</p>
      <p className="text-display leading-none">{value}</p>
      {meta && <p className="mt-2 text-sm text-ink-muted">{meta}</p>}
      {children}
    </div>
  )
}
