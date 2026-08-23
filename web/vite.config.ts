import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import tailwindcss from '@tailwindcss/vite'
import path from 'node:path'

// Deployed to https://eintswavex.github.io/FinancialAM/, so every asset URL has
// to be prefixed with the repository name. Vite handles that through `base`.
export default defineConfig({
  base: '/FinancialAM/',
  plugins: [react(), tailwindcss()],
  resolve: {
    alias: { '@': path.resolve(import.meta.dirname, 'src') },
  },
  build: {
    outDir: 'dist',
    sourcemap: true,
  },
})
