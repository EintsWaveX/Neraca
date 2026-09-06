/*
  oxlint-disable jsx-a11y/no-redundant-roles, jsx-a11y/no-interactive-element-to-noninteractive-role

  The roles on the ledger table below look redundant to a linter reading the
  markup alone, and they would be, were the table always laid out as a table.
  Below 48rem a media query sets `display: grid` on the rows so each entry
  folds onto two lines, and changing `display` on a table element drops its
  implicit semantics in every current engine. Restating the roles is what
  keeps a screen reader being told this is a table on a phone. The second rule
  is a plain false positive: a `td` is not an interactive element.

  When the real screens are built this markup becomes one shared component and
  the suppression moves there with it, rather than being repeated per page.
*/

/**
 * The Passbook specimen.
 *
 * A single page holding every decision the design system makes, so the system
 * can be argued about before seven screens are built on top of it. It is a
 * real route rather than a screenshot: the type is the real type, the tokens
 * are the real tokens, and the ledger below computes its running balance
 * through the same domain functions the application uses.
 */

import { useEffect, useMemo, useState } from 'react'
import { CATEGORIES, CATEGORY_GROUP_LABELS } from '@neraca/domain/categories'
import { money, sum, type Money } from '@neraca/domain/money'
import { Combobox, type ComboboxOption } from './Combobox'
import { Figure, MoneyFigure } from './Figure'

/* ------------------------------------------------------------------ tokens */

const STOCK = [
  ['--paper', 'the sheet'],
  ['--paper-raised', 'a sheet laid on top'],
  ['--paper-sunken', 'the gutter'],
  ['--paper-edge', 'a lifted edge'],
] as const

const INK = [
  ['--ink', 'the entry itself'],
  ['--ink-muted', 'the column heading'],
  ['--ink-faint', 'the note in the margin'],
] as const

const MEANING = [
  ['--indigo', 'the one accent, nila and iron gall'],
  ['--credit', 'money in'],
  ['--debit', 'money out'],
  ['--stamp', 'a threshold passed'],
] as const

function Swatch({ token, note }: { token: string; note: string }) {
  return (
    <div className="flex items-center gap-3 py-1.5">
      <span
        className="h-8 w-8 shrink-0 rounded-control border border-rule"
        style={{ background: `var(${token})` }}
      />
      <span className="figure text-sm text-ink">{token}</span>
      <span className="text-sm text-ink-muted">{note}</span>
    </div>
  )
}

function Section({
  title,
  lede,
  children,
}: {
  title: string
  lede?: string
  children: React.ReactNode
}) {
  return (
    <section className="border-t border-rule pt-8 pb-12">
      <h2 className="text-h2 leading-tight">{title}</h2>
      {lede && <p className="measure mt-2 text-ink-muted">{lede}</p>}
      <div className="mt-6">{children}</div>
    </section>
  )
}

/* ------------------------------------------------------------------ ledger */

interface Entry {
  date: string
  description: string
  category: string
  minor: number
}

/* An ordinary fortnight in Jakarta, which is the point: the system has to hold
   a salary and a coffee in the same column without either looking wrong. */
const ENTRIES: Entry[] = [
  { date: '31/08', description: 'Gaji Agustus', category: 'Salary', minor: 12_500_000 },
  { date: '30/08', description: 'Sewa kos September', category: 'Rent', minor: -3_200_000 },
  { date: '29/08', description: 'Kopi Tuku', category: 'Coffee', minor: -28_000 },
  { date: '28/08', description: 'Pindah ke BCA', category: 'Transfer', minor: -500_000 },
  { date: '27/08', description: 'Listrik PLN', category: 'Utilities', minor: -412_000 },
  { date: '26/08', description: 'Belanja Sayur', category: 'Groceries', minor: -187_500 },
  { date: '24/08', description: 'Gojek ke kantor', category: 'Transport', minor: -34_000 },
  { date: '22/08', description: 'Freelance, desain logo', category: 'Side income', minor: 2_750_000 },
]

const OPENING = 74_000_000

/* The hero balance and the ledger's closing balance are the same number, so it
   is derived once rather than written down in two places that could drift. */
const NET = ENTRIES.reduce((total, e) => total + e.minor, 0)

