import { expect, test } from '@playwright/test'
import { enterDemo } from './helpers'

/**
 * The paths that change stored data.
 *
 * Everything else in this directory reads: it walks screens, checks headings,
 * samples contrast and asserts headers. The one test that opened the
 * transaction dialog deliberately pressed Escape rather than saving, so until
 * now nothing exercised creating, editing or deleting a record through the
 * interface, nor exporting one, nor the lock that stands in front of all of it.
 *
 * Those are the paths where a defect costs somebody their data rather than
 * merely looking wrong, which is a poor place for the coverage to stop.
 *
 * Each test gets its own browser context and therefore its own IndexedDB, so
 * nothing here can reach another test's profile. The lifecycle test still
 * deletes what it created, because a test that leaves a stray record behind
 * makes every screenshot taken afterwards confusing.
 */

/** Unique per run, so a row can be found by its own description and nothing else. */
function marker(name: string): string {
  return `e2e ${name} ${Date.now()}`
}

test('a transaction can be created, edited and deleted', async ({ page }) => {
  await enterDemo(page)
  await page.goto('/transactions')

  const rows = page.locator('table.ledger tbody tr:not(.ledger-total)')
  await expect(rows.first()).toBeVisible()

  const created = marker('created')

  await page.getByRole('button', { name: /add transaction/i }).click()
  const dialog = page.getByRole('dialog')
  await expect(dialog).toBeVisible()

  // Found by role and accessible name rather than by getByLabel, because a
  // required field's <label> also contains the aria-hidden asterisk, so its
  // text is "Wallet*" and an exact label match never finds it. The accessible
  // name computation drops the asterisk, which is the whole point of hiding it.
  //
  // The category list is filtered by the chosen type, so type is picked first
  // and the category options are only meaningful afterwards. Index 1 skips the
  // disabled placeholder that every one of these selects opens on.
  await dialog.getByRole('combobox', { name: 'Transaction type' }).selectOption({ index: 1 })
  await dialog.getByRole('combobox', { name: 'Category' }).selectOption({ index: 1 })
  await dialog.getByRole('combobox', { name: 'Wallet' }).selectOption({ index: 1 })
  await dialog.getByRole('textbox', { name: 'Amount', exact: true }).fill('12345')
  await dialog.getByRole('textbox', { name: 'Description' }).fill(created)

  // The date field is left at today, so the new row sorts to the top of a
  // register that is ordered by date descending and paginated at twenty.
  await dialog.getByRole('button', { name: 'Save', exact: true }).click()
  await expect(dialog).not.toBeVisible()

  const row = rows.filter({ hasText: created })
  await expect(row, 'the saved transaction never appeared in the register').toHaveCount(1)
  await expect(row).toContainText('12.345')

  // Edit it. The same form, opened on an existing record rather than a blank.
  const edited = marker('edited')
  await row.getByRole('button', { name: 'Edit', exact: true }).click()
  await expect(dialog).toBeVisible()
  await dialog.getByRole('textbox', { name: 'Description' }).fill(edited)
  await dialog.getByRole('button', { name: 'Save', exact: true }).click()
  await expect(dialog).not.toBeVisible()

  await expect(rows.filter({ hasText: edited })).toHaveCount(1)
  await expect(rows.filter({ hasText: created }), 'the old description survived the edit').toHaveCount(0)

  // Delete it, through the confirmation rather than around it.
  await rows.filter({ hasText: edited }).getByRole('button', { name: 'Delete', exact: true }).click()
  const confirm = page.getByRole('dialog')
  await expect(confirm).toBeVisible()
  await confirm.getByRole('button', { name: 'Delete', exact: true }).click()
  await expect(confirm).not.toBeVisible()

  await expect(rows.filter({ hasText: edited }), 'the transaction outlived its deletion').toHaveCount(0)
})

test('a profile can be exported and the export holds its data', async ({ page }, testInfo) => {
  test.skip(testInfo.project.name !== 'desktop', 'the export controls are the same at both widths')

  await enterDemo(page)
  await page.goto('/settings')

  // Settings is tabbed and only the open panel is in the tree, so the panel
  // holding the export controls has to be opened before anything in it exists.
  await page.getByRole('tab', { name: 'CSV import and export' }).click()
  const panel = page.getByRole('tabpanel')

  // Asserted through the fallback textarea rather than by capturing a file.
  // DataPanel renders the identical content into a read only field beside
  // every download precisely so a person can copy it by hand when a download
  // is blocked, which makes it the honest thing to assert against: if the
  // textarea is right, the blob built from the same string is right.
  const exportButtons = panel.getByRole('button', { name: 'Export', exact: true })
  await expect(exportButtons).toHaveCount(2)

  // The whole profile as JSON.
  await exportButtons.first().click()
  await expect(panel.getByRole('link', { name: /-backup\.json$/ })).toBeVisible()
  await panel.getByRole('button', { name: 'Preview', exact: true }).first().click()

  const backup = await panel.locator('textarea[readonly]').first().inputValue()
  const parsed = JSON.parse(backup) as Record<string, unknown>
  expect(Object.keys(parsed), `the backup parsed but held nothing useful: ${backup.slice(0, 200)}`)
    .toEqual(expect.arrayContaining(['profile', 'wallets', 'transactions']))

  // The transactions as CSV.
  await exportButtons.nth(1).click()
  await expect(panel.getByRole('link', { name: /-transactions\.csv$/ })).toBeVisible()
})

test('a PIN locks the profile and the right one opens it', async ({ page }, testInfo) => {
  test.skip(testInfo.project.name !== 'desktop', 'the lock screen is one field at every width')

  await enterDemo(page)
  await page.goto('/settings')

  // "Set a PIN" names the tab, the panel, the card, the field and the button.
  // Everything here is therefore scoped to the open panel and picked by role,
  // since the string on its own is ambiguous five ways. A PIN field is a
  // password input, which carries no implicit role at all, so it is the one
  // thing that still has to be found by its label.
  await page.getByRole('tab', { name: 'Set a PIN' }).click()
  const panel = page.getByRole('tabpanel')

  await panel.getByLabel('Set a PIN', { exact: true }).fill('4821')
  await panel.getByLabel('Confirm PIN', { exact: true }).fill('4821')
  await panel.getByRole('button', { name: 'Set a PIN', exact: true }).click()
  await expect(panel.getByText('Done', { exact: true })).toBeVisible()

  // A reload is the point: the PIN has to survive into a new page load, since
  // what it guards against is somebody picking the device up later.
  await page.reload()

  const lock = page.getByRole('heading', { level: 1, name: /enter your pin/i })
  await expect(lock, 'the profile opened without asking for the PIN').toBeVisible()

  // Not an exact label match: the lock screen's field is required, so its
  // <label> carries the aria-hidden asterisk and its text is "Enter your PIN*".
  // A password input has no implicit role, so there is no name based lookup to
  // fall back to the way the form fields above use one.
  await page.getByLabel(/enter your pin/i).fill('0000')
  await page.getByRole('button', { name: 'OK', exact: true }).click()
  await expect(page.getByRole('alert')).toBeVisible()
  await expect(lock, 'a wrong PIN opened the profile').toBeVisible()

  await page.getByLabel(/enter your pin/i).fill('4821')
  await page.getByRole('button', { name: 'OK', exact: true }).click()

  await expect(page.getByRole('navigation').first()).toBeVisible()
  await expect(lock).not.toBeVisible()
})
