import { expect, test } from '@playwright/test'
import { expectProductionHeaders } from './helpers'

/**
 * The deployment itself, checked against the origin that visitors get.
 *
 * Everything else in this directory runs against `vite preview`, which replays
 * the header block out of vercel.json rather than being sent it by an edge. It
 * is a good stand in and it caught real things, but it cannot prove that Vercel
 * applied the configuration, that the rewrite rules survived, or that the cache
 * headers landed on the paths they were written for. A configuration file is a
 * request, not a result.
 *
 * Run with the origin in the environment, which is also why this file is
 * excluded from the main config:
 *
 *   SMOKE_URL=https://neraca-ledger.vercel.app npm run smoke
 */

test('the edge serves the production header block', async ({ page }) => {
  await expectProductionHeaders(await page.goto('/'))
})

test('a deep link is rewritten to the application rather than 404ing', async ({ page }) => {
  // The single most likely thing to be wrong on a first real deployment. A
  // static host without the rewrite serves nothing at /transactions, because
  // there is no such file: the route only exists once the bundle is running.
  const response = await page.goto('/transactions')
  expect(response?.status(), 'the SPA rewrite did not apply').toBe(200)

  await expect(page.getByRole('heading', { level: 1, name: /transactions/i })).toBeVisible({
    timeout: 20_000,
  })
})

test('a cold visit lands in the seeded demo profile', async ({ page }) => {
  await page.goto('/')

  // Decision 8, asserted against the deployment rather than a local build,
  // because seeding runs off IndexedDB and a shipped service worker is the one
  // thing that could serve a stale bundle to a first time visitor.
  await expect(page.getByRole('heading', { level: 1 })).toBeVisible({ timeout: 20_000 })

  const balance = page.locator('.figure-display').first()
  await expect(balance).toBeVisible()
  await expect(balance).toContainText(/\d/)
})

test('the cache headers landed on the paths they were written for', async ({ request, page }) => {
  await page.goto('/')

  // Hashed assets are immutable for a year; the service worker must not be,
  // or a visitor keeps whichever worker they first met and never sees another
  // deployment. Getting these two the wrong way round is silent for months.
  const asset = await page.evaluate(
    () =>
      [...document.querySelectorAll('script[src]')]
        .map((s) => new URL((s as HTMLScriptElement).src).pathname)
        .find((path) => path.startsWith('/assets/')) ?? null,
  )
  expect(asset, 'no hashed asset was linked from the page').not.toBeNull()

  const assetResponse = await request.get(asset!)
  expect(assetResponse.headers()['cache-control']).toContain('immutable')

  const workerResponse = await request.get('/sw.js')
  expect(workerResponse.headers()['cache-control']).toContain('must-revalidate')
})
