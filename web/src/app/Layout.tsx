/**
 * The application shell.
 *
 * One list of nav items drives three different renderings: the desktop
 * sidebar, the mobile bottom tab bar, and (implicitly) the page title in the
 * header, so a route can never be reachable from one surface and not the
 * other. `NavLink` sets `aria-current="page"` on the active link on its own,
 * which is why nothing here sets that attribute by hand.
 */

import type { ReactNode } from 'react'
import { NavLink, Outlet } from 'react-router-dom'
import { useI18n } from '@/i18n'
import { useProfile, useProfiles } from './ProfileProvider'
import { ThemeToggle } from '@/ui'

interface NavItem {
  to: string
  /** Matches a key under the `nav` dictionary group. */
  labelKey: 'dashboard' | 'transactions' | 'wallets' | 'budgets' | 'recurring' | 'reports' | 'settings'
  icon: ReactNode
  /** Only the dashboard route needs an exact match; every other path is also a prefix of nothing else here, but `end` costs nothing to set consistently. */
  end?: boolean
}

const NAV_ITEMS: NavItem[] = [
  { to: '/', labelKey: 'dashboard', icon: <GridIcon />, end: true },
  { to: '/transactions', labelKey: 'transactions', icon: <SwapIcon /> },
  { to: '/wallets', labelKey: 'wallets', icon: <WalletIcon /> },
  { to: '/budgets', labelKey: 'budgets', icon: <PieIcon /> },
  { to: '/recurring', labelKey: 'recurring', icon: <RepeatIcon /> },
  { to: '/reports', labelKey: 'reports', icon: <BarsIcon /> },
  { to: '/settings', labelKey: 'settings', icon: <GearIcon /> },
]

export function Layout() {
  const { t, locale, setLocale } = useI18n()
  const profile = useProfile()
  const { profiles, select, close } = useProfiles()

  return (
    <div className="flex min-h-dvh flex-col bg-bg md:flex-row">
      {/* Desktop sidebar. Hidden entirely below md so it never competes with the bottom tab bar for space. */}
      <aside className="hidden shrink-0 flex-col gap-1 border-r border-line bg-surface px-3 py-4 md:flex md:w-56">
        <div className="mb-3 px-2 text-base font-semibold text-text">{t.common.appName}</div>
        <nav aria-label={t.nav.dashboard} className="flex flex-col gap-1">
          {NAV_ITEMS.map((item) => (
            <NavLink
              key={item.to}
              to={item.to}
              end={item.end}
              className={({ isActive }) =>
                `flex items-center gap-2.5 rounded-control px-2.5 py-2 text-sm font-medium ${
                  isActive ? 'bg-accent-soft text-accent' : 'text-muted hover:bg-surface-sunken hover:text-text'
                }`
              }
            >
              <span aria-hidden="true" className="[&>svg]:h-5 [&>svg]:w-5">
                {item.icon}
              </span>
              {t.nav[item.labelKey]}
            </NavLink>
          ))}
        </nav>
      </aside>

      <div className="flex min-w-0 flex-1 flex-col">
        <header className="flex items-center justify-between gap-3 border-b border-line bg-surface px-4 py-3 sm:px-6">
          <ProfileSwitch
            profiles={profiles}
            currentId={profile.id}
            onSelect={select}
            onLock={close}
            switchLabel={t.profile.switchProfile}
            lockLabel={t.common.close}
          />
          <div className="flex items-center gap-2">
            <LocaleSwitch locale={locale} onChange={setLocale} label={t.settings.language.label} />
            <ThemeToggle />
          </div>
        </header>

        {/* Bottom tab bar leaves room below it (pb-16) so the last bit of page content is never hidden behind the fixed bar. */}
        <main className="min-w-0 flex-1 pb-16 md:pb-0">
          <Outlet />
        </main>
      </div>

      <nav
        aria-label={t.nav.dashboard}
        className="fixed inset-x-0 bottom-0 z-10 flex justify-around overflow-x-auto border-t border-line bg-surface px-1 py-1 [padding-bottom:env(safe-area-inset-bottom)] md:hidden"
      >
        {NAV_ITEMS.map((item) => (
          <NavLink
            key={item.to}
            to={item.to}
            end={item.end}
            className={({ isActive }) =>
              `flex min-w-14 flex-col items-center gap-0.5 rounded-control px-1.5 py-1.5 text-[0.65rem] font-medium ${
                isActive ? 'text-accent' : 'text-muted'
              }`
            }
          >
            <span aria-hidden="true" className="[&>svg]:h-5 [&>svg]:w-5">
              {item.icon}
            </span>
            <span className="truncate">{t.nav[item.labelKey]}</span>
          </NavLink>
        ))}
      </nav>
    </div>
  )
}

/**
 * Switching between profiles, and getting back to the picker.
 *
 * Without this the app was a one way door: creating a second profile switched
 * to it with no route back, so a visitor who tapped "start my own profile"
 * lost sight of the demo data entirely even though it was still in the
 * database. A native select is used rather than a custom menu because it is
 * keyboard operable and behaves properly on Android without any work.
 */
