import { defineConfig } from 'vitest/config'

// One runner across every workspace, so `npm test` at the root is the whole
// suite rather than whichever package you happen to be standing in.
export default defineConfig({
  test: {
    projects: ['apps/*', 'packages/*'],
  },
})
