import { defineConfig, devices } from '@playwright/test'

/**
 * The smoke suite, run against a deployment rather than a local build.
 *
 * Separate from playwright.config.ts because almost every setting is the
 * opposite: no `webServer`, since the thing under test is already running and
 * is not ours to start; a baseURL from the environment rather than a fixed
 * port; and no accessibility or journey coverage, which belongs against a
 * build you can iterate on rather than against production.
 *
 *   SMOKE_URL=https://neraca-ledger.vercel.app npm run smoke
 */

const target = process.env['SMOKE_URL']

if (!target) {
  // Failing here beats defaulting to production. A smoke suite that silently
  // picks its own target is one somebody eventually runs against the live site
  // by accident, and one that silently passes against nothing is worse.
  throw new Error('SMOKE_URL is not set. Pass the origin to smoke test, for example SMOKE_URL=https://neraca-ledger.vercel.app')
}

export default defineConfig({
  testDir: './e2e',
  testMatch: '**/smoke.spec.ts',
  fullyParallel: true,
  // A deployment is shared and remote, so a failure here is more likely to be
  // a real problem than a local flake. One retry only, to absorb a cold start.
  retries: 1,
  reporter: [['list']],
  timeout: 60_000,
  expect: { timeout: 20_000 },

  use: {
    baseURL: target,
    trace: 'retain-on-failure',
    screenshot: 'only-on-failure',
  },

  // One browser. This checks the deployment, not the rendering, and the
  // rendering is covered thoroughly against the local build.
  projects: [{ name: 'deployed', use: { ...devices['Desktop Chrome'] } }],
})
