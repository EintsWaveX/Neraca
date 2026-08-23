import type { HTMLAttributes } from 'react'

export interface SkeletonProps extends HTMLAttributes<HTMLDivElement> {
  /** text for a line of copy, block for a card or image area, circle for an avatar. */
  shape?: 'text' | 'block' | 'circle'
}

const shapeClasses: Record<NonNullable<SkeletonProps['shape']>, string> = {
  text: 'rounded',
  block: 'rounded-control',
  circle: 'rounded-full',
}

// Built on Tailwind's animate-pulse rather than a hand rolled gradient sweep,
// because it needs no keyframes beyond what Tailwind already ships, and the
// global rule in index.css that zeroes animation-duration under
// prefers-reduced-motion already covers it without any extra work here.
export function Skeleton({ shape = 'text', className, ...props }: SkeletonProps) {
  return (
    <div
      aria-hidden="true"
      className={`animate-pulse bg-surface-sunken ${shapeClasses[shape]} ${className ?? ''}`}
      {...props}
    />
  )
}
