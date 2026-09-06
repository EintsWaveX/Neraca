import { expect, test } from '@playwright/test'
import { enterDemo } from './helpers'

/**
 * The security posture, asserted rather than hoped for.
 *
 * These run against `vite preview`, which serves the exact header block from
 * vercel.json (see the `preview.headers` note in apps/web/vite.config.ts), so
 * loosening a directive in the deployed configuration fails here instead of
 * quietly shipping.
 */

interface Directives {
  [name: string]: string[]
}

function parseCsp(header: string): Directives {
  const out: Directives = {}
  for (const part of header.split(';')) {
    const [name, ...values] = part.trim().split(/\s+/)
    if (name) out[name] = values
  }
  return out
}

test('the policy forbids inline and injected script', async ({ page }) => {
  const response = await page.goto('/')
  const csp = response?.headers()['content-security-policy']
  expect(csp, 'no Content-Security-Policy header was served').toBeTruthy()

  const directives = parseCsp(csp!)

  // The two that actually stop cross site scripting. Everything else on this
  // page is defence in depth; these are the load bearing ones.
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
})

test('the supporting headers are all present', async ({ page }) => {
  const response = await page.goto('/')
  const headers = response!.headers()

  expect(headers['x-content-type-options']).toBe('nosniff')
  expect(headers['referrer-policy']).toBe('no-referrer')
  expect(headers['cross-origin-opener-policy']).toBe('same-origin')
  expect(headers['permissions-policy']).toContain('geolocation=()')
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
