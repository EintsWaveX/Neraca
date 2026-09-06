# FinancialAM, web build

The browser build of FinancialAM. React, TypeScript, Vite and Tailwind, with
every byte of data living in the visitor's own browser through IndexedDB. There
is no server and no account.

For what the application does, why it exists alongside the C console build in
`cli/`, and the decisions behind it, see the [root readme](../README.md) and
[CLAUDE.md](../CLAUDE.md).

## Running it

```
npm install
npm run dev
```

## Verification

All three have to pass before anything ships. The deploy workflows run them
ahead of the deploy, so a failure blocks the release rather than reaching the
live site.

```
npx tsc -p tsconfig.app.json --noEmit    # zero errors, strict mode
npx vitest run                            # all green
npm run build                             # must succeed
```

`npm run lint` runs Oxlint on top of those. It is not a release gate, but new
warnings are worth reading rather than ignoring.

## Layout

| Path | What lives there |
|---|---|
| `src/domain/` | The business rules. Plain TypeScript, no React and no storage, so the rules can be tested directly |
| `src/data/` | The `Repository` interface, its IndexedDB implementation, and the seeded demo profile |
| `src/ui/` | The design system. Tokens are defined in `src/index.css` and never hardcoded |
| `src/features/` | One folder per screen |
| `src/i18n/` | English and Indonesian dictionaries, kept in identical shape by a test |
| `src/app/` | Providers, routing shell, profile gate |

## Deployment

Deployed to Vercel from `.github/workflows/vercel-production.yml` on a push to
`main`, and to a preview URL from `.github/workflows/vercel-preview.yml` on a
pull request. Vercel's own Git integration is switched off in `vercel.json` so
those workflows are the only path to a deploy, which is what lets the
verification gates actually block one.

The Vercel project's Root Directory is set to `web`.
