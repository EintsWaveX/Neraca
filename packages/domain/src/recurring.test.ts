import { describe, expect, it } from 'vitest'
import type { RecurringRule } from './types'
import { dueOccurrences, materialise, occurrencesBetween } from './recurring'

function rule(overrides: Partial<RecurringRule> = {}): RecurringRule {
  return {
    id: 'r1',
    profileId: 'p1',
    name: 'Rent',
    frequency: 'monthly',
    interval: 1,
    startDate: '2026-01-01',
    endDate: null,
    lastRunDate: null,
    active: true,
    template: {
      walletId: 'w1',
      toWalletId: null,
      direction: 'expense',
      typeId: 'bill-payment',
      categoryId: 'house-and-apartment-rent',
      amount: 5_000_000,
      currency: 'IDR',
      description: 'Rent',
    },
    createdAt: '2026-01-01T00:00:00.000Z',
    ...overrides,
  }
}

describe('occurrencesBetween', () => {
  it('returns nothing for an inactive rule', () => {
    expect(occurrencesBetween(rule({ active: false }), '2026-01-01', '2026-12-31')).toEqual([])
  })

  it('fires daily on every interval day', () => {
    const r = rule({ frequency: 'daily', interval: 2, startDate: '2026-08-01' })
    expect(occurrencesBetween(r, '2026-08-01', '2026-08-08')).toEqual([
      '2026-08-01', '2026-08-03', '2026-08-05', '2026-08-07',
    ])
  })

  it('fires weekly, every `interval` weeks', () => {
    const r = rule({ frequency: 'weekly', interval: 2, startDate: '2026-08-03' })
    expect(occurrencesBetween(r, '2026-08-03', '2026-09-15')).toEqual([
      '2026-08-03', '2026-08-17', '2026-08-31', '2026-09-14',
    ])
  })

  it('fires yearly on the same day each interval', () => {
    const r = rule({ frequency: 'yearly', interval: 1, startDate: '2026-03-15' })
    expect(occurrencesBetween(r, '2026-01-01', '2029-01-01')).toEqual([
      '2026-03-15', '2027-03-15', '2028-03-15',
    ])
  })

  it('stops at the rule end date even when the query range goes further', () => {
    const r = rule({ frequency: 'monthly', interval: 1, startDate: '2026-01-01', endDate: '2026-03-01' })
    expect(occurrencesBetween(r, '2026-01-01', '2026-12-31')).toEqual([
      '2026-01-01', '2026-02-01', '2026-03-01',
    ])
  })

  it('returns nothing when the query range ends before the rule starts', () => {
    const r = rule({ startDate: '2026-06-01' })
    expect(occurrencesBetween(r, '2026-01-01', '2026-03-01')).toEqual([])
  })

  it('respects the lower bound of the query range', () => {
    const r = rule({ frequency: 'monthly', interval: 1, startDate: '2026-01-01' })
    expect(occurrencesBetween(r, '2026-04-01', '2026-06-30')).toEqual([
      '2026-04-01', '2026-05-01', '2026-06-01',
    ])
  })

  describe('month end drift', () => {
    it('a rule starting on the 31st lands on the last day of a shorter month', () => {
      const r = rule({ frequency: 'monthly', interval: 1, startDate: '2026-01-31' })
      const occurrences = occurrencesBetween(r, '2026-01-01', '2026-06-30')
      expect(occurrences).toEqual([
        '2026-01-31', // January: 31 days
        '2026-02-28', // February: clamped, 2026 is not a leap year
        '2026-03-31', // March: back to the 31st, not stuck at 28
        '2026-04-30', // April: clamped to 30
        '2026-05-31', // May: back to the 31st
        '2026-06-30', // June: clamped to 30
      ])
    })

    it('does not permanently drift to the 28th after a clamped month', () => {
      const r = rule({ frequency: 'monthly', interval: 1, startDate: '2026-01-31' })
      const [, , march] = occurrencesBetween(r, '2026-01-01', '2026-03-31')
      expect(march).toBe('2026-03-31')
    })
  })
})

describe('dueOccurrences', () => {
  it('starts from the rule startDate when it has never run', () => {
    const r = rule({ frequency: 'monthly', interval: 1, startDate: '2026-01-01', lastRunDate: null })
    expect(dueOccurrences(r, '2026-03-01')).toEqual(['2026-01-01', '2026-02-01', '2026-03-01'])
  })

  it('excludes the last run date itself and anything before it', () => {
    const r = rule({ frequency: 'monthly', interval: 1, startDate: '2026-01-01', lastRunDate: '2026-02-01' })
    expect(dueOccurrences(r, '2026-04-01')).toEqual(['2026-03-01', '2026-04-01'])
  })

  it('returns nothing when fully caught up', () => {
    const r = rule({ frequency: 'monthly', interval: 1, startDate: '2026-01-01', lastRunDate: '2026-03-01' })
    expect(dueOccurrences(r, '2026-03-01')).toEqual([])
  })
})

describe('materialise', () => {
  it('builds one row per date from the rule template, with recurringId set', () => {
    const r = rule()
    const rows = materialise(r, ['2026-01-01', '2026-02-01'])
    expect(rows).toHaveLength(2)
    expect(rows[0]).toMatchObject({
      profileId: 'p1',
      walletId: 'w1',
      direction: 'expense',
      categoryId: 'house-and-apartment-rent',
      amount: 5_000_000,
      currency: 'IDR',
      date: '2026-01-01',
      recurringId: 'r1',
    })
    expect(rows[1]?.date).toBe('2026-02-01')
  })

  it('produces no id or createdAt fields, leaving those to storage', () => {
    const rows = materialise(rule(), ['2026-01-01'])
    expect(rows[0]).not.toHaveProperty('id')
    expect(rows[0]).not.toHaveProperty('createdAt')
  })
})