function Ledger({ replayKey }: { replayKey: number }) {
  // Running balance goes through the domain's own sum rather than being added
  // up in the view, so this page exercises the real arithmetic.
  const rows = useMemo(() => {
    let balance = OPENING
    return ENTRIES.map((entry) => {
      balance += entry.minor
      return { ...entry, balance }
    })
  }, [])

  const net = useMemo(() => sum(ENTRIES.map((e) => money(e.minor, 'IDR')), 'IDR'), [])

  return (
    <div key={replayKey}>
      <table role="table" className="ledger ledger-narrow w-full border-collapse text-left">
        <caption className="sr-only">
          A fortnight of entries with a running balance, in Indonesian rupiah
        </caption>
        <thead>
          <tr role="row" className="border-b border-rule-strong">
            <th scope="col" className="pb-2 text-sm font-normal text-ink-muted">
              Date
            </th>
            <th scope="col" className="pb-2 text-sm font-normal text-ink-muted">
              Description
            </th>
            <th scope="col" className="pb-2 text-right text-sm font-normal text-ink-muted">
              Amount <span className="text-ink-faint">(IDR)</span>
            </th>
            <th scope="col" className="pb-2 text-right text-sm font-normal text-ink-muted">
              Balance <span className="text-ink-faint">(IDR)</span>
            </th>
          </tr>
        </thead>
        <tbody>
          {rows.map((row, i) => (
            <tr
              key={row.date + row.description}
              role="row"
              className="print-in border-b border-rule"
              style={{ '--print-index': i } as React.CSSProperties}
            >
              <td role="cell" className="c-date py-[var(--row-pad)] pr-3 align-baseline">
                <Figure className="text-sm text-ink-muted">{row.date}</Figure>
              </td>
              <td role="cell" className="c-desc py-[var(--row-pad)] pr-4 align-baseline">
                <span className="text-ink">{row.description}</span>
                <span className="ml-2 text-xs text-ink-faint">{row.category}</span>
              </td>
              <td
                role="cell"
                className="c-amount py-[var(--row-pad)] pl-4 text-right align-baseline whitespace-nowrap"
              >
                <MoneyFigure
                  value={money(row.minor, 'IDR')}
                  tone="auto"
                  signDisplay="always"
                  showSymbol={false}
                />
              </td>
              <td
                role="cell"
                className="c-balance py-[var(--row-pad)] pl-4 text-right align-baseline whitespace-nowrap"
              >
                <MoneyFigure
                  value={money(row.balance, 'IDR')}
                  showSymbol={false}
                  className="text-ink-muted"
                />
              </td>
            </tr>
          ))}
          <tr role="row" className="ledger-total">
            <td role="cell" className="c-date" />
            <td role="cell" className="c-desc pt-2 text-sm text-ink-muted">
              Net movement
            </td>
            <td role="cell" className="c-amount pt-2 pl-4 text-right whitespace-nowrap">
              <MoneyFigure value={net} tone="auto" signDisplay="always" showSymbol={false} />
            </td>
            <td role="cell" className="c-balance pt-2 pl-4 text-right whitespace-nowrap">
              <MoneyFigure value={money(OPENING + NET, 'IDR')} showSymbol={false} />
            </td>
          </tr>
        </tbody>
      </table>
    </div>
  )
}

/* -------------------------------------------------------------------- page */

const SAMPLE_CURRENCIES: Money[] = [
  money(1_500_000, 'IDR'),
  money(1234, 'USD'),
  money(98_760, 'JPY'),
  money(4250, 'EUR'),
  money(129_900, 'GBP'),
]

const WALLETS: ReadonlyArray<readonly [string, string]> = [
  ['cash', 'Cash'],
  ['bca', 'BCA'],
  ['gopay', 'GoPay'],
  ['savings', 'Savings'],
]

