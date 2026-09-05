/**
 * Export and import, plus the danger zone.
 *
 * DOWNLOADS. A page embedded in some contexts (an iframe, certain in-app
 * browsers) blocks a script that calls .click() on a detached anchor to
 * force a save. The fix used everywhere in this file is the one the task
 * calls for: build the blob, put its URL on a real <a download> that is
 * actually in the page, and let the person click it themselves. That is a
 * genuine user activated download the same way clicking any other link is,
 * so it keeps working where a synthetic one would not. The object URL is
 * revoked a few seconds after that click, giving the browser time to have
 * already opened the blob before the URL stops resolving. A "preview" toggle
 * next to every download always renders the same content into a read only,
 * selectable textarea too, so a person can copy it by hand if the download
 * itself is the part that is blocked.
 *
 * CSV IMPORT. A bad row is recorded and skipped by domain/csv.ts's
 * importRows, never allowed to abort the rows around it. This file mirrors
 * that: every row that failed is listed with its row number and reason
 * rather than being swallowed into a single generic error.
 */

import {
  useEffect, useRef, useState, type ChangeEvent, type DragEvent,
} from 'react'
import { useI18n, type T } from '@/i18n'
import { useProfile, useProfiles } from '@/app/ProfileProvider'
import { useAsync, useRepository } from '@/app/repo'
import { buildDemoBackup, todayIso } from '@/data/seed'
import {
  Button, Card, CardBody, CardHeader, CardTitle, Input, Modal, Select, Textarea,
} from '@/ui'
import {
  detectColumns, EXPORT_COLUMNS, importRows, parseCsv, transactionsToCsv,
  type CsvField, type ImportContext, type ImportError,
} from '@/domain/csv'
import { CATEGORIES } from '@/domain/categories'
import { TRANSACTION_TYPES } from '@/domain/txTypes'
import { CURRENCY_CODES, type CurrencyCode } from '@/domain/currency'
import { newId, nowIso } from '@/data/ids'
import type { ProfileBackup, Transaction } from '@/domain/types'

// ---------------------------------------------------------------------------
// Shared download control: a real anchor, a blob URL, a revoke, and a
// fallback textarea. See the file banner above for why each piece is there.
// ---------------------------------------------------------------------------

interface GeneratedFile {
  content: string
  message?: string
}

interface DownloadAreaProps {
  triggerLabel: string
  filename: string
  mime: string
  generate: () => Promise<GeneratedFile> | GeneratedFile
  disabled?: boolean
}

