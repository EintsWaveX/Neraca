/**
 * PIN hashing.
 *
 * Read this before trusting it with more than it offers: the PIN is a
 * convenience lock for a device shared with other people, not encryption of
 * the data. Every profile, wallet and transaction in this app lives in the
 * visitor's own IndexedDB in plain, readable form, whether or not a PIN is
 * set. Anyone who opens the browser's developer tools and looks at Application
 * storage can read all of it directly, PIN or no PIN. Hashing only keeps the
 * digits themselves out of the database as plain text; it does nothing to
 * protect anything else a profile owns.
 */

/**
 * OWASP's current floor for PBKDF2-SHA256 is 600000 iterations, but that
 * figure targets a server verifying a login against a stored credential. This
 * is a four to eight digit device lock re-checked on every unlock of a
 * personal finance app running on whatever phone or laptop happens to be
 * around, so 210000 (roughly the older 2023 OWASP minimum) is used instead to
 * keep unlocking from stalling on modest hardware, while still costing far
 * more than a single unsalted SHA-256 pass would.
 */
const ITERATIONS = 210_000
const SALT_BYTES = 16
const HASH_BITS = 256

function toBase64(bytes: Uint8Array<ArrayBuffer>): string {
  let binary = ''
  for (const byte of bytes) binary += String.fromCharCode(byte)
  return btoa(binary)
}

function fromBase64(value: string): Uint8Array<ArrayBuffer> {
  const binary = atob(value)
  const bytes = new Uint8Array(binary.length)
  for (let i = 0; i < binary.length; i++) bytes[i] = binary.charCodeAt(i)
  return bytes
}

// Typed explicitly as `Uint8Array<ArrayBuffer>` rather than the bare
// `Uint8Array` TypeScript would otherwise infer, because `crypto.subtle`'s
// DOM types require a view backed by a real `ArrayBuffer`, not the more
// general `ArrayBufferLike` a plain `Uint8Array` annotation allows (which
// also covers a `SharedArrayBuffer`). Every caller here constructs its bytes
// with `new Uint8Array(n)`, which is always backed by a fresh `ArrayBuffer`,
// so the annotation only makes an already true fact visible to the compiler.
async function derive(pin: string, salt: Uint8Array<ArrayBuffer>): Promise<Uint8Array<ArrayBuffer>> {
  const keyMaterial = await crypto.subtle.importKey(
    'raw',
    new TextEncoder().encode(pin),
    'PBKDF2',
    false,
    ['deriveBits'],
  )
  const bits = await crypto.subtle.deriveBits(
    // `salt` is a Uint8Array, and TypeScript's DOM lib types this parameter
    // as BufferSource, which a Uint8Array satisfies at runtime; it is spelled
    // out as a cast free expression here on purpose so a stricter future lib
    // update would catch a real mismatch instead of one hidden behind `as`.
    { name: 'PBKDF2', salt, iterations: ITERATIONS, hash: 'SHA-256' },
    keyMaterial,
    HASH_BITS,
  )
  return new Uint8Array(bits)
}

export async function hashPin(pin: string): Promise<{ hash: string; salt: string }> {
  const salt = crypto.getRandomValues(new Uint8Array(SALT_BYTES))
  const digest = await derive(pin, salt)
  return { hash: toBase64(digest), salt: toBase64(salt) }
}

export async function verifyPin(pin: string, hash: string, salt: string): Promise<boolean> {
  const digest = await derive(pin, fromBase64(salt))
  const expected = fromBase64(hash)

  // A length mismatch means a corrupted or foreign value, not a wrong PIN;
  // it is fine to return early here since no attacker model depends on this
  // path taking constant time; only the digit-by-digit comparison below does.
  if (digest.length !== expected.length) return false

  // Constant time comparison so a wrong guess close to the real PIN cannot be
  // told apart, by timing, from one that is nowhere near it. There is no
  // realistic attacker for a shared-device lock over unencrypted data, but
  // getting this comparison right costs nothing, so there is no reason to
  // fall back to a short circuiting `===` on the digest bytes.
  let diff = 0
  for (let i = 0; i < digest.length; i++) {
    // Safe to assert: the loop is bounded by `digest.length`, and the lengths
    // were just checked equal, so both arrays have a defined byte at `i`.
    diff |= digest[i]! ^ expected[i]!
  }
  return diff === 0
}
