/**
 * Small motion helpers shared across src/ui and src/features.
 *
 * These stay separate from the CSS-only vocabulary in index.css because a
 * few pieces of motion cannot be pure CSS: staggering a list needs a value
 * threaded from the map index, and a progress bar that should ease in on
 * mount (not only on change) needs one render at 0 before the real value
 * lands so the CSS transition on width has something to transition from.
 */

import { useEffect, useState, type CSSProperties } from 'react'

/** A style object carrying the --stagger-index custom property .animate-rise-in reads its delay from. */
export type StaggerStyle = CSSProperties & { '--stagger-index'?: number }

/**
 * Builds the inline style for the Nth item in a staggered entrance list.
 * Kept as a CSS custom property rather than a computed `animationDelay`, so
 * the delay curve (and its 300ms cap) is defined once in index.css instead
 * of being recomputed at every call site.
 */
export function staggerStyle(index: number): StaggerStyle {
  return { '--stagger-index': index }
}

/**
 * Reads the reduced-motion media query once. Not reactive on its own; a
 * hook that needs to react to it changing mid-session watches the query
 * itself (see useChartMotion in features/reports/charts.tsx).
 */
export function prefersReducedMotion(): boolean {
  return typeof window !== 'undefined' && window.matchMedia('(prefers-reduced-motion: reduce)').matches
}

/**
 * Starts at 0 and flips to `target` one animation frame after mount, so a
 * width bound to this value eases in via the element's own CSS transition
 * (see .bar-fill in index.css) instead of snapping straight to its final
 * size. A later change to `target` needs no special handling here: the
 * value simply changes and the CSS transition animates the difference.
 *
 * Under reduced motion this returns `target` immediately, since there is no
 * transition for the jump from 0 to hide behind in that case.
 */
export function useMountedPercent(target: number): number {
  const [mounted, setMounted] = useState(prefersReducedMotion)

  useEffect(() => {
    if (mounted) return
    // One frame is enough for the browser to have painted the 0% state, so
    // the jump to `target` on the next frame is a change the CSS transition
    // actually catches, rather than two states collapsing into one paint.
    const frame = requestAnimationFrame(() => setMounted(true))
    return () => cancelAnimationFrame(frame)
    // Intentionally runs once per mount: this tracks "has this instance
    // finished its own entrance", not something meant to replay.
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [])

  return mounted ? target : 0
}
