import type { HTMLAttributes } from 'react'
import { cn } from '../lib/utils'

export type BadgeTone = 'neutral' | 'positive' | 'negative' | 'warning' | 'accent'

export interface BadgeProps extends HTMLAttributes<HTMLSpanElement> {
  tone?: BadgeTone
}

const toneClasses: Record<BadgeTone, string> = {
  neutral: 'bg-surface-sunken text-muted border-line',
  positive: 'bg-positive-soft text-positive border-positive/20',
  negative: 'bg-negative-soft text-negative border-negative/20',
  warning: 'bg-warning-soft text-warning border-warning/20',
  accent: 'bg-accent-soft text-accent border-accent/20',
}

export function Badge({ tone = 'neutral', className, ...props }: BadgeProps) {
  return (
    <span
      className={cn(
        "inline-flex items-center rounded-full border px-2 py-0.5 text-xs font-medium transition-colors duration-[var(--dur)] ease-[var(--ease-out)]",
        toneClasses[tone],
        className
      )}
      {...props}
    />
  )
}
