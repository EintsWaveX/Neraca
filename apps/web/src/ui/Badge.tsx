import type { HTMLAttributes } from 'react'
import { cn } from '../lib/utils'

export type BadgeTone = 'neutral' | 'positive' | 'negative' | 'warning' | 'accent'

export interface BadgeProps extends HTMLAttributes<HTMLSpanElement> {
  tone?: BadgeTone
}

const toneClasses: Record<BadgeTone, string> = {
  neutral: 'border-rule bg-paper-sunken text-ink-muted',
  positive: 'border-credit/30 bg-credit-soft text-credit',
  negative: 'border-debit/30 bg-debit-soft text-debit',
  warning: 'border-stamp/30 bg-stamp-soft text-stamp',
  accent: 'border-indigo/30 bg-indigo-soft text-indigo',
}

export function Badge({ tone = 'neutral', className, ...props }: BadgeProps) {
  return (
    <span
      className={cn(
        // A stamp, not a pill: squared off, because a ledger marks a row with
        // an inked rectangle and nothing in this system is capsule shaped.
        "inline-flex items-center rounded-[2px] border px-1.5 py-0.5 text-xs transition-colors duration-[var(--dur-fast)] ease-[var(--ease)]",
        toneClasses[tone],
        className
      )}
      {...props}
    />
  )
}
