/**
 * Settings: profile fields, the PIN lock, language, exchange rates and data
 * management, laid out as tabs so each stays reachable without a long single
 * scroll on a 360px phone.
 */

import { useEffect, useState } from 'react'
import { useI18n } from '@/i18n'
import { useProfile, useProfiles } from '@/app/ProfileProvider'
import { useRepository } from '@/app/repo'
import { Page } from '@/design/primitives'
import {
  Button, Card, CardBody, CardHeader, CardTitle, Input, Select, Tabs, Textarea,
} from '@/ui'
import { CURRENCY_CODES, CURRENCIES, type CurrencyCode } from '@neraca/domain/currency'
import { hashPin, verifyPin } from '@/data/pin'
import type { Profile } from '@neraca/domain/types'
import RatesPanel from './RatesPanel'
import DataPanel from './DataPanel'

// ---------------------------------------------------------------------------
// Profile
// ---------------------------------------------------------------------------

type ProfileFormFields = Pick<
  Profile,
  | 'displayName' | 'firstName' | 'lastName' | 'email' | 'phoneNumber' | 'dateOfBirth' | 'sex'
  | 'careerProfiling' | 'aboutMe' | 'attendingCollege' | 'companyWorking' | 'degreeIn' | 'baseCurrency'
>

function formFromProfile(profile: Profile): ProfileFormFields {
  const {
    displayName, firstName, lastName, email, phoneNumber, dateOfBirth, sex,
    careerProfiling, aboutMe, attendingCollege, companyWorking, degreeIn, baseCurrency,
  } = profile
  return {
    displayName, firstName, lastName, email, phoneNumber, dateOfBirth, sex,
    careerProfiling, aboutMe, attendingCollege, companyWorking, degreeIn, baseCurrency,
  }
}

function ProfileSection() {
  const { t } = useI18n()
  const profile = useProfile()
  const repo = useRepository()
  const { refresh } = useProfiles()

  const [form, setForm] = useState<ProfileFormFields>(() => formFromProfile(profile))
  const [saving, setSaving] = useState(false)
  const [saved, setSaved] = useState(false)

  // Keeps the form in step if the profile is edited from elsewhere (a CSV or
  // JSON import that changes the active profile's own record, for example).
  useEffect(() => {
    setForm(formFromProfile(profile))
  }, [profile])

  function set<K extends keyof ProfileFormFields>(key: K, value: ProfileFormFields[K]) {
    setForm((previous) => ({ ...previous, [key]: value }))
    setSaved(false)
  }

  async function handleSave() {
    setSaving(true)
    try {
      const updated: Profile = { ...profile, ...form }
      await repo.putProfile(updated)
      await refresh()
      setSaved(true)
    } finally {
      setSaving(false)
    }
  }

  const currencyChanged = form.baseCurrency !== profile.baseCurrency

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.nav.profile}</CardTitle>
      </CardHeader>
      <CardBody className="flex flex-col gap-4">
        <div className="grid grid-cols-1 gap-3 sm:grid-cols-2">
          <Input
            label={t.profile.fields.displayName}
            required
            value={form.displayName}
            onChange={(event) => set('displayName', event.target.value)}
          />
          <Input
            label={t.profile.fields.firstName}
            value={form.firstName}
            onChange={(event) => set('firstName', event.target.value)}
          />
          <Input
            label={t.profile.fields.lastName}
            value={form.lastName}
            onChange={(event) => set('lastName', event.target.value)}
          />
          <Input
            type="email"
            label={t.profile.fields.email}
            value={form.email}
            onChange={(event) => set('email', event.target.value)}
          />
          <Input
            type="tel"
            label={t.profile.fields.phoneNumber}
            value={form.phoneNumber}
            onChange={(event) => set('phoneNumber', event.target.value)}
          />
          <Input
            type="date"
            label={t.profile.fields.dateOfBirth}
            value={form.dateOfBirth ?? ''}
            onChange={(event) => set('dateOfBirth', event.target.value === '' ? null : event.target.value)}
          />
          <Input
            label={t.profile.fields.sex}
            value={form.sex}
            onChange={(event) => set('sex', event.target.value)}
          />
          <Input
            label={t.profile.fields.attendingCollege}
            value={form.attendingCollege}
            onChange={(event) => set('attendingCollege', event.target.value)}
          />
          <Input
            label={t.profile.fields.companyWorking}
            value={form.companyWorking}
            onChange={(event) => set('companyWorking', event.target.value)}
          />
          <Input
            label={t.profile.fields.degreeIn}
            value={form.degreeIn}
            onChange={(event) => set('degreeIn', event.target.value)}
          />
          <Select
            label={t.profile.fields.baseCurrency}
            value={form.baseCurrency}
            hint={currencyChanged ? t.settings.currency.changeWarning : undefined}
            onChange={(event) => set('baseCurrency', event.target.value as CurrencyCode)}
          >
            {CURRENCY_CODES.map((code) => (
              <option key={code} value={code}>{code} ({CURRENCIES[code].name})</option>
            ))}
          </Select>
        </div>

        <Textarea
          label={t.profile.fields.careerProfiling}
          value={form.careerProfiling}
          onChange={(event) => set('careerProfiling', event.target.value)}
        />
        <Textarea
          label={t.profile.fields.aboutMe}
          value={form.aboutMe}
          onChange={(event) => set('aboutMe', event.target.value)}
        />

        {/*
          The base currency only changes what future totals are reported in.
          Every amount already recorded stays in whatever minor units and
          currency it was written with, so this warning is permanent and
          field level, not a one time confirmation dialog, because the fact
          it describes is true every time this field is touched.
        */}
        {currencyChanged && (
          <p role="alert" className="text-sm text-warning">
            {t.settings.currency.changeWarning}
          </p>
        )}

        <div className="flex items-center gap-3">
          <Button onClick={() => void handleSave()} loading={saving}>
            {t.profile.saveButton}
          </Button>
          {saved && <span className="text-sm text-positive">{t.common.done}</span>}
        </div>
      </CardBody>
    </Card>
  )
}

