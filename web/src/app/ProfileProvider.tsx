/**
 * Which profile is open, and whether it has been unlocked.
 *
 * On a completely empty database this seeds the demo profile and selects it,
 * so a first time visitor lands in a populated application instead of an empty
 * state. The seed only ever runs when there are no profiles at all, so it can
 * never overwrite real data, and clearing the demo is an explicit action.
 *
 * The unlock flag lives in memory only. Persisting it would mean the PIN stops
 * being a lock at all after the first entry, and it is already only a
 * convenience lock over a shared device.
 */

import {
  createContext, useCallback, useContext, useEffect, useMemo, useState, type ReactNode,
} from 'react'
import type { Profile } from '@/domain/types'
import { buildDemoBackup, todayIso } from '@/data/seed'
import { useRepository } from './repo'

const SELECTED_KEY = 'financialam.profile'

function readStoredSelection(): string | null {
  try {
    return localStorage.getItem(SELECTED_KEY)
  } catch {
    // Private browsing modes throw on access rather than returning null.
    return null
  }
}

function storeSelection(id: string | null): void {
  try {
    if (id === null) localStorage.removeItem(SELECTED_KEY)
    else localStorage.setItem(SELECTED_KEY, id)
  } catch {
    // Losing the remembered selection is a small inconvenience, not an error.
  }
}

export interface ProfileContextValue {
  profiles: Profile[]
  profile: Profile | null
  /** False while a profile with a PIN set has not been unlocked yet. */
  unlocked: boolean
  loading: boolean
  select: (id: string) => void
  unlock: () => void
  close: () => void
  refresh: () => Promise<void>
}

const ProfileContext = createContext<ProfileContextValue | null>(null)

export function ProfileProvider({ children }: { children: ReactNode }) {
  const repo = useRepository()
  const [profiles, setProfiles] = useState<Profile[]>([])
  const [selectedId, setSelectedId] = useState<string | null>(null)
  const [unlocked, setUnlocked] = useState(false)
  const [loading, setLoading] = useState(true)

  const refresh = useCallback(async () => {
    const rows = await repo.listProfiles()
    setProfiles(rows)
  }, [repo])

  useEffect(() => {
    let live = true

    async function boot() {
      let rows = await repo.listProfiles()

      if (rows.length === 0) {
        // Anchored to today, not to the seed's reference date, so the
        // dashboard's current month cards are never empty on a first visit.
        await repo.importProfile(buildDemoBackup(todayIso()))
        rows = await repo.listProfiles()
      }
      if (!live) return
      setProfiles(rows)

      const remembered = readStoredSelection()
      const chosen =
        rows.find((row) => row.id === remembered) ??
        (rows.length === 1 ? rows[0] : undefined)

      if (chosen) {
        setSelectedId(chosen.id)
        // A profile with no PIN is open as soon as it is chosen.
        setUnlocked(chosen.pinHash === null)
      }
      setLoading(false)
    }

    boot().catch(() => {
      if (live) setLoading(false)
    })
    return () => {
      live = false
    }
  }, [repo])

  const select = useCallback(
    (id: string) => {
      const found = profiles.find((row) => row.id === id)
      setSelectedId(id)
      setUnlocked(found ? found.pinHash === null : false)
      storeSelection(id)
    },
    [profiles],
  )

  const close = useCallback(() => {
    setSelectedId(null)
    setUnlocked(false)
    storeSelection(null)
  }, [])

  const profile = useMemo(
    () => profiles.find((row) => row.id === selectedId) ?? null,
    [profiles, selectedId],
  )

  const value = useMemo<ProfileContextValue>(
    () => ({
      profiles,
      profile,
      unlocked,
      loading,
      select,
      unlock: () => setUnlocked(true),
      close,
      refresh,
    }),
    [profiles, profile, unlocked, loading, select, close, refresh],
  )

  return <ProfileContext.Provider value={value}>{children}</ProfileContext.Provider>
}

export function useProfiles(): ProfileContextValue {
  const value = useContext(ProfileContext)
  if (!value) throw new Error('useProfiles must be used inside a ProfileProvider')
  return value
}

/**
 * The open profile, for screens that cannot render without one. The router
 * only mounts those screens behind the unlock gate, so throwing here means a
 * routing mistake rather than an expected state.
 */
export function useProfile(): Profile {
  const { profile } = useProfiles()
  if (!profile) throw new Error('useProfile used outside an unlocked profile route')
  return profile
}
