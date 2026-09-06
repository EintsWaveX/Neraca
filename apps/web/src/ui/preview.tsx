import { useState, type ReactNode } from 'react'
import { money } from '@neraca/domain/money'
import type { Money } from '@neraca/domain/money'
import { CURRENCY_CODES } from '@neraca/domain/currency'
import type { CurrencyCode } from '@neraca/domain/currency'
import {
  Badge,
  Button,
  Card,
  CardBody,
  CardFooter,
  CardHeader,
  CardTitle,
  EmptyState,
  Input,
  Modal,
  MoneyInput,
  Select,
  Skeleton,
  Table,
  TBody,
  TD,
  TH,
  THead,
  Tabs,
  TR,
  Textarea,
  ThemeToggle,
} from './index'
import type { SortDirection, TabItem } from './index'

/** A small decorative icon shared by a couple of demo rows below. Not exported: this file is a visual check page, not a component. */
function ReceiptIcon() {
  return (
    <svg viewBox="0 0 24 24" fill="none" aria-hidden="true">
      <path
        d="M6 3h12v18l-3-2-3 2-3-2-3 2V3z"
        stroke="currentColor"
        strokeWidth="1.5"
        strokeLinejoin="round"
      />
      <path d="M9 8h6M9 12h6M9 16h3" stroke="currentColor" strokeWidth="1.5" strokeLinecap="round" />
    </svg>
  )
}

function Section({ title, children }: { title: string; children: ReactNode }) {
  return (
    <section className="flex flex-col gap-3">
      <h2 className="text-lg font-semibold text-text">{title}</h2>
      {children}
    </section>
  )
}

function Row({ children }: { children: ReactNode }) {
  return <div className="flex flex-wrap items-center gap-3">{children}</div>
}

const transactions = [
  { id: 'tx1', label: 'Groceries', category: 'Food', amount: money(-45050, 'USD') },
  { id: 'tx2', label: 'Salary', category: 'Income', amount: money(520000, 'USD') },
  { id: 'tx3', label: 'Electricity bill', category: 'Utilities', amount: money(-12300, 'USD') },
]