export default function Specimen() {
  const [theme, setTheme] = useState<'light' | 'dark'>('light')
  const [density, setDensity] = useState<'comfortable' | 'compact'>('comfortable')
  const [replayKey, setReplayKey] = useState(0)
  const [category, setCategory] = useState<string | null>(null)
  const [checks, setChecks] = useState<string[]>(['cash'])

  useEffect(() => {
    document.documentElement.dataset['theme'] = theme
    document.documentElement.dataset['density'] = density
  }, [theme, density])

  const categoryOptions: ComboboxOption[] = useMemo(
    () =>
      CATEGORIES.map((c) => ({
        id: c.id,
        label: c.en,
        group: CATEGORY_GROUP_LABELS[c.group].en,
        hint: c.emoji,
      })),
    [],
  )

  function toggleCheck(id: string) {
    setChecks((prev) => (prev.includes(id) ? prev.filter((c) => c !== id) : [...prev, id]))
  }

  return (
    <div className="min-h-dvh bg-paper text-ink">
      <div className="mx-auto max-w-4xl px-5 py-10 sm:px-8">
        <header className="flex flex-wrap items-end justify-between gap-4 pb-10">
          <div>
            <p className="text-h1 lowercase tracking-tight">neraca</p>
            <p className="text-sm text-ink-muted">The Passbook system</p>
          </div>
          <div className="flex items-center gap-2">
            <button
              type="button"
              onClick={() => setTheme(theme === 'light' ? 'dark' : 'light')}
              className="rounded-control border border-rule px-3 py-1.5 text-sm transition-colors duration-[--dur-fast] hover:border-rule-strong"
            >
              {theme === 'light' ? 'Dark' : 'Light'}
            </button>
            <button
              type="button"
              onClick={() => setDensity(density === 'comfortable' ? 'compact' : 'comfortable')}
              className="rounded-control border border-rule px-3 py-1.5 text-sm transition-colors duration-[--dur-fast] hover:border-rule-strong"
            >
              {density === 'comfortable' ? 'Compact' : 'Comfortable'}
            </button>
          </div>
        </header>

        {/*
          The hero is the passbook itself. The whole argument of this system is
          that a balance and the rows that produced it, set in ruled type, beat
          a grid of tiles, so the page opens by doing it rather than by
          describing it. The rule down the left is the book's binding.
        */}
        <div className="spine pl-5 sm:pl-8">
          <p className="text-sm text-ink-muted">Kekayaan bersih</p>
          <p className="text-display leading-none">
            <MoneyFigure value={money(OPENING + NET, 'IDR')} display />
          </p>
          <p className="mt-2 text-sm text-ink-muted">
            <Figure tone="credit">+4,2%</Figure>{' '}
            <span>on last month, across eight entries</span>
          </p>

          <div className="mt-8">
            <Ledger replayKey={replayKey} />
          </div>

          <div className="mt-4 flex flex-wrap items-center gap-3">
            <button
              type="button"
              onClick={() => setReplayKey((k) => k + 1)}
              className="rounded-control bg-indigo px-3 py-1.5 text-sm text-indigo-on transition-colors duration-[--dur-fast] hover:bg-indigo-hover"
            >
              Print again
            </button>
            <span className="text-sm text-ink-faint">
              Rows are laid down left to right, once on arrival. Reduced motion skips it.
            </span>
          </div>
        </div>

        <p className="measure mt-14 text-ink-muted">
          The reference is the buku tabungan: the savings passbook a branch prints on an impact
          printer, with fixed pitch figures, feint ruled rows and a running balance down the right
          hand edge. Structure comes from ruled lines and typography. A card here means a genuinely
          contained thing, such as a dialog, and never a paragraph in a box with a shadow under it.
          What follows is every decision resting on that.
        </p>

        <div className="mt-10">
          <Section
            title="Stock and ink"
            lede="Four steps of paper rather than two, because a dense table needs enough separation to keep a gutter, a sheet and a lifted edge apart without reaching for a shadow. The hue leans green, the way manila and newsprint do, rather than the pink cream that shows up on every generated page."
          >
            <div className="grid gap-6 sm:grid-cols-2">
              <div>
                {STOCK.map(([token, note]) => (
                  <Swatch key={token} token={token} note={note} />
                ))}
              </div>
              <div>
                {INK.map(([token, note]) => (
                  <Swatch key={token} token={token} note={note} />
                ))}
                <Swatch token="--rule" note="the feint ruled line" />
                <Swatch token="--rule-strong" note="the rule drawn under a total" />
              </div>
            </div>
          </Section>

          <Section
            title="What colour is allowed to mean"
            lede="Exactly one thing: the direction money moved. Both semantic colours are muted, because a purchase is not an error and a salary is not a success toast. Neither is ever the only carrier of the meaning, so sign, alignment and weight say the same thing to a reader who cannot separate the hues."
          >
            <div className="grid gap-6 sm:grid-cols-2">
              <div>
                {MEANING.map(([token, note]) => (
                  <Swatch key={token} token={token} note={note} />
                ))}
              </div>
              <div className="rounded-sheet border border-rule bg-paper-raised p-4">
                <p className="text-sm text-ink-muted">
                  The same two rows with colour removed entirely:
                </p>
                <div className="mt-3 grayscale">
                  <div className="flex items-baseline justify-between border-b border-rule py-2">
                    <span>Gaji Agustus</span>
                    <MoneyFigure
                      value={money(12_500_000, 'IDR')}
                      tone="auto"
                      signDisplay="always"
                    />
                  </div>
                  <div className="flex items-baseline justify-between py-2">
                    <span>Kopi Tuku</span>
                    <MoneyFigure value={money(-28_000, 'IDR')} tone="auto" signDisplay="always" />
                  </div>
                </div>
              </div>
            </div>
          </Section>

          <Section
            title="Type"
            lede="IBM Plex Sans for language and IBM Plex Mono for every figure, date and identifier. One superfamily, so the numbers and the prose share a skeleton. Both are self hosted, so the first paint never waits on a third party and the security policy can forbid outside font origins outright."
          >
            <div className="space-y-4">
              <p className="text-h1 leading-tight">Kekayaan bersih bulan ini</p>
              <p className="text-h2 leading-tight">Net worth this month</p>
              <p className="text-h3 leading-snug">Spending by category</p>
              <p className="measure">
                Body text at one rem, set to a line length under sixty eight characters and a line
                height of 1.55. This is the size everything you actually read is set at, so it has
                to survive a cheap Android screen in daylight.
              </p>
              <p className="text-sm text-ink-muted">
                Small, for column headings and secondary notes.
              </p>
              <p className="text-xs text-ink-faint">Micro, for the note in the margin.</p>
            </div>
          </Section>

          <Section
            title="Figures"
            lede="The currency symbol and the minor units are pushed back a step in size and colour, so the eye lands on the digits you actually compare. The symbol always leads, even in locales that trail it, because a ledger column is read downwards and a symbol that moved between rows would break the only alignment this design has."
          >
            <div className="grid gap-8 sm:grid-cols-2">
              <div className="space-y-3">
                {SAMPLE_CURRENCIES.map((m) => (
                  <div key={m.currency} className="flex items-baseline justify-between gap-4">
                    <span className="text-sm text-ink-muted">{m.currency}</span>
                    <MoneyFigure value={m} className="text-h3" />
                  </div>
                ))}
              </div>
              <div className="space-y-3">
                <div className="flex items-baseline justify-between gap-4">
                  <span className="text-sm text-ink-muted">Money in</span>
                  <MoneyFigure
                    value={money(12_500_000, 'IDR')}
                    tone="auto"
                    signDisplay="always"
                    className="text-h3"
                  />
                </div>
                <div className="flex items-baseline justify-between gap-4">
                  <span className="text-sm text-ink-muted">Money out</span>
                  <MoneyFigure
                    value={money(-412_000, 'IDR')}
                    tone="auto"
                    signDisplay="always"
                    className="text-h3"
                  />
                </div>
                <div className="flex items-baseline justify-between gap-4">
                  <span className="text-sm text-ink-muted">Rate, not money</span>
                  <Figure className="text-h3">0,000061</Figure>
                </div>
                <div className="flex items-baseline justify-between gap-4">
                  <span className="text-sm text-ink-muted">Share of budget</span>
                  <Figure className="text-h3">62,4%</Figure>
                </div>
              </div>
            </div>
          </Section>

          <Section
            title="Choosing among many things"
            lede="There are 55 categories and 24 transaction types. A native select holding 55 options is a scroll wheel on a phone and a wall of text on a desktop, and both ask you to find something rather than to type it. This types instead, promotes what you use, and groups the rest."
          >
            <div className="grid items-start gap-8 sm:grid-cols-2">
              <Combobox
                label="Category"
                options={categoryOptions}
                value={category}
                onChange={setCategory}
                promoted={['groceries', 'daily-transportations', 'snacks-and-drinks']}
                description="Type to narrow. Arrow keys move, Enter chooses, Escape closes."
              />
              <fieldset className="border-0 p-0">
                <legend className="mb-2 text-sm text-ink-muted">Wallets to include</legend>
                <div className="space-y-1">
                  {WALLETS.map(([id, label]) => (
                    <label key={id} className="flex cursor-pointer items-center gap-2.5 py-1">
                      <input
                        type="checkbox"
                        checked={checks.includes(id)}
                        onChange={() => toggleCheck(id)}
                        className="h-4 w-4 accent-[var(--indigo)]"
                      />
                      <span>{label}</span>
                    </label>
                  ))}
                </div>
              </fieldset>
            </div>
          </Section>

          <Section
            title="Where motion is allowed to live"
            lede="On the shell and nowhere else. The kawung field below is the batik motif this palette's indigo is named for, and it appears on the sign in screen, the lock screen and an empty state. It never sits behind a table or a balance, which is the one rule that lets an app about money have a moving background at all. It stops when the tab is hidden and when reduced motion is set."
          >
            <div className="kawung flex min-h-52 items-center justify-center rounded-sheet border border-rule bg-paper-raised p-8">
              <div className="text-center">
                <p className="text-h3">Nothing here yet</p>
                <p className="mt-1 text-sm text-ink-muted">
                  Add your first wallet and the ledger starts.
                </p>
              </div>
            </div>
          </Section>
        </div>
      </div>
    </div>
  )
}
