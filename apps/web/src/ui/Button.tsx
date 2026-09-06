import { forwardRef, type ButtonHTMLAttributes, type ReactNode } from 'react'
import { cn } from '../lib/utils'

export type ButtonVariant = 'primary' | 'secondary' | 'ghost' | 'danger'
export type ButtonSize = 'sm' | 'md'

export interface ButtonProps extends ButtonHTMLAttributes<HTMLButtonElement> {
  variant?: ButtonVariant
  size?: ButtonSize
  /** Shows a spinner in place of the icon slot and blocks interaction via the native disabled attribute. */
  loading?: boolean
  /** Rendered before the label. Marked aria-hidden because the button's own accessible name already carries the meaning. */
  icon?: ReactNode
}

// The glow this used to carry was drawn from a token the Passbook system
// removed: nothing in a ledger emits light. A button now answers a press
// by changing its own ground, which is also the cheaper effect, since a
// background colour costs no new compositing layer.
const variantClasses: Record<ButtonVariant, string> = {
  primary: 'bg-indigo text-indigo-on hover:bg-indigo-hover',
  secondary: 'border border-rule bg-paper-raised text-ink hover:border-rule-strong hover:bg-paper-sunken',
  ghost: 'bg-transparent text-ink-muted hover:bg-paper-sunken hover:text-ink',
  // The debit token sits at nearly the same lightness as the accent in both
  // themes, so indigo-on, the token built for "text on a saturated surface of
  // roughly this lightness", also reads correctly here without inventing a
  // colour the rest of the system does not know about.
  danger: 'bg-debit text-indigo-on hover:opacity-90',
}

const sizeClasses: Record<ButtonSize, string> = {
  sm: 'h-8 px-3 text-sm gap-1.5',
  md: 'h-10 px-4 text-sm gap-2',
}

export const Button = forwardRef<HTMLButtonElement, ButtonProps>(function Button(
  { variant = 'primary', size = 'md', loading = false, icon, disabled, className, children, type = 'button', ...rest },
  ref,
) {
  const isDisabled = disabled || loading
  return (
    <button
      ref={ref}
      type={type}
      disabled={isDisabled}
      aria-busy={loading || undefined}
      // The press lives on transform, so it costs no layout. There is no lift
      // on hover any more: in this system nothing floats above the page, and a
      // control that rises off the paper contradicts every rule around it. The
      // transition names its properties rather than using transition-all, so a
      // variant adding a border or a filter does not silently animate too.
      className={cn(
        "inline-flex items-center justify-center rounded-control font-medium transition-[color,background-color,border-color,transform] duration-[var(--dur-fast)] ease-[var(--ease)]",
        "active:scale-[0.98]",
        "disabled:cursor-not-allowed disabled:opacity-60 disabled:active:scale-100",
        variantClasses[variant],
        sizeClasses[size],
        className
      )}
      {...rest}
    >
      {loading ? (
        <Spinner className="h-4 w-4" />
      ) : icon ? (
        <span aria-hidden="true" className="inline-flex h-4 w-4 items-center justify-center [&>svg]:h-4 [&>svg]:w-4">
          {icon}
        </span>
      ) : null}
      {children}
    </button>
  )
})

function Spinner({ className }: { className?: string }) {
  return (
    <svg className={`animate-spin ${className ?? ''}`} viewBox="0 0 24 24" fill="none" aria-hidden="true">
      <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4" />
      <path className="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8v4a4 4 0 00-4 4H4z" />
    </svg>
  )
}
