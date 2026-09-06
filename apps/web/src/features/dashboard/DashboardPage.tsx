/**
 * The landing screen: a snapshot of where things stand, not a place to edit
 * anything. Every number here is derived straight from wallets, transactions
 * and budgets already in the repository, the same way the rest of the app
 * derives them, so nothing on this page can drift out of sync with the
 * screens that actually manage that data.
 */

import { useState } from 'react'
import { Link } from 'react-router-dom'
import { format } from 'date-fns'
import { useProfile, useProfiles } from '@/app/ProfileProvider'
import { useRepository, useAsync } from '@/app/repo'
import { blankProfile } from '@/app/ProfileGate'
import { useI18n } from '@/i18n'
import {
  Badge, type BadgeTone, Button, Card, CardBody, CardHeader, CardTitle, EmptyState,
  ProgressBar, Skeleton, staggerStyle, Table, TBody, TD, TH, THead, TR, useCountUp,
} from '@/ui'
import { walletBalance, netWorth } from '@neraca/domain/balances'
import { signedBase } from '@neraca/domain/rates'
import { activeAlerts, type BudgetStatus } from '@neraca/domain/budget'
import { formatMoney, money, negate, sum, type Money } from '@neraca/domain/money'
import { categoryById } from '@neraca/domain/categories'
import type { Transaction } from '@neraca/domain/types'
import type { CurrencyCode } from '@neraca/domain/currency'

