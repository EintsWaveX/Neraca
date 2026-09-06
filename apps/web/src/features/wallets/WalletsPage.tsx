/**
 * The wallets screen.
 *
 * A wallet's balance is derived, not stored (see domain/balances.ts), so this
 * screen needs the full transaction set for the profile to compute anything.
 * That is a deliberate exception to "never load everything and filter in the
 * browser": there is no filtering happening here, the whole set is the input
 * the balance formula is defined over, the same way the transactions screen's
 * running total needs the whole filtered set rather than just one page of it.
 */

import { useMemo, useState } from 'react'
import type { Wallet } from '@neraca/domain/types'
import { netWorth, walletBalance } from '@neraca/domain/balances'
import { useRepository, useAsync } from '@/app/repo'
import { useProfile } from '@/app/ProfileProvider'
import { useI18n } from '@/i18n'
import { Badge, Button, EmptyState, Modal, Skeleton } from '@/ui'
import { Block, Hero, Page } from '@/design/primitives'
import { MoneyFigure } from '@/design/Figure'
import { LedgerTable, type LedgerColumn } from '@/design/LedgerTable'
import { WalletForm } from './WalletForm'

export default function WalletsPage() {
  const { t } = useI18n()
  const repo = useRepository()
  const profile = useProfile()

  const [showArchived, setShowArchived] = useState(false)
  const [refreshKey, setRefreshKey] = useState(0)
  const [editing, setEditing] = useState<Wallet | 'new' | null>(null)
  const [deleteTarget, setDeleteTarget] = useState<Wallet | null>(null)
  const [blockedTarget, setBlockedTarget] = useState<Wallet | null>(null)
  const [busy, setBusy] = useState(false)

  const wallets = useAsync(() => repo.listWallets(profile.id), [repo, profile.id, refreshKey])
  // No filter fields set beyond profileId: every row for the profile is what
  // the balance and net worth formulas need to see.
  const transactions = useAsync(
    () => repo.listTransactions({ profileId: profile.id }),
    [repo, profile.id, refreshKey],
  )
  const rates = useAsync(() => repo.listRates(profile.id), [repo, profile.id, refreshKey])

  // Memoised so the fallback empty array is referentially stable across
  // renders while loading, not a fresh array every time that would otherwise
  // needlessly invalidate the useMemo values derived from it below.
  const walletList = useMemo(() => wallets.data ?? [], [wallets.data])
  const txList = useMemo(() => transactions.data ?? [], [transactions.data])
  const rateList = useMemo(() => rates.data ?? [], [rates.data])

  const visibleWallets = useMemo(
    () => walletList.filter((w) => showArchived || !w.archived),
    [walletList, showArchived],
  )

  const total = useMemo(() => {
    if (!wallets.data || !transactions.data || !rates.data) return null
    try {
      return netWorth(walletList, txList, profile.baseCurrency, rateList)
    } catch {
      // A wallet in a currency with no rate on record yet. Reported through
      // the empty-state hint below rather than left as a thrown error, since
      // it is the same "add a rate first" situation as an unconvertible
      // transaction, just surfaced on this screen instead.
      return null
    }
  }, [wallets.data, transactions.data, rates.data, walletList, txList, rateList, profile.baseCurrency])

  const loading = wallets.loading || transactions.loading

  function reload() {
    setRefreshKey((k) => k + 1)
  }

  function handleDeleteClick(wallet: Wallet) {
    const inUse = txList.some((tx) => tx.walletId === wallet.id || tx.toWalletId === wallet.id)
    if (inUse) setBlockedTarget(wallet)
    else setDeleteTarget(wallet)
  }

  async function toggleArchive(wallet: Wallet) {
    setBusy(true)
    try {
      await repo.putWallet({ ...wallet, archived: !wallet.archived })
      reload()
    } finally {
      setBusy(false)
    }
  }

  async function archiveBlocked() {
    if (!blockedTarget) return
    setBusy(true)
    try {
      await repo.putWallet({ ...blockedTarget, archived: true })
      setBlockedTarget(null)
      reload()
    } finally {
      setBusy(false)
    }
  }

  async function confirmDelete() {
    if (!deleteTarget) return
    setBusy(true)
    try {
      await repo.deleteWallet(deleteTarget.id)
      setDeleteTarget(null)
      reload()
    } finally {
      setBusy(false)
    }
  }

  const columns: ReadonlyArray<LedgerColumn<Wallet>> = [
    {
      key: 'name',
      header: t.wallet.fields.name,
      area: 'desc',
      render: (wallet) => (
        <span className="flex min-w-0 flex-col">
          <span className="flex items-center gap-2">
            <span className="truncate text-ink">{wallet.name}</span>
            {wallet.archived && <Badge tone="neutral">{t.wallet.archived}</Badge>}
          </span>
          <span className="text-xs text-ink-faint">
            {t.wallet.kinds[wallet.kind]} · {wallet.currency}
          </span>
        </span>
      ),
    },
    {
      key: 'balance',
      // No currency in the heading: every wallet holds its own, which is why
      // these figures keep their symbols where a single currency column drops
      // them.
      header: t.wallet.balanceLabel,
      area: 'amount',
      align: 'right',
      render: (wallet) => {
        const balance = walletBalance(wallet, txList)
        return <MoneyFigure value={balance} tone={balance.minor < 0 ? 'debit' : 'neutral'} />
      },
    },
    {
      key: 'actions',
      header: <span className="sr-only">{t.common.edit}</span>,
      area: 'balance',
      align: 'right',
      render: (wallet) => (
        <span className="flex flex-wrap justify-end gap-1">
          <Button size="sm" variant="ghost" onClick={() => setEditing(wallet)}>
            {t.common.edit}
          </Button>
          <Button size="sm" variant="ghost" disabled={busy} onClick={() => toggleArchive(wallet)}>
            {wallet.archived ? t.wallet.unarchive : t.wallet.archive}
          </Button>
          <Button size="sm" variant="ghost" onClick={() => handleDeleteClick(wallet)}>
            {t.common.delete}
          </Button>
        </span>
      ),
    },
  ]

  return (
    <Page>
      <header className="flex flex-wrap items-center justify-between gap-3">
        <h1 className="text-h2 leading-tight">{t.wallet.title}</h1>
        <Button onClick={() => setEditing('new')}>{t.wallet.add}</Button>
      </header>

      <div className="mt-8">
        <Hero
          label={t.wallet.totalBalance}
          value={total ? <MoneyFigure value={total} display /> : '-'}
          {...(!total && !loading ? { meta: t.empty.exchangeRates } : {})}
        />
      </div>

      <Block
        title={t.wallet.title}
        action={
          <label className="flex items-center gap-2 text-sm text-ink-muted">
            <input
              type="checkbox"
              checked={showArchived}
              onChange={(event) => setShowArchived(event.target.checked)}
              className="h-4 w-4 accent-[var(--indigo)]"
            />
            {t.wallet.archived}
          </label>
        }
      >
        {loading ? (
          <div className="flex flex-col gap-2 py-2" aria-hidden="true">
            <Skeleton shape="block" className="h-10 w-full" />
            <Skeleton shape="block" className="h-10 w-full" />
          </div>
        ) : visibleWallets.length === 0 ? (
          <EmptyState title={t.empty.wallets} />
        ) : (
          <LedgerTable
            caption={t.wallet.title}
            columns={columns}
            rows={visibleWallets}
            rowKey={(wallet) => wallet.id}
          />
        )}
      </Block>

      <Modal
        open={editing !== null}
        onClose={() => setEditing(null)}
        title={editing === 'new' ? t.wallet.add : t.wallet.edit}
      >
        {editing !== null && (
          <WalletForm
            wallet={editing === 'new' ? undefined : editing}
            existingWallets={walletList}
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
        title={t.wallet.delete}
        footer={
          <>
            <Button variant="secondary" onClick={() => setDeleteTarget(null)}>
              {t.common.cancel}
            </Button>
            <Button variant="danger" loading={busy} onClick={confirmDelete}>
              {t.common.delete}
            </Button>
          </>
        }
      >
        <p className="text-sm text-text">
          {deleteTarget ? t('wallet.deleteConfirm', { name: deleteTarget.name }) : ''}
        </p>
      </Modal>

      <Modal
        open={blockedTarget !== null}
        onClose={() => setBlockedTarget(null)}
        title={t.wallet.delete}
        footer={
          <>
            <Button variant="secondary" onClick={() => setBlockedTarget(null)}>
              {t.common.cancel}
            </Button>
            <Button variant="primary" loading={busy} onClick={archiveBlocked}>
              {t.wallet.archive}
            </Button>
          </>
        }
      >
        <p className="text-sm text-text">
          {blockedTarget ? t('wallet.deleteConfirm', { name: blockedTarget.name }) : ''}
        </p>
      </Modal>
    </Page>
  )
}
