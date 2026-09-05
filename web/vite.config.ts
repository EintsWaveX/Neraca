import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import tailwindcss from '@tailwindcss/vite'
import { VitePWA } from 'vite-plugin-pwa'
import path from 'node:path'

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
        name: 'FinancialAM',
        short_name: 'FinancialAM',
        description: 'A personal finance manager in your browser',
        display: 'standalone',
        // A manifest cannot read a CSS custom property, so these two are the
        // only place a colour is written literally. They are the sRGB values of
        // the --accent and --surface tokens in src/index.css, not a Tailwind
        // palette entry. If those tokens move, these move with them.
        theme_color: '#008f86',
        background_color: '#ffffff',
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
})
