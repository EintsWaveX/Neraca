/**
 * Exchange rates: list, add, edit, delete.
 *
 * A rate row means "one whole unit of `currency` is worth `rate` units of the
 * profile's base currency, from `date` onward until a newer rate for the
 * same currency is entered". src/domain/rates.ts's findRate is what actually
 * applies that rule when a transaction is priced; this panel only manages
 * the rows it reads from.
 */

import { useMemo, useState } from 'react'
import { useI18n } from '@/i18n'
import { useProfile } from '@/app/ProfileProvider'
import { useAsync, useRepository } from '@/app/repo'
import {
  Badge, Button, Card, CardBody, CardHeader, CardTitle, EmptyState, Input, Modal, Select, Skeleton,
  Table, TBody, TD, TH, THead, TR,
} from '@/ui'
import { CURRENCY_CODES, CURRENCIES, isCurrencyCode, type CurrencyCode } from '@/domain/currency'
import { newId, nowIso } from '@/data/ids'
import type { ExchangeRate } from '@/domain/types'

interface RateFormState {
  currency: CurrencyCode
  rate: string
  date: string
}

function emptyForm(defaultCurrency: CurrencyCode, today: string): RateFormState {
  return { currency: defaultCurrency, rate: '', date: today }
}

export default function RatesPanel() {
  const { t, formatDate } = useI18n()
  const profile = useProfile()
  const repo = useRepository()

  const { data: rates, loading: ratesLoading, reload: reloadRates } = useAsync(
    () => repo.listRates(profile.id),
    [repo, profile.id],
  )
  const { data: wallets } = useAsync(() => repo.listWallets(profile.id), [repo, profile.id])

  const usedCurrencies = useMemo(() => {
    const codes = new Set<CurrencyCode>()
    for (const wallet of wallets ?? []) {
      if (wallet.currency !== profile.baseCurrency) codes.add(wallet.currency)
    }
    return Array.from(codes)
  }, [wallets, profile.baseCurrency])

  const foreignCurrencies = CURRENCY_CODES.filter((code) => code !== profile.baseCurrency)
  const today = useMemo(() => new Date().toISOString().slice(0, 10), [])

  const [editing, setEditing] = useState<ExchangeRate | null>(null)
  const [formOpen, setFormOpen] = useState(false)
  const [form, setForm] = useState<RateFormState>(() => emptyForm(foreignCurrencies[0] ?? profile.baseCurrency, today))
  const [formError, setFormError] = useState<string | null>(null)
  const [deleting, setDeleting] = useState<ExchangeRate | null>(null)

  function openAdd() {
    setEditing(null)
    setForm(emptyForm(usedCurrencies[0] ?? foreignCurrencies[0] ?? profile.baseCurrency, today))
    setFormError(null)
    setFormOpen(true)
  }

  function openEdit(rate: ExchangeRate) {
    setEditing(rate)
    setForm({ currency: rate.currency, rate: String(rate.rate), date: rate.date })
    setFormError(null)
    setFormOpen(true)
  }

  async function saveForm() {
    const parsed = Number(form.rate.replace(',', '.'))
    if (!Number.isFinite(parsed) || parsed <= 0) {
      setFormError(t.validation.invalidExchangeRate)
      return
    }
    if (!isCurrencyCode(form.currency)) {
      setFormError(t.validation.invalidCurrencyCode)
      return
    }
    const row: ExchangeRate = {
      id: editing?.id ?? newId('rate'),
      profileId: profile.id,
      currency: form.currency,
      rate: parsed,
      date: form.date,
      createdAt: editing?.createdAt ?? nowIso(),
    }
    await repo.putRate(row)
    setFormOpen(false)
    reloadRates()
  }

  async function confirmDelete() {
    if (!deleting) return
    await repo.deleteRate(deleting.id)
    setDeleting(null)
    reloadRates()
  }

  return (
    <div className="flex flex-col gap-4">
      <Card>
        <CardBody className="flex flex-col gap-2">
          <p className="text-sm text-muted">{t.settings.exchangeRates.hint}</p>
          {/*
            A rate row is "how many units of the base currency one whole unit
            of the foreign currency is worth", not the other way round. The
            field label below already says this ("Rate to base currency");
            this line spells out the base currency itself so the label reads
            unambiguously.
          */}
          <p className="text-sm text-muted">
            {t.settings.currency.baseLabel}: <span className="font-medium text-text">{profile.baseCurrency}</span>
          </p>
          {usedCurrencies.length > 0 && (
            <div className="flex flex-wrap items-center gap-2 pt-1">
              <span className="text-sm text-muted">{t.wallet.fields.currency}:</span>
              {usedCurrencies.map((code) => (
                <Badge key={code} tone={rates?.some((r) => r.currency === code) ? 'positive' : 'warning'}>
                  {code}
                </Badge>
              ))}
            </div>
          )}
        </CardBody>
      </Card>

      <Card>
        <CardHeader>
          <CardTitle>{t.settings.exchangeRates.title}</CardTitle>
          <Button size="sm" onClick={openAdd} disabled={foreignCurrencies.length === 0}>
            {t.settings.exchangeRates.add}
          </Button>
        </CardHeader>
        <CardBody>
          {ratesLoading ? (
            <Skeleton shape="block" className="h-32 w-full" />
          ) : !rates || rates.length === 0 ? (
            <EmptyState title={t.empty.exchangeRates} />
          ) : (
            <Table>
              <THead>
                <TR>
                  <TH>{t.settings.exchangeRates.fields.currency}</TH>
                  <TH>{t.settings.exchangeRates.fields.rate}</TH>
                  <TH>{t.settings.exchangeRates.fields.date}</TH>
                  <TH aria-hidden="true"></TH>
                </TR>
              </THead>
              <TBody>
                {[...rates]
                  .sort((a, b) => (a.currency === b.currency ? b.date.localeCompare(a.date) : a.currency.localeCompare(b.currency)))
                  .map((rate) => (
                    <TR key={rate.id}>
                      <TD>{rate.currency}</TD>
                      <TD numeric>{rate.rate}</TD>
                      <TD>{formatDate(rate.date)}</TD>
                      <TD>
                        <div className="flex justify-end gap-2">
                          <Button size="sm" variant="ghost" onClick={() => openEdit(rate)}>
                            {t.common.edit}
                          </Button>
                          <Button size="sm" variant="ghost" onClick={() => setDeleting(rate)}>
                            {t.common.delete}
                          </Button>
                        </div>
                      </TD>
                    </TR>
                  ))}
              </TBody>
            </Table>
          )}
        </CardBody>
      </Card>

      <Modal
        open={formOpen}
        onClose={() => setFormOpen(false)}
        title={editing ? t.settings.exchangeRates.edit : t.settings.exchangeRates.add}
        footer={
          <>
            <Button variant="secondary" onClick={() => setFormOpen(false)}>{t.common.cancel}</Button>
            <Button onClick={saveForm}>{t.common.save}</Button>
          </>
        }
      >
        <div className="flex flex-col gap-3">
          <Select
            label={t.settings.exchangeRates.fields.currency}
            value={form.currency}
            onChange={(event) => setForm((prev) => ({ ...prev, currency: event.target.value as CurrencyCode }))}
          >
            {foreignCurrencies.map((code) => (
              <option key={code} value={code}>{code} ({CURRENCIES[code].name})</option>
            ))}
          </Select>
          <Input
            label={t.settings.exchangeRates.fields.rate}
            hint={t.settings.exchangeRates.hint}
            inputMode="decimal"
            value={form.rate}
            onChange={(event) => setForm((prev) => ({ ...prev, rate: event.target.value }))}
            error={formError ?? undefined}
          />
          <Input
            type="date"
            label={t.settings.exchangeRates.fields.date}
            value={form.date}
            onChange={(event) => setForm((prev) => ({ ...prev, date: event.target.value }))}
          />
        </div>
      </Modal>

      <Modal
        open={deleting !== null}
        onClose={() => setDeleting(null)}
        title={t.settings.exchangeRates.delete}
        footer={
          <>
            <Button variant="secondary" onClick={() => setDeleting(null)}>{t.common.cancel}</Button>
            <Button variant="danger" onClick={confirmDelete}>{t.common.delete}</Button>
          </>
        }
      >
        {deleting && (
          <p className="text-sm text-text">
            {deleting.currency} {t.common.from} {formatDate(deleting.date)}
          </p>
        )}
      </Modal>
    </div>
  )
}
