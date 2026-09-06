#!/usr/bin/env node
/**
 * Bundle budgets, enforced hard.
 *
 * A warning nobody has to act on is a warning everybody stops reading, so this
 * exits non zero and fails the build rather than printing a caution. The
 * numbers below are ceilings with real headroom, not the current sizes: a
 * budget set to today's exact figure fails on the next honest change and gets
 * raised reflexively until it means nothing.
 *
 * Gzip is what is measured because gzip is what crosses the network. Raw bytes
 * matter for parse time, which is why the entry has a separate raw ceiling: on
 * a low end Android, parsing is often the slower half of the cost.
 *
 * Why this exists at all: the reports screen once shipped 114 KB of charting
 * library, gzipped, for one screen most visitors never opened. Nothing warned
 * anybody, because nothing was watching.
 */

import { gzipSync } from 'node:zlib'
import { readFileSync, readdirSync, statSync } from 'node:fs'
import { join } from 'node:path'

const DIST = 'apps/web/dist'

/** Ceilings in kilobytes. `raw` is optional and only set where parse cost bites. */
const BUDGETS = [
  { label: 'entry (React, router, shell, dashboard)', match: /^index-.*\.js$/, gzip: 145, raw: 460 },
  { label: 'any single lazy route chunk', match: /^(?!index-)[A-Za-z].*\.js$/, gzip: 25 },
  { label: 'stylesheet', match: /\.css$/, gzip: 20 },
]

/** Everything the browser must fetch before the first screen can be drawn. */
const CRITICAL_PATH_GZIP_KB = 180

const KB = 1024

function walk(dir) {
  const out = []
  for (const entry of readdirSync(dir)) {
    const full = join(dir, entry)
    if (statSync(full).isDirectory()) out.push(...walk(full))
    else out.push(full)
  }
  return out
}

function gzipKb(path) {
  return gzipSync(readFileSync(path), { level: 9 }).length / KB
}

function rawKb(path) {
  return statSync(path).size / KB
}

let failed = false
const report = []

const assetDir = join(DIST, 'assets')
let assets
try {
  assets = readdirSync(assetDir)
} catch {
  console.error(`Bundle budget: no build found at ${assetDir}. Run the build first.`)
  process.exit(1)
}

for (const budget of BUDGETS) {
  const matches = assets.filter((name) => budget.match.test(name))
  for (const name of matches) {
    const path = join(assetDir, name)
    const gz = gzipKb(path)
    const raw = rawKb(path)
    const overGzip = gz > budget.gzip
    const overRaw = budget.raw !== undefined && raw > budget.raw
    if (overGzip || overRaw) failed = true
    report.push({
      name,
      label: budget.label,
      gz,
      raw,
      limitGz: budget.gzip,
      limitRaw: budget.raw,
      over: overGzip || overRaw,
    })
  }
}

// The critical path is the entry script plus the stylesheet: everything else is
// lazy and is not on the way to a first paint.
const critical = walk(assetDir)
  .filter((p) => /index-.*\.(js|css)$/.test(p))
  .reduce((sum, p) => sum + gzipKb(p), 0)

const criticalOver = critical > CRITICAL_PATH_GZIP_KB
if (criticalOver) failed = true

const pad = (s, n) => String(s).padEnd(n)
console.log('\nBundle budgets (gzip, kilobytes)\n')
for (const row of report.sort((a, b) => b.gz - a.gz)) {
  const limits = row.limitRaw ? `${row.limitGz} gz / ${row.limitRaw} raw` : `${row.limitGz} gz`
  console.log(
    `  ${row.over ? 'OVER ' : '  ok '} ${pad(row.name, 40)} ${pad(row.gz.toFixed(1), 8)} of ${limits}`,
  )
}
console.log(
  `\n  ${criticalOver ? 'OVER ' : '  ok '} ${pad('critical path (entry js + css)', 40)} ${pad(critical.toFixed(1), 8)} of ${CRITICAL_PATH_GZIP_KB} gz`,
)

if (failed) {
  console.error(
    '\nBundle budget exceeded. Either make it smaller, or raise the ceiling in\n' +
      'scripts/check-bundle-size.mjs and say in the commit message why the app\n' +
      'is now allowed to cost more.\n',
  )
  process.exit(1)
}

console.log('\nAll budgets met.\n')
