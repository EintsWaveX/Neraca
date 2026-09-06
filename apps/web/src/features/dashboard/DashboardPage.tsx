/**
 * The landing screen: a snapshot of where things stand, not a place to edit
 * anything. Every number here is derived straight from wallets, transactions
 * and budgets already in the repository, the same way the rest of the app
 * derives them, so nothing on this page can drift out of sync with the
 * screens that actually manage that data.
 *
 * Laid out as a passbook rather than a dashboard. The old version opened with
 * a tile for the total balance beside a grid of wallet tiles, which left a
 * third of the first screen empty and gave a coffee the same visual weight as
 * a month of net worth. Here one figure answers the question you opened the
 * app to ask, and everything under it is a ruled list feeding that figure.
 */

import { useState } from 'react'
import { Link } from 'react-router-dom'
import { format } from 'date-fns'
import { useProfile, useProfiles } from '@/app/ProfileProvider'
import { useRepository, useAsync } from '@/app/repo'
import { blankProfile } from '@/app/ProfileGate'
import { useI18n } from '@/i18n'
import { Button, EmptyState, ProgressBar, Skeleton, useCountUp } from '@/ui'
import { Block, Hero, Page, RuledRow } from '@/design/primitives'
import { Figure, MoneyFigure } from '@/design/Figure'
import { LedgerTable, type LedgerColumn } from '@/design/LedgerTable'
import { walletBalance, netWorth } from '@neraca/domain/balances'
import { signedBase } from '@neraca/domain/rates'
import { activeAlerts, type BudgetStatus } from '@neraca/domain/budget'
import { formatMoney, money, negate, sum, type Money } from '@neraca/domain/money'
import { categoryById } from '@neraca/domain/categories'
import type { Transaction, Wallet } from '@neraca/domain/types'

const DEMO_BANNER_KEY_PREFIX = 'neraca.dashboard.demoBannerDismissed.'

function readDismissed(profileId: string): boolean {
  try {
    return localStorage.getItem(DEMO_BANNER_KEY_PREFIX + profileId) === '1'
  } catch {
    return false
  }
}

function storeDismissed(profileId: string): void {
  try {
    localStorage.setItem(DEMO_BANNER_KEY_PREFIX + profileId, '1')
  } catch {
    // Losing the dismissal is a minor inconvenience: the banner just shows again next visit.
  }
}

