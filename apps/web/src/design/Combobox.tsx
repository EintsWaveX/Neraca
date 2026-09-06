/**
 * A searchable single select.
 *
 * The app has 55 categories and 24 transaction types. A native select holding
 * 55 options is a scroll wheel on a phone and a wall of text on a desktop, and
 * in both cases it asks the reader to find something rather than to type it.
 * This types instead, promotes what you actually use, and groups the rest.
 *
 * Built on a real text input with the listbox pattern rather than on a div
 * pretending to be one, so keyboard operation, the accessibility tree and the
 * on-screen keyboard a phone raises are all the genuine article. The visible
 * label is required, not optional: an unlabelled control here would be a
 * control nobody using a screen reader could identify among six others on the
 * same form.
 */

import { useEffect, useId, useMemo, useRef, useState } from 'react'

export interface ComboboxOption {
  id: string
  label: string
  /** Options carrying the same group name are rendered under one heading. */
  group?: string
  hint?: string
}

export interface ComboboxProps {
  label: string
  options: readonly ComboboxOption[]
  value: string | null
  onChange: (id: string) => void
  /** Ids surfaced above everything else, newest first. Usually recent choices. */
  promoted?: readonly string[]
  placeholder?: string
  /** Describes the control beyond its label, for example a validation rule. */
  description?: string
}

interface Row {
  kind: 'heading' | 'option'
  key: string
  label: string
  option?: ComboboxOption
}

function buildRows(
  options: readonly ComboboxOption[],
  promoted: readonly string[],
  query: string,
): Row[] {
  const needle = query.trim().toLowerCase()
  const matches = needle === ''
    ? options
    : options.filter((o) => o.label.toLowerCase().includes(needle))

  const rows: Row[] = []
  const byId = new Map(matches.map((o) => [o.id, o]))

  // Promoted entries appear once at the top and again in their own group, so
  // muscle memory for the group position is not broken by having used a thing
  // recently. The duplicate is why row keys are prefixed rather than being the
  // option id.
  const promotedHere = promoted.map((id) => byId.get(id)).filter((o): o is ComboboxOption => !!o)
  if (promotedHere.length > 0 && needle === '') {
    rows.push({ kind: 'heading', key: 'h:recent', label: 'Recent' })
    for (const o of promotedHere) {
      rows.push({ kind: 'option', key: `recent:${o.id}`, label: o.label, option: o })
    }
  }

  const groups = new Map<string, ComboboxOption[]>()
  for (const o of matches) {
    const g = o.group ?? ''
    const bucket = groups.get(g)
    if (bucket) bucket.push(o)
    else groups.set(g, [o])
  }
  for (const [group, items] of groups) {
    if (group !== '') rows.push({ kind: 'heading', key: `h:${group}`, label: group })
    for (const o of items) {
      rows.push({ kind: 'option', key: `opt:${o.id}`, label: o.label, option: o })
    }
  }
  return rows
}

