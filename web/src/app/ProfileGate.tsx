/**
 * Gate the whole app behind a chosen, unlocked profile.
 *
 * Three states, in order: booting (profiles not loaded yet), no profile
 * selected (picker, with a create flow) and a selected profile still behind
 * its PIN. Only past all three does `children` (the shell and every route
 * inside it) ever mount, so nothing downstream has to defend against a null
 * profile itself.
 */

import { useEffect, useState, type FormEvent, type ReactNode } from 'react'
import { useProfiles } from './ProfileProvider'
import { useRepository } from './repo'
import { useI18n } from '@/i18n'
import { Button, Card, CardBody, Input, Modal, Select, Skeleton } from '@/ui'
import { CURRENCIES, CURRENCY_CODES, type CurrencyCode } from '@/domain/currency'
import type { Locale, Profile } from '@/domain/types'
import { newId, nowIso } from '@/data/ids'
import { verifyPin } from '@/data/pin'

/**
 * Only display name and base currency are collected up front. The rest of
 * the profile record (name, contact details, the bio fields carried over
 * from the original C registration form) is optional and belongs in
 * Settings, so a brand new profile starts blank there rather than blocking
 * creation on a long form nobody asked to fill in yet.
 */
export function blankProfile(displayName: string, baseCurrency: CurrencyCode, locale: Locale): Profile {
  return {
    id: newId('prof'),
    displayName,
    firstName: '',
    lastName: '',
    email: '',
    phoneNumber: '',
    dateOfBirth: null,
    sex: '',
    careerProfiling: '',
    aboutMe: '',
    attendingCollege: '',
    companyWorking: '',
    degreeIn: '',
    baseCurrency,
    locale,
    pinHash: null,
    pinSalt: null,
    createdAt: nowIso(),
    isDemo: false,
  }
}

export function ProfileGate({ children }: { children: ReactNode }) {
  const { profiles, profile, unlocked, loading, select, unlock, close, refresh } = useProfiles()
  const repo = useRepository()
  const { locale } = useI18n()
  const [createOpen, setCreateOpen] = useState(false)

  if (loading) return <BootSkeleton />

  if (!profile) {
    return (
      <>
        <ProfilePicker profiles={profiles} onSelect={select} onCreateNew={() => setCreateOpen(true)} />
        <CreateProfileModal
          open={createOpen}
          onClose={() => setCreateOpen(false)}
          defaultLocale={locale}
          onCreated={async (created) => {
            await repo.putProfile(created)
            await refresh()
            select(created.id)
            setCreateOpen(false)
          }}
        />
      </>
    )
  }

  if (profile.pinHash && profile.pinSalt && !unlocked) {
    return <PinScreen profile={profile} onUnlocked={unlock} onSwitchProfile={close} />
  }

  return <>{children}</>
}

function BootSkeleton() {
  return (
    <div className="flex min-h-dvh items-center justify-center bg-bg p-4">
      <div className="flex w-full max-w-sm flex-col gap-3">
        <Skeleton shape="block" className="h-6 w-40" />
        <Skeleton shape="block" className="h-20 w-full" />
        <Skeleton shape="block" className="h-20 w-full" />
      </div>
    </div>
  )
}

function ProfilePicker({
  profiles,
  onSelect,
  onCreateNew,
}: {
  profiles: Profile[]
  onSelect: (id: string) => void
  onCreateNew: () => void
}) {
  const { t } = useI18n()
  return (
    <div className="flex min-h-dvh items-center justify-center bg-bg p-4">
      <Card className="w-full max-w-md">
        <CardBody className="flex flex-col gap-4">
          <div>
            <h1 className="text-lg font-semibold text-text">{t.profile.chooseTitle}</h1>
            <p className="mt-1 text-sm text-muted">{t.profile.chooseSubtitle}</p>
          </div>
          {profiles.length > 0 && (
            <ul className="flex flex-col gap-2">
              {profiles.map((row) => (
                <li key={row.id}>
                  <button
                    type="button"
                    onClick={() => onSelect(row.id)}
                    className="flex w-full flex-col items-start gap-0.5 rounded-control border border-line px-3 py-2.5 text-left hover:bg-surface-sunken"
                  >
                    <span className="text-sm font-medium text-text">{row.displayName}</span>
                    <span className="text-xs text-muted">{row.baseCurrency}</span>
                  </button>
                </li>
              ))}
            </ul>
          )}
          <Button variant="secondary" onClick={onCreateNew}>
            {t.profile.createNew}
          </Button>
        </CardBody>
      </Card>
    </div>
  )
}

