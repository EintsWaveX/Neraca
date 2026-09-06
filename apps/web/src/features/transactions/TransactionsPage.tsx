/**
 * The transactions screen: a filtered, sorted, paginated register.
 *
 * Filtering, sorting and paging all go through `repository.listTransactions`
 * and `countTransactions` rather than being done in the browser against a
 * full local copy, so the page stays responsive no matter how many rows a
 * profile has built up. The one exception is the running total footer: there
 * is no server side sum in `Repository`, so totalling the filtered set means
 * fetching every matching row once, unpaginated, purely to add it up. That is
 * still driven entirely by the query filters, never by re-filtering in the
 * browser.
 *
 * The register is the screen this whole design is named after, so it is the
 * plainest one: a heading, the filters, and the ledger. The running total sits
 * in the table's own footer under the heavier rule, where a ledger puts a sum,
 * rather than floating in a card header away from the column it totals.
 */

import { useEffect, useMemo, useState } from 'react'
import type { Transaction } from '@neraca/domain/types'
import type { TransactionQuery } from '@/data/repository'
import { add, negate, zero, money, type Money } from '@neraca/domain/money'
import { signedBase } from '@neraca/domain/rates'
import { categoryById } from '@neraca/domain/categories'
import { transactionTypeById } from '@neraca/domain/txTypes'
import { useRepository, useAsync } from '@/app/repo'
import { useProfile } from '@/app/ProfileProvider'
import { useI18n } from '@/i18n'
import { Button, EmptyState, Modal, Skeleton } from '@/ui'
import { Block, Page } from '@/design/primitives'
import { Figure, MoneyFigure } from '@/design/Figure'
import { LedgerTable, type LedgerColumn, type SortDirection } from '@/design/LedgerTable'
import {
  FilterPanel, buildTransactionQuery, createEmptyFilters, filtersAreDefault,
  type TransactionFiltersState,
} from './FilterPanel'
import { TransactionForm } from './TransactionForm'

const PAGE_SIZE = 20

type Sort = NonNullable<TransactionQuery['sort']>

function nextSortFor(current: Sort, column: 'date' | 'amount'): Sort {
  if (column === 'date') return current === 'date-desc' ? 'date-asc' : 'date-desc'
  return current === 'amount-desc' ? 'amount-asc' : 'amount-desc'
}

/**
 * The transaction's own amount, signed by direction, in its own currency and
 * not converted. A transfer shows plain, with no sign, because it did not add
 * to or subtract from anything overall.
 */
function rowAmount(tx: Transaction): Money {
  const amt = money(tx.amount, tx.currency)
  return tx.direction === 'expense' ? negate(amt) : amt
}

