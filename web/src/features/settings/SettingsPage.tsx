import { useI18n } from '@/i18n'

/**
 * Placeholder so the router and build stay green while the real settings
 * screen is being built elsewhere. Renders only the page title.
 */
export default function SettingsPage() {
  const { t } = useI18n()
  return (
    <div className="p-4 sm:p-6">
      <h1 className="text-lg font-semibold text-text">{t.settings.title}</h1>
    </div>
  )
}
