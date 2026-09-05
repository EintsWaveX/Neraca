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

const variantClasses: Record<ButtonVariant, string> = {
  // The soft shadow on hover/focus is the one glow this design system uses
  // outside the active nav item, derived from --accent-glow (itself
  // color-mix'd from --accent) rather than a hardcoded colour, so a primary
  // button reads as the call to action without a second accent colour.
  primary: 'bg-accent text-accent-text hover:bg-accent-hover hover:shadow-[0_0_16px_var(--accent-glow)] focus-visible:shadow-[0_0_16px_var(--accent-glow)]',
  secondary: 'bg-surface text-text border border-line hover:bg-surface-sunken focus-visible:ring-2 focus-visible:ring-accent',
  ghost: 'bg-transparent text-text hover:bg-surface-sunken focus-visible:ring-2 focus-visible:ring-accent',
  // The negative token sits at nearly the same lightness as accent in both
  // themes (see src/index.css), so accent-text, the token built for "text on
  // top of a saturated, mid-lightness surface", also reads correctly here
  // without inventing a colour the rest of the design system does not know.
  danger: 'bg-negative text-accent-text hover:opacity-90',
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
      // The lift and press live on transform, never on padding or border, so
      // they cost no layout: hovering nudges the button up a hair, pressing
      // it settles back down and slightly smaller, the same feedback a
      // physical button gives. Disabled buttons get neither, since there is
      // nothing to invite a press toward. The transition names its properties
      // rather than using transition-all, so a variant adding a border or a
      // filter does not silently animate it too.
      className={cn(
        "inline-flex items-center justify-center rounded-control font-medium transition-[color,background-color,box-shadow,transform] duration-[var(--dur)] ease-[var(--ease-out)]",
        "hover:-translate-y-px active:translate-y-0 active:scale-[0.97]",
        "disabled:cursor-not-allowed disabled:opacity-60 disabled:hover:translate-y-0 disabled:active:scale-100",
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
