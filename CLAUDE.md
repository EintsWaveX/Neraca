# Working agreement for this repository

This file is the standing brief for any AI coding agent working on FinancialAM,
and it doubles as the record of what was decided and why. It is checked in on
purpose. Anyone reading the repository should be able to see which constraints
came from me and which choices the agent made inside them.

## What this project is

Two builds of one personal finance program.

`cli/` holds the original C console application, 8,101 lines in the Windows
build and 8,119 in the POSIX one, and it is a
maintained build rather than an archive. `web/` holds the browser version. The
web build is not a port of the terminal interface: the domain, the data model
and the business rules carry over, the arrow-key menus and the Windows message
boxes do not.

A business rule corrected in one build gets corrected in the other. Bugs found
while specifying the rewrite get fixed in the C as well, because both builds are
meant to work.

## Decisions I made, which are not open for the agent to revisit

These were settled before any code was written. An agent that thinks one of them
is wrong should say so and wait, not act.

1. **Client side only.** Data lives in the visitor's own browser through
   IndexedDB. There is no server. This is what allows the app to be a static
   page on a static host at no cost and with nothing to operate. Persistence sits
   behind the `Repository` interface in `src/data/repository.ts` so a server
   backed implementation is a drop in replacement later, but adding one now is
   out of scope.
2. **React, TypeScript, Vite, Tailwind.** Chosen because it is the stack the
   roles I am applying for actually use. TypeScript is not decoration here: the
   app does money arithmetic across currencies, and the types are load bearing.
3. **Its own repository, its own deployment.** Deployed to Vercel at
   `financial-am.vercel.app`, not folded into the portfolio repository. This
   started on GitHub Pages and moved once the app wanted things a repository
   subpath makes awkward: a root `base`, so the service worker scope and the
   manifest `start_url` are the whole origin rather than a folder inside it,
   real SPA rewrites in place of a copied `404.html`, and per path cache
   headers. Deploys run through Vercel's own Git integration, gated by the
   `buildCommand` in `web/vercel.json`.
4. **Rebuilt as a product, not ported as coursework.** The unfinished parts of
   the C version get finished rather than faithfully reproduced. The bugs get
   fixed rather than preserved.
5. **Local profiles with a PIN, not real accounts.** The C version had
   registration, login and recovery backed by Caesar ciphered text files. That
   was never security. A browser app with no server cannot honestly claim to be
   either, so the PIN is described as a convenience lock over a shared device
   and nothing more. Do not write copy that implies the stored data is
   encrypted, because it is not.
6. **English by default, Indonesian available.** Both locales are real. The C
   original was bilingual and dropping that would be a step backwards.
7. **Multi currency with conversion.** Each transaction stores the rate that
   applied on its own date. Reports convert using that stored rate and never a
   fresh lookup, because re-converting last year's purchase at today's rate
   would silently rewrite history.
8. **A seeded demo profile on first visit.** Someone opening the link should
   land in a populated application, not an empty state.

## House rules

- **Money is never a float.** Amounts are integer minor units plus a currency
  code. Note that rupiah and yen have zero minor units while dollars have two,
  so anything converting between currencies has to go through
  `minorUnitScale`. All arithmetic goes through `src/domain/money.ts`.
- **The domain layer stays pure.** Everything under `src/domain/` is plain
  TypeScript with no React import and no storage access, so the rules can be
  tested directly. If a rule is hard to test, it is in the wrong layer.
- **Colours come from the design tokens** defined in `src/index.css`. Never
  hardcode a hex value or a Tailwind palette colour, because the same system is
  shared with four sibling applications and both themes have to keep working.
- **Accessibility is part of done**, not a later pass. Keyboard operation,
  labels, roles and visible focus.
- **No em dashes and no en dashes**, anywhere, including code comments and
  translated strings. Restructure the sentence instead of swapping the
  punctuation.
- **Comments explain why, not what.** A comment restating the line below it is
  noise. A comment explaining a decision that looks wrong until you know the
  reason is worth writing.

## How the work was actually split

I set the constraints above, reviewed the output, and corrected it where it was
wrong. Some of what was corrected, kept here because the corrections are the
interesting part:

- The first money parser read `1.500.000,75` in a zero decimal currency as
  150,000,075 rupiah, because it checked the currency before deciding which
  separator was a decimal point. Caught by a test that had been written to
  assert the buggy behaviour rather than the correct one, which is its own
  lesson about tests that only document what the code already does.
- Agents were briefed to treat the surveys of the original C program as the
  specification, and to fix the identified bugs rather than reproduce them.

## Verification that must pass before anything ships

```
cd web
npx tsc -p tsconfig.app.json --noEmit    # zero errors, strict mode
npx vitest run                            # all green
npm run build                             # must succeed
```

The `buildCommand` in `web/vercel.json` runs all three, so a broken typecheck
or a failing test fails the deployment rather than reaching the live site.
Vercel builds every pull request to its own preview URL on the same terms.

The two workflows under `.github/workflows/` do the same job better, because
the gates surface as pull request checks rather than as a build log, but they
are dormant: GitHub Actions is locked account wide by a billing issue and
cannot run at all. Each carries the note explaining how to restore it. Do not
enable both paths at once, or every change deploys twice.
