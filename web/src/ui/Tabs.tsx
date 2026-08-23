import { useId, useRef, useState, type KeyboardEvent, type ReactNode } from 'react'

export interface TabItem {
  id: string
  label: string
  content: ReactNode
  disabled?: boolean
}

export interface TabsProps {
  items: TabItem[]
  value?: string
  defaultValue?: string
  onChange?: (id: string) => void
  /** Accessible name for the tablist itself, since it rarely has visible text labelling it directly. */
  label: string
  className?: string
}

/** Controlled if `value` is passed, otherwise manages its own selection starting from `defaultValue`. */
export function Tabs({ items, value, defaultValue, onChange, label, className }: TabsProps) {
  const [internal, setInternal] = useState(defaultValue ?? items[0]?.id)
  const active = value ?? internal
  // Prefixed so two <Tabs> on the same page never collide on id even if
  // callers reuse the same TabItem ids across them.
  const uid = useId()
  const buttonRefs = useRef<Array<HTMLButtonElement | null>>([])

  function select(id: string) {
    if (value === undefined) setInternal(id)
    onChange?.(id)
  }

  function handleKeyDown(event: KeyboardEvent<HTMLDivElement>) {
    if (!['ArrowRight', 'ArrowLeft', 'Home', 'End'].includes(event.key)) return
    const enabled = items.map((item, index) => ({ item, index })).filter(({ item }) => !item.disabled)
    if (enabled.length === 0) return
    const currentIndex = items.findIndex((item) => item.id === active)
    const currentPos = enabled.findIndex(({ index }) => index === currentIndex)
    let nextPos = currentPos === -1 ? 0 : currentPos
    if (event.key === 'ArrowRight') nextPos = (currentPos + 1) % enabled.length
    else if (event.key === 'ArrowLeft') nextPos = (currentPos - 1 + enabled.length) % enabled.length
    else if (event.key === 'Home') nextPos = 0
    else if (event.key === 'End') nextPos = enabled.length - 1
    event.preventDefault()
    const next = enabled[nextPos]
    if (!next) return
    buttonRefs.current[next.index]?.focus()
    select(next.item.id)
  }

  return (
    <div className={className}>
      <div role="tablist" aria-label={label} onKeyDown={handleKeyDown} className="flex gap-1 border-b border-line">
        {items.map((item, index) => {
          const selected = item.id === active
          return (
            <button
              key={item.id}
              ref={(el) => {
                buttonRefs.current[index] = el
              }}
              role="tab"
              type="button"
              id={`${uid}-tab-${item.id}`}
              aria-selected={selected}
              aria-controls={`${uid}-panel-${item.id}`}
              disabled={item.disabled}
              // Roving tabindex: only the selected tab sits in the page's Tab
              // order, arrow keys move focus between the rest.
              tabIndex={selected ? 0 : -1}
              onClick={() => select(item.id)}
              className={`-mb-px border-b-2 px-3 py-2 text-sm font-medium disabled:cursor-not-allowed disabled:opacity-50 ${
                selected ? 'border-accent text-text' : 'border-transparent text-muted hover:text-text'
              }`}
            >
              {item.label}
            </button>
          )
        })}
      </div>
      {items.map((item) => (
        <div
          key={item.id}
          role="tabpanel"
          id={`${uid}-panel-${item.id}`}
          aria-labelledby={`${uid}-tab-${item.id}`}
          hidden={item.id !== active}
          tabIndex={0}
          className="pt-4"
        >
          {item.content}
        </div>
      ))}
    </div>
  )
}