function DownloadArea({ triggerLabel, filename, mime, generate, disabled }: DownloadAreaProps) {
  const { t } = useI18n()
  const [file, setFile] = useState<GeneratedFile | null>(null)
  const [url, setUrl] = useState<string | null>(null)
  const [showText, setShowText] = useState(false)
  const [busy, setBusy] = useState(false)

  // Revoke whatever URL this instance is holding when it unmounts, so
  // navigating away from settings does not leak a blob URL.
  useEffect(() => () => {
    if (url) URL.revokeObjectURL(url)
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [])

  async function handleGenerate() {
    setBusy(true)
    try {
      const result = await generate()
      setFile(result)
      setUrl((previous) => {
        if (previous) URL.revokeObjectURL(previous)
        return URL.createObjectURL(new Blob([result.content], { type: mime }))
      })
    } finally {
      setBusy(false)
    }
  }

  function handleAnchorClick() {
    if (!url) return
    const toRevoke = url
    window.setTimeout(() => URL.revokeObjectURL(toRevoke), 4000)
  }

  return (
    <div className="flex flex-col gap-2">
      <div className="flex flex-wrap items-center gap-2">
        <Button onClick={handleGenerate} loading={busy} disabled={disabled}>
          {triggerLabel}
        </Button>
        {url && (
          <a
            href={url}
            download={filename}
            onClick={handleAnchorClick}
            className="inline-flex h-10 items-center justify-center rounded-control border border-line bg-surface px-4 text-sm font-medium text-accent hover:bg-surface-sunken"
          >
            {filename}
          </a>
        )}
        {file && (
          <Button variant="ghost" size="sm" onClick={() => setShowText((prev) => !prev)}>
            {t.csv.import.previewTitle}
          </Button>
        )}
      </div>
      {file?.message && <p className="text-xs text-positive">{file.message}</p>}
      {showText && file && (
        <Textarea
          label={t.csv.import.previewTitle}
          value={file.content}
          readOnly
          rows={8}
          className="font-mono text-xs"
          onFocus={(event) => event.currentTarget.select()}
        />
      )}
    </div>
  )
}

function safeFileName(name: string): string {
  const cleaned = name.trim().replace(/[^a-zA-Z0-9 _-]/g, '').replace(/\s+/g, '-')
  return cleaned === '' ? 'profile' : cleaned
}

// ---------------------------------------------------------------------------
// Profile backup: export and import a whole profile as JSON.
// ---------------------------------------------------------------------------

function ProfileBackupSection() {
  const { t } = useI18n()
  const profile = useProfile()
  const repo = useRepository()
  const { refresh } = useProfiles()
  const fileInputRef = useRef<HTMLInputElement>(null)
  const [importedName, setImportedName] = useState<string | null>(null)
  const [importError, setImportError] = useState<string | null>(null)

  async function handleImportFile(event: ChangeEvent<HTMLInputElement>) {
    const file = event.target.files?.[0]
    event.target.value = ''
    if (!file) return
    setImportError(null)
    setImportedName(null)
    try {
      const text = await file.text()
      const backup = JSON.parse(text) as ProfileBackup
      const newProfileId = await repo.importProfile(backup)
      const created = await repo.getProfile(newProfileId)
      await refresh()
      setImportedName(created?.displayName ?? newProfileId)
    } catch {
      setImportError(t.common.unknownError)
    }
  }

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.settings.profiles.manage}</CardTitle>
      </CardHeader>
      <CardBody className="flex flex-col gap-4">
        <DownloadArea
          triggerLabel={t.csv.export.exportButton}
          filename={`${safeFileName(profile.displayName)}-backup.json`}
          mime="application/json"
          generate={async () => {
            const backup = await repo.exportProfile(profile.id)
            return { content: JSON.stringify(backup, null, 2) }
          }}
        />
        <div className="flex flex-col gap-2 border-t border-line pt-4">
          <div>
            <Button variant="secondary" onClick={() => fileInputRef.current?.click()}>
              {t.csv.import.chooseFile}
            </Button>
            <input
              ref={fileInputRef}
              type="file"
              accept="application/json,.json"
              className="hidden"
              onChange={(event) => void handleImportFile(event)}
            />
          </div>
          {importedName && (
            <p className="text-sm text-positive">{t.profile.newProfileTitle}: {importedName}</p>
          )}
          {importError && (
            <p role="alert" className="text-sm text-negative">{importError}</p>
          )}
        </div>
      </CardBody>
    </Card>
  )
}

// ---------------------------------------------------------------------------
// CSV export: every transaction in this profile.
// ---------------------------------------------------------------------------

function CsvExportSection() {
  const { t } = useI18n()
  const profile = useProfile()
  const repo = useRepository()

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.csv.export.title}</CardTitle>
      </CardHeader>
      <CardBody>
        <DownloadArea
          triggerLabel={t.csv.export.exportButton}
          filename={`${safeFileName(profile.displayName)}-transactions.csv`}
          mime="text/csv"
          generate={async () => {
            const rows = await repo.listTransactions({ profileId: profile.id })
            return { content: transactionsToCsv(rows), message: t('csv.export.successMessage', { count: rows.length }) }
          }}
        />
      </CardBody>
    </Card>
  )
}

// ---------------------------------------------------------------------------
// CSV import: a bank statement or any file with a date and an amount.
// ---------------------------------------------------------------------------

const CSV_FIELDS: readonly CsvField[] = ['date', 'description', 'amount', 'debit', 'credit']

/**
 * No column header pair for "money in / money out" exists in csv.columns
 * (that group only names our own export's columns, which never has a debit
 * or credit column). The income/expense direction words mean exactly that
 * for a bank statement's debit and credit columns, so they are reused here.
 */
function csvFieldLabel(field: CsvField, t: T): string {
  switch (field) {
    case 'date': return t.csv.columns.date
    case 'description': return t.csv.columns.description
    case 'amount': return t.csv.columns.amount
    case 'debit': return t.transaction.directions.expense
    case 'credit': return t.transaction.directions.income
  }
}

function buildTemplateCsv(baseCurrency: CurrencyCode): string {
  const header = EXPORT_COLUMNS.join(',')
  const example = [
    '2026-08-01', 'expense', '', '', 'groceries', 'payment-with-card', '50000', baseCurrency, 'Example row',
  ].join(',')
  return `${header}\r\n${example}`
}

