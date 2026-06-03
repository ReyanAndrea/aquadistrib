# AquaDistrib
### Sistem Analisis dan Optimasi Distribusi Air Bersih Berbasis Prioritas Wilayah

> Proyek UAS Praktikum Struktur Data dan Algoritma B
> SDG 6: Clean Water & Sanitation — Kelompok 04 Prak SDA B

---

## Deskripsi

AquaDistrib adalah sistem berbasis **Command Line Interface (CLI)** yang dirancang untuk menganalisis dan mengoptimalkan distribusi air bersih ke berbagai wilayah berdasarkan tingkat kebutuhan, ketersediaan sumber air, dan jumlah penduduk.

Sistem ini berkontribusi langsung pada **SDG 6 (Clean Water and Sanitation)** dengan membantu pengambil keputusan seperti PDAM atau dinas terkait dalam mengalokasikan pasokan air secara adil, terukur, dan berbasis data.

---

## Struktur Project

```
aquadistrib/
├── include/
│   └── aquadistrib.h     # Definisi struct & deklarasi semua fungsi
├── src/
│   ├── main.c            # Entry point & menu CLI utama
│   ├── linked_list.c     # LL data wilayah + Insertion Sort + Linear Search
│   ├── log.c             # LL kedua untuk audit trail distribusi
│   ├── heap.c            # Priority Queue berbasis Max-Heap
│   ├── scoring.c         # Kalkulasi skor prioritas komposit
│   ├── greedy.c          # Algoritma Greedy untuk distribusi air
│   └── utils.c           # Input, laporan CLI, helper
└── Makefile
```

---

## Struktur Data & Algoritma

### Struktur Data
| # | Struktur Data | Kegunaan |
|---|---|---|
| 1 | Linked List (NodeWilayah) | Menyimpan data utama wilayah secara dinamis |
| 2 | Linked List (NodeLog) | Audit trail setiap transaksi distribusi |
| 3 | Max-Heap (Priority Queue) | Antrian wilayah berdasarkan skor prioritas tertinggi |

### Algoritma
| # | Algoritma | Kegunaan | Kompleksitas |
|---|---|---|---|
| 1 | Insertion Sort | Mengurutkan wilayah berdasarkan skor (descending) | O(n^2) / O(n) |
| 2 | Greedy Algorithm | Mengalokasikan pasokan air secara optimal | O(n log n) |
| 3 | Linear Search | Mencari wilayah berdasarkan nama | O(n) |

---

## Cara Menjalankan

### Kompilasi (Windows)
```
gcc -Wall -I./include -o aquadistrib src/main.c src/linked_list.c src/log.c src/heap.c src/scoring.c src/greedy.c src/utils.c
```

### Jalankan (Windows)
```
.\aquadistrib
```

### Linux / Mac
```
make
./aquadistrib
```

---

## Tim Pengembang

| Nama | NIM | Tanggung Jawab |
|---|---|---|
| Reyan Andrea | 2208107010014 | main.c + utils.c + Intergrasi Sistem |
| Muhammad Haikal Al Fikrah | 250810701100084 | greedy.c + log.c |
| Iza Humaira Irwanda | 250810701100047 | linked_list.c + scoring.c |
| Bilqisthi Alya Karenina | 250810701100097 | heap.c |

---

## Referensi

- Cormen, T.H. et al. (2009). Introduction to Algorithms, 3rd Ed. MIT Press.
- Lafore, R. (2002). Data Structures and Algorithms in C++. Sams Publishing.
- UN SDGs. Goal 6: Clean Water and Sanitation. https://sdgs.un.org/goals/goal6
- GeeksforGeeks. Data Structures & Algorithms. https://www.geeksforgeeks.org

---

*Praktikum Struktur Data dan Algoritma B · Universitas Syiah Kuala · 2026*