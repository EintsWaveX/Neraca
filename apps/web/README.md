# Neraca, web build

The browser build. React, TypeScript, Vite and Tailwind, with every byte of
data living in the visitor's own browser through IndexedDB. There is no server
and no account.

For what the application does, why it exists alongside the C console build in
`cli/`, and the decisions behind it, see the [root readme](../../README.md) and
[CLAUDE.md](../../CLAUDE.md).

## Running it

Every command belongs at the repository root, not here: this is one workspace of
several, and the scripts reach across all of them.

```
npm install
npm run dev
```

## Verification

`npm run verify` at the root is the release gate, and the deployment runs the
same command, so a failure blocks the release rather than reaching the live
site. `npm run verify:full` adds the end to end suite, which is not part of the
deploy gate because it needs a browser download.

## Layout

| Path | What lives there |
|---|---|
| `src/data/` | The `Repository` interface, its IndexedDB implementation, the PIN hashing, and the seeded demo profile |
| `src/design/` | The Passbook design system: the ledger table, the figures, the page primitives, and the specimen page that exercises them |
| `src/ui/` | The component library. Tokens are defined in `src/index.css` and never hardcoded |
| `src/features/` | One folder per screen |
| `src/i18n/` | English and Indonesian dictionaries, kept in identical shape by a test |
| `src/app/` | Providers, routing shell, profile gate, update prompt |

The business rules are not here. They live in `packages/domain`, as a package
rather than a folder so that the dependency points one way and nothing in them
can reach for React or for storage by accident.

## Deployment

Deployed to Vercel through its own Git integration, gated by the `buildCommand`
in the root `vercel.json`, which runs `npm run verify` before anything ships.
Every pull request gets its own preview URL on the same terms.

The two workflows in `.github/workflows/` would do this better, as pull request
checks rather than a build log, but they are dormant behind a billing lock.
Each carries the note explaining how to restore it. Do not enable both paths at
once.

The Vercel project builds from the repository root, with `outputDirectory` set
to `apps/web/dist`.