function CsvImportSection() {
  const { t, locale } = useI18n()
  const profile = useProfile()
  const repo = useRepository()
  const { data: wallets } = useAsync(() => repo.listWallets(profile.id), [repo, profile.id])
  const { data: rates } = useAsync(() => repo.listRates(profile.id), [repo, profile.id])

  const [header, setHeader] = useState<string[] | null>(null)
  const [rows, setRows] = useState<string[][]>([])
  const [mapping, setMapping] = useState<Partial<Record<CsvField, number>>>({})
  const [walletId, setWalletId] = useState('')
  const [currency, setCurrency] = useState<CurrencyCode>(profile.baseCurrency)
  const [defaultCategoryId, setDefaultCategoryId] = useState(CATEGORIES[0]?.id ?? '')
  const [defaultTypeId, setDefaultTypeId] = useState(TRANSACTION_TYPES[0]?.id ?? '')
  const [result, setResult] = useState<{ count: number; errors: ImportError[] } | null>(null)
  const [parseError, setParseError] = useState<string | null>(null)
  const [busy, setBusy] = useState(false)
  const fileInputRef = useRef<HTMLInputElement>(null)

  useEffect(() => {
    if (walletId !== '' || !wallets || wallets.length === 0) return
    const first = wallets[0]
    if (!first) return
    setWalletId(first.id)
    setCurrency(first.currency)
  }, [wallets, walletId])

  async function readFile(file: File) {
    setResult(null)
    setParseError(null)
    try {
      const text = await file.text()
      const parsed = parseCsv(text)
      const [firstRow, ...rest] = parsed
      if (!firstRow) {
        setParseError(t.validation.unsupportedFileType)
        return
      }
      setHeader(firstRow)
      setRows(rest)
      setMapping(detectColumns(firstRow))
    } catch {
      setParseError(t.validation.unsupportedFileType)
    }
  }

  function handleFileInput(event: ChangeEvent<HTMLInputElement>) {
    const file = event.target.files?.[0]
    event.target.value = ''
    if (file) void readFile(file)
  }

  function handleDrop(event: DragEvent<HTMLDivElement>) {
    event.preventDefault()
    const file = event.dataTransfer.files[0]
    if (file) void readFile(file)
  }

  function setMappingField(field: CsvField, columnIndex: number | null) {
    setMapping((previous) => {
      const next = { ...previous }
      if (columnIndex === null) delete next[field]
      else next[field] = columnIndex
      return next
    })
  }

  async function runImport() {
    if (rows.length === 0 || walletId === '') return
    setBusy(true)
    try {
      const ctx: ImportContext = {
        profileId: profile.id,
        walletId,
        currency,
        baseCurrency: profile.baseCurrency,
        rates: rates ?? [],
        defaultCategoryId,
        defaultTypeId,
      }
      const { transactions, errors } = importRows(rows, mapping, ctx)
      const full: Transaction[] = transactions.map((tx) => ({ ...tx, id: newId('txn'), createdAt: nowIso() }))
      // Rows that failed never reach putTransactions at all; a bad row is
      // recorded in `errors` and simply left out, the same "skip, do not
      // abort" rule importRows itself already applies while reading them.
      if (full.length > 0) await repo.putTransactions(full)
      setResult({ count: full.length, errors })
    } finally {
      setBusy(false)
    }
  }

  const categoryLabel = (id: string): string => {
    const category = CATEGORIES.find((c) => c.id === id)
    if (!category) return id
    return locale === 'id' ? category.id_ : category.en
  }
  const typeLabel = (id: string): string => {
    const type = TRANSACTION_TYPES.find((tt) => tt.id === id)
    if (!type) return id
    return locale === 'id' ? type.id_ : type.en
  }

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.csv.import.title}</CardTitle>
      </CardHeader>
      <CardBody className="flex flex-col gap-4">
        <DownloadArea
          triggerLabel={t.csv.import.downloadTemplate}
          filename="transactions-template.csv"
          mime="text/csv"
          generate={() => ({ content: buildTemplateCsv(profile.baseCurrency) })}
        />

        <div
          onDragOver={(event) => event.preventDefault()}
          onDrop={handleDrop}
          className="flex flex-col items-center gap-2 rounded-card border border-dashed border-line px-4 py-6 text-center"
        >
          <p className="text-sm text-muted">{t.csv.import.dragDrop}</p>
          <Button variant="secondary" size="sm" onClick={() => fileInputRef.current?.click()}>
            {t.csv.import.chooseFile}
          </Button>
          <input
            ref={fileInputRef}
            type="file"
            accept=".csv,text/csv"
            className="hidden"
            onChange={handleFileInput}
          />
        </div>

        {parseError && <p role="alert" className="text-sm text-negative">{parseError}</p>}

        {header && (
          <div className="flex flex-col gap-4 border-t border-line pt-4">
            <p className="text-sm text-muted">{t('csv.import.rowsFound', { count: rows.length })}</p>

            <div className="flex flex-col gap-2">
              <p className="text-sm font-medium text-text">{t.csv.import.mapColumnsTitle}</p>
              <p className="text-xs text-muted">{t.csv.import.mapColumnsPrompt}</p>
              <div className="grid grid-cols-1 gap-3 sm:grid-cols-2">
                {CSV_FIELDS.map((field) => (
                  <Select
                    key={field}
                    label={csvFieldLabel(field, t)}
                    value={mapping[field] ?? ''}
                    onChange={(event) => {
                      const value = event.target.value
                      setMappingField(field, value === '' ? null : Number(value))
                    }}
                  >
                    <option value="">{t.csv.import.columnUnmapped}</option>
                    {header.map((column, index) => (
                      <option key={index} value={index}>{column.trim() || `#${index + 1}`}</option>
                    ))}
                  </Select>
                ))}
              </div>
            </div>

            <div className="grid grid-cols-1 gap-3 sm:grid-cols-2">
              <Select
                label={t.transaction.fields.wallet}
                value={walletId}
                onChange={(event) => {
                  const nextId = event.target.value
                  setWalletId(nextId)
                  const wallet = wallets?.find((w) => w.id === nextId)
                  if (wallet) setCurrency(wallet.currency)
                }}
              >
                {(wallets ?? []).map((wallet) => (
                  <option key={wallet.id} value={wallet.id}>{wallet.name}</option>
                ))}
              </Select>
              <Select
                label={t.transaction.fields.currency}
                value={currency}
                onChange={(event) => setCurrency(event.target.value as CurrencyCode)}
              >
                {CURRENCY_CODES.map((code) => (
                  <option key={code} value={code}>{code}</option>
                ))}
              </Select>
              <Select
                label={t.transaction.fields.category}
                value={defaultCategoryId}
                onChange={(event) => setDefaultCategoryId(event.target.value)}
              >
                {CATEGORIES.map((category) => (
                  <option key={category.id} value={category.id}>{categoryLabel(category.id)}</option>
                ))}
              </Select>
              <Select
                label={t.transaction.fields.type}
                value={defaultTypeId}
                onChange={(event) => setDefaultTypeId(event.target.value)}
              >
                {TRANSACTION_TYPES.map((type) => (
                  <option key={type.id} value={type.id}>{typeLabel(type.id)}</option>
                ))}
              </Select>
            </div>

            <div>
              <Button onClick={() => void runImport()} loading={busy} disabled={walletId === '' || rows.length === 0}>
                {t.csv.import.importButton}
              </Button>
            </div>
          </div>
        )}

        {result && (
          <div className="flex flex-col gap-2 border-t border-line pt-4">
            <p className="text-sm text-positive">{t('csv.import.successMessage', { count: result.count })}</p>
            {result.errors.length > 0 && (
              <div className="flex flex-col gap-1">
                <p className="text-sm font-medium text-negative">{t.csv.import.errorsTitle}</p>
                <p className="text-xs text-muted">{t('csv.import.skippedRows', { count: result.errors.length })}</p>
                <ul className="flex max-h-48 flex-col gap-1 overflow-y-auto rounded-control border border-line p-2 text-xs text-muted">
                  {result.errors.map((err) => (
                    <li key={err.row}>{t('csv.import.rowError', { row: err.row, message: err.reason })}</li>
                  ))}
                </ul>
              </div>
            )}
          </div>
        )}
      </CardBody>
    </Card>
  )
}

