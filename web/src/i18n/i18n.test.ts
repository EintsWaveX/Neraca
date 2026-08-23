import { describe, expect, it } from 'vitest'
import { en } from './en'
import { id } from './id'
import { createT, labelFor } from './index'

/** Recursively collects every dot separated path to a string leaf. */
function collectPaths(value: unknown, prefix = ''): string[] {
  if (typeof value === 'string') {
    return [prefix]
  }
  if (value !== null && typeof value === 'object') {
    return Object.entries(value as Record<string, unknown>).flatMap(([key, child]) =>
      collectPaths(child, prefix === '' ? key : `${prefix}.${key}`),
    )
  }
  throw new Error(`Unexpected non string, non object value at "${prefix}".`)
}

describe('dictionary shape', () => {
  const enPaths = collectPaths(en).sort()
  const idPaths = collectPaths(id).sort()

  it('gives the Indonesian dictionary exactly the same key paths as English', () => {
    expect(idPaths).toEqual(enPaths)
  })

  it('has no path missing from the Indonesian dictionary', () => {
    const missing = enPaths.filter((path) => !idPaths.includes(path))
    expect(missing).toEqual([])
  })

  it('has no extra path in the Indonesian dictionary', () => {
    const extra = idPaths.filter((path) => !enPaths.includes(path))
    expect(extra).toEqual([])
  })

  // En dash and em dash written as escapes on purpose, so the characters
  // being screened out never appear literally in this source file either.
  const dashPattern = /[\u2013\u2014]/

  it('never uses an em dash or an en dash in any English string', () => {
    const offenders = enPaths.filter((path) => dashPattern.test(getByPath(en, path)))
    expect(offenders).toEqual([])
  })

  it('never uses an em dash or an en dash in any Indonesian string', () => {
    const offenders = idPaths.filter((path) => dashPattern.test(getByPath(id, path)))
    expect(offenders).toEqual([])
  })
})

function getByPath(dict: Record<string, unknown>, path: string): string {
  const value = path.split('.').reduce<unknown>((acc, segment) => {
    if (acc !== null && typeof acc === 'object' && segment in acc) {
      return (acc as Record<string, unknown>)[segment]
    }
    return undefined
  }, dict)
  if (typeof value !== 'string') {
    throw new Error(`Expected a string at "${path}".`)
  }
  return value
}

describe('interpolation', () => {
  it('replaces a single token', () => {
    const t = createT(en)
    expect(t('wallet.deleteConfirm', { name: 'Cash' })).toBe(
      'Delete "Cash"? Transactions already recorded against it are kept, but the wallet will no longer appear in new entries.',
    )
  })

  it('replaces more than one token', () => {
    const t = createT(en)
    expect(t('budget.spentOfLimit', { spent: 'Rp150.000', limit: 'Rp500.000' })).toBe(
      'Rp150.000 of Rp500.000 spent',
    )
  })

  it('replaces tokens in the Indonesian dictionary too', () => {
    const t = createT(id)
    expect(t('budget.spentOfLimit', { spent: 'Rp150.000', limit: 'Rp500.000' })).toBe(
      'Rp150.000 dari Rp500.000 terpakai',
    )
  })

  it('leaves an unrecognised token untouched', () => {
    const t = createT(en)
    expect(t('budget.remaining', { wrongKey: '1' })).toBe('{amount} remaining')
  })

  it('returns the plain string when no params are given', () => {
    const t = createT(en)
    expect(t('common.save')).toBe('Save')
  })

  it('supports direct property access alongside the callable form', () => {
    const t = createT(en)
    expect(t.common.save).toBe('Save')
    expect(t.budget.onTrack).toBe('On track')
  })
})

describe('labelFor', () => {
  const item = { en: 'Groceries', id_: 'Belanja Harian' }

  it('picks the English label for the en locale', () => {
    expect(labelFor(item, 'en')).toBe('Groceries')
  })

  it('picks the Indonesian label for the id locale', () => {
    expect(labelFor(item, 'id')).toBe('Belanja Harian')
  })

  it('works for objects that carry extra fields, like a real category', () => {
    const category = {
      id: 'groceries',
      group: 'groceries' as const,
      flow: 'expense' as const,
      en: 'Groceries',
      id_: 'Belanja Harian',
      emoji: '\u{1F6D2}',
    }
    expect(labelFor(category, 'en')).toBe('Groceries')
    expect(labelFor(category, 'id')).toBe('Belanja Harian')
  })
})
