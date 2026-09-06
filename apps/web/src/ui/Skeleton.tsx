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

// Built on the shared .animate-shimmer keyframe (index.css) rather than
// Tailwind's flat animate-pulse, so a loading placeholder reads as a sweep
// of light rather than a blunt fade in and out. The global rule in
// index.css that zeroes animation-duration under prefers-reduced-motion
// already covers it without any extra work here: it settles on the
// gradient's end position almost instantly instead of looping.
export function Skeleton({ shape = 'text', className, ...props }: SkeletonProps) {
  return (
    <div
      aria-hidden="true"
      className={`animate-shimmer ${shapeClasses[shape]} ${className ?? ''}`}
      {...props}
    />
  )
}
