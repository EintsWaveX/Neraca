import type { HTMLAttributes } from 'react'
import { cn } from '../lib/utils'

export interface CardProps extends HTMLAttributes<HTMLDivElement> {
  /** Lifts on hover/focus-within, for a card that acts as one interactive unit (a record with its own edit or delete controls, say). Left off by default so a purely presentational card never implies an affordance it does not have. */
  interactive?: boolean
}

/**
 * A genuinely contained group, such as a panel of settings controls.
 *
 * No shadow. In the Passbook system a shadow means the thing is floating
 * above the page, which is true of a dialog and of nothing else, so a panel
 * is marked by its rule and its ground rather than by being lifted off the
 * paper. Lists of records are not cards at all: they are ruled rows.
 */
export function Card({ interactive, className, ...props }: CardProps) {
  return (
    <div
      className={cn(
        "rounded-sheet border border-rule bg-paper-raised",
        interactive && "card-interactive",
        className
      )}
      {...props}
    />
  )
}

export interface CardHeaderProps extends HTMLAttributes<HTMLDivElement> {}

export function CardHeader({ className, ...props }: CardHeaderProps) {
  return (
    <div
      className={cn("flex items-center justify-between gap-3 border-b border-rule px-5 py-3", className)}
      {...props}
    />
  )
}

export interface CardTitleProps extends HTMLAttributes<HTMLHeadingElement> {}

export function CardTitle({ className, ...props }: CardTitleProps) {
  return <h3 className={cn("text-h3 leading-snug text-ink", className)} {...props} />
}

export interface CardBodyProps extends HTMLAttributes<HTMLDivElement> {}

export function CardBody({ className, ...props }: CardBodyProps) {
  return <div className={cn("px-5 py-4", className)} {...props} />
}

export interface CardFooterProps extends HTMLAttributes<HTMLDivElement> {}

export function CardFooter({ className, ...props }: CardFooterProps) {
  return (
    <div
      className={cn("flex items-center justify-end gap-2 border-t border-rule px-5 py-3", className)}
      {...props}
    />
  )
}