export function UiPreview() {
  const [modalOpen, setModalOpen] = useState(false)
  const [amount, setAmount] = useState<Money | null>(money(1250075, 'USD'))
  const [budgetAmount, setBudgetAmount] = useState<Money | null>(null)
  const [currency] = useState<CurrencyCode>('IDR')
  const [selectValue, setSelectValue] = useState<CurrencyCode>('USD')
  const [sortDirection, setSortDirection] = useState<SortDirection>('ascending')
  const [loading, setLoading] = useState(false)

  const tabItems: TabItem[] = [
    { id: 'overview', label: 'Overview', content: <p className="text-sm text-muted">Overview panel content.</p> },
    { id: 'activity', label: 'Activity', content: <p className="text-sm text-muted">Activity panel content.</p> },
    {
      id: 'disabled',
      label: 'Disabled',
      disabled: true,
      content: <p className="text-sm text-muted">Not reachable.</p>,
    },
  ]

  return (
    <div className="mx-auto flex max-w-3xl flex-col gap-10 bg-bg px-4 py-8 text-text">
      <header className="flex items-center justify-between gap-4">
        <h1 className="text-2xl font-semibold">UI component preview</h1>
        <ThemeToggle />
      </header>

      <Section title="Button">
        <Row>
          <Button variant="primary">Primary</Button>
          <Button variant="secondary">Secondary</Button>
          <Button variant="ghost">Ghost</Button>
          <Button variant="danger">Danger</Button>
        </Row>
        <Row>
          <Button size="sm">Small</Button>
          <Button size="md">Medium</Button>
        </Row>
        <Row>
          <Button icon={<ReceiptIcon />}>With icon</Button>
          <Button loading={loading} onClick={() => setLoading((v) => !v)}>
            {loading ? 'Loading' : 'Toggle loading'}
          </Button>
          <Button disabled>Disabled</Button>
        </Row>
      </Section>

      <Section title="Card">
        <Card>
          <CardHeader>
            <CardTitle>Monthly budget</CardTitle>
            <Badge tone="positive">On track</Badge>
          </CardHeader>
          <CardBody className="flex flex-col gap-2">
            <p className="text-sm text-muted">You have spent 62% of your grocery budget this month.</p>
          </CardBody>
          <CardFooter>
            <Button variant="secondary" size="sm">
              View details
            </Button>
          </CardFooter>
        </Card>
      </Section>

      <Section title="Input and Textarea">
        <div className="flex flex-col gap-4">
          <Input label="Account name" placeholder="Everyday spending" hint="Shown on your dashboard." />
          <Input label="Email" defaultValue="not-an-email" error="Enter a valid email address." />
          <Input label="Disabled field" disabled defaultValue="Cannot edit" />
          <Textarea label="Notes" hint="Optional, up to 200 characters." placeholder="Add a note" />
        </div>
      </Section>

      <Section title="Select">
        <div className="flex flex-col gap-4">
          <Select
            label="Default currency"
            value={selectValue}
            onChange={(event) => setSelectValue(event.target.value as CurrencyCode)}
            hint="Used for new transactions."
          >
            {CURRENCY_CODES.map((code) => (
              <option key={code} value={code}>
                {code}
              </option>
            ))}
          </Select>
          <Select label="Required field" required error="Choose an option.">
            <option value="">Choose one</option>
            <option value="a">Option A</option>
          </Select>
        </div>
      </Section>

      <Section title="MoneyInput">
        <div className="flex flex-col gap-4">
          <MoneyInput
            label="Amount"
            currency={selectValue}
            value={amount}
            onChange={setAmount}
            hint="Type freely, it only reformats on blur."
          />
          <MoneyInput label="Budget cap" currency={currency} value={budgetAmount} onChange={setBudgetAmount} error="Required." />
        </div>
      </Section>

      <Section title="Modal">
        <Button onClick={() => setModalOpen(true)}>Open modal</Button>
        <Modal
          open={modalOpen}
          onClose={() => setModalOpen(false)}
          title="Delete transaction"
          footer={
            <>
              <Button variant="secondary" onClick={() => setModalOpen(false)}>
                Cancel
              </Button>
              <Button variant="danger" onClick={() => setModalOpen(false)}>
                Delete
              </Button>
            </>
          }
        >
          <p className="text-sm text-muted">This cannot be undone. Are you sure you want to delete this transaction?</p>
        </Modal>
      </Section>

      <Section title="Table">
        <Table>
          <THead>
            <TR>
              <TH>Label</TH>
              <TH>Category</TH>
              <TH
                sortable
                sortDirection={sortDirection}
                onSort={() => setSortDirection((d) => (d === 'ascending' ? 'descending' : 'ascending'))}
              >
                Amount
              </TH>
            </TR>
          </THead>
          <TBody>
            {transactions.map((tx) => (
              <TR key={tx.id}>
                <TD>{tx.label}</TD>
                <TD>{tx.category}</TD>
                <TD numeric>{(tx.amount.minor / 100).toFixed(2)}</TD>
              </TR>
            ))}
          </TBody>
        </Table>
      </Section>

      <Section title="Badge">
        <Row>
          <Badge tone="neutral">Neutral</Badge>
          <Badge tone="positive">Positive</Badge>
          <Badge tone="negative">Negative</Badge>
          <Badge tone="warning">Warning</Badge>
          <Badge tone="accent">Accent</Badge>
        </Row>
      </Section>

      <Section title="Tabs">
        <Tabs label="Account sections" items={tabItems} defaultValue="overview" />
      </Section>

      <Section title="EmptyState">
        <EmptyState
          icon={<ReceiptIcon />}
          title="No transactions yet"
          description="Add your first transaction to start tracking your spending."
          action={<Button>Add transaction</Button>}
        />
      </Section>

      <Section title="Skeleton">
        <div className="flex flex-col gap-3">
          <Skeleton shape="text" className="h-4 w-48" />
          <Skeleton shape="block" className="h-24 w-full" />
          <Skeleton shape="circle" className="h-10 w-10" />
        </div>
      </Section>
    </div>
  )
}
