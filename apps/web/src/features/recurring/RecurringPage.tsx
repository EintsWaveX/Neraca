/**
 * Recurring rules screen: every rule with its schedule in words, what is due
 * right now, and generation into real transactions (both on demand and once
 * automatically on load).
 */

import { useEffect, useRef, useState, type ReactNode } from 'react'
import { addYears, format, parseISO } from 'date-fns'
import { useRepository, useAsync } from '@/app/repo'
import { useProfile } from '@/app/ProfileProvider'
import { useI18n } from '@/i18n'
import type { ExchangeRate, IsoDate, RecurringRule, Transaction } from '@neraca/domain/types'
import type { CurrencyCode } from '@neraca/domain/currency'
import { dueOccurrences, materialise, occurrencesBetween } from '@neraca/domain/recurring'
import { findRate } from '@neraca/domain/rates'
import { newId, nowIso } from '@/data/ids'
import { Badge, Button, EmptyState, Modal, Skeleton } from '@/ui'
import { Block, Page, RuledRow } from '@/design/primitives'
import { RecurringForm } from './RecurringForm'

/**
 * Builds the transaction rows a rule's due occurrences imply, filling in a
 * real `rateToBase` for anything not already in the profile's base currency.
 *
 * Stops at the first occurrence with no usable rate rather than skipping it:
 * `dueOccurrences` walks forward from `lastRunDate`, so advancing that date
 * past an occurrence that was never actually written would mean that date's
 * transaction can never be generated, even after a rate is added later.
 */
function buildRowsForRule(
  rule: RecurringRule,
  asOf: IsoDate,
  rates: readonly ExchangeRate[],
  baseCurrency: CurrencyCode,
): { rows: Transaction[]; lastRunDate: IsoDate | null; blockedCurrency: CurrencyCode | null } {
  const dueDates = dueOccurrences(rule, asOf)
  if (dueDates.length === 0) return { rows: [], lastRunDate: rule.lastRunDate, blockedCurrency: null }

  const drafts = materialise(rule, dueDates)
  const rows: Transaction[] = []
  let lastRunDate = rule.lastRunDate
  let blockedCurrency: CurrencyCode | null = null

  for (const draft of drafts) {
    const rate = draft.currency === baseCurrency ? 1 : findRate(rates, draft.currency, draft.date, baseCurrency)
    if (rate === null) {
      blockedCurrency = draft.currency
      break
    }
    rows.push({ ...draft, id: newId('txn'), createdAt: nowIso(), rateToBase: rate })
    lastRunDate = draft.date
  }

  return { rows, lastRunDate, blockedCurrency }
}

/** How far ahead to look for a next-due date or a preview, when a rule has no end date of its own. */
function horizonFor(rule: RecurringRule, today: IsoDate): IsoDate {
  return rule.endDate ?? format(addYears(parseISO(today), 3), 'yyyy-MM-dd')
}