const DEMO_BANNER_KEY_PREFIX = 'financialam.dashboard.demoBannerDismissed.'

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
  const { t } = useI18n()

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

  // Computed here, above the loading/error early returns below, because
  // useCountUp is a hook: it has to run on every render in the same order,
  // including the ones where `data` is not back yet. Every domain call here
  // already tolerates the empty arrays that fall out of `data` being
  // undefined (sum([]) and netWorth([]) both settle on zero rather than
  // throwing), so this is safe to run before the loading check.
  const base = profile.baseCurrency
  const wallets = data?.wallets ?? []
  const transactions = data?.transactions ?? []
  const budgets = data?.budgets ?? []
  const rates = data?.rates ?? []
  // Archived wallets keep their history for reports but drop out of the
  // headline totals, the same way an archived wallet drops out of new entry
  // pickers elsewhere in the app.
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
  // signedBase already returns a negative figure for an expense, so the sum
  // is negated back to the positive "amount spent" figure this card shows.
  const expenseTotal = negate(
    sum(monthTxs.filter((tx) => tx.direction === 'expense').map((tx) => signedBase(tx, base)), base),
  )
  // Transfers contribute zero through signedBase, so summing every month
  // transaction here already excludes them from the net figure with no
  // separate filter needed.
  const netTotal = sum(monthTxs.map((tx) => signedBase(tx, base)), base)

  // The four headline figures a reader's eye lands on first, and the only
  // numbers on this page that count up rather than rendering their final
  // value straight away. While `data` is still loading these all animate
  // toward 0; the moment real numbers land, the target changes and each
  // counts up from there, whether that is from 0 or from a stale figure.
  const animatedWorth = useCountUp(worth?.minor ?? 0)
  const animatedIncome = useCountUp(incomeTotal.minor)
  const animatedExpense = useCountUp(expenseTotal.minor)
  const animatedNet = useCountUp(netTotal.minor)

  async function handleStartOwnProfile() {
    setStartingOwn(true)
    try {
      // A demo profile's own name and currency carry over onto the fresh one,
      // since they describe the visitor's own locale, not the sample data.
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
      <div className="p-4 sm:p-6">
        <EmptyState title={t.common.unknownError} action={<Button onClick={reload}>{t.common.retry}</Button>} />
      </div>
    )
  }

  const alerts = activeAlerts(budgets, transactions, base)
  const recent = transactions.slice(0, 10)
  const hasNoTransactions = transactions.length === 0

  return (
    <div className="flex flex-col gap-4 p-4 sm:gap-6 sm:p-6">
      {profile.isDemo && !bannerDismissed && (
        <DemoBanner onDismiss={handleDismissBanner} onStartOwn={handleStartOwnProfile} starting={startingOwn} />
      )}

      <div className="grid grid-cols-1 gap-4 sm:grid-cols-2 lg:grid-cols-3">
        {/*
          `self-start` matters here. A grid row stretches every cell to the
          height of its tallest, which is the wallet list beside this card, so
          without it this card inherited that height and centred one short line
          inside roughly three hundred pixels of empty surface. Sizing to its
          own content is what keeps the row from reading as an unfinished
          layout.
        */}
        <Card className="animate-rise-in self-start lg:col-span-1" style={staggerStyle(0)}>
          <CardHeader>
            <CardTitle>{t.wallet.totalBalance}</CardTitle>
          </CardHeader>
          <CardBody>
            <p className={`text-2xl font-semibold tnum sm:text-3xl ${worth && worth.minor < 0 ? 'text-negative' : 'text-text'}`}>
              {worth ? formatMoney({ minor: Math.round(animatedWorth), currency: worth.currency }) : '-'}
            </p>
          </CardBody>
        </Card>

        <Card className="animate-rise-in sm:col-span-2 lg:col-span-2" style={staggerStyle(1)}>
          <CardHeader>
            <CardTitle>{t.wallet.title}</CardTitle>
          </CardHeader>
          <CardBody>
            {activeWallets.length === 0 ? (
              <p className="text-sm text-muted">{t.empty.wallets}</p>
            ) : (
              <div className="grid grid-cols-1 gap-3 sm:grid-cols-2">
                {activeWallets.map((wallet, index) => (
                  <div
                    key={wallet.id}
                    className="card-interactive animate-rise-in rounded-control border border-line p-3"
                    style={staggerStyle(index)}
                  >
                    <p className="truncate text-sm font-medium text-text">{wallet.name}</p>
                    <p className="text-xs text-muted">{t.wallet.kinds[wallet.kind]}</p>
                    <p className="mt-1 text-lg font-semibold tnum text-text">
                      {formatMoney(walletBalance(wallet, transactions))}
                    </p>
                  </div>
                ))}
              </div>
            )}
          </CardBody>
        </Card>
      </div>

      <div className="grid grid-cols-1 gap-4 sm:grid-cols-3">
        <Card className="animate-rise-in" style={staggerStyle(2)}>
          <CardHeader>
            <CardTitle>{t.report.totalIncome}</CardTitle>
          </CardHeader>
          <CardBody>
            <p className="text-xl font-semibold tnum text-positive">
              {formatMoney({ minor: Math.round(animatedIncome), currency: incomeTotal.currency })}
            </p>
          </CardBody>
        </Card>
        <Card className="animate-rise-in" style={staggerStyle(3)}>
          <CardHeader>
            <CardTitle>{t.report.totalExpense}</CardTitle>
          </CardHeader>
          <CardBody>
            <p className="text-xl font-semibold tnum text-negative">
              {formatMoney({ minor: Math.round(animatedExpense), currency: expenseTotal.currency })}
            </p>
          </CardBody>
        </Card>
        <Card className="animate-rise-in" style={staggerStyle(4)}>
          <CardHeader>
            <CardTitle>{t.report.netBalance}</CardTitle>
          </CardHeader>
          <CardBody>
            <p className={`text-xl font-semibold tnum ${netTotal.minor < 0 ? 'text-negative' : 'text-positive'}`}>
              {formatMoney(
                { minor: Math.round(animatedNet), currency: netTotal.currency },
                { signDisplay: 'always' },
              )}
            </p>
          </CardBody>
        </Card>
      </div>

      {alerts.length > 0 && (
        <Card className="animate-rise-in" style={staggerStyle(5)}>
          <CardHeader>
            <CardTitle>{t.budget.title}</CardTitle>
          </CardHeader>
          <CardBody className="flex flex-col gap-4">
            {alerts.map((status, index) => (
              <BudgetAlertRow key={status.budget.id} status={status} index={index} />
            ))}
          </CardBody>
        </Card>
      )}

      <Card className="animate-rise-in" style={staggerStyle(6)}>
        <CardHeader>
          <CardTitle>{t.transaction.title}</CardTitle>
          <Link to="/transactions" className="text-sm font-medium text-accent hover:underline">
            {t.nav.transactions}
          </Link>
        </CardHeader>
        <CardBody>
          {hasNoTransactions ? (
            <EmptyState
              title={t.empty.transactions}
              action={
                <Link to="/transactions">
                  <Button>{t.transaction.add}</Button>
                </Link>
              }
            />
          ) : (
            <Table>
              <THead>
                <TR>
                  <TH>{t.transaction.fields.date}</TH>
                  <TH>{t.transaction.fields.category}</TH>
                  <TH>{t.transaction.fields.description}</TH>
                  <TH className="text-right">{t.transaction.fields.amount}</TH>
                </TR>
              </THead>
              <TBody>
                {recent.map((tx, index) => (
                  <RecentTransactionRow key={tx.id} tx={tx} baseCurrency={base} index={index} />
                ))}
              </TBody>
            </Table>
          )}
        </CardBody>
      </Card>
    </div>
  )
}

