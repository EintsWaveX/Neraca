import AxeBuilder from '@axe-core/playwright'
import { expect, test } from '@playwright/test'
import { enterDemo, setTheme, settle, SCREENS } from './helpers'

/**
 * Accessibility is part of done, per CLAUDE.md, so it is a gate rather than a
 * later pass.
 *
 * axe catches the mechanical half: contrast, names, roles, landmark structure.
 * It cannot tell whether the interface makes sense with a keyboard, which is
 * why the keyboard journeys below are written out by hand.
 */

const RULESETS = ['wcag2a', 'wcag2aa', 'wcag21a', 'wcag21aa']

/**
 * axe walks the whole rendered tree and computes a contrast ratio for every
 * text node on it, which on the register is a few thousand of them. That is
 * genuinely slower than the rest of the suite and is not a symptom of anything
 * being wrong, so these tests get twice the default budget. Capping the worker
 * count in the config is what actually fixed the flaking; this is the headroom
 * for a CI runner slower than any laptop.
 */
test.describe.configure({ timeout: 60_000 })

for (const screen of SCREENS) {
  test(`${screen.name} has no accessibility violations`, async ({ page }) => {
    await enterDemo(page)
    await page.goto(screen.path)
    await expect(page.getByRole('heading', { level: 1, name: screen.heading })).toBeVisible()
    await settle(page)

    const results = await new AxeBuilder({ page }).withTags(RULESETS).analyze()

    // Naming the violations in the failure beats a bare count: the whole point
    // of running this in CI is that whoever broke it should not have to
    // re-run it locally to find out what they broke.
    const summary = results.violations
      .map((v) => `${v.id} (${v.impact}): ${v.nodes.length} node(s)\n    ${v.help}`)
      .join('\n  ')
    expect(results.violations, `axe on ${screen.path}:\n  ${summary}`).toEqual([])
  })
}

test('the dark theme keeps its contrast', async ({ page }) => {
  await enterDemo(page)
  await setTheme(page, 'dark')
  await settle(page)

  // Dark mode is where contrast quietly fails: the first draft of this palette
  // sat at a lightness that read as pure black and lost the accent entirely.
  const results = await new AxeBuilder({ page })
    .withTags(RULESETS)
    .include('body')
    .analyze()

  const summary = results.violations.map((v) => `${v.id}: ${v.help}`).join('\n  ')
  expect(results.violations, `axe in dark mode:\n  ${summary}`).toEqual([])
})

test('the whole shell is reachable with a keyboard alone', async ({ page }, testInfo) => {
  test.skip(testInfo.project.name !== 'desktop', 'tab order is a pointerless-desktop concern')

  await enterDemo(page)

  // Walk forward through the document and collect what actually took focus.
  const reached: string[] = []
  for (let i = 0; i < 25; i += 1) {
    await page.keyboard.press('Tab')
    const description = await page.evaluate(() => {
      const el = document.activeElement
      if (!el || el === document.body) return null
      const label = el.getAttribute('aria-label') ?? el.textContent?.trim().slice(0, 40) ?? ''
      return `${el.tagName.toLowerCase()}:${label}`
    })
    if (description) reached.push(description)
  }

  // Every primary destination should be tabbable without a pointer.
  const joined = reached.join(' | ').toLowerCase()
  for (const word of ['dashboard', 'transactions', 'wallets', 'budgets']) {
    expect(joined, `"${word}" was never focused while tabbing:\n${joined}`).toContain(word)
  }
})

test('focus is always visible on the element that has it', async ({ page }, testInfo) => {
  test.skip(testInfo.project.name !== 'desktop', 'no visible focus ring on a touch device')

  await enterDemo(page)
  await page.keyboard.press('Tab')

  // A focus style that resolves to "none" is the single most common way an
  // otherwise keyboard operable app becomes unusable without a pointer.
  const outline = await page.evaluate(() => {
    const el = document.activeElement
    if (!el) return null
    const style = getComputedStyle(el)
    return {
      outlineStyle: style.outlineStyle,
      outlineWidth: style.outlineWidth,
      boxShadow: style.boxShadow,
    }
  })

  expect(outline).not.toBeNull()
  const hasRing =
    (outline!.outlineStyle !== 'none' && outline!.outlineWidth !== '0px') ||
    (outline!.boxShadow !== 'none' && outline!.boxShadow !== '')
  expect(hasRing, `focused element had no visible ring: ${JSON.stringify(outline)}`).toBe(true)
})

test('the category combobox is fully operable from the keyboard', async ({ page }, testInfo) => {
  test.skip(testInfo.project.name !== 'desktop', 'covered separately as a sheet on mobile')

  // The specimen is the one page that mounts the combobox outside a form, so
  // it is the cheapest honest place to exercise the listbox pattern.
  await page.goto('/specimen')

  const combobox = page.getByRole('combobox', { name: /category/i })
  await combobox.focus()
  await expect(combobox).toHaveAttribute('aria-expanded', 'true')

  await page.keyboard.press('ArrowDown')
  await page.keyboard.press('Enter')

  await expect(combobox).toHaveAttribute('aria-expanded', 'false')
  await expect(combobox).not.toHaveValue('')
})
