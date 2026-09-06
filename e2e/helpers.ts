import { expect, type Page, type Response } from '@playwright/test'

/**
 * Open the app and get into the seeded demo profile.
 *
 * A first visit seeds one demo profile and drops straight into it, with no
 * picker and no sign up wall, which is decision 8: somebody opening the link
 * should land in a populated application. The picker only appears once a
 * second profile exists, so this handles both and does not assume either.
 *
 * The generous timeout is not padding. A fresh browser context has an empty
 * IndexedDB, so the first load writes fourteen months of demo history before
 * anything can render, and under parallel workers that occasionally runs past
 * the default expect timeout. Waiting longer here is honest; retrying the
 * whole test would be hiding it.
 */
export async function enterDemo(page: Page): Promise<void> {
  await page.goto('/')

  const picker = page.getByRole('heading', { name: /who is using this device/i })
  if (await picker.isVisible().catch(() => false)) {
    await page.getByRole('button', { name: /demo/i }).first().click()
  }

  await expect(page.getByRole('heading', { level: 1 })).toBeVisible({ timeout: 20_000 })
}

/**
 * Wait until nothing on the page is still moving.
 *
 * Rows print in by animating their opacity and clip path, and axe samples
 * whatever colour is on screen at the instant it runs. Sampling half way
 * through a fade reports the blend as the foreground colour, which produced a
 * spread of near miss contrast failures (3.56, 4.04, 4.22, 4.35, 4.47) that
 * were all the same one token at different points in its own entrance. A
 * transient value during an animation is not a WCAG failure; the settled one
 * is what a reader actually reads.
 *
 * Two things this has to get right, and the obvious version gets neither.
 *
 * Animations that never end are excluded rather than waited for. The kawung
 * field is a 90 second infinite drift and the skeleton shimmer loops forever,
 * so waiting for either to reach a resting state waits for something that will
 * not happen. Neither is on a screen this suite currently visits, which is the
 * only reason the simpler version worked, and the first empty state that shows
 * one would have turned into a ten second timeout pointing at the wrong thing.
 *
 * And quiet has to be sustained rather than instantaneous. `getAnimations()`
 * is empty both after everything has finished and before anything has begun,
 * so a check that fires on the first quiet frame can pass in the gap between
 * React committing the rows and the browser starting their entrance, which
 * hands axe a page that starts fading the moment it begins reading. That is
 * where the near miss contrast readings came from. Requiring several
 * consecutive quiet frames tells the two kinds of silence apart.
 */
export async function settle(page: Page): Promise<void> {
  await page.waitForFunction(
    () => {
      const state = window as unknown as { __settleQuietFrames?: number }
      const stillRunning = document.getAnimations().some((animation) => {
        if (animation.effect?.getComputedTiming().iterations === Infinity) return false
        return animation.playState === 'running'
      })
      state.__settleQuietFrames = stillRunning ? 0 : (state.__settleQuietFrames ?? 0) + 1
      return state.__settleQuietFrames >= 5
    },
    undefined,
    { timeout: 10_000, polling: 'raf' },
  )
}

/** Force a theme so an assertion is not at the mercy of the runner's OS setting. */
export async function setTheme(page: Page, theme: 'light' | 'dark'): Promise<void> {
  await page.evaluate((value) => {
    document.documentElement.dataset['theme'] = value
  }, theme)
}

/**
 * The routes a visitor can reach, with the h1 each one shows.
 *
 * Matched by heading role rather than by text: a plain text match found the
 * navigation link of the same name first, which is visible on a desktop and
 * hidden on a phone, so every mobile assertion failed against an element
 * that was never the page heading in the first place.
 */
export const SCREENS = [
  { path: '/', heading: /total balance/i, name: 'dashboard' },
  { path: '/transactions', heading: /transactions/i, name: 'transactions' },
  { path: '/wallets', heading: /wallets/i, name: 'wallets' },
  { path: '/budgets', heading: /budgets/i, name: 'budgets' },
  { path: '/recurring', heading: /recurring/i, name: 'recurring' },
  { path: '/reports', heading: /reports/i, name: 'reports' },
  { path: '/settings', heading: /settings/i, name: 'settings' },
] as const

/** One directive name to the tokens that follow it. */
export function parseCsp(header: string): Record<string, string[]> {
  const out: Record<string, string[]> = {}
  for (const part of header.split(';')) {
    const [name, ...values] = part.trim().split(/\s+/)
    if (name) out[name] = values
  }
  return out
}

/**
 * The production header block, asserted in one place.
 *
 * Two suites need it. The local one runs against `vite preview`, which replays
 * the block out of vercel.json through the `preview.headers` hook in
 * apps/web/vite.config.ts, and the smoke one runs against the deployed origin,
 * where Vercel serves it for real. Writing the expectations twice would let the
 * two drift, and a policy that passes locally while production serves
 * something weaker is the exact failure these tests exist to catch.
 */
export async function expectProductionHeaders(response: Response | null): Promise<void> {
  expect(response, 'no response at all').not.toBeNull()
  const headers = response!.headers()

  const csp = headers['content-security-policy']
  expect(csp, 'no Content-Security-Policy header was served').toBeTruthy()
  const directives = parseCsp(csp!)

  // The two that actually stop cross site scripting. Everything else here is
  // defence in depth; these are the load bearing ones.
  expect(directives['script-src']).toEqual(["'self'"])
  expect(directives['script-src']).not.toContain("'unsafe-inline'")
  expect(directives['script-src']).not.toContain("'unsafe-eval'")

  // Nothing may embed this app, which is what stops a clickjacked transfer.
  expect(directives['frame-ancestors']).toEqual(["'none'"])
  expect(directives['object-src']).toEqual(["'none'"])
  expect(directives['base-uri']).toEqual(["'self'"])

  // Fonts are self hosted precisely so this can be closed. If a font ever
  // moves back to a CDN, this fails and the decision has to be made again out
  // loud rather than by adding a domain to a list.
  expect(directives['font-src']).toEqual(["'self'"])

  // Inline style attributes are allowed because React sets them for the
  // stagger index and the bar widths; inline <style> elements are not.
  expect(directives['style-src']).toEqual(["'self'"])
  expect(directives['style-src-attr']).toEqual(["'unsafe-inline'"])

  expect(headers['x-content-type-options']).toBe('nosniff')
  expect(headers['referrer-policy']).toBe('no-referrer')
  expect(headers['cross-origin-opener-policy']).toBe('same-origin')
  expect(headers['permissions-policy']).toContain('geolocation=()')
}