// ---------------------------------------------------------------------------
// Security (PIN)
// ---------------------------------------------------------------------------

function SecuritySection() {
  const { t } = useI18n()
  const profile = useProfile()
  const repo = useRepository()
  const { refresh } = useProfiles()

  const hasPin = profile.pinHash !== null

  const [currentPin, setCurrentPin] = useState('')
  const [newPin, setNewPin] = useState('')
  const [confirmPin, setConfirmPin] = useState('')
  const [error, setError] = useState<string | null>(null)
  const [success, setSuccess] = useState<string | null>(null)
  const [busy, setBusy] = useState(false)

  function resetFields() {
    setCurrentPin('')
    setNewPin('')
    setConfirmPin('')
  }

  async function checkCurrentPin(): Promise<boolean> {
    if (!hasPin) return true
    if (profile.pinHash === null || profile.pinSalt === null) return true
    return verifyPin(currentPin, profile.pinHash, profile.pinSalt)
  }

  async function handleSetOrChange() {
    setError(null)
    setSuccess(null)
    if (!/^\d+$/.test(newPin)) { setError(t.validation.pinDigitsOnly); return }
    if (newPin.length < 4) { setError(t.validation.pinLength); return }
    if (newPin !== confirmPin) { setError(t.validation.pinsDontMatch); return }

    setBusy(true)
    try {
      if (hasPin && !(await checkCurrentPin())) {
        setError(t.profile.pin.incorrect)
        return
      }
      const { hash, salt } = await hashPin(newPin)
      await repo.putProfile({ ...profile, pinHash: hash, pinSalt: salt })
      await refresh()
      resetFields()
      setSuccess(t.common.done)
    } finally {
      setBusy(false)
    }
  }

  async function handleRemove() {
    setError(null)
    setSuccess(null)
    setBusy(true)
    try {
      if (!(await checkCurrentPin())) {
        setError(t.profile.pin.incorrect)
        return
      }
      await repo.putProfile({ ...profile, pinHash: null, pinSalt: null })
      await refresh()
      resetFields()
      setSuccess(t.profile.pin.removedConfirm)
    } finally {
      setBusy(false)
    }
  }

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.profile.pin.setTitle}</CardTitle>
      </CardHeader>
      <CardBody className="flex flex-col gap-4">
        {/*
          The one sentence in the dictionary that already says this app's PIN
          is a convenience lock and not encryption. It is shown here
          unconditionally, whether a PIN exists yet or not, because the fact
          it states is true in both states: the data underneath is always
          stored in the clear.
        */}
        <p className="text-sm text-muted">{t.profile.pin.setPrompt}</p>

        {hasPin && (
          <Input
            type="password"
            inputMode="numeric"
            label={t.profile.pin.enterTitle}
            value={currentPin}
            onChange={(event) => setCurrentPin(event.target.value)}
          />
        )}

        <div className="grid grid-cols-1 gap-3 sm:grid-cols-2">
          <Input
            type="password"
            inputMode="numeric"
            label={t.profile.pin.setTitle}
            value={newPin}
            onChange={(event) => setNewPin(event.target.value)}
          />
          <Input
            type="password"
            inputMode="numeric"
            label={t.profile.pin.confirmLabel}
            value={confirmPin}
            onChange={(event) => setConfirmPin(event.target.value)}
          />
        </div>

        {error && <p role="alert" className="text-sm text-negative">{error}</p>}
        {success && <p className="text-sm text-positive">{success}</p>}

        <div className="flex flex-wrap gap-2">
          <Button onClick={() => void handleSetOrChange()} loading={busy}>
            {t.profile.pin.setTitle}
          </Button>
          {hasPin && (
            <Button variant="danger" onClick={() => void handleRemove()} loading={busy}>
              {t.profile.pin.remove}
            </Button>
          )}
        </div>
      </CardBody>
    </Card>
  )
}

