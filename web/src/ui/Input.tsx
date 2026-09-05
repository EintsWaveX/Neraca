import { forwardRef, useId, type InputHTMLAttributes, type TextareaHTMLAttributes } from 'react'
import { cn } from '../lib/utils'

export interface InputProps extends Omit<InputHTMLAttributes<HTMLInputElement>, 'id'> {
  label: string
  hint?: string
  error?: string
  id?: string
}

export const Input = forwardRef<HTMLInputElement, InputProps>(function Input(
  { label, hint, error, id, className, required, ...props },
  ref,
) {
  const generatedId = useId()
  const inputId = id ?? generatedId
  const hintId = hint ? `${inputId}-hint` : undefined
  const errorId = error ? `${inputId}-error` : undefined
  const describedBy = [errorId, hintId].filter(Boolean).join(' ') || undefined

  return (
    <div className="flex flex-col gap-1.5">
      <label htmlFor={inputId} className="text-sm font-medium text-text">
        {label}
        {required && (
          <span aria-hidden="true" className="text-negative">
            {' '}
            *
          </span>
        )}
      </label>
      <input
        ref={ref}
        id={inputId}
        required={required}
        aria-invalid={error ? true : undefined}
        aria-describedby={describedBy}
        className={cn(
          "w-full rounded-control border bg-surface px-3 py-2 text-sm text-text placeholder:text-faint transition-[border-color,box-shadow] duration-[var(--dur)] ease-[var(--ease-out)]",
          "focus-visible:border-accent focus-visible:ring-1 focus-visible:ring-accent focus-visible:outline-none",
          "disabled:cursor-not-allowed disabled:opacity-60",
          error ? "border-negative focus-visible:border-negative focus-visible:ring-negative" : "border-line",
          className
        )}
        {...props}
      />
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

export interface TextareaProps extends Omit<TextareaHTMLAttributes<HTMLTextAreaElement>, 'id'> {
  label: string
  hint?: string
  error?: string
  id?: string
}

export const Textarea = forwardRef<HTMLTextAreaElement, TextareaProps>(function Textarea(
  { label, hint, error, id, className, required, ...props },
  ref,
) {
  const generatedId = useId()
  const textareaId = id ?? generatedId
  const hintId = hint ? `${textareaId}-hint` : undefined
  const errorId = error ? `${textareaId}-error` : undefined
  const describedBy = [errorId, hintId].filter(Boolean).join(' ') || undefined

  return (
    <div className="flex flex-col gap-1.5">
      <label htmlFor={textareaId} className="text-sm font-medium text-text">
        {label}
        {required && (
          <span aria-hidden="true" className="text-negative">
            {' '}
            *
          </span>
        )}
      </label>
      <textarea
        ref={ref}
        id={textareaId}
        required={required}
        aria-invalid={error ? true : undefined}
        aria-describedby={describedBy}
        className={cn(
          "min-h-24 w-full rounded-control border bg-surface px-3 py-2 text-sm text-text placeholder:text-faint transition-[border-color,box-shadow] duration-[var(--dur)] ease-[var(--ease-out)]",
          "focus-visible:border-accent focus-visible:ring-1 focus-visible:ring-accent focus-visible:outline-none",
          "disabled:cursor-not-allowed disabled:opacity-60",
          error ? "border-negative focus-visible:border-negative focus-visible:ring-negative" : "border-line",
          className
        )}
        {...props}
      />
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