export default function RecurringPage() {
  const repo = useRepository()
  const profile = useProfile()
  const { t, locale, formatDate } = useI18n()

  const today = format(new Date(), 'yyyy-MM-dd')

  const rulesAsync = useAsync(() => repo.listRecurring(profile.id), [repo, profile.id])
  const walletsAsync = useAsync(() => repo.listWallets(profile.id), [repo, profile.id])
  const ratesAsync = useAsync(() => repo.listRates(profile.id), [repo, profile.id])

  const rules = rulesAsync.data ?? []
  const wallets = walletsAsync.data ?? []

  const [formOpen, setFormOpen] = useState(false)
  const [editingRule, setEditingRule] = useState<RecurringRule | null>(null)
  const [deleteTarget, setDeleteTarget] = useState<RecurringRule | null>(null)
  const [generatingId, setGeneratingId] = useState<string | null>(null)
  const [banner, setBanner] = useState<{ tone: 'positive' | 'warning'; text: string } | null>(null)

  async function generateRule(rule: RecurringRule) {
    const rates = ratesAsync.data ?? []
    const { rows, lastRunDate, blockedCurrency } = buildRowsForRule(rule, today, rates, profile.baseCurrency)
    if (rows.length > 0) {
      await repo.putTransactions(rows)
      if (lastRunDate !== rule.lastRunDate) {
        await repo.putRecurring({ ...rule, lastRunDate })
      }
    }
    return { count: rows.length, blockedCurrency }
  }

  async function handleGenerateNow(rule: RecurringRule) {
    setGeneratingId(rule.id)
    const result = await generateRule(rule)
    setGeneratingId(null)
    rulesAsync.reload()
    if (result.blockedCurrency) {
      setBanner({ tone: 'warning', text: t.empty.exchangeRates })
    } else if (result.count > 0) {
      setBanner({ tone: 'positive', text: t('csv.import.successMessage', { count: result.count }) })
    }
  }

  // Generate whatever is already due, once, as soon as the rules and rates
  // are both in hand. Guarded by a ref rather than a dependency on the data
  // itself, since generating writes new data and would otherwise retrigger.
  const autoRanRef = useRef(false)
  useEffect(() => {
    if (autoRanRef.current) return
    if (rulesAsync.loading || ratesAsync.loading) return
    if (!rulesAsync.data || !ratesAsync.data) return
    autoRanRef.current = true

    async function runDueRules() {
      const dueRules = (rulesAsync.data ?? []).filter(
        (rule) => rule.active && dueOccurrences(rule, today).length > 0,
      )
      if (dueRules.length === 0) return
      let totalCreated = 0
      let anyBlocked = false
      for (const rule of dueRules) {
        const result = await generateRule(rule)
        totalCreated += result.count
        if (result.blockedCurrency) anyBlocked = true
      }
      if (totalCreated > 0 || anyBlocked) rulesAsync.reload()
      if (totalCreated > 0) {
        setBanner({ tone: 'positive', text: t('csv.import.successMessage', { count: totalCreated }) })
      } else if (anyBlocked) {
        setBanner({ tone: 'warning', text: t.empty.exchangeRates })
      }
    }

    runDueRules()
    // Deliberately narrow: this should fire once, when loading finishes, not
    // on every reload the manual "generate now" button triggers afterwards.
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [rulesAsync.loading, ratesAsync.loading])

  function frequencyPhrase(rule: RecurringRule): string {
    const unit = t(`recurring.frequencies.${rule.frequency}`).toLowerCase()
    // Indonesian does not inflect nouns for plural, so only English gets the
    // trailing "s"; t.recurring.everyNPeriods supplies the sentence shape for
    // both locales.
    const pluralUnit = locale === 'en' && rule.interval !== 1 ? `${unit}s` : unit
    return t('recurring.everyNPeriods', { interval: rule.interval, unit: pluralUnit })
  }

  function nextDueDate(rule: RecurringRule): IsoDate | null {
    const occurrences = occurrencesBetween(rule, today, horizonFor(rule, today))
    return occurrences[0] ?? null
  }

  function previewDates(rule: RecurringRule): IsoDate[] {
    return occurrencesBetween(rule, today, horizonFor(rule, today)).slice(0, 3)
  }

  function openCreate() {
    setEditingRule(null)
    setFormOpen(true)
  }

  function openEdit(rule: RecurringRule) {
    setEditingRule(rule)
    setFormOpen(true)
  }

  async function handleSave(rule: RecurringRule) {
    await repo.putRecurring(rule)
    setFormOpen(false)
    setEditingRule(null)
    rulesAsync.reload()
  }

  async function confirmDelete() {
    if (!deleteTarget) return
    await repo.deleteRecurring(deleteTarget.id)
    setDeleteTarget(null)
    rulesAsync.reload()
  }

  async function toggleActive(rule: RecurringRule) {
    await repo.putRecurring({ ...rule, active: !rule.active })
    rulesAsync.reload()
  }

  const loading = rulesAsync.loading

  return (
    <Page>
      <header className="flex flex-wrap items-center justify-between gap-3">
        <h1 className="text-h2 leading-tight">{t.recurring.title}</h1>
        <Button onClick={openCreate}>{t.recurring.add}</Button>
      </header>

      {/* A note in the margin rather than a filled band, for the same reason
          the budget alerts are: the result of an action should not be the
          loudest thing on the screen it happened on. */}
      {banner && (
        <div
          role="status"
          className={`mt-6 flex items-center justify-between gap-3 border-l-2 py-2 pl-3 text-sm ${
            banner.tone === 'positive' ? 'border-credit text-credit' : 'border-stamp text-stamp'
          }`}
        >
          <span>{banner.text}</span>
          <button
            type="button"
            aria-label={t.common.close}
            onClick={() => setBanner(null)}
            className="text-current"
          >
            <CloseIcon />
          </button>
        </div>
      )}

      <Block title={t.recurring.title}>
        {loading ? (
          <div className="flex flex-col gap-3 py-2" aria-hidden="true">
            <Skeleton shape="block" className="h-16 w-full" />
            <Skeleton shape="block" className="h-16 w-full" />
          </div>
        ) : rules.length === 0 ? (
          <EmptyState
            title={t.empty.recurring}
            action={
              <Button size="sm" onClick={openCreate}>
                {t.recurring.add}
              </Button>
            }
          />
        ) : (
          rules.map((rule, index) => {
            const due = dueOccurrences(rule, today).length > 0
            const next = nextDueDate(rule)
            const preview = previewDates(rule)
            return (
              <RuledRow
                key={rule.id}
                index={index}
                label={rule.name}
                note={frequencyPhrase(rule)}
                value={
                  <span className="flex items-center gap-2">
                    {due && <Badge tone="warning">{t.recurring.pastDue}</Badge>}
                    {!rule.active && <Badge tone="neutral">{t.recurring.fields.active}</Badge>}
                    <IconButton label={`${t.common.edit}: ${rule.name}`} onClick={() => openEdit(rule)}>
                      <PencilIcon />
                    </IconButton>
                    <IconButton
                      label={`${t.common.delete}: ${rule.name}`}
                      onClick={() => setDeleteTarget(rule)}
                    >
                      <TrashIcon />
                    </IconButton>
                  </span>
                }
                below={
                  <div className="flex flex-wrap items-center justify-between gap-3 text-xs text-ink-muted">
                    <span>
                      {t.recurring.fields.nextRun}: {next ? formatDate(next) : t.common.none}
                      {preview.length > 0 && (
                        <>
                          {' · '}
                          {t.recurring.upcoming}: {preview.map((date) => formatDate(date)).join(', ')}
                        </>
                      )}
                    </span>
                    <span className="flex items-center gap-3">
                      <label className="flex items-center gap-2 text-ink-muted">
                        <input
                          type="checkbox"
                          checked={rule.active}
                          onChange={() => toggleActive(rule)}
                          className="h-4 w-4 accent-[var(--indigo)]"
                        />
                        {t.recurring.fields.active}
                      </label>
                      {due && (
                        <Button
                          size="sm"
                          variant="secondary"
                          loading={generatingId === rule.id}
                          onClick={() => handleGenerateNow(rule)}
                        >
                          {t.recurring.runNow}
                        </Button>
                      )}
                    </span>
                  </div>
                }
              />
            )
          })
        )}
      </Block>

      <Modal
        open={formOpen}
        onClose={() => {
          setFormOpen(false)
          setEditingRule(null)
        }}
        title={editingRule ? t.recurring.edit : t.recurring.add}
      >
        <RecurringForm
          profileId={profile.id}
          initial={editingRule}
          wallets={wallets}
          onSave={handleSave}
          onCancel={() => {
            setFormOpen(false)
            setEditingRule(null)
          }}
        />
      </Modal>

      <Modal
        open={deleteTarget !== null}
        onClose={() => setDeleteTarget(null)}
        title={t.recurring.delete}
        footer={
          <>
            <Button variant="secondary" onClick={() => setDeleteTarget(null)}>
              {t.common.cancel}
            </Button>
            <Button variant="danger" onClick={confirmDelete}>
              {t.common.delete}
            </Button>
          </>
        }
      >
        <p className="text-sm text-muted">{t.recurring.deleteConfirm}</p>
      </Modal>
    </Page>
  )
}

function IconButton({ label, onClick, children }: { label: string; onClick: () => void; children: ReactNode }) {
  return (
    <button
      type="button"
      aria-label={label}
      title={label}
      onClick={onClick}
      className="inline-flex h-7 w-7 items-center justify-center rounded-control text-muted hover:bg-surface-sunken hover:text-text"
    >
      {children}
    </button>
  )
}

function PencilIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true" className="h-4 w-4">
      <path
        d="M13.5 3.5l3 3L6 17H3v-3L13.5 3.5z"
        stroke="currentColor"
        strokeWidth="1.4"
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  )
}

function TrashIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true" className="h-4 w-4">
      <path
        d="M4 6h12M8 6V4.5A1.5 1.5 0 019.5 3h1A1.5 1.5 0 0112 4.5V6m-6.5 0l.6 9.4a1.5 1.5 0 001.5 1.4h3.8a1.5 1.5 0 001.5-1.4L14.5 6"
        stroke="currentColor"
        strokeWidth="1.4"
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  )
}

function CloseIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true" className="h-4 w-4">
      <path d="M5 5l10 10M15 5L5 15" stroke="currentColor" strokeWidth="1.5" strokeLinecap="round" />
    </svg>
  )
}
