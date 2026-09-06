/**
 * The ledger table.
 *
 * One place owns the two awkward parts of the Passbook's central object, so
 * no screen has to get them right on its own:
 *
 * 1. Below 48rem each row folds onto two lines rather than scrolling sideways
 *    or shrinking its figures. Four columns on a phone is not a table anybody
 *    can read, and horizontal scroll on the primary screen of a finance app
 *    hides the number you opened it to see.
 * 2. Folding needs `display: grid` on the rows, which drops the implicit table
 *    semantics in every current engine, so the roles are restated here. That is
 *    why this file carries the lint suppression and no screen has to.
 *
 * Columns declare which of the four slots they occupy when folded. A table
 * with no balance column simply leaves that slot empty and the grid collapses
 * it, so the same rule serves a three column and a four column ledger.
 */

/* oxlint-disable jsx-a11y/no-redundant-roles, jsx-a11y/no-interactive-element-to-noninteractive-role -- see the note above: the roles are load bearing once the rows become a grid, and a `td` is not an interactive element. */

import type { ReactNode } from 'react'

/** Where a column sits once a row folds onto two lines on a narrow screen. */
export type LedgerArea = 'date' | 'desc' | 'amount' | 'balance'

export interface LedgerColumn<T> {
  key: string
  header: ReactNode
  area: LedgerArea
  align?: 'left' | 'right'
  /** Applied to both the header cell and every body cell in the column. */
  className?: string
  render: (row: T, index: number) => ReactNode
}

export interface LedgerTableProps<T> {
  /** Read by assistive tech in place of the visual heading above the table. */
  caption: string
  columns: ReadonlyArray<LedgerColumn<T>>
  rows: readonly T[]
  rowKey: (row: T, index: number) => string
  /**
   * A totals row, drawn under the heavier rule a ledger uses beneath a sum.
   * Cells are matched to columns by key; a column with no entry renders empty.
   */
  footer?: Partial<Record<string, ReactNode>>
  footerLabel?: ReactNode
  /**
   * Rows print in on mount by default, the way an impact printer lays them
   * down. Turn it off where the list is already inside something that
   * animated, so the same rows are not printed twice.
   */
  animate?: boolean
}

const AREA_CLASS: Record<LedgerArea, string> = {
  date: 'c-date',
  desc: 'c-desc',
  amount: 'c-amount',
  balance: 'c-balance',
}

export function LedgerTable<T>({
  caption,
  columns,
  rows,
  rowKey,
  footer,
  footerLabel,
  animate = true,
}: LedgerTableProps<T>) {
  return (
    <table role="table" className="ledger ledger-narrow w-full border-collapse text-left">
      <caption className="sr-only">{caption}</caption>
      <thead>
        <tr role="row" className="border-b border-rule-strong">
          {columns.map((col) => (
            <th
              key={col.key}
              scope="col"
              className={[
                'pb-2 text-sm font-normal text-ink-muted',
                col.align === 'right' ? 'text-right' : '',
                col.className ?? '',
              ]
                .filter(Boolean)
                .join(' ')}
            >
              {col.header}
            </th>
          ))}
        </tr>
      </thead>
      <tbody>
        {rows.map((row, index) => (
          <tr
            key={rowKey(row, index)}
            role="row"
            className={`border-b border-rule ${animate ? 'print-in' : ''}`}
            style={{ '--print-index': index } as React.CSSProperties}
          >
            {columns.map((col) => (
              <td
                key={col.key}
                role="cell"
                className={[
                  AREA_CLASS[col.area],
                  'py-[var(--row-pad)] align-baseline',
                  col.align === 'right' ? 'pl-4 text-right whitespace-nowrap' : 'pr-3',
                  col.className ?? '',
                ]
                  .filter(Boolean)
                  .join(' ')}
              >
                {col.render(row, index)}
              </td>
            ))}
          </tr>
        ))}
        {footer && (
          <tr role="row" className="ledger-total">
            {columns.map((col, i) => {
              const content = footer[col.key] ?? (i === 0 && footerLabel ? footerLabel : null)
              return (
                <td
                  key={col.key}
                  role="cell"
                  className={[
                    AREA_CLASS[col.area],
                    'pt-2',
                    col.align === 'right' ? 'pl-4 text-right whitespace-nowrap' : 'text-sm text-ink-muted',
                  ].join(' ')}
                >
                  {content}
                </td>
              )
            })}
          </tr>
        )}
      </tbody>
    </table>
  )
}