function DashboardSkeleton() {
  return (
    <div className="flex flex-col gap-4 p-4 sm:gap-6 sm:p-6" aria-hidden="true">
      <Skeleton shape="block" className="h-24 w-full" />
      <div className="grid grid-cols-1 gap-4 sm:grid-cols-3">
        <Skeleton shape="block" className="h-28 w-full" />
        <Skeleton shape="block" className="h-28 w-full" />
        <Skeleton shape="block" className="h-28 w-full" />
      </div>
      <Skeleton shape="block" className="h-48 w-full" />
      <Skeleton shape="block" className="h-64 w-full" />
    </div>
  )
}

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
    <div className="flex flex-col gap-2 rounded-card border border-line bg-accent-soft px-4 py-3 sm:flex-row sm:items-center sm:justify-between">
      <p className="text-sm text-text">{t.demo.bannerText}</p>
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
  const tone: BadgeTone = over ? 'negative' : 'warning'
  const barClass = over ? 'bg-negative' : 'bg-warning'
  const pct = Math.min(100, Math.round(status.fraction * 100))

  return (
    <div className="animate-rise-in flex flex-col gap-1.5" style={staggerStyle(index)}>
      <div className="flex flex-wrap items-center justify-between gap-2">
        <span className="flex flex-wrap items-baseline gap-x-2 text-sm font-medium text-text">
          {label}
          <span className="text-xs font-normal text-faint">{status.budget.periodKey}</span>
        </span>
        <Badge tone={tone}>
          {over ? t('budget.overLimit', { amount: formatMoney(negate(status.remaining)) }) : t.budget.nearLimit}
        </Badge>
      </div>
      <p className="text-xs text-muted">
        {t('budget.spentOfLimit', { spent: formatMoney(status.spent), limit: formatMoney(status.limit) })}
      </p>
      <ProgressBar value={pct} label={label} barClassName={barClass} />
    </div>
  )
}

function RecentTransactionRow({
  tx,
  baseCurrency,
  index,
}: {
  tx: Transaction
  baseCurrency: CurrencyCode
  index: number
}) {
  const { t, formatDate, labelFor } = useI18n()
  const category = categoryById(tx.categoryId)
  const isTransfer = tx.direction === 'transfer'
  const label = isTransfer ? t.transaction.directions.transfer : category ? labelFor(category) : tx.categoryId
  const signed = signedBase(tx, baseCurrency)
  const amountClass = isTransfer ? 'text-text' : signed.minor < 0 ? 'text-negative' : 'text-positive'
  // A transfer nets to zero in the base currency through signedBase (by
  // design, see rates.ts), so the row shows the actual amount moved instead
  // of a figure that would otherwise always read as zero.
  const displayAmount = isTransfer ? money(tx.amount, tx.currency) : signed

  return (
    <TR className="animate-rise-in" style={staggerStyle(index)}>
      <TD>{formatDate(tx.date)}</TD>
      <TD>{label}</TD>
      <TD className="max-w-[14rem] truncate">{tx.description || '-'}</TD>
      <TD numeric className={amountClass}>
        {formatMoney(displayAmount, { signDisplay: isTransfer ? 'auto' : 'always' })}
      </TD>
    </TR>
  )
}