const CREATE_PROFILE_FORM_ID = 'create-profile-form'

function CreateProfileModal({
  open,
  onClose,
  defaultLocale,
  onCreated,
}: {
  open: boolean
  onClose: () => void
  defaultLocale: Locale
  onCreated: (profile: Profile) => void | Promise<void>
}) {
  const { t } = useI18n()
  const [displayName, setDisplayName] = useState('')
  const [baseCurrency, setBaseCurrency] = useState<CurrencyCode>('IDR')
  const [saving, setSaving] = useState(false)
  const [error, setError] = useState<string | null>(null)

  // Fields are cleared each time the dialog opens rather than on close, since
  // <Modal> keeps its content mounted between opens for its close animation.
  useEffect(() => {
    if (open) {
      setDisplayName('')
      setBaseCurrency('IDR')
      setError(null)
    }
  }, [open])

  async function handleSubmit(event: FormEvent) {
    event.preventDefault()
    const trimmed = displayName.trim()
    if (!trimmed) {
      setError(t.validation.required)
      return
    }
    setSaving(true)
    try {
      await onCreated(blankProfile(trimmed, baseCurrency, defaultLocale))
    } finally {
      setSaving(false)
    }
  }

  return (
    <Modal
      open={open}
      onClose={onClose}
      title={t.profile.newProfileTitle}
      footer={
        <>
          <Button variant="secondary" onClick={onClose} disabled={saving}>
            {t.common.cancel}
          </Button>
          <Button type="submit" form={CREATE_PROFILE_FORM_ID} loading={saving}>
            {t.profile.saveButton}
          </Button>
        </>
      }
    >
      <form id={CREATE_PROFILE_FORM_ID} className="flex flex-col gap-4" onSubmit={handleSubmit}>
        <Input
          label={t.profile.fields.displayName}
          value={displayName}
          onChange={(event) => {
            setDisplayName(event.target.value)
            setError(null)
          }}
          error={error ?? undefined}
          required
          autoFocus
        />
        <Select
          label={t.profile.fields.baseCurrency}
          value={baseCurrency}
          onChange={(event) => setBaseCurrency(event.target.value as CurrencyCode)}
        >
          {CURRENCY_CODES.map((code) => (
            <option key={code} value={code}>
              {code} ({CURRENCIES[code].name})
            </option>
          ))}
        </Select>
      </form>
    </Modal>
  )
}

function PinScreen({
  profile,
  onUnlocked,
  onSwitchProfile,
}: {
  profile: Profile
  onUnlocked: () => void
  onSwitchProfile: () => void
}) {
  const { t } = useI18n()
  const [pin, setPin] = useState('')
  const [error, setError] = useState<string | null>(null)
  const [checking, setChecking] = useState(false)

  async function handleSubmit(event: FormEvent) {
    event.preventDefault()
    if (!profile.pinHash || !profile.pinSalt) return
    setChecking(true)
    setError(null)
    try {
      const ok = await verifyPin(pin, profile.pinHash, profile.pinSalt)
      if (ok) {
        onUnlocked()
      } else {
        setError(t.profile.pin.incorrect)
        setPin('')
      }
    } finally {
      setChecking(false)
    }
  }

  return (
    <div className="flex min-h-dvh items-center justify-center bg-bg p-4">
      <Card className="w-full max-w-sm">
        <CardBody className="flex flex-col gap-4">
          <div>
            <h1 className="text-lg font-semibold text-text">{t.profile.pin.enterTitle}</h1>
            <p className="mt-1 text-sm text-muted">{t.profile.pin.enterPrompt}</p>
          </div>
          <form className="flex flex-col gap-4" onSubmit={handleSubmit}>
            <Input
              label={t.profile.pin.enterTitle}
              type="password"
              inputMode="numeric"
              autoComplete="off"
              value={pin}
              onChange={(event) => setPin(event.target.value)}
              error={error ?? undefined}
              autoFocus
              required
            />
            <Button type="submit" loading={checking} disabled={pin.length === 0}>
              {t.common.ok}
            </Button>
          </form>
          <Button variant="ghost" onClick={onSwitchProfile}>
            {t.profile.switchProfile}
          </Button>
        </CardBody>
      </Card>
    </div>
  )
}
