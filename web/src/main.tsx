import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import App from './App.tsx'
import { RepositoryProvider } from './app/repo'
import { I18nProvider } from './i18n'
import { ProfileProvider } from './app/ProfileProvider'
import { registerSW } from 'virtual:pwa-register'

// Register the service worker for the PWA
registerSW({ immediate: true })

// Provider order matters: ProfileProvider reads and writes through
// useRepository, so it has to sit inside RepositoryProvider. I18nProvider
// wraps ProfileProvider too, since the profile picker and PIN screen in
// ProfileGate both call useI18n for their copy, before any route renders.
createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <RepositoryProvider>
      <I18nProvider>
        <ProfileProvider>
          <App />
        </ProfileProvider>
      </I18nProvider>
    </RepositoryProvider>
  </StrictMode>,
)