export default function DashboardPage() {
  const profile = useProfile()
  const { refresh, select } = useProfiles()
  const repo = useRepository()
  const { t, formatDate, labelFor } = useI18n()

  const { data, loading, error, reload } = useAsync(async () => {
    const [wallets, transactions, budgets, rates] = await Promise.all([
      repo.listWallets(profile.id),
      repo.listTransactions({ profileId: profile.id, sort: 'date-desc' }),
      repo.listBudgets(profile.id),
      repo.listRates(profile.id),
    ])
    return { wallets, transactions, budgets, rates }
  }, [repo, profile.id])

  const [bannerDismissed, setBannerDismissed] = useState(() => readDismissed(profile.id))
  const [startingOwn, setStartingOwn] = useState(false)

  // Computed above the loading and error early returns below, because
  // useCountUp is a hook and has to run on every render in the same order,
  // including the ones where `data` is not back yet. Every domain call here
  // already tolerates the empty arrays that fall out of `data` being
  // undefined, so this is safe to run before the loading check.
  const base = profile.baseCurrency
  const wallets = data?.wallets ?? []
  const transactions = data?.transactions ?? []
  const budgets = data?.budgets ?? []
  const rates = data?.rates ?? []
  // Archived wallets keep their history for reports but drop out of the
  // headline totals, the same way they drop out of new entry pickers.
  const activeWallets = wallets.filter((wallet) => !wallet.archived)

  let worth: Money | null = null
  try {
    worth = netWorth(activeWallets, transactions, base, rates)
  } catch {
    // Missing exchange rate for one wallet's currency. Better to show a dash
    // than to take the whole dashboard down over one figure.
    worth = null
  }

  const thisMonthPrefix = format(new Date(), 'yyyy-MM')
  const monthTxs = transactions.filter((tx) => tx.date.startsWith(thisMonthPrefix))
  const incomeTotal = sum(
    monthTxs.filter((tx) => tx.direction === 'income').map((tx) => signedBase(tx, base)),
    base,
  )
  // signedBase already returns a negative figure for an expense, so the sum is
  // negated back to the positive "amount spent" figure this row shows.
  const expenseTotal = negate(
    sum(monthTxs.filter((tx) => tx.direction === 'expense').map((tx) => signedBase(tx, base)), base),
  )
  // Transfers contribute zero through signedBase, so summing every month
  // transaction already excludes them from the net with no separate filter.
  const netTotal = sum(monthTxs.map((tx) => signedBase(tx, base)), base)

  // The one figure the page exists for is the only number that counts up.
  // Animating four at once turned the first paint into a slot machine.
  const animatedWorth = useCountUp(worth?.minor ?? 0)

  async function handleStartOwnProfile() {
    setStartingOwn(true)
    try {
      // A demo profile's own name and currency carry over onto the fresh one,
      // since they describe the visitor's locale, not the sample data.
      const created = blankProfile(profile.displayName, profile.baseCurrency, profile.locale)
      await repo.putProfile(created)
      await refresh()
      select(created.id)
    } finally {
      setStartingOwn(false)
    }
  }

  function handleDismissBanner() {
    setBannerDismissed(true)
    storeDismissed(profile.id)
  }

  if (loading) return <DashboardSkeleton />

  if (error || !data) {
    return (
      <Page>
        <EmptyState title={t.common.unknownError} action={<Button onClick={reload}>{t.common.retry}</Button>} />
      </Page>
    )
  }

  const alerts = activeAlerts(budgets, transactions, base)
  const recent = transactions.slice(0, 10)

  const walletColumns: ReadonlyArray<LedgerColumn<Wallet>> = [
    {
      key: 'name',
      header: t.wallet.fields.name,
      area: 'desc',
      render: (wallet) => (
        <span className="flex flex-wrap items-baseline gap-x-2">
          <span className="text-ink">{wallet.name}</span>
          <span className="text-xs text-ink-faint">{t.wallet.kinds[wallet.kind]}</span>
        </span>
      ),
    },
    {
      key: 'balance',
      header: t.wallet.balance,
      area: 'amount',
      align: 'right',
      render: (wallet) => <MoneyFigure value={walletBalance(wallet, transactions)} />,
    },
  ]

  const recentColumns: ReadonlyArray<LedgerColumn<Transaction>> = [
    {
      key: 'date',
      header: t.transaction.fields.date,
      area: 'date',
      render: (tx) => <Figure className="text-sm text-ink-muted">{formatDate(tx.date)}</Figure>,
    },
    {
      key: 'description',
      header: t.transaction.fields.description,
      area: 'desc',
      render: (tx) => {
        const category = categoryById(tx.categoryId)
        const label =
          tx.direction === 'transfer'
            ? t.transaction.directions.transfer
            : category
              ? labelFor(category)
              : tx.categoryId
        return (
          <span className="flex min-w-0 flex-wrap items-baseline gap-x-2">
            <span className="truncate text-ink">{tx.description || label}</span>
            <span className="text-xs text-ink-faint">{label}</span>
          </span>
        )
      },
    },
    {
      key: 'amount',
      header: `${t.transaction.fields.amount} (${base})`,
      area: 'amount',
      align: 'right',
      render: (tx) => {
        const isTransfer = tx.direction === 'transfer'
        // A transfer nets to zero in the base currency through signedBase, by
        // design, so the row shows the amount actually moved rather than a
        // figure that would always read as nothing happened.
        const displayAmount = isTransfer ? money(tx.amount, tx.currency) : signedBase(tx, base)
        return (
          <MoneyFigure
            value={displayAmount}
            tone={isTransfer ? 'neutral' : 'auto'}
            signDisplay={isTransfer ? 'auto' : 'always'}
            showSymbol={isTransfer && tx.currency !== base}
          />
        )
      },
    },
  ]

  return (
    <Page>
      {profile.isDemo && !bannerDismissed && (
        <DemoBanner onDismiss={handleDismissBanner} onStartOwn={handleStartOwnProfile} starting={startingOwn} />
      )}

      <Hero
        label={t.wallet.totalBalance}
        value={
          worth ? (
            <MoneyFigure
              value={{ minor: Math.round(animatedWorth), currency: worth.currency }}
              display
              tone={worth.minor < 0 ? 'debit' : 'neutral'}
            />
          ) : (
            '-'
          )
        }
        meta={
          <>
            {t.common.thisMonth}
            {': '}
            <MoneyFigure value={netTotal} tone="auto" signDisplay="always" className="text-sm" />
          </>
        }
      />

      <Block
        title={t.wallet.title}
        action={
          <Link to="/wallets" className="text-sm text-indigo hover:underline">
            {t.nav.wallets}
          </Link>
        }
      >
        {activeWallets.length === 0 ? (
          <p className="py-4 text-sm text-ink-muted">{t.empty.wallets}</p>
        ) : (
          <LedgerTable
            caption={t.wallet.title}
            columns={walletColumns}
            rows={activeWallets}
            rowKey={(wallet) => wallet.id}
          />
        )}
      </Block>

      <Block title={t.common.thisMonth}>
        <RuledRow
          index={0}
          label={t.report.totalIncome}
          value={<MoneyFigure value={incomeTotal} tone="credit" />}
        />
        <RuledRow
          index={1}
          label={t.report.totalExpense}
          value={<MoneyFigure value={expenseTotal} tone="debit" />}
        />
        <RuledRow
          index={2}
          className="ledger-total"
          label={<span className="font-medium">{t.report.netBalance}</span>}
          value={<MoneyFigure value={netTotal} tone="auto" signDisplay="always" />}
        />
      </Block>

      {alerts.length > 0 && (
        <Block
          title={t.budget.title}
          action={
            <Link to="/budgets" className="text-sm text-indigo hover:underline">
              {t.nav.budgets}
            </Link>
          }
        >
          {alerts.map((status, index) => (
            <BudgetAlertRow key={status.budget.id} status={status} index={index} />
          ))}
        </Block>
      )}

      <Block
        title={t.transaction.title}
        action={
          <Link to="/transactions" className="text-sm text-indigo hover:underline">
            {t.nav.transactions}
          </Link>
        }
      >
        {transactions.length === 0 ? (
          <EmptyState
            title={t.empty.transactions}
            action={
              <Link to="/transactions">
                <Button>{t.transaction.add}</Button>
              </Link>
            }
          />
        ) : (
          <LedgerTable
            caption={t.transaction.title}
            columns={recentColumns}
            rows={recent}
            rowKey={(tx) => tx.id}
          />
        )}
      </Block>
    </Page>
  )
}

