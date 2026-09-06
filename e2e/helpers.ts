import { expect, type Page } from '@playwright/test'

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
 */
export async function settle(page: Page): Promise<void> {
  await page.waitForFunction(
    () => document.getAnimations().every((animation) => animation.playState !== 'running'),
    undefined,
    { timeout: 10_000 },
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
