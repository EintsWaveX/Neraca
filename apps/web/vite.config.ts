import { defineConfig } from 'vitest/config'
import react from '@vitejs/plugin-react'
import tailwindcss from '@tailwindcss/vite'
import { VitePWA } from 'vite-plugin-pwa'
import path from 'node:path'
import { readFileSync } from 'node:fs'

/*
  The production security headers, read from the one place they are defined.

  Vercel applies vercel.json at the edge, which `vite preview` knows nothing
  about, so without this the end to end test asserting a strict Content
  Security Policy would be testing a page served with no policy at all and
  passing for the wrong reason. Reading the real file means the preview server
  and production cannot drift, and a directive loosened in vercel.json fails
  the test that guards it rather than quietly taking effect.
*/
function productionHeaders(): Record<string, string> {
  const config = JSON.parse(
    readFileSync(path.resolve(import.meta.dirname, '../../vercel.json'), 'utf8'),
  ) as { headers?: Array<{ source: string; headers: Array<{ key: string; value: string }> }> }

  const everyPath = config.headers?.find((entry) => entry.source === '/(.*)')
  if (!everyPath) throw new Error('vercel.json has no headers block for /(.*)')

  return Object.fromEntries(everyPath.headers.map((h) => [h.key, h.value]))
}

// Deployed to Vercel, which serves the build at the domain root, so asset URLs
// need no prefix. This was '/FinancialAM/' while the app lived on GitHub Pages
// under a repository path. Changing it back would break Vercel: the built
// index.html would ask for /FinancialAM/assets/*, the SPA rewrite would answer
// with index.html, and the module script would fail to parse.
export default defineConfig({
  base: '/',
  plugins: [
    react(),
    tailwindcss(),
    VitePWA({
      // 'prompt', not 'autoUpdate'. A silent swap of the running shell can pull
      // the ground out from under a half filled transaction form, so the new
      // build waits behind a dismissible bar the visitor chooses to accept.
      registerType: 'prompt',
      manifest: {
        name: 'Neraca',
        short_name: 'Neraca',
        description: 'A private, local first personal finance ledger',
        display: 'standalone',
        // A manifest cannot read a CSS custom property, so this is one of the
        // two places a colour is written literally, the other being the
        // theme-color meta tags in index.html. Both carry the sRGB value of the
        // --paper token in src/index.css. If that token moves, these move with
        // it.
        theme_color: '#f9f6ee',
        background_color: '#f9f6ee',
        // The SVG scales to any size a launcher asks for, but iOS ignores SVG
        // icons entirely and Android needs a maskable one to avoid having the
        // glyph cropped by whatever shape the launcher applies, so the PNGs in
        // public/ cover what the SVG cannot.
        icons: [
          { src: 'favicon.svg', sizes: 'any', type: 'image/svg+xml', purpose: 'any' },
          { src: 'pwa-192x192.png', sizes: '192x192', type: 'image/png', purpose: 'any' },
          { src: 'pwa-512x512.png', sizes: '512x512', type: 'image/png', purpose: 'any' },
          {
            src: 'pwa-maskable-512x512.png',
            sizes: '512x512',
            type: 'image/png',
            purpose: 'maskable',
          },
        ],
      },
      workbox: {
        globPatterns: ['**/*.{js,css,html,ico,png,svg,woff2}'],
      },
    }),
  ],
  resolve: {
    alias: { '@': path.resolve(import.meta.dirname, 'src') },
  },
  build: {
    outDir: 'dist',
    sourcemap: true,
  },
  // Preview only, never dev: the dev server injects styles and the HMR
  // client inline, which the production policy correctly forbids.
  preview: {
    headers: productionHeaders(),
  },
  test: {
    name: 'web',
    environment: 'node',
    include: ['src/**/*.test.{ts,tsx}'],
  },
})
