import type { ReactNode } from 'react'

export interface EmptyStateProps {
  /** Any small illustrative element, an inline svg most often. Decorative, so it is hidden from assistive tech. */
  icon?: ReactNode
  title: string
  description?: string
  /** Typically a <Button>, left untyped as ReactNode so any actionable element can go here. */
  action?: ReactNode
  className?: string
}

export function EmptyState({ icon, title, description, action, className }: EmptyStateProps) {
  return (
    <div
      className={`flex flex-col items-center gap-3 border-y border-rule px-6 py-12 text-center ${className ?? ''}`}
    >
      {icon && (
        <div aria-hidden="true" className="text-ink-faint [&>svg]:h-10 [&>svg]:w-10">
          {icon}
        </div>
      )}
      <div className="flex flex-col gap-1">
        <p className="text-ink">{title}</p>
        {description && <p className="max-w-sm text-sm text-ink-muted">{description}</p>}
      </div>
      {action && <div className="mt-1">{action}</div>}
    </div>
  )
}
