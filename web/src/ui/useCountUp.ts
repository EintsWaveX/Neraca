import { useEffect, useRef, useState } from 'react'
import { prefersReducedMotion } from './motion'

/**
 * Eases a displayed number from its previous value toward `target` whenever
 * `target` changes, including counting up from 0 on first mount. Meant only
 * for the handful of headline figures a reader's eye lands on first (net
 * worth, this month's totals); every other number in the app, table cells
 * included, renders its final value directly with no hook involved, since
 * animating a whole column of figures would be noise rather than emphasis.
 *
 * Snaps straight to `target` under reduced motion, checked at the point the
 * animation would otherwise start, since a rapidly changing number is
 * exactly the kind of motion that preference exists to suppress and it
 * cannot be neutralised by the CSS transition-duration rule in index.css
 * the way a plain CSS animation can.
 */
export function useCountUp(target: number, durationMs = 600): number {
  const [value, setValue] = useState(() => (prefersReducedMotion() ? target : 0))
  // Tracks whether this instance has already run at least one animation, so
  // the first run always starts from 0 (a fresh mount) while later runs
  // (the target changed) start from wherever the display currently sits.
  const startedRef = useRef(false)

  useEffect(() => {
    if (prefersReducedMotion()) {
      setValue(target)
      return
    }

    const from = startedRef.current ? value : 0
    startedRef.current = true
    const delta = target - from
    if (delta === 0) {
      setValue(target)
      return
    }

    let frame: number
    const start = performance.now()

    function tick(now: number) {
      const elapsed = now - start
      const t = Math.min(1, elapsed / durationMs)
      // Cubic ease-out: fast start, gentle settle, the same shape --ease-out
      // draws for the CSS-driven motion everywhere else in the app.
      const eased = 1 - Math.pow(1 - t, 3)
      setValue(from + delta * eased)
      if (t < 1) frame = requestAnimationFrame(tick)
    }

    frame = requestAnimationFrame(tick)
    return () => cancelAnimationFrame(frame)
    // `value` is read only to seed `from` on the render that scheduled this
    // effect; depending on it would restart the animation every frame it
    // updates its own state.
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [target, durationMs])

  return value
}
