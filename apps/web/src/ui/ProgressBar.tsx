import type { HTMLAttributes } from 'react'
import { useMountedPercent } from './motion'

export interface ProgressBarProps extends Omit<HTMLAttributes<HTMLDivElement>, 'children'> {
  /** 0 to 100. Clamping to that range is the caller's job; this component renders whatever it is given. */
  value: number
  label: string
  /** Tailwind classes for the filled portion's colour, e.g. "bg-positive". Left as a caller-supplied class since callers already compute their own state-to-colour mapping. */
  barClassName?: string
}

/**
 * A track-and-fill progress bar whose fill eases to its width on mount and
 * on every later value change, rather than jumping straight there. Used for
 * both the dashboard's budget alerts and the budgets screen's own cards, so
 * the two do not each reimplement the same aria wiring and motion.
 */
export function ProgressBar({ value, label, barClassName = 'bg-accent', className, ...rest }: ProgressBarProps) {
  const width = useMountedPercent(value)
  return (
    <div
      role="progressbar"
      aria-label={label}
      aria-valuemin={0}
      aria-valuemax={100}
      // The accessible value is always the real target, never the
      // in-progress animated width, so assistive tech reads the correct
      // figure immediately instead of whatever the entrance animation
      // happens to be mid-way through.
      aria-valuenow={value}
      className={`h-2 w-full overflow-hidden rounded-full bg-surface-sunken ${className ?? ''}`}
      {...rest}
    >
      <div className={`bar-fill h-full rounded-full ${barClassName}`} style={{ width: `${width}%` }} />
    </div>
  )
}
