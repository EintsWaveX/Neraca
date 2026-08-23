import { lazy, Suspense, type ReactNode } from 'react'
import { createBrowserRouter, RouterProvider } from 'react-router-dom'
import { Skeleton } from './ui'
import { ProfileGate } from './app/ProfileGate'
import { Layout } from './app/Layout'

// Every feature page is lazy loaded so the first paint only pays for the
// dashboard, and so this file can be finished and type-check clean while the
// other pages are still being written in parallel by other agents.
const DashboardPage = lazy(() => import('./features/dashboard/DashboardPage'))
const TransactionsPage = lazy(() => import('./features/transactions/TransactionsPage'))
const WalletsPage = lazy(() => import('./features/wallets/WalletsPage'))
const BudgetsPage = lazy(() => import('./features/budgets/BudgetsPage'))
const RecurringPage = lazy(() => import('./features/recurring/RecurringPage'))
const ReportsPage = lazy(() => import('./features/reports/ReportsPage'))
const SettingsPage = lazy(() => import('./features/settings/SettingsPage'))

/** Shown while a lazy page chunk is loading, and while a page's own first async read is in flight. */
function PageSkeleton() {
  return (
    <div className="flex flex-col gap-4 p-4 sm:p-6" aria-hidden="true">
      <Skeleton shape="block" className="h-8 w-48" />
      <Skeleton shape="block" className="h-32 w-full" />
      <Skeleton shape="block" className="h-64 w-full" />
    </div>
  )
}

function withSuspense(element: ReactNode) {
  return <Suspense fallback={<PageSkeleton />}>{element}</Suspense>
}

const router = createBrowserRouter(
  [
    {
      // ProfileGate wraps the whole app: it decides between the profile
      // picker, the PIN screen and the real shell, and only mounts Layout
      // (with its Outlet of feature routes) once a profile is unlocked.
      element: (
        <ProfileGate>
          <Layout />
        </ProfileGate>
      ),
      children: [
        { path: '/', element: withSuspense(<DashboardPage />) },
        { path: '/transactions', element: withSuspense(<TransactionsPage />) },
        { path: '/wallets', element: withSuspense(<WalletsPage />) },
        { path: '/budgets', element: withSuspense(<BudgetsPage />) },
        { path: '/recurring', element: withSuspense(<RecurringPage />) },
        { path: '/reports', element: withSuspense(<ReportsPage />) },
        { path: '/settings', element: withSuspense(<SettingsPage />) },
      ],
    },
  ],
  // The app is served from a GitHub Pages project subpath, so every route
  // and every history push has to be relative to that subpath, not the
  // domain root.
  { basename: import.meta.env.BASE_URL },
)

export default function App() {
  return <RouterProvider router={router} />
}
