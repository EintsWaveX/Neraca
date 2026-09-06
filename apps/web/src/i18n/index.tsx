/**
 * The i18n layer.
 *
 * `I18nProvider` holds the current locale in React state and mirrors it to
 * `localStorage` so a reload keeps the choice. `useI18n` hands components a
 * `t` accessor that is both callable, `t('budget.overLimit')`, and a plain
 * nested object, `t.budget.overLimit`, plus `formatDate`, `formatNumber` and
 * `labelFor` already bound to the current locale.
 *
 * The dot path passed to `t` is checked against the real shape of the
 * dictionary at compile time through `LeafPaths`, so a typo or a key that was
 * never added is a build error rather than a blank label in the running app.
 */

import {
  createContext,
  useCallback,
  useContext,
  useMemo,
  useState,
  type ReactNode,
} from 'react'
import type { IsoDate, Locale } from '@neraca/domain/types'
import { en } from './en'
import { id } from './id'

export { en } from './en'
export { id } from './id'

type Dict = typeof en

/** Every dot separated path to a string leaf in the dictionary. */
type LeafPaths<T> = {
  [K in keyof T & string]: T[K] extends string ? K : `${K}.${LeafPaths<T[K]>}`
}[keyof T & string]

type InterpolateParams = Record<string, string | number>

/** Callable form: `t('budget.overLimit', { amount })`. */
type TFunction = <P extends LeafPaths<Dict>>(path: P, params?: InterpolateParams) => string

/** `t` supports both the callable form and direct property access. */
export type T = Dict & TFunction

const DICTS: Record<Locale, Dict> = { en, id }

const LOCALE_STORAGE_KEY = 'financialam.locale'

function isLocale(value: unknown): value is Locale {
  return value === 'en' || value === 'id'
}

function getByPath(dict: Dict, path: string): string {
  let current: unknown = dict
  for (const segment of path.split('.')) {
    if (current !== null && typeof current === 'object' && segment in current) {
      current = (current as Record<string, unknown>)[segment]
    } else {
      return path
    }
  }
  return typeof current === 'string' ? current : path
}

function interpolate(template: string, params: InterpolateParams): string {
  return template.replace(/\{(\w+)\}/g, (match, key: string) => {
    return Object.prototype.hasOwnProperty.call(params, key) ? String(params[key]) : match
  })
}

/**
 * Builds the callable and directly addressable `t` for one dictionary.
 * Exported on its own so tests can exercise interpolation without going
 * through the React provider.
 */
export function createT(dict: Dict): T {
  const call = ((path: string, params?: InterpolateParams) => {
    const raw = getByPath(dict, path)
    return params ? interpolate(raw, params) : raw
  }) as TFunction
  return Object.assign(call, dict)
}

/**
 * Picks the field matching the given locale from anything carrying both an
 * `en` and an `id_` label, which covers categories, category groups and
 * transaction types alike.
 */
export function labelFor<Item extends { en: string; id_: string }>(item: Item, locale: Locale): string {
  return locale === 'id' ? item.id_ : item.en
}

function intlLocaleFor(locale: Locale): string {
  return locale === 'id' ? 'id-ID' : 'en-GB'
}

const DEFAULT_DATE_OPTIONS: Intl.DateTimeFormatOptions = {
  day: 'numeric',
  month: 'short',
  year: 'numeric',
}

export function formatDate(
  date: Date | IsoDate,
  locale: Locale,
  options: Intl.DateTimeFormatOptions = DEFAULT_DATE_OPTIONS,
): string {
  const value = typeof date === 'string' ? new Date(date) : date
  return new Intl.DateTimeFormat(intlLocaleFor(locale), options).format(value)
}

export function formatNumber(value: number, locale: Locale, options?: Intl.NumberFormatOptions): string {
  return new Intl.NumberFormat(intlLocaleFor(locale), options).format(value)
}

function readStoredLocale(): Locale | null {
  try {
    const raw = window.localStorage.getItem(LOCALE_STORAGE_KEY)
    return isLocale(raw) ? raw : null
  } catch {
    return null
  }
}

function persistLocale(locale: Locale): void {
  try {
    window.localStorage.setItem(LOCALE_STORAGE_KEY, locale)
  } catch {
    // Private browsing or a disabled storage API. The choice still applies
    // for the running session, it just will not survive a reload.
  }
}

function detectBrowserLocale(): Locale {
  try {
    const language = typeof navigator === 'undefined' ? '' : navigator.language
    return language.toLowerCase().startsWith('id') ? 'id' : 'en'
  } catch {
    return 'en'
  }
}

function resolveInitialLocale(): Locale {
  return readStoredLocale() ?? detectBrowserLocale()
}

export interface I18nContextValue {
  locale: Locale
  setLocale: (locale: Locale) => void
  t: T
  formatDate: (date: Date | IsoDate, options?: Intl.DateTimeFormatOptions) => string
  formatNumber: (value: number, options?: Intl.NumberFormatOptions) => string
  labelFor: <Item extends { en: string; id_: string }>(item: Item) => string
}

const I18nContext = createContext<I18nContextValue | null>(null)

export function I18nProvider({ children }: { children: ReactNode }) {
  const [locale, setLocaleState] = useState<Locale>(resolveInitialLocale)

  const setLocale = useCallback((next: Locale) => {
    setLocaleState(next)
    persistLocale(next)
  }, [])

  const t = useMemo(() => createT(DICTS[locale]), [locale])

  const formatDateBound = useCallback(
    (date: Date | IsoDate, options?: Intl.DateTimeFormatOptions) => formatDate(date, locale, options),
    [locale],
  )

  const formatNumberBound = useCallback(
    (value: number, options?: Intl.NumberFormatOptions) => formatNumber(value, locale, options),
    [locale],
  )

  const labelForBound = useCallback(
    <Item extends { en: string; id_: string }>(item: Item) => labelFor(item, locale),
    [locale],
  )

  const value = useMemo<I18nContextValue>(
    () => ({
      locale,
      setLocale,
      t,
      formatDate: formatDateBound,
      formatNumber: formatNumberBound,
      labelFor: labelForBound,
    }),
    [locale, setLocale, t, formatDateBound, formatNumberBound, labelForBound],
  )

  return <I18nContext.Provider value={value}>{children}</I18nContext.Provider>
}

export function useI18n(): I18nContextValue {
  const ctx = useContext(I18nContext)
  if (ctx === null) {
    throw new Error('useI18n must be called within an I18nProvider.')
  }
  return ctx
}
