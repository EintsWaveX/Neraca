import { useEffect, useRef, useState } from 'react'
import { registerSW } from 'virtual:pwa-register'
import { useI18n } from '@/i18n'
import { Button } from '@/ui'

/**
 * Offers a new build instead of installing it underneath the visitor.
 *
 * vite-plugin-pwa is configured with registerType 'prompt' (see
 * vite.config.ts), so a waiting service worker stays idle until something
 * calls its update function. That something is this bar. The alternative,
 * 'autoUpdate', reloads the page on its own, which on a data application can
 * throw away a half filled transaction form the visitor was still typing in.
 */
export function UpdatePrompt() {
  const { t } = useI18n()
  const [needRefresh, setNeedRefresh] = useState(false)
  const [dismissed, setDismissed] = useState(false)
  const updateSW = useRef<((reload?: boolean) => Promise<void>) | null>(null)

  useEffect(() => {
    // Registering inside an effect rather than at module scope keeps the
    // service worker out of any environment that imports this module without
    // a browser behind it, the test run included, and holds registration back
    // until after the first paint.
    updateSW.current = registerSW({
      onNeedRefresh() {
        setNeedRefresh(true)
      },
    })
  }, [])

  if (!needRefresh || dismissed) return null

  return (
    <div
      role="status"
      aria-live="polite"
      // Sits above the mobile tab bar (which is fixed at bottom-0) rather than
      // on top of it, and drops to the bottom edge once that bar is gone at md.
      className="animate-rise-in fixed inset-x-4 bottom-20 z-20 mx-auto flex max-w-md items-center justify-between gap-3 rounded-card border border-line bg-surface-raised px-4 py-3 shadow-[var(--shadow-pop)] md:bottom-4"
    >
      <p className="text-sm text-text">{t.update.available}</p>
      <div className="flex shrink-0 items-center gap-2">
        <Button variant="ghost" size="sm" onClick={() => setDismissed(true)}>
          {t.update.dismiss}
        </Button>
        <Button variant="primary" size="sm" onClick={() => void updateSW.current?.(true)}>
          {t.update.reload}
        </Button>
      </div>
    </div>
  )
}
