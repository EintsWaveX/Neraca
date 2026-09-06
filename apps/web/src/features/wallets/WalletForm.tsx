/**
 * Create and edit form for a single wallet.
 */

import { useState, type FormEvent } from 'react'
import type { Wallet, WalletKind } from '@neraca/domain/types'
import { CURRENCY_CODES, type CurrencyCode } from '@neraca/domain/currency'
import { fromMajor, money, toMajor, zero, type Money } from '@neraca/domain/money'
import { newId, nowIso } from '@/data/ids'
import { useRepository } from '@/app/repo'
import { useProfile } from '@/app/ProfileProvider'
import { useI18n } from '@/i18n'
import { Button, Input, MoneyInput, Select } from '@/ui'

export interface WalletFormProps {
  /** Omitted for a brand new wallet. */
  wallet?: Wallet
  /** Every other wallet on the profile, for the duplicate-name check. */
  existingWallets: readonly Wallet[]
  onSaved: () => void
  onCancel: () => void
}

const WALLET_KINDS: readonly WalletKind[] = ['cash', 'bank', 'ewallet', 'savings', 'credit']

export function WalletForm({ wallet, existingWallets, onSaved, onCancel }: WalletFormProps) {
  const { t } = useI18n()
  const profile = useProfile()
  const repo = useRepository()

  const [name, setName] = useState(wallet?.name ?? '')
  const [kind, setKind] = useState<WalletKind>(wallet?.kind ?? 'cash')
  const [currency, setCurrency] = useState<CurrencyCode>(wallet?.currency ?? profile.baseCurrency)
  const [openingBalance, setOpeningBalance] = useState<Money | null>(
    wallet ? money(wallet.openingBalance, wallet.currency) : zero(profile.baseCurrency),
  )
  const [nameError, setNameError] = useState<string | undefined>(undefined)
  const [amountError, setAmountError] = useState<string | undefined>(undefined)
  const [saving, setSaving] = useState(false)

  function handleCurrencyChange(next: CurrencyCode) {
    setCurrency(next)
    // Reinterpret the same major-unit figure under the new currency instead
    // of keeping the old minor-unit integer as is: IDR has no decimals and
    // USD has two, so the same integer would mean a wildly different amount
    // if it were just carried across unchanged.
    setOpeningBalance((prev) => (prev ? fromMajor(toMajor(prev), next) : null))
  }

  async function handleSubmit(event: FormEvent) {
    event.preventDefault()
    const trimmedName = name.trim()
    let hasError = false

    if (!trimmedName) {
      setNameError(t.validation.required)
      hasError = true
    } else if (
      existingWallets.some((w) => w.id !== wallet?.id && w.name.trim().toLowerCase() === trimmedName.toLowerCase())
    ) {
      setNameError(t.validation.duplicateWalletName)
      hasError = true
    } else {
      setNameError(undefined)
    }

    if (!openingBalance) {
      setAmountError(t.validation.invalidAmount)
      hasError = true
    } else {
      setAmountError(undefined)
    }

    if (hasError || !openingBalance) return

    setSaving(true)
    try {
      const record: Wallet = {
        id: wallet?.id ?? newId('wal'),
        profileId: profile.id,
        name: trimmedName,
        kind,
        currency,
        openingBalance: openingBalance.minor,
        archived: wallet?.archived ?? false,
        createdAt: wallet?.createdAt ?? nowIso(),
      }
      await repo.putWallet(record)
      onSaved()
    } finally {
      setSaving(false)
    }
  }

  return (
    <form onSubmit={handleSubmit} className="flex flex-col gap-4" noValidate>
      <Input
        label={t.wallet.fields.name}
        required
        value={name}
        onChange={(event) => setName(event.target.value)}
        error={nameError}
      />

      <Select label={t.wallet.fields.kind} value={kind} onChange={(event) => setKind(event.target.value as WalletKind)}>
        {WALLET_KINDS.map((k) => (
          <option key={k} value={k}>
            {t.wallet.kinds[k]}
          </option>
        ))}
      </Select>

      <Select
        label={t.wallet.fields.currency}
        value={currency}
        onChange={(event) => handleCurrencyChange(event.target.value as CurrencyCode)}
      >
        {CURRENCY_CODES.map((code) => (
          <option key={code} value={code}>
            {code}
          </option>
        ))}
      </Select>

      <MoneyInput
        label={t.wallet.fields.openingBalance}
        currency={currency}
        value={openingBalance}
        onChange={setOpeningBalance}
        error={amountError}
      />

      <div className="flex justify-end gap-2 pt-2">
        <Button type="button" variant="secondary" onClick={onCancel}>
          {t.common.cancel}
        </Button>
        <Button type="submit" loading={saving}>
          {t.common.save}
        </Button>
      </div>
    </form>
  )
}