function ProfileSwitch({
  profiles,
  currentId,
  onSelect,
  onLock,
  switchLabel,
  lockLabel,
}: {
  profiles: Array<{ id: string; displayName: string }>
  currentId: string
  onSelect: (id: string) => void
  onLock: () => void
  switchLabel: string
  lockLabel: string
}) {
  const current = profiles.find((row) => row.id === currentId)

  // With a single profile there is nothing to switch to, so showing a control
  // implying otherwise would be noise.
  if (profiles.length < 2) {
    return <span className="truncate text-sm font-medium text-text">{current?.displayName ?? ''}</span>
  }

  return (
    <div className="flex min-w-0 items-center gap-1.5">
      <label className="sr-only" htmlFor="profile-switch">
        {switchLabel}
      </label>
      <select
        id="profile-switch"
        value={currentId}
        onChange={(event) => onSelect(event.currentTarget.value)}
        className="min-w-0 max-w-44 truncate rounded-control border border-line bg-surface px-2 py-1 text-sm font-medium text-text transition-colors hover:border-line-strong"
      >
        {profiles.map((row) => (
          <option key={row.id} value={row.id}>
            {row.displayName}
          </option>
        ))}
      </select>
      <button
        type="button"
        onClick={onLock}
        title={lockLabel}
        className="rounded-control px-2 py-1 text-xs font-medium text-muted transition-colors hover:bg-surface-sunken hover:text-text"
      >
        {lockLabel}
      </button>
    </div>
  )
}

function LocaleSwitch({
  locale,
  onChange,
  label,
}: {
  locale: 'en' | 'id'
  onChange: (locale: 'en' | 'id') => void
  label: string
}) {
  return (
    <div role="group" aria-label={label} className="flex overflow-hidden rounded-control border border-line text-xs font-medium">
      <button
        type="button"
        onClick={() => onChange('en')}
        aria-pressed={locale === 'en'}
        className={`px-2.5 py-1.5 ${locale === 'en' ? 'bg-accent text-accent-text' : 'bg-surface text-muted hover:bg-surface-sunken'}`}
      >
        EN
      </button>
      <button
        type="button"
        onClick={() => onChange('id')}
        aria-pressed={locale === 'id'}
        className={`px-2.5 py-1.5 ${locale === 'id' ? 'bg-accent text-accent-text' : 'bg-surface text-muted hover:bg-surface-sunken'}`}
      >
        ID
      </button>
    </div>
  )
}

// Deliberately plain, minimal-stroke icons in the same style as the ones
// already in src/ui (viewBox 0 0 20 20, stroke currentColor), so the nav
// does not introduce a second icon language.
function GridIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true">
      <rect x="2.5" y="2.5" width="6" height="6" rx="1" stroke="currentColor" strokeWidth="1.5" />
      <rect x="11.5" y="2.5" width="6" height="6" rx="1" stroke="currentColor" strokeWidth="1.5" />
      <rect x="2.5" y="11.5" width="6" height="6" rx="1" stroke="currentColor" strokeWidth="1.5" />
      <rect x="11.5" y="11.5" width="6" height="6" rx="1" stroke="currentColor" strokeWidth="1.5" />
    </svg>
  )
}

function SwapIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true">
      <path d="M4 7h11l-3-3M16 13H5l3 3" stroke="currentColor" strokeWidth="1.5" strokeLinecap="round" strokeLinejoin="round" />
    </svg>
  )
}

function WalletIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true">
      <rect x="2.5" y="5" width="15" height="11" rx="2" stroke="currentColor" strokeWidth="1.5" />
      <path d="M2.5 8h15" stroke="currentColor" strokeWidth="1.5" />
      <circle cx="14" cy="12" r="1" fill="currentColor" />
    </svg>
  )
}

function PieIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true">
      <path d="M10 2.5v7.5h7.5A7.5 7.5 0 1010 2.5z" stroke="currentColor" strokeWidth="1.5" strokeLinejoin="round" />
    </svg>
  )
}

function RepeatIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true">
      <path
        d="M4 9V7a3 3 0 013-3h8m0 0l-2.5-2.5M15 4l-2.5 2.5M16 11v2a3 3 0 01-3 3H5m0 0l2.5 2.5M5 16l2.5-2.5"
        stroke="currentColor"
        strokeWidth="1.5"
        strokeLinecap="round"
        strokeLinejoin="round"
      />
    </svg>
  )
}

function BarsIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true">
      <path d="M4 16V9M10 16V4M16 16v-6" stroke="currentColor" strokeWidth="1.5" strokeLinecap="round" />
    </svg>
  )
}

function GearIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true">
      <circle cx="10" cy="10" r="2.5" stroke="currentColor" strokeWidth="1.5" />
      <path
        d="M10 3v1.6M10 15.4V17M17 10h-1.6M4.6 10H3M14.8 5.2l-1.1 1.1M6.3 13.7l-1.1 1.1M14.8 14.8l-1.1-1.1M6.3 6.3L5.2 5.2"
        stroke="currentColor"
        strokeWidth="1.5"
        strokeLinecap="round"
      />
    </svg>
  )
}
