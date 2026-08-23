/**
 * Repository access for the React tree.
 *
 * The provider takes an implementation rather than reaching for the IndexedDB
 * one directly, so tests and stories can pass an in-memory double without any
 * mocking machinery. Nothing in the component tree imports `idb.ts`.
 */

import { createContext, useContext, useEffect, useState, type ReactNode } from 'react'
import type { Repository } from '@/data/repository'
import { getRepository } from '@/data/idb'

const RepositoryContext = createContext<Repository | null>(null)

export function RepositoryProvider({
  children,
  repository,
}: {
  children: ReactNode
  repository?: Repository
}) {
  const [value] = useState<Repository>(() => repository ?? getRepository())
  return <RepositoryContext.Provider value={value}>{children}</RepositoryContext.Provider>
}

export function useRepository(): Repository {
  const repo = useContext(RepositoryContext)
  if (!repo) throw new Error('useRepository must be used inside a RepositoryProvider')
  return repo
}

/**
 * Run an async read and track its state.
 *
 * Deliberately small. A data fetching library would be more capable, but every
 * read here is a local IndexedDB call that resolves in under a millisecond, so
 * the caching and retry machinery would be weight with nothing to carry. The
 * `deps` array works like the one on `useEffect`.
 */
export function useAsync<T>(
  run: () => Promise<T>,
  deps: readonly unknown[],
): { data: T | undefined; loading: boolean; error: Error | null; reload: () => void } {
  const [data, setData] = useState<T>()
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState<Error | null>(null)
  const [nonce, setNonce] = useState(0)

  useEffect(() => {
    // Guards against a slow earlier read resolving after a newer one and
    // overwriting fresher data with stale data.
    let live = true
    setLoading(true)
    setError(null)
    run().then(
      (result) => {
        if (!live) return
        setData(result)
        setLoading(false)
      },
      (cause: unknown) => {
        if (!live) return
        setError(cause instanceof Error ? cause : new Error(String(cause)))
        setLoading(false)
      },
    )
    return () => {
      live = false
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [...deps, nonce])

  return { data, loading, error, reload: () => setNonce((n) => n + 1) }
}
