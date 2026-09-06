import { useEffect, useState } from 'react'

type Theme = 'light' | 'dark' | 'system'

const STORAGE_KEY = 'financialam.theme'
const ORDER: Theme[] = ['light', 'dark', 'system']

function isTheme(value: string): value is Theme {
  return value === 'light' || value === 'dark' || value === 'system'
}

function readStoredTheme(): Theme {
  try {
    const stored = localStorage.getItem(STORAGE_KEY)
    if (stored && isTheme(stored)) return stored
  } catch {
    // Private browsing and locked down storage throw on access. Fall back
    // to following the system preference, which needs no storage at all.
  }
  return 'system'
}

function nextTheme(current: Theme): Theme {
  const index = ORDER.indexOf(current)
  return ORDER[(index + 1) % ORDER.length] ?? 'system'
}

export interface ThemeToggleProps {
  className?: string
}

/** Cycles light, dark, system on each activation. See src/index.css for how data-theme drives the actual palette swap. */
export function ThemeToggle({ className }: ThemeToggleProps) {
  const [theme, setTheme] = useState<Theme>(readStoredTheme)

  useEffect(() => {
    if (theme === 'system') {
      // No attribute at all lets the prefers-color-scheme media query in
      // index.css take back over, rather than pinning to whichever mode was
      // last explicitly chosen.
      document.documentElement.removeAttribute('data-theme')
    } else {
      document.documentElement.setAttribute('data-theme', theme)
    }
    try {
      localStorage.setItem(STORAGE_KEY, theme)
    } catch {
      // Nothing to recover here; the in-memory theme still applies for this session.
    }
  }, [theme])

  const upcoming = nextTheme(theme)
  const label = `Theme: ${theme}. Activate to switch to ${upcoming}.`

  return (
    <button
      type="button"
      onClick={() => setTheme(upcoming)}
      aria-label={label}
      title={label}
      className={`inline-flex h-9 w-9 items-center justify-center rounded-control border border-line bg-surface text-muted hover:bg-surface-sunken hover:text-text ${className ?? ''}`}
    >
      {theme === 'light' ? <SunIcon /> : theme === 'dark' ? <MoonIcon /> : <SystemIcon />}
    </button>
  )
}

function SunIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true" className="h-4 w-4">
      <circle cx="10" cy="10" r="3.5" stroke="currentColor" strokeWidth="1.5" />
      <path
        d="M10 2v2M10 16v2M18 10h-2M4 10H2M15.5 4.5l-1.4 1.4M5.9 14.1l-1.4 1.4M15.5 15.5l-1.4-1.4M5.9 5.9L4.5 4.5"
        stroke="currentColor"
        strokeWidth="1.5"
        strokeLinecap="round"
      />
    </svg>
  )
}

function MoonIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true" className="h-4 w-4">
      <path
        d="M17 11.5A7 7 0 018.5 3a7 7 0 108.5 8.5z"
        stroke="currentColor"
        strokeWidth="1.5"
        strokeLinejoin="round"
      />
    </svg>
  )
}

function SystemIcon() {
  return (
    <svg viewBox="0 0 20 20" fill="none" aria-hidden="true" className="h-4 w-4">
      <rect x="2.5" y="4" width="15" height="10" rx="1.5" stroke="currentColor" strokeWidth="1.5" />
      <path d="M7 17h6M10 14v3" stroke="currentColor" strokeWidth="1.5" strokeLinecap="round" />
    </svg>
  )
}
