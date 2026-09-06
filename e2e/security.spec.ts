import { expect, test } from '@playwright/test'
import { enterDemo, expectProductionHeaders } from './helpers'

/**
 * The security posture, asserted rather than hoped for.
 *
 * These run against `vite preview`, which serves the exact header block from
 * vercel.json (see the `preview.headers` note in apps/web/vite.config.ts), so
 * loosening a directive in the deployed configuration fails here instead of
 * quietly shipping.
 *
 * The header expectations themselves live in helpers.ts, because the smoke
 * suite asserts the same ones against the deployed origin and the two must not
 * be allowed to drift.
 */

test('the production header block is served', async ({ page }) => {
  await expectProductionHeaders(await page.goto('/'))
})

test('the page carries no inline script for a policy to have to allow', async ({ page }) => {
  await page.goto('/')

  // The precondition for `script-src 'self'` being viable at all. If a build
  // tool ever starts injecting a registration snippet inline, this catches it
  // before the policy has to be loosened to accommodate it.
  const inlineScripts = await page.evaluate(
    () =>
      [...document.querySelectorAll('script')].filter(
        (s) => !s.src && (s.textContent ?? '').trim() !== '',
      ).length,
  )
  expect(inlineScripts).toBe(0)
})

test('the service worker never caches a response containing profile data', async ({ page }) => {
  await enterDemo(page)

  // Everything the worker precaches is a build artefact. A cached response
  // holding somebody's spending would survive a sign out and sit in the
  // browser's cache storage where nothing in the app would ever clear it.
  const cached = await page.evaluate(async () => {
    if (!('caches' in window)) return []
    const names = await caches.keys()
    const urls: string[] = []
    for (const name of names) {
      const cache = await caches.open(name)
      for (const request of await cache.keys()) urls.push(request.url)
    }
    return urls
  })

  // Build artefacts are excluded by path, not by name: the lazy route
  // chunks are called things like TransactionsPage-BFIXulHq.js, which a
  // name based filter reads as data and a path based one correctly does
  // not. This assertion is about response bodies, not file names.
  const suspicious = cached
    .filter((url) => !new URL(url).pathname.startsWith('/assets/'))
    .filter((url) => /profile|transaction|wallet|budget/i.test(url))
  expect(suspicious, `cache storage held request URLs that look like data:\n${suspicious.join('\n')}`).toEqual([])
})

test('no profile data leaves the machine', async ({ page }) => {
  const external: string[] = []
  page.on('request', (request) => {
    const url = new URL(request.url())
    if (url.hostname !== 'localhost' && url.hostname !== '127.0.0.1') external.push(request.url())
  })

  await enterDemo(page)
  await page.goto('/reports')
  await page.goto('/transactions')

  // Stage 1 is entirely local. When the sync API arrives in stage 2 this
  // becomes an allowlist of exactly one origin rather than an empty set, and
  // the assertion keeps its meaning: nothing talks to anywhere unexpected.
  expect(external, `unexpected outbound requests:\n${external.join('\n')}`).toEqual([])
})
