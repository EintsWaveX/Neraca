# Neraca

**A personal finance manager, in two builds: a browser application and the C
console program it grew out of.**

| Build | Where | What it is |
|---|---|---|
| **Neraca** | [neraca-ledger.vercel.app](https://neraca-ledger.vercel.app/) | React and TypeScript, runs entirely in the browser, no server |
| **FinancialAM** | `cli/` | The original, 8,101 lines of C using only the standard library plus Win32, with a POSIX variant of 8,119 beside it |

Both are maintained. The console version is the lightweight build, not an
archive, and a rule corrected in one gets corrected in the other.

*Neraca* is Indonesian for a balance sheet, and also for the beam of a pair of
scales. The web build took the name when it stopped being a port of the console
program and became its own thing. FinancialAM is what the C build is still
called, because that is what it is.

---

## The web build

Open the link and the application is already populated: a demo profile with
fourteen months of history across six wallets, so there is something to look at
before you type anything. A banner offers to clear it and start your own.

Everything lives in your own browser through IndexedDB. There is no account, no
server, and nothing leaves the machine.

### What it does

| Area | |
|---|---|
| **Wallets** | Cash, bank, e-wallet, savings and credit, each in its own currency, with balances derived from transactions rather than stored |
| **Transactions** | Income, expense and transfers across 55 categories and 24 transaction types, all carried over from the C version |
| **Search** | Filter by date range, wallet, category, type, direction, amount range and free text |
| **Budgets** | Monthly and yearly, per category or across all spending, with alerts as a threshold is approached and passed |
| **Recurring** | Repeating rules that generate real, editable transactions rather than being summed on the fly |
| **Reports** | Spending over time, category breakdown, income against expenses, and budget burn down |
| **Multi currency** | Every transaction stores the rate that applied on its own date |
| **Import and export** | Whole profile as JSON, transactions as CSV, with column detection for Indonesian and English bank exports |
| **Languages** | English and Indonesian throughout |

### Three decisions worth explaining

**Money is never a floating point number.** Amounts are integer minor units
plus a currency code. The catch is that the number of minor units is not always
two: rupiah and yen have none, so `Rp 1.500.000` is stored as `1500000` while
`$12.34` is stored as `1234`. Anything crossing between currencies has to
account for that, and one of the first bugs found here was a parser that read
`1.500.000,75` as a hundred and fifty million rupiah because it asked the
currency about decimal places before deciding which separator was a decimal
point.

**A rate is a fact about a moment.** Each transaction stores the exchange rate
that applied on its own date, and reports convert using that stored rate rather
than looking one up. Re-converting last year's purchase at today's rate would
silently rewrite history, and every total built on it would be wrong.

**The PIN is a lock, not encryption.** A profile can carry a PIN, hashed with
PBKDF2 through WebCrypto. It stops somebody picking up an unlocked laptop and
reading your spending. It does not encrypt the stored data, which remains
readable in the browser's own developer tools, and no browser application
without a server can honestly claim otherwise. The C version's Caesar cipher
made the same promise less honestly.

### Running it

One install at the root covers every workspace.

```bash
npm install
npm run dev
```

### Verification

```bash
npm run verify        # typecheck, unit tests, build, bundle budget
npm run verify:full   # the above, then the end to end suite
npm run lint          # Oxlint, not a release gate
```

`npm run verify` is what the deployment runs, so a failing typecheck or test
fails the deploy rather than reaching the live site. It covers 201 unit tests
over the domain rules and the storage layer.

`npm run e2e` adds 42 Playwright tests across a desktop viewport and a Pixel 7,
run against `vite preview` rather than the dev server: the dev server injects
its HMR client and its styles inline, which the production Content Security
Policy correctly forbids, so a suite pointed at dev would pass while the real
deployment was broken. They cover the journeys, the security headers, and
accessibility through axe.

### How it is put together

An npm workspace. The domain rules are a package rather than a folder, so the
dependency only points one way and nothing in them can reach for React or for
storage by accident.

```
packages/domain/    pure rules: money, currencies, categories, rates, balances,
                    budgets, recurrence, CSV, reports. No React, no storage,
                    which is what makes them directly testable.
packages/config/    the shared TypeScript and Oxlint configuration.
apps/web/src/data/      the Repository contract, its IndexedDB implementation,
                        and the seeded demo profile. Nothing above this layer
                        knows where data lives, so a server backed version
                        would be a drop in replacement.
apps/web/src/design/    the Passbook design system: the ledger table, the
                        figures, the page primitives, and a specimen page.
apps/web/src/ui/        the component library. Tokens live in index.css and are
                        never hardcoded.
apps/web/src/features/  one folder per screen.
apps/web/src/i18n/      English and Indonesian, kept in identical shape by a test.
apps/web/src/app/       providers, routing shell, profile gate.
e2e/                    the Playwright suite, run from the root.
```

---

## The console build

```bash
cd cli
gcc FinancialAM-05-CA-WIN.c -o FinancialAM.exe      # Windows, uses windows.h and conio.h
gcc FinancialAM-05-CA-UNIX.c -o FinancialAM -lm     # POSIX
```

Written to find out how much of a real application could be built with nothing
but C and the standard library. The menu system, the input validation, the file
format, the account storage, the text encoding and the on-screen histograms are
all hand rolled, which is the point of the exercise and also why the source is
one large file rather than a module tree.

`cli/Updates.txt` is a changelog kept by hand across all 57 commits, with every
change categorised.

**On its text encoding:** it is a Caesar style substitution cipher, which is
obfuscation and not encryption. It will stop somebody glancing at a save file
and nothing more. Do not reuse it to protect anything that matters.

---

## Built with an AI agent, and the receipts are in the repository

`CLAUDE.md` is the standing brief: the constraints I set, which decisions were
mine, and which the agent made inside them. It is checked in deliberately, so
anyone reading this can see the division rather than take my word for it.

What that looked like in practice: I set the architecture, the storage
strategy, the stack and the honesty rules, then reviewed the output and
corrected it. The defects that survived into review and were caught by running
the thing rather than reading it are written up in `CLAUDE.md` and each has a
test pinning it, including a demo dataset that generated income into one set of
wallets and spending out of another, leaving the cash wallet nine million
rupiah in the red on the first screen a visitor would see, and a register that
could not be sorted on a phone while telling a screen reader that it could.

---

## Licence

GNU GPL v3.0. See `LICENSE`.
