import type { HTMLAttributes, TableHTMLAttributes, TdHTMLAttributes, ThHTMLAttributes } from 'react'

export interface TableProps extends TableHTMLAttributes<HTMLTableElement> {}

/** Wraps the table in its own horizontal scroller, so a wide table scrolls in place instead of pushing the page out. */
export function Table({ className, children, ...props }: TableProps) {
  return (
    <div className="w-full overflow-x-auto rounded-card border border-line">
      <table className={`w-full min-w-max border-collapse text-sm text-text ${className ?? ''}`} {...props}>
        {children}
      </table>
    </div>
  )
}

export interface THeadProps extends HTMLAttributes<HTMLTableSectionElement> {}

export function THead({ className, ...props }: THeadProps) {
  return (
    <thead className={`bg-surface-sunken text-xs uppercase tracking-wide text-muted ${className ?? ''}`} {...props} />
  )
}

export interface TBodyProps extends HTMLAttributes<HTMLTableSectionElement> {}

export function TBody({ className, ...props }: TBodyProps) {
  return <tbody className={`divide-y divide-line ${className ?? ''}`} {...props} />
}

export interface TRProps extends HTMLAttributes<HTMLTableRowElement> {}

export function TR({ className, ...props }: TRProps) {
  return <tr className={className} {...props} />
}

export type SortDirection = 'ascending' | 'descending' | 'none'

export interface THProps extends Omit<ThHTMLAttributes<HTMLTableCellElement>, 'onClick'> {
  sortable?: boolean
  sortDirection?: SortDirection
  /** Kept separate from the native onClick, since a sortable header's clickable surface is the inner button, not the cell. */
  onSort?: () => void
}

export function TH({ sortable, sortDirection = 'none', onSort, className, children, ...props }: THProps) {
  return (
    <th
      scope="col"
      aria-sort={sortable ? sortDirection : undefined}
      className={`whitespace-nowrap px-4 py-2.5 text-left font-semibold ${className ?? ''}`}
      {...props}
    >
      {sortable ? (
        <button
          type="button"
          onClick={onSort}
          className="inline-flex items-center gap-1 text-left font-semibold text-muted hover:text-text"
        >
          {children}
          <SortIcon direction={sortDirection} />
        </button>
      ) : (
        children
      )}
    </th>
  )
}

function SortIcon({ direction }: { direction: SortDirection }) {
  return (
    <svg viewBox="0 0 12 12" aria-hidden="true" className="h-3 w-3 shrink-0 text-faint">
      <path d="M6 2l3 3.5H3L6 2z" fill="currentColor" opacity={direction === 'ascending' ? 1 : 0.35} />
      <path d="M6 10l-3-3.5h6L6 10z" fill="currentColor" opacity={direction === 'descending' ? 1 : 0.35} />
    </svg>
  )
}

export interface TDProps extends TdHTMLAttributes<HTMLTableCellElement> {
  /** Right aligns and switches to tabular figures, for money and other digit columns that need to line up. */
  numeric?: boolean
}

export function TD({ numeric, className, ...props }: TDProps) {
  return <td className={`px-4 py-2.5 ${numeric ? 'text-right tnum' : 'text-left'} ${className ?? ''}`} {...props} />
}
