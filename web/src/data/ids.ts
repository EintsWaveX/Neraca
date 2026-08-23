/**
 * Id generation.
 *
 * Ids are prefixed with the entity kind (`txn_`, `wal_`, and so on) so a
 * value pulled up in DevTools or a stack trace is self describing. Nothing in
 * the schema parses the prefix back out; it is for a human reading the data,
 * not for the code.
 *
 * "Sortable" here means a plain string comparison of two ids roughly follows
 * creation order, because each id starts with a base36 timestamp. That is
 * useful for eyeballing data in DevTools, but nothing in the app relies on it
 * for correctness: every list that needs a real ordering sorts on `date` or
 * `createdAt` explicitly, since two ids can still tie within the same
 * millisecond.
 */

/**
 * Breaks ties between ids created in the same millisecond. A plain in memory
 * counter is enough because the only thing it needs to do is keep same-tab,
 * same-millisecond ids apart; it does not need to survive a reload or be
 * shared across tabs.
 */
let sequence = 0

/**
 * `crypto.randomUUID` covers every browser this app ships to, but IndexedDB
 * itself has been around for longer than that method has, so a runtime that
 * otherwise runs the app fine could still be missing it. `getRandomValues` is
 * the older, more widely supported half of the same API, so it is what the
 * fallback leans on rather than reaching for `Math.random`, which is not
 * meant to be collision resistant.
 */
function randomToken(): string {
  const cryptoObj = globalThis.crypto
  if (cryptoObj && typeof cryptoObj.randomUUID === 'function') {
    return cryptoObj.randomUUID().replace(/-/g, '')
  }
  if (cryptoObj && typeof cryptoObj.getRandomValues === 'function') {
    const bytes = cryptoObj.getRandomValues(new Uint8Array(16))
    return Array.from(bytes, (byte) => byte.toString(16).padStart(2, '0')).join('')
  }
  // No WebCrypto at all. This should not happen on anything the app actually
  // targets, but a slightly weaker id is better than a thrown error while
  // recording a transaction.
  return `${Math.random().toString(16).slice(2)}${Math.random().toString(16).slice(2)}`
}

export function newId(prefix: string): string {
  const timestamp = Date.now().toString(36)
  const tie = (sequence++).toString(36)
  return `${prefix}_${timestamp}_${tie}_${randomToken()}`
}

export function nowIso(): string {
  return new Date().toISOString()
}
