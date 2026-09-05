import { useEffect, useId, useRef, type MouseEvent, type ReactNode } from 'react'
import { X } from 'lucide-react'
import { cn } from '../lib/utils'

export interface ModalProps {
  open: boolean
  onClose: () => void
  title: string
  children: ReactNode
  footer?: ReactNode
  className?: string
}

/**
 * Built on the native <dialog> element rather than a hand rolled overlay.
 * A modally shown <dialog> already traps Tab focus inside itself and makes
 * the rest of the page inert per the HTML spec, so the tricky part of an
 * accessible modal comes for free from the browser. What is left to wire up
 * by hand is: syncing showModal()/close() with the `open` prop, closing on a
 * click outside the card, and restoring focus to whatever triggered it.
 */
export function Modal({ open, onClose, title, children, footer, className }: ModalProps) {
  const dialogRef = useRef<HTMLDialogElement>(null)
  const triggerRef = useRef<HTMLElement | null>(null)
  const titleId = useId()

  useEffect(() => {
    const dialogEl = dialogRef.current
    if (!dialogEl) return
    if (open) {
      // Opening a modal is always a response to a user interaction, so
      // whatever has focus right now is the trigger to return focus to later.
      triggerRef.current = document.activeElement instanceof HTMLElement ? document.activeElement : null
      if (!dialogEl.open) dialogEl.showModal()
    } else if (dialogEl.open) {
      dialogEl.close()
    }
  }, [open])

  useEffect(() => {
    const dialogEl = dialogRef.current
    if (!dialogEl) return
    // The 'close' event covers every way the dialog can close: Escape (which
    // the browser turns into a 'cancel' then a 'close'), the close button
    // below calling .close() directly, and the outside click handler. Routing
    // all of them through one event keeps onClose called exactly once per
    // close and keeps focus restoration in a single place.
    function handleClose() {
      onClose()
      triggerRef.current?.focus()
    }
    dialogEl.addEventListener('close', handleClose)
    return () => dialogEl.removeEventListener('close', handleClose)
  }, [onClose])

  function handleBackdropClick(event: MouseEvent<HTMLDialogElement>) {
    const dialogEl = dialogRef.current
    if (!dialogEl) return
    // A click on a <dialog>'s own ::backdrop reports the dialog element
    // itself as the target, the same as a click on the dialog's padding
    // would, so distance from the visible card is what separates "outside"
    // from "inside", not the event target.
    const rect = dialogEl.getBoundingClientRect()
    const insideCard =
      event.clientX >= rect.left &&
      event.clientX <= rect.right &&
      event.clientY >= rect.top &&
      event.clientY <= rect.bottom
    if (!insideCard) dialogEl.close()
  }

  return (
    <dialog
      ref={dialogRef}
      aria-labelledby={titleId}
      onClick={handleBackdropClick}
      className={cn(
        "m-auto max-h-[85vh] w-[min(32rem,calc(100vw-2rem))] overflow-y-auto rounded-card border border-line bg-surface p-0 text-text shadow-[var(--shadow-pop)] backdrop:bg-[oklch(0%_0_0/0.45)] backdrop:backdrop-blur-[2px]",
        className
      )}
    >
      <div className="flex items-center justify-between gap-4 border-b border-line px-5 py-4">
        <h2 id={titleId} className="text-base font-semibold text-text">
          {title}
        </h2>
        <button
          type="button"
          onClick={() => dialogRef.current?.close()}
          aria-label="Close dialog"
          className="rounded-control p-1 text-muted hover:bg-surface-sunken hover:text-text transition-colors"
        >
          <X className="h-4 w-4" aria-hidden="true" />
        </button>
      </div>
      <div className="px-5 py-4">{children}</div>
      {footer && <div className="flex justify-end gap-2 border-t border-line px-5 py-4">{footer}</div>}
    </dialog>
  )
}
