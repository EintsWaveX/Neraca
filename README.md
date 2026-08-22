# FinancialAM

**A personal financial management system, written from scratch in C, as a Windows console application.**

Track accounts, budgets, income, and expenses from the terminal. No frameworks,
no external dependencies: 8,101 lines of C across 53 functions, using only the
standard library plus the Win32 API.

Started October 2023, last substantial update March 2024, 57 commits.

---

## Why this exists

This was written to find out how much of a real application could be built with
nothing but C and the standard library. Everything a framework would normally
hand you had to be built by hand: the menu system, the input validation, the
file format, the account storage, the text encoding, and the on-screen charts.

That constraint is the point of the project. It is also why the source is one
large file rather than a module tree.

---

## Features

| Area | What it does |
|---|---|
| **Accounts** | Registration and login, with password handling and per-account save files |
| **Budgeting** | Set a budget, record income and expenses against it |
| **Transactions** | Add, review, and persist transaction history |
| **Reporting** | Horizontal histogram charts rendered directly in the console |
| **Persistence** | Human-readable save files, with a configuration file for tunable settings |
| **Encoding** | Caesar-style encode/decode pass over stored text (see the security note below) |

Configuration lives in `FinancialAM-05-CA-CONFIGURATIONS.txt`, which is
commented in place and read at startup. Changing `PerExpense`, for example,
rescales the histogram output.

---

## Files

```
FinancialAM-05-CA-WIN.c            the Windows build (8,101 lines)
FinancialAM-05-CA-UNIX.c           the POSIX build
FinancialAM-05-CA-CONFIGURATIONS.txt   runtime settings, commented inline
SKYR-FMSA-RegisteredAccounts.txt   account store
aaa-SaveFile.txt                   example save file
EncodedTextSample.txt              sample encoded text
DecodedTextSample.txt              the same text decoded
Updates.txt                        a hand-kept changelog covering all 57 commits
```

`Updates.txt` is worth a look on its own. It is a full changelog written by hand
across the life of the project, with every commit categorised as an addition,
deletion, tweak, or update.

---

## Building

**Windows:**

```bash
gcc FinancialAM-05-CA-WIN.c -o FinancialAM.exe
```

Uses `<windows.h>` and `<conio.h>` for console control and notifications.

**POSIX:**

```bash
gcc FinancialAM-05-CA-UNIX.c -o FinancialAM -lm
```

The UNIX build drops the Win32 calls. It is the less exercised of the two.

A prebuilt `FinancialAM-05-CA-WIN.exe` is committed for convenience.

---

## Security note, read this before reusing anything here

The text encoding in this project is a **Caesar-style substitution cipher**. It
is obfuscation, not encryption. It will stop somebody glancing at a save file
and nothing more, and passwords stored under it should be treated as stored in
plain text.

This is a deliberate note rather than an omission: the project was a exercise in
building things from first principles in C, and the cipher was written to
understand the mechanics of one. Do not reuse this code to protect anything that
matters. Real password storage needs a slow, salted hash such as bcrypt or
Argon2, which is a different problem with a different answer.

---

## Status

Complete and working, no longer actively developed. Kept here because it is a
record of what the standard library alone can carry.

## Licence

GNU GPL v3.0. See `LICENSE`.
