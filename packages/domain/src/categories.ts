/**
 * Spending and income categories.
 *
 * These are the categories from `struct MoneytoryGroupingPerCategory` in the
 * original C program, kept in the groupings the source laid them out in. The
 * names are carried over deliberately: the point of this rewrite is that the
 * domain survives the change of language, so a category that existed in the
 * terminal version still means the same thing here.
 *
 * Two spelling slips in the original C field names are corrected here, since
 * these ids appear in CSV exports: `AccountReceiveable` and
 * `HouseAndAppartmentRent`.
 */

export type Flow = 'income' | 'expense'

export interface Category {
  id: string
  group: CategoryGroupId
  /** Whether this category normally records money coming in or going out. */
  flow: Flow
  /** English label. */
  en: string
  /** Indonesian label. */
  id_: string
  emoji: string
}

export const CATEGORY_GROUPS = [
  'income', 'bills', 'education', 'family', 'food', 'giving', 'groceries',
  'health', 'leisure', 'lending', 'installments', 'refunds', 'savings',
  'shopping', 'sports', 'transport', 'travel', 'transfers', 'other',
] as const

export type CategoryGroupId = (typeof CATEGORY_GROUPS)[number]

export const CATEGORY_GROUP_LABELS: Record<CategoryGroupId, { en: string; id_: string }> = {
  income: { en: 'Income', id_: 'Pemasukan' },
  bills: { en: 'Bills and Utilities', id_: 'Tagihan dan Utilitas' },
  education: { en: 'Education', id_: 'Pendidikan' },
  family: { en: 'Family', id_: 'Keluarga' },
  food: { en: 'Food and Drink', id_: 'Makanan dan Minuman' },
  giving: { en: 'Gifts and Donations', id_: 'Hadiah dan Donasi' },
  groceries: { en: 'Groceries', id_: 'Belanja Harian' },
  health: { en: 'Health', id_: 'Kesehatan' },
  leisure: { en: 'Leisure', id_: 'Hiburan' },
  lending: { en: 'Loans', id_: 'Pinjaman' },
  installments: { en: 'Installments', id_: 'Cicilan' },
  refunds: { en: 'Refunds', id_: 'Pengembalian Dana' },
  savings: { en: 'Savings and Investments', id_: 'Tabungan dan Investasi' },
  shopping: { en: 'Shopping', id_: 'Belanja' },
  sports: { en: 'Sports', id_: 'Olahraga' },
  transport: { en: 'Transport', id_: 'Transportasi' },
  travel: { en: 'Travel', id_: 'Perjalanan' },
  transfers: { en: 'Transfers and Fees', id_: 'Transfer dan Biaya' },
  other: { en: 'Other', id_: 'Lainnya' },
}

const c = (
  id: string,
  group: CategoryGroupId,
  flow: Flow,
  en: string,
  id_: string,
  emoji: string,
): Category => ({ id, group, flow, en, id_, emoji })