// ---------------------------------------------------------------------------
// Danger zone: delete this profile, or reset everything on this device.
// ---------------------------------------------------------------------------

function DangerZoneSection() {
  const { t } = useI18n()
  const profile = useProfile()
  const repo = useRepository()
  const { close, refresh } = useProfiles()

  const [deleteOpen, setDeleteOpen] = useState(false)
  const [deleteInput, setDeleteInput] = useState('')
  const [resetOpen, setResetOpen] = useState(false)
  const [resetInput, setResetInput] = useState('')
  const [busy, setBusy] = useState(false)

  async function confirmDeleteProfile() {
    setBusy(true)
    try {
      await repo.deleteProfile(profile.id)
      close()
      await refresh()
    } finally {
      setBusy(false)
      setDeleteOpen(false)
    }
  }

  async function confirmReset() {
    setBusy(true)
    try {
      await repo.clearAll()
      close()
      await refresh()
    } finally {
      setBusy(false)
      setResetOpen(false)
    }
  }

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.settings.dangerZone.title}</CardTitle>
      </CardHeader>
      <CardBody className="flex flex-col gap-4">
        <div className="flex flex-col gap-2 sm:flex-row sm:items-center sm:justify-between">
          <div>
            <p className="text-sm font-medium text-text">{t.profile.deleteProfileTitle}</p>
            <p className="text-xs text-muted">{t.profile.deleteProfileConfirm}</p>
          </div>
          <Button
            variant="danger"
            onClick={() => { setDeleteInput(''); setDeleteOpen(true) }}
          >
            {t.common.delete}
          </Button>
        </div>

        <div className="flex flex-col gap-2 border-t border-line pt-4 sm:flex-row sm:items-center sm:justify-between">
          <div>
            <p className="text-sm font-medium text-text">{t.settings.dangerZone.resetApp}</p>
            <p className="text-xs text-muted">{t.settings.dangerZone.resetConfirmBody}</p>
          </div>
          <Button
            variant="danger"
            onClick={() => { setResetInput(''); setResetOpen(true) }}
          >
            {t.settings.dangerZone.resetApp}
          </Button>
        </div>
      </CardBody>

      <Modal
        open={deleteOpen}
        onClose={() => setDeleteOpen(false)}
        title={t.profile.deleteProfileTitle}
        footer={
          <>
            <Button variant="secondary" onClick={() => setDeleteOpen(false)}>{t.common.cancel}</Button>
            <Button
              variant="danger"
              loading={busy}
              disabled={deleteInput !== profile.displayName}
              onClick={() => void confirmDeleteProfile()}
            >
              {t.common.delete}
            </Button>
          </>
        }
      >
        <div className="flex flex-col gap-3">
          <p className="text-sm text-text">{t.profile.deleteProfileConfirm}</p>
          <p className="text-sm text-muted">{t.profile.fields.displayName}: {profile.displayName}</p>
          <Input
            label={t.profile.fields.displayName}
            value={deleteInput}
            onChange={(event) => setDeleteInput(event.target.value)}
          />
        </div>
      </Modal>

      <Modal
        open={resetOpen}
        onClose={() => setResetOpen(false)}
        title={t.settings.dangerZone.resetConfirmTitle}
        footer={
          <>
            <Button variant="secondary" onClick={() => setResetOpen(false)}>{t.common.cancel}</Button>
            <Button
              variant="danger"
              loading={busy}
              disabled={resetInput !== profile.displayName}
              onClick={() => void confirmReset()}
            >
              {t.common.confirm}
            </Button>
          </>
        }
      >
        <div className="flex flex-col gap-3">
          <p className="text-sm text-text">{t.settings.dangerZone.resetConfirmBody}</p>
          <p className="text-sm text-muted">{t.profile.fields.displayName}: {profile.displayName}</p>
          <Input
            label={t.profile.fields.displayName}
            value={resetInput}
            onChange={(event) => setResetInput(event.target.value)}
          />
        </div>
      </Modal>
    </Card>
  )
}