export default function TransactionsPage() {
  const { t, formatDate, labelFor } = useI18n()
  const repo = useRepository()
  const profile = useProfile()

  const wallets = useAsync(() => repo.listWallets(profile.id), [repo, profile.id])
  const rates = useAsync(() => repo.listRates(profile.id), [repo, profile.id])
  // Memoised so the fallback empty array is referentially stable across
  // renders while loading, rather than invalidating the memo below on every
  // render just because `?? []` made a fresh array.
  const walletList = useMemo(() => wallets.data ?? [], [wallets.data])
  const rateList = useMemo(() => rates.data ?? [], [rates.data])
  const walletById = useMemo(() => new Map(walletList.map((w) => [w.id, w])), [walletList])

  const [filters, setFilters] = useState<TransactionFiltersState>(() => createEmptyFilters())
  const [sort, setSort] = useState<Sort>('date-desc')
  const [page, setPage] = useState(0)
  const [refreshKey, setRefreshKey] = useState(0)
  const [editing, setEditing] = useState<Transaction | 'new' | null>(null)
  const [deleteTarget, setDeleteTarget] = useState<Transaction | null>(null)
  const [deleting, setDeleting] = useState(false)

  const baseQuery = useMemo(
    () => buildTransactionQuery(filters, profile.id),
    // eslint-disable-next-line react-hooks/exhaustive-deps
    [filters, profile.id],
  )

  // Any change to the filter query invalidates the current page: staying on
  // page 3 of what is now a narrower result set could point past its end.
  useEffect(() => {
    setPage(0)
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [baseQuery])

  const listQuery = useMemo<TransactionQuery>(
    () => ({ ...baseQuery, sort, limit: PAGE_SIZE, offset: page * PAGE_SIZE }),
    [baseQuery, sort, page],
  )

  const list = useAsync(() => repo.listTransactions(listQuery), [repo, listQuery, refreshKey])
  const count = useAsync(() => repo.countTransactions(baseQuery), [repo, baseQuery, refreshKey])
  const totals = useAsync(
    () => repo.listTransactions({ ...baseQuery, sort: 'date-desc' }),
    [repo, baseQuery, refreshKey],
  )

  const rows = list.data ?? []
  const total = count.data ?? 0

  const runningTotal = useMemo(() => {
    if (!totals.data) return null
    return totals.data.reduce(
      (acc, tx) => add(acc, signedBase(tx, profile.baseCurrency)),
      zero(profile.baseCurrency),
    )
  }, [totals.data, profile.baseCurrency])

  function reload() {
    setRefreshKey((k) => k + 1)
  }

  async function confirmDelete() {
    if (!deleteTarget) return
    setDeleting(true)
    try {
      await repo.deleteTransaction(deleteTarget.id)
      setDeleteTarget(null)
      reload()
    } finally {
      setDeleting(false)
    }
  }

  const dateSortDir: SortDirection =
    sort === 'date-desc' ? 'descending' : sort === 'date-asc' ? 'ascending' : 'none'
  const amountSortDir: SortDirection =
    sort === 'amount-desc' ? 'descending' : sort === 'amount-asc' ? 'ascending' : 'none'

  const loading = list.loading || wallets.loading

  const columns: ReadonlyArray<LedgerColumn<Transaction>> = [
    {
      key: 'date',
      header: t.transaction.fields.date,
      area: 'date',
      sortable: true,
      sortDirection: dateSortDir,
      onSort: () => setSort((s) => nextSortFor(s, 'date')),
      render: (tx) => <Figure className="text-sm text-ink-muted">{formatDate(tx.date)}</Figure>,
    },
    {
      key: 'description',
      header: t.transaction.fields.description,
      area: 'desc',
      render: (tx) => {
        const category = categoryById(tx.categoryId)
        const type = transactionTypeById(tx.typeId)
        const sourceWallet = walletById.get(tx.walletId)
        const destWallet = tx.toWalletId ? walletById.get(tx.toWalletId) : undefined
        return (
          <span className="flex min-w-0 flex-col">
            <span className="truncate text-ink">
              {tx.description || (category ? labelFor(category) : tx.categoryId)}
            </span>
            <span className="truncate text-xs text-ink-faint">
              {category ? labelFor(category) : tx.categoryId}
              {type ? ` · ${labelFor(type)}` : ''}
              {' · '}
              {sourceWallet?.name ?? tx.walletId}
              {destWallet ? ` to ${destWallet.name}` : ''}
            </span>
          </span>
        )
      },
    },
    {
      key: 'amount',
      header: t.transaction.fields.amount,
      area: 'amount',
      align: 'right',
      sortable: true,
      sortDirection: amountSortDir,
      onSort: () => setSort((s) => nextSortFor(s, 'amount')),
      render: (tx) => (
        <MoneyFigure
          value={rowAmount(tx)}
          tone={tx.direction === 'transfer' ? 'neutral' : 'auto'}
          signDisplay={tx.direction === 'transfer' ? 'never' : 'always'}
        />
      ),
    },
    {
      key: 'actions',
      // The column exists to hold controls, so it has no heading of its own.
      // A caption naming it would be read out on every row for no benefit.
      header: <span className="sr-only">{t.common.edit}</span>,
      area: 'balance',
      align: 'right',
      render: (tx) => (
        <span className="flex justify-end gap-1">
          <Button size="sm" variant="ghost" onClick={() => setEditing(tx)}>
            {t.common.edit}
          </Button>
          <Button size="sm" variant="ghost" onClick={() => setDeleteTarget(tx)}>
            {t.common.delete}
          </Button>
        </span>
      ),
    },
  ]

  return (
    <Page>
      <header className="flex flex-wrap items-center justify-between gap-3">
        <h1 className="text-h2 leading-tight">{t.transaction.title}</h1>
        <Button onClick={() => setEditing('new')} disabled={walletList.length === 0}>
          {t.transaction.add}
        </Button>
      </header>

      <div className="mt-6">
        <FilterPanel
          value={filters}
          onChange={setFilters}
          wallets={walletList}
          baseCurrency={profile.baseCurrency}
        />
      </div>

      <Block title={t('transaction.filter.resultsCount', { count: rows.length, total })}>
        {loading ? (
          <div className="flex flex-col gap-2 py-2" aria-hidden="true">
            <Skeleton shape="block" className="h-10 w-full" />
            <Skeleton shape="block" className="h-10 w-full" />
            <Skeleton shape="block" className="h-10 w-full" />
          </div>
        ) : rows.length === 0 ? (
          <EmptyState title={filtersAreDefault(filters) ? t.empty.transactions : t.empty.searchResults} />
        ) : (
          <>
            <LedgerTable
              caption={t.transaction.title}
              columns={columns}
              rows={rows}
              rowKey={(tx) => tx.id}
              footerLabel={t.report.netBalance}
              {...(runningTotal
                ? {
                    footer: {
                      amount: (
                        <MoneyFigure value={runningTotal} tone="auto" signDisplay="always" />
                      ),
                    },
                  }
                : {})}
            />

            <div className="mt-4 flex flex-wrap items-center justify-between gap-2 text-sm text-ink-muted">
              <p>{t('transaction.filter.resultsCount', { count: rows.length, total })}</p>
              <div className="flex gap-2">
                <Button
                  variant="secondary"
                  size="sm"
                  onClick={() => setPage((p) => Math.max(0, p - 1))}
                  disabled={page === 0}
                >
                  {t.common.back}
                </Button>
                <Button
                  variant="secondary"
                  size="sm"
                  onClick={() => setPage((p) => p + 1)}
                  disabled={page * PAGE_SIZE + rows.length >= total}
                >
                  {t.common.next}
                </Button>
              </div>
            </div>
          </>
        )}
      </Block>

      <Modal
        open={editing !== null}
        onClose={() => setEditing(null)}
        title={editing === 'new' ? t.transaction.add : t.transaction.edit}
      >
        {editing !== null && (
          <TransactionForm
            wallets={walletList}
            rates={rateList}
            initial={editing === 'new' ? undefined : editing}
            onSaved={() => {
              setEditing(null)
              reload()
            }}
            onCancel={() => setEditing(null)}
          />
        )}
      </Modal>

      <Modal
        open={deleteTarget !== null}
        onClose={() => setDeleteTarget(null)}
        title={t.transaction.delete}
        footer={
          <>
            <Button variant="secondary" onClick={() => setDeleteTarget(null)}>
              {t.common.cancel}
            </Button>
            <Button variant="danger" loading={deleting} onClick={confirmDelete}>
              {t.common.delete}
            </Button>
          </>
        }
      >
        <p className="text-sm text-ink">{t.transaction.deleteConfirm}</p>
      </Modal>
    </Page>
  )
}
