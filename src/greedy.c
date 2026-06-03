//  greedy.c — Algoritma Greedy untuk distribusi air
//
//  Strategi: pada setiap iterasi, pilih wilayah dengan skor
//  TERTINGGI (sudah ada di Max-Heap), alokasikan air sesuai
//  kebutuhan. Ulangi sampai pasokan habis atau semua terlayani.
//
//  Kenapa Greedy?
//  1. Keputusan lokal-optimal (selalu pilih yang paling butuh)
//    sudah menghasilkan solusi global yang baik untuk masalah
//    alokasi sumber daya dengan satu sumber (single depot)
//  2. Kompleksitas: O(n log n) — n extract dari heap O(log n)

#include <stdio.h>
#include "../include/aquadistrib.h"

// Kebutuhan minimum per wilayah yang dianggap "terlayani penuh"
// = penduduk × 60 liter/hari (standar WHO)
#define KEBUTUHAN_STANDAR 60.0f

// DISTRIBUSI GREEDY 
// Input : MaxHeap berisi wilayah terurut, total pasokan (liter)
// Output: NodeLog* berisi riwayat distribusi
// Kompleksitas: O(n log n)
NodeLog* distribusi_greedy(MaxHeap *h, float pasokan) {
    NodeLog *log_head = NULL;
    float sisa = pasokan;

    printf("\n[GREEDY] Memulai distribusi air...\n");
    printf("         Pasokan awal: %.0f liter\n\n", pasokan);

    while (!heap_is_empty(h) && sisa > 0) {
        // Ambil wilayah prioritas tertinggi dari heap → O(log n)
        Wilayah w = heap_extract_max(h);

        // Hitung kebutuhan wilayah ini
        float kebutuhan = w.penduduk * KEBUTUHAN_STANDAR;
        float alokasi;
        int   status;

        if (sisa >= kebutuhan) {
            // Pasokan cukup untuk memenuhi kebutuhan penuh
            alokasi = kebutuhan;
            status  = STATUS_TERLAYANI;
            sisa   -= alokasi;
        } else {
            // Pasokan tidak cukup, berikan sisa yang ada
            alokasi = sisa;
            status  = STATUS_SEBAGIAN;
            sisa    = 0;
        }

        w.alokasi = alokasi;
        w.status  = status;

        // Catat ke log (Linked List kedua)
        log_head = log_insert(log_head, w.nama, alokasi, status);

        printf("  -> %-20s | Skor: %5.2f | Alokasi: %7.0f L | %s\n",
               w.nama, w.skor, alokasi,
               status == STATUS_TERLAYANI ? "TERLAYANI" : "SEBAGIAN");
    }

    // Wilayah yang tersisa di heap (pasokan sudah habis)
    while (!heap_is_empty(h)) {
        Wilayah w = heap_extract_max(h);
        log_head = log_insert(log_head, w.nama, 0, STATUS_BELUM);
        printf("  -> %-20s | Skor: %5.2f | Alokasi:       0 L | TIDAK TERLAYANI\n",
               w.nama, w.skor);
    }

    printf("\n[GREEDY] Selesai. Sisa pasokan: %.0f liter\n", sisa);
    return log_head;
}
