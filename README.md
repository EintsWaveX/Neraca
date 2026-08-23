# FinancialAM

**A personal finance manager, in two builds: a browser application and the C
console program it grew out of.**

| Build | Where | What it is |
|---|---|---|
| **Web** | [eintswavex.github.io/FinancialAM](https://eintswavex.github.io/FinancialAM/) | React and TypeScript, runs entirely in the browser, no server |
| **Console** | `cli/` | The original, 8,281 lines of C using only the standard library plus Win32 |

Both are maintained. The console version is the lightweight build, not an
archive, and a rule corrected in one gets corrected in the other.

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

```bash
cd web
npm install
npm run dev
```

```bash
npx tsc -p tsconfig.app.json --noEmit   # strict, with noUncheckedIndexedAccess
npx vitest run                           # the domain rules and the storage layer
npm run build
```

The deploy workflow runs all three, so a failing test cannot reach the live
site.

### How it is put together

```
web/src/domain/    pure rules: money, currencies, categories, rates, balances,
                   budgets, recurrence, CSV, reports. No React, no storage,
                   which is what makes them directly testable.
web/src/data/      the Repository contract and its IndexedDB implementation.
                   Nothing above this layer knows where data lives, so a server
                   backed version would be a drop in replacement.
web/src/ui/        the component library and design tokens.
web/src/features/  one folder per screen.
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
corrected it. Four defects that survived into review and were caught by
running the thing rather than reading it are written up in `CLAUDE.md` and each
has a test pinning it, including a demo dataset that generated income into one
set of wallets and spending out of another, leaving the cash wallet nine
million rupiah in the red on the first screen a visitor would see.

---

## Licence

GNU GPL v3.0. See `LICENSE`.
