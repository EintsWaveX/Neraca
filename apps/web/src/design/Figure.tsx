/**
 * Money, set the way a ledger sets it.
 *
 * The currency symbol and the minor units are pushed back a step in both size
 * and colour so the eye lands on the significant digits, which is the part you
 * actually compare down a column. The split is done with `formatToParts`
 * rather than by slicing the formatted string, because the separator, the
 * grouping and the symbol's position all move between locales: `Rp 1.500.000`
 * and `12,34 €` cannot be pulled apart by looking for a full stop.
 *
 * Zero decimal currencies simply produce no fraction parts, so rupiah and yen
 * fall out of the same code path with nothing special written for them.
 */

import { CURRENCIES } from '@neraca/domain/currency'
import { toMajor, type Money } from '@neraca/domain/money'

export type FigureTone = 'neutral' | 'credit' | 'debit' | 'auto'

export interface MoneyFigureProps {
  value: Money
  /** Overrides the currency's own convention, for a profile reading in id-ID. */
  locale?: string
  signDisplay?: 'auto' | 'never' | 'always'
  /**
   * `auto` colours by the sign of the value. Left neutral by default, because
   * most figures on a screen are balances rather than movements, and a page
   * where every number is coloured is a page where colour means nothing.
   */
  tone?: FigureTone
  /**
   * A ledger names its currency once at the head of a column, not on every
   * row. Pass false inside a table whose heading already says which currency
   * the column is in.
   */
  showSymbol?: boolean
  /**
   * Set the figure in the sans rather than the mono. Monospace exists to make
   * a column line up; a single balance at display size has no column to line
   * up with, and Plex Mono gives a full character width to the thousands
   * separator, which at 48px punches visible holes through the number.
   */
  display?: boolean
  className?: string
}

type Split = { symbol: string; body: string; fraction: string }

function splitParts(
  value: Money,
  locale: string,
  signDisplay: 'auto' | 'never' | 'always',
): Split {
  const meta = CURRENCIES[value.currency]
  try {
    const parts = new Intl.NumberFormat(locale, {
      style: 'currency',
      currency: value.currency,
      minimumFractionDigits: meta.decimals,
      maximumFractionDigits: meta.decimals,
      signDisplay,
    }).formatToParts(toMajor(value))

    let symbol = ''
    let body = ''
    let fraction = ''
    for (const part of parts) {
      if (part.type === 'currency') symbol += part.value
      else if (part.type === 'decimal' || part.type === 'fraction') fraction += part.value
      // Literals are only ever the locale's own spacing: grouping arrives as
      // its own `group` part. Dropping them keeps the sign hard against the
      // digits, so a minus reads as belonging to the number rather than
      // floating between the symbol and it.
      else if (part.type !== 'literal') body += part.value
    }
    return { symbol, body: body.trim(), fraction }
  } catch {
    // A runtime without this currency in its Intl data still has to render
    // something a person can read, which matters on older Android browsers.
    const major = toMajor(value)
    const fixed = Math.abs(major).toFixed(meta.decimals)
    const dot = fixed.indexOf('.')
    return {
      symbol: meta.symbol,
      body: (major < 0 ? '-' : '') + (dot === -1 ? fixed : fixed.slice(0, dot)),
      fraction: dot === -1 ? '' : fixed.slice(dot),
    }
  }
}

export function MoneyFigure({
  value,
  locale,
  signDisplay = 'auto',
  tone = 'neutral',
  showSymbol = true,
  display = false,
  className,
}: MoneyFigureProps) {
  const resolved = locale ?? CURRENCIES[value.currency].numberLocale
  const { symbol, body, fraction } = splitParts(value, resolved, signDisplay)

  const resolvedTone =
    tone === 'auto' ? (value.minor < 0 ? 'debit' : value.minor > 0 ? 'credit' : 'neutral') : tone

  const toneClass =
    resolvedTone === 'credit' ? 'figure-credit' : resolvedTone === 'debit' ? 'figure-debit' : ''

  return (
    <span
      className={[display ? 'figure-display' : 'figure', toneClass, className]
        .filter(Boolean)
        .join(' ')}
    >
      {showSymbol && symbol !== '' && <span className="figure-symbol">{symbol}</span>}
      {body}
      {fraction !== '' && <span className="figure-minor">{fraction}</span>}
    </span>
  )
}

export interface FigureProps {
  children: React.ReactNode
  tone?: Exclude<FigureTone, 'auto'>
  className?: string
}

/** Any other number that belongs in a column: a percentage, a count, a rate. */
export function Figure({ children, tone = 'neutral', className }: FigureProps) {
  const toneClass = tone === 'credit' ? 'figure-credit' : tone === 'debit' ? 'figure-debit' : ''
  return <span className={['figure', toneClass, className].filter(Boolean).join(' ')}>{children}</span>
}