export function Combobox({
  label,
  options,
  value,
  onChange,
  promoted = [],
  placeholder = 'Type to search',
  description,
}: ComboboxProps) {
  const baseId = useId()
  const listId = `${baseId}-list`
  const descId = `${baseId}-desc`

  const [open, setOpen] = useState(false)
  const [query, setQuery] = useState('')
  const [activeIndex, setActiveIndex] = useState(0)
  const rootRef = useRef<HTMLDivElement>(null)
  const listRef = useRef<HTMLUListElement>(null)

  const selected = useMemo(() => options.find((o) => o.id === value) ?? null, [options, value])
  const rows = useMemo(() => buildRows(options, promoted, query), [options, promoted, query])
  const optionRows = useMemo(() => rows.filter((r) => r.kind === 'option'), [rows])

  // The displayed text is the selection while closed and the query while open,
  // so opening the control does not wipe what the reader can see it is set to.
  const shown = open ? query : (selected?.label ?? '')

  useEffect(() => {
    if (!open) return
    function onPointerDown(event: PointerEvent) {
      if (!rootRef.current?.contains(event.target as Node)) setOpen(false)
    }
    document.addEventListener('pointerdown', onPointerDown)
    return () => document.removeEventListener('pointerdown', onPointerDown)
  }, [open])

  useEffect(() => {
    if (!open || !listRef.current) return
    const active = listRef.current.querySelector('[data-active="true"]')
    active?.scrollIntoView({ block: 'nearest' })
  }, [open, activeIndex])

  function commit(index: number) {
    const row = optionRows[index]
    if (!row?.option) return
    onChange(row.option.id)
    setOpen(false)
    setQuery('')
  }

  function onKeyDown(event: React.KeyboardEvent<HTMLInputElement>) {
    if (!open && (event.key === 'ArrowDown' || event.key === 'Enter')) {
      setOpen(true)
      setActiveIndex(0)
      event.preventDefault()
      return
    }
    if (!open) return

    switch (event.key) {
      case 'ArrowDown':
        setActiveIndex((i) => Math.min(i + 1, optionRows.length - 1))
        event.preventDefault()
        break
      case 'ArrowUp':
        setActiveIndex((i) => Math.max(i - 1, 0))
        event.preventDefault()
        break
      case 'Home':
        setActiveIndex(0)
        event.preventDefault()
        break
      case 'End':
        setActiveIndex(optionRows.length - 1)
        event.preventDefault()
        break
      case 'Enter':
        commit(activeIndex)
        event.preventDefault()
        break
      case 'Escape':
        setOpen(false)
        setQuery('')
        event.preventDefault()
        break
      case 'Tab':
        setOpen(false)
        break
    }
  }

  const activeId = optionRows[activeIndex]
    ? `${baseId}-${optionRows[activeIndex].key}`
    : undefined

  return (
    <div ref={rootRef} className="relative">
      <label htmlFor={baseId} className="block text-sm text-ink-muted mb-1">
        {label}
      </label>
      <input
        id={baseId}
        role="combobox"
        type="text"
        autoComplete="off"
        aria-expanded={open}
        aria-controls={listId}
        aria-autocomplete="list"
        {...(activeId ? { 'aria-activedescendant': activeId } : {})}
        {...(description ? { 'aria-describedby': descId } : {})}
        value={shown}
        placeholder={placeholder}
        onChange={(e) => {
          setQuery(e.target.value)
          setActiveIndex(0)
          if (!open) setOpen(true)
        }}
        onFocus={() => setOpen(true)}
        onKeyDown={onKeyDown}
        className="w-full bg-paper-raised text-ink border border-rule rounded-control px-3 py-2 outline-none transition-colors duration-[--dur-fast] hover:border-rule-strong focus:border-indigo"
      />
      {description && (
        <p id={descId} className="mt-1 text-xs text-ink-faint">
          {description}
        </p>
      )}

      {open && (
        <ul
          ref={listRef}
          id={listId}
          role="listbox"
          aria-label={label}
          className="absolute z-30 mt-1 max-h-64 w-full overflow-auto rounded-sheet border border-rule bg-paper-raised py-1 shadow-[var(--shadow-sheet)] lift-in"
        >
          {optionRows.length === 0 && (
            <li className="px-3 py-2 text-sm text-ink-faint">Nothing matches {`"${query}"`}</li>
          )}
          {rows.map((row) => {
            if (row.kind === 'heading') {
              return (
                <li
                  key={row.key}
                  role="presentation"
                  className="px-3 pt-2 pb-1 text-xs text-ink-faint"
                >
                  {row.label}
                </li>
              )
            }
            const index = optionRows.indexOf(row)
            const isActive = index === activeIndex
            const isSelected = row.option?.id === value
            return (
              <li
                key={row.key}
                id={`${baseId}-${row.key}`}
                role="option"
                aria-selected={isSelected}
                data-active={isActive}
                onPointerEnter={() => setActiveIndex(index)}
                onClick={() => commit(index)}
                className={[
                  'flex cursor-pointer items-baseline justify-between gap-3 px-3 py-1.5 text-body',
                  isActive ? 'bg-indigo-soft' : '',
                  isSelected ? 'text-indigo' : 'text-ink',
                ].join(' ')}
              >
                <span>{row.label}</span>
                {row.option?.hint && (
                  <span className="figure text-xs text-ink-faint">{row.option.hint}</span>
                )}
              </li>
            )
          })}
        </ul>
      )}
    </div>
  )
}