function DashboardSkeleton() {
  return (
    <Page>
      <div aria-hidden="true" className="flex flex-col gap-8">
        <div className="spine flex flex-col gap-2 pl-4 sm:pl-6">
          <Skeleton shape="text" className="h-4 w-28" />
          <Skeleton shape="block" className="h-12 w-72 max-w-full" />
        </div>
        <Skeleton shape="block" className="h-48 w-full" />
        <Skeleton shape="block" className="h-32 w-full" />
        <Skeleton shape="block" className="h-64 w-full" />
      </div>
    </Page>
  )
}

/**
 * The note explaining that this is sample data.
 *
 * A marginal note against an indigo rule rather than a filled panel: the
 * first thing a visitor sees should be their own balance, not a coloured
 * band telling them it is not really theirs.
 */
function DemoBanner({
  onDismiss,
  onStartOwn,
  starting,
}: {
  onDismiss: () => void
  onStartOwn: () => void
  starting: boolean
}) {
  const { t } = useI18n()
  return (
    <div className="mb-8 flex flex-col gap-2 border-l-2 border-indigo bg-paper-sunken py-3 pl-4 pr-3 sm:flex-row sm:items-center sm:justify-between">
      <p className="text-sm text-ink-muted">{t.demo.bannerText}</p>
      <div className="flex shrink-0 items-center gap-2">
        <Button size="sm" variant="secondary" onClick={onStartOwn} loading={starting}>
          {t.profile.createNew}
        </Button>
        <Button size="sm" variant="ghost" aria-label={t.common.close} onClick={onDismiss}>
          {t.common.close}
        </Button>
      </div>
    </div>
  )
}

function BudgetAlertRow({ status, index }: { status: BudgetStatus; index: number }) {
  const { t, labelFor } = useI18n()
  const category = status.budget.categoryId ? categoryById(status.budget.categoryId) : undefined
  const label = category ? labelFor(category) : t.budget.fields.allCategories
  const over = status.state === 'over'
  const pct = Math.min(100, Math.round(status.fraction * 100))

  return (
    <RuledRow
      index={index}
      label={label}
      note={status.budget.periodKey}
      value={
        <span className="text-sm">
          <MoneyFigure value={status.spent} tone={over ? 'debit' : 'neutral'} showSymbol={false} />
          <span className="text-ink-faint"> / </span>
          <MoneyFigure value={status.limit} className="text-ink-muted" showSymbol={false} />
        </span>
      }
      below={
        <div className="flex items-center gap-3">
          <ProgressBar
            value={pct}
            label={label}
            barClassName={over ? 'bg-debit' : 'bg-stamp'}
            className="flex-1"
          />
          <span className="shrink-0 text-xs text-ink-muted">
            {over
              ? t('budget.overLimit', { amount: formatMoney(negate(status.remaining)) })
              : t.budget.nearLimit}
          </span>
        </div>
      }
    />
  )
}