// ---------------------------------------------------------------------------

/**
 * Bring the demo profile back.
 *
 * The seed only runs when the database holds no profiles at all, which is the
 * right rule for a first visit but leaves no way back once a second profile
 * exists. Someone who taps "start my own profile" and then deletes the demo
 * has no route to the sample data again, and the demo is the thing that makes
 * this app worth opening cold. This restores it as an additional profile and
 * never touches what is already there.
 */
function RestoreDemoSection() {
  const { t } = useI18n()
  const repo = useRepository()
  const { profiles, select, refresh } = useProfiles()
  const [busy, setBusy] = useState(false)

  const existing = profiles.find((row) => row.isDemo)

  async function restore() {
    setBusy(true)
    try {
      const id = await repo.importProfile(buildDemoBackup(todayIso()))
      await refresh()
      select(id)
    } finally {
      setBusy(false)
    }
  }

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.demo.restoreTitle}</CardTitle>
      </CardHeader>
      <CardBody className="flex flex-col gap-3">
        <p className="text-sm text-muted">{t.demo.restoreBody}</p>
        <div>
          <Button variant="secondary" onClick={() => void (existing ? select(existing.id) : restore())} loading={busy}>
            {existing ? t.demo.goToDemo : t.demo.restoreButton}
          </Button>
        </div>
      </CardBody>
    </Card>
  )
}

export default function DataPanel() {
  return (
    <div className="flex flex-col gap-4">
      <ProfileBackupSection />
      <CsvExportSection />
      <CsvImportSection />
      <RestoreDemoSection />
      <DangerZoneSection />
    </div>
  )
}
