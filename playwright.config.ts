import { defineConfig, devices } from '@playwright/test'

/**
 * End to end tests run against the built application served by `vite preview`,
 * never against the dev server.
 *
 * The dev server injects its HMR client and its styles inline, which the
 * production Content Security Policy correctly forbids, so a suite pointed at
 * dev would pass while the real deployment was broken. Preview serves the same
 * bundle and, through the `preview.headers` block in apps/web/vite.config.ts,
 * the same headers the edge will serve.
 */
export default defineConfig({
  testDir: './e2e',
  // The smoke suite needs a deployment rather than this config's preview
  // server, so it has its own config and is kept out of this one's run.
  testIgnore: '**/smoke.spec.ts',
  fullyParallel: true,
  // A test that only passes sometimes is worse than no test, so a retry in CI
  // is allowed to mask a flake exactly once and the run is still reported.
  retries: process.env['CI'] ? 1 : 0,
  reporter: process.env['CI'] ? [['list'], ['html', { open: 'never' }]] : [['list']],
  // Left to itself Playwright takes half the cores, which is six here, and
  // axe-core is expensive enough that six of them at once starved each other
  // until the accessibility tests failed on the 30s test timeout at random, a
  // different screen each run. Every one of them finishes in four or five
  // seconds when it is not fighting the others for a core. Capping the workers
  // costs wall clock and buys results that measure the application rather than
  // the machine it happened to run on.
  workers: process.env['CI'] ? 2 : '25%',
  timeout: 30_000,
  expect: { timeout: 7_000 },

  use: {
    baseURL: 'http://localhost:4173',
    trace: 'retain-on-failure',
    screenshot: 'only-on-failure',
    // Every profile in this app lives in IndexedDB, so tests must not share
    // one. Playwright gives each test its own context, which is its own
    // origin storage, so isolation is already the default here.
  },

  projects: [
    { name: 'desktop', use: { ...devices['Desktop Chrome'] } },
    // A real phone viewport rather than a narrowed desktop one, since the
    // ledger's whole narrow layout hangs off a width breakpoint.
    { name: 'mobile', use: { ...devices['Pixel 7'] } },
  ],

  webServer: {
    // Vite is invoked directly rather than through the root preview script:
    // arguments after -- do not survive being forwarded through a nested
    // `npm run -w`, so the port silently never reached vite.
    command: 'npx vite preview --port 4173 --strictPort',
    cwd: 'apps/web',
    url: 'http://localhost:4173',
    reuseExistingServer: !process.env['CI'],
    timeout: 120_000,
  },
})
