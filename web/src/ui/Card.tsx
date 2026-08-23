import type { HTMLAttributes } from 'react'

export interface CardProps extends HTMLAttributes<HTMLDivElement> {}

/** The card surface itself. Uses the shared --radius-card and --shadow-card tokens so every card in every app matches. */
export function Card({ className, ...props }: CardProps) {
  return (
    <div
      className={`rounded-card border border-line bg-surface shadow-[var(--shadow-card)] ${className ?? ''}`}
      {...props}
    />
  )
}

export interface CardHeaderProps extends HTMLAttributes<HTMLDivElement> {}

export function CardHeader({ className, ...props }: CardHeaderProps) {
  return (
    <div
      className={`flex items-center justify-between gap-3 border-b border-line px-5 py-4 ${className ?? ''}`}
      {...props}
    />
  )
}

export interface CardTitleProps extends HTMLAttributes<HTMLHeadingElement> {}

export function CardTitle({ className, ...props }: CardTitleProps) {
  return <h3 className={`text-sm font-semibold text-text ${className ?? ''}`} {...props} />
}

export interface CardBodyProps extends HTMLAttributes<HTMLDivElement> {}

export function CardBody({ className, ...props }: CardBodyProps) {
  return <div className={`px-5 py-4 ${className ?? ''}`} {...props} />
}

export interface CardFooterProps extends HTMLAttributes<HTMLDivElement> {}

export function CardFooter({ className, ...props }: CardFooterProps) {
  return (
    <div
      className={`flex items-center justify-end gap-2 border-t border-line px-5 py-4 ${className ?? ''}`}
      {...props}
    />
  )
}