export const CATEGORIES: readonly Category[] = [
  c('account-receivable', 'income', 'income', 'Account Receivable', 'Piutang Usaha', '\u{1F9FE}'),
  c('additional-income', 'income', 'income', 'Additional Income', 'Pemasukan Tambahan', '\u{2795}'),
  c('allowance', 'income', 'income', 'Allowance', 'Uang Saku', '\u{1FA99}'),
  c('bonus', 'income', 'income', 'Bonus', 'Bonus', '\u{1F389}'),
  c('business-profit', 'income', 'income', 'Business Profit', 'Laba Usaha', '\u{1F4C8}'),
  c('incomings', 'income', 'income', 'Incomings', 'Penerimaan', '\u{1F4E5}'),
  c('interests', 'income', 'income', 'Interest', 'Bunga', '\u{1F4B9}'),
  c('investments-withdrawal', 'income', 'income', 'Investment Withdrawal', 'Pencairan Investasi', '\u{1F4E4}'),
  c('salary', 'income', 'income', 'Salary', 'Gaji', '\u{1F4BC}'),

  c('electricity-water-gas', 'bills', 'expense', 'Electricity, Water and Gas', 'Listrik, Air dan Gas', '\u{1F4A1}'),
  c('house-and-apartment-rent', 'bills', 'expense', 'House and Apartment Rent', 'Sewa Rumah dan Apartemen', '\u{1F3E0}'),
  c('household', 'bills', 'expense', 'Household', 'Rumah Tangga', '\u{1F9FA}'),
  c('insurance', 'bills', 'expense', 'Insurance', 'Asuransi', '\u{1F6E1}'),
  c('mobile-and-data', 'bills', 'expense', 'Mobile and Data', 'Pulsa dan Kuota', '\u{1F4F1}'),
  c('handheld-electric-device', 'bills', 'expense', 'Handheld Electric Device', 'Perangkat Elektronik Genggam', '\u{1F50C}'),
  c('tv-and-internet', 'bills', 'expense', 'TV and Internet', 'TV dan Internet', '\u{1F4FA}'),

  c('classes-and-workshops', 'education', 'expense', 'Classes and Workshops', 'Kelas dan Lokakarya', '\u{1F393}'),
  c('school-supplies', 'education', 'expense', 'School Supplies', 'Perlengkapan Sekolah', '\u{1F4DA}'),
  c('tuition-fee', 'education', 'expense', 'Tuition Fee', 'Uang Kuliah', '\u{1F3EB}'),

  c('children-family-needs', 'family', 'expense', 'Children and Family Needs', 'Kebutuhan Anak dan Keluarga', '\u{1F476}'),
  c('parent-family-needs', 'family', 'expense', 'Parent Family Needs', 'Kebutuhan Orang Tua', '\u{1F46A}'),

  c('daily-meal', 'food', 'expense', 'Daily Meal', 'Makan Harian', '\u{1F35A}'),
  c('snacks-and-drinks', 'food', 'expense', 'Snacks and Drinks', 'Camilan dan Minuman', '\u{1F964}'),

  c('gifting', 'giving', 'expense', 'Gifting', 'Hadiah', '\u{1F381}'),
  c('charity', 'giving', 'expense', 'Charity', 'Amal', '\u{1F932}'),

  c('groceries', 'groceries', 'expense', 'Groceries', 'Belanja Harian', '\u{1F6D2}'),

  c('doctor-and-hospital', 'health', 'expense', 'Doctor and Hospital', 'Dokter dan Rumah Sakit', '\u{1F3E5}'),
  c('medicines', 'health', 'expense', 'Medicines', 'Obat obatan', '\u{1F48A}'),
  c('personal-care', 'health', 'expense', 'Personal Care', 'Perawatan Diri', '\u{1F9F4}'),

  c('books', 'leisure', 'expense', 'Books', 'Buku', '\u{1F4D6}'),
  c('dining-out', 'leisure', 'expense', 'Dining Out', 'Makan di Luar', '\u{1F37D}'),
  c('games', 'leisure', 'expense', 'Games', 'Permainan', '\u{1F3AE}'),
  c('hobby', 'leisure', 'expense', 'Hobby', 'Hobi', '\u{1F3A8}'),
  c('movies-and-music', 'leisure', 'expense', 'Movies and Music', 'Film dan Musik', '\u{1F3AC}'),
  c('pets', 'leisure', 'expense', 'Pets', 'Hewan Peliharaan', '\u{1F43E}'),

  c('loan-disbursements', 'lending', 'income', 'Loan Disbursement', 'Pencairan Pinjaman', '\u{1F3E6}'),

  c('car-installments', 'installments', 'expense', 'Car Installments', 'Cicilan Mobil', '\u{1F697}'),
  c('credit-card', 'installments', 'expense', 'Credit Card', 'Kartu Kredit', '\u{1F4B3}'),
  c('home-mortgage', 'installments', 'expense', 'Home Mortgage', 'KPR', '\u{1F3E1}'),

  c('refunds', 'refunds', 'income', 'Refunds', 'Pengembalian Dana', '\u{21A9}'),
  c('reimbursements', 'refunds', 'income', 'Reimbursements', 'Penggantian Biaya', '\u{1F9FE}'),

  c('investments', 'savings', 'expense', 'Investments', 'Investasi', '\u{1F4CA}'),
  c('savings', 'savings', 'expense', 'Savings', 'Tabungan', '\u{1F416}'),

  c('fashions', 'shopping', 'expense', 'Fashion', 'Fesyen', '\u{1F457}'),
  c('gadget-and-electronics', 'shopping', 'expense', 'Gadgets and Electronics', 'Gawai dan Elektronik', '\u{1F4BB}'),
  c('home-appliances', 'shopping', 'expense', 'Home Appliances', 'Peralatan Rumah', '\u{1F9EF}'),

  c('sport-activities', 'sports', 'expense', 'Sport Activities', 'Aktivitas Olahraga', '\u{1F3C3}'),
  c('sport-equipments', 'sports', 'expense', 'Sport Equipment', 'Peralatan Olahraga', '\u{1F3CB}'),

  c('daily-transportations', 'transport', 'expense', 'Daily Transport', 'Transportasi Harian', '\u{1F68C}'),
  c('gasolines', 'transport', 'expense', 'Fuel', 'Bahan Bakar', '\u{26FD}'),
  c('parking-and-toll-fee', 'transport', 'expense', 'Parking and Toll', 'Parkir dan Tol', '\u{1F17F}'),
  c('vehicle-maintenance', 'transport', 'expense', 'Vehicle Maintenance', 'Perawatan Kendaraan', '\u{1F527}'),

  c('attractions-and-tours', 'travel', 'expense', 'Attractions and Tours', 'Wisata dan Tur', '\u{1F3A1}'),
  c('hotel-and-villa', 'travel', 'expense', 'Hotel and Villa', 'Hotel dan Vila', '\u{1F3E8}'),
  c('transports-on-vacations', 'travel', 'expense', 'Holiday Transport', 'Transportasi Liburan', '\u{2708}'),

  c('cash-withdrawal', 'transfers', 'expense', 'Cash Withdrawal', 'Tarik Tunai', '\u{1F3E7}'),
  c('cost-and-taxes', 'transfers', 'expense', 'Costs and Taxes', 'Biaya dan Pajak', '\u{1F9EE}'),
  c('send-to-business', 'transfers', 'expense', 'Send to Business', 'Kirim ke Bisnis', '\u{1F3E2}'),
  c('send-to-personal', 'transfers', 'expense', 'Send to Personal', 'Kirim ke Pribadi', '\u{1F464}'),
  c('top-up-ewallet-cards', 'transfers', 'expense', 'Top Up E Wallet and Cards', 'Isi Ulang E Wallet dan Kartu', '\u{1F4B3}'),

  c('uncategorized', 'other', 'expense', 'Uncategorised', 'Belum Dikategorikan', '\u{2753}'),
  c('others', 'other', 'expense', 'Other', 'Lainnya', '\u{1F4E6}'),
]

export const CATEGORY_BY_ID: ReadonlyMap<string, Category> = new Map(
  CATEGORIES.map((cat) => [cat.id, cat]),
)

export function categoryById(id: string): Category | undefined {
  return CATEGORY_BY_ID.get(id)
}

export function categoriesForFlow(flow: Flow): readonly Category[] {
  return CATEGORIES.filter((cat) => cat.flow === flow)
}

export function categoriesInGroup(group: CategoryGroupId): readonly Category[] {
  return CATEGORIES.filter((cat) => cat.group === group)
}
