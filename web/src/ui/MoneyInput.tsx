import { forwardRef, useEffect, useId, useRef, useState, type InputHTMLAttributes } from 'react'
import { formatMoney, parseMoneyInput } from '@/domain/money'
import type { Money } from '@/domain/money'
import { CURRENCIES } from '@/domain/currency'
import type { CurrencyCode } from '@/domain/currency'

export interface MoneyInputProps
  extends Omit<InputHTMLAttributes<HTMLInputElement>, 'id' | 'value' | 'onChange' | 'type'> {
  currency: CurrencyCode
  value: Money | null
  onChange: (value: Money | null) => void
  label: string
  hint?: string
  error?: string
  id?: string
}

export const MoneyInput = forwardRef<HTMLInputElement, MoneyInputProps>(function MoneyInput(
  { currency, value, onChange, label, hint, error, id, className, onFocus, onBlur, ...props },
  ref,
) {
  const generatedId = useId()
  const inputId = id ?? generatedId
  const hintId = hint ? `${inputId}-hint` : undefined
  const errorId = error ? `${inputId}-error` : undefined
  const describedBy = [errorId, hintId].filter(Boolean).join(' ') || undefined

  // The field keeps its own draft text so a keystroke is never rewritten out
  // from under the caret. It only snaps to the canonical formatted form on
  // blur, or when a new value arrives from outside while the field is not
  // focused (e.g. the parent resets the form).
  const [text, setText] = useState(() => (value ? formatMoney(value, { showSymbol: false }) : ''))
  const focused = useRef(false)

  useEffect(() => {
    if (!focused.current) {
      setText(value ? formatMoney(value, { showSymbol: false }) : '')
    }
  }, [value, currency])

  const symbol = CURRENCIES[currency].symbol

  return (
    <div className="flex flex-col gap-1.5">
      <label htmlFor={inputId} className="text-sm font-medium text-text">
        {label}
      </label>
      <div className="relative">
        <span
          aria-hidden="true"
          className="pointer-events-none absolute inset-y-0 left-3 flex items-center text-sm text-faint"
        >
          {symbol}
        </span>
        <input
          ref={ref}
          id={inputId}
          type="text"
          inputMode="decimal"
          value={text}
          aria-invalid={error ? true : undefined}
          aria-describedby={describedBy}
          className={`w-full rounded-control border bg-surface py-2 pl-9 pr-3 text-sm text-text tnum placeholder:text-faint transition-[border-color,box-shadow] duration-[var(--dur)] ease-[var(--ease-out)] focus-visible:border-accent focus-visible:shadow-[0_0_0_3px_var(--accent-soft)] disabled:cursor-not-allowed disabled:opacity-60 ${
            error ? 'border-negative' : 'border-line'
          } ${className ?? ''}`}
          onFocus={(event) => {
            focused.current = true
            onFocus?.(event)
          }}
          onChange={(event) => {
            const raw = event.target.value
            setText(raw)
            onChange(parseMoneyInput(raw, currency))
          }}
          onBlur={(event) => {
            focused.current = false
            const parsed = parseMoneyInput(text, currency)
            setText(parsed ? formatMoney(parsed, { showSymbol: false }) : '')
            onBlur?.(event)
          }}
          {...props}
        />
      </div>
      {hint && !error && (
        <p id={hintId} className="text-xs text-muted">
          {hint}
        </p>
      )}
      {error && (
        <p id={errorId} role="alert" className="text-xs text-negative">
          {error}
        </p>
      )}
    </div>
  )
})