// ---------------------------------------------------------------------------
// Language and appearance
// ---------------------------------------------------------------------------

function LanguageSection() {
  const { t, locale, setLocale } = useI18n()

  return (
    <Card>
      <CardHeader>
        <CardTitle>{t.settings.language.label}</CardTitle>
      </CardHeader>
      <CardBody className="flex flex-col gap-4">
        <div className="max-w-xs">
          <Select
            label={t.settings.language.label}
            value={locale}
            onChange={(event) => setLocale(event.target.value === 'id' ? 'id' : 'en')}
          >
            <option value="en">{t.settings.language.en}</option>
            <option value="id">{t.settings.language.id}</option>
          </Select>
        </div>
        {/*
          No dictionary key describes the theme control at all: ThemeToggle
          itself (src/ui/ThemeToggle.tsx, owned by another agent) renders its
          own accessible name as a plain literal string rather than through
          t, so there is no existing translated sentence for this note to
          reuse either. A short literal note is kept here rather than
          dropping the note the task asks for; every other string on this
          page still comes from the dictionary.
        */}
        <p className="text-sm text-muted">
          {t('settings.appearance.themeHint')}
        </p>
      </CardBody>
    </Card>
  )
}

// ---------------------------------------------------------------------------

export default function SettingsPage() {
  const { t } = useI18n()

  return (
    <Page>
      <h1 className="text-h2 leading-tight">{t.settings.title}</h1>

      <Tabs
        label={t.settings.title}
        items={[
          { id: 'profile', label: t.nav.profile, content: <ProfileSection /> },
          { id: 'security', label: t.profile.pin.setTitle, content: <SecuritySection /> },
          { id: 'language', label: t.settings.language.label, content: <LanguageSection /> },
          { id: 'rates', label: t.settings.exchangeRates.title, content: <RatesPanel /> },
          { id: 'data', label: t.csv.title, content: <DataPanel /> },
        ]}
      />
    </Page>
  )
}
