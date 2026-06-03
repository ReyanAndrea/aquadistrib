//  main.c — Entry point AquaDistrib CLI
//
//  Alur program:
//  1. Input data wilayah → simpan ke Linked List
//  2. Hitung skor prioritas tiap wilayah
//  3. Insertion Sort linked list (descending by skor)
//  4. Masukkan ke Max-Heap
//  5. Greedy distribusi → catat ke Log (Linked List 2)
//  6. Cetak laporan akhir

#include <stdio.h>
#include <stdlib.h>
#include "../include/aquadistrib.h"

// ── BANNER ───────────────────────────────────────────────────
void tampil_banner() {
    printf("======================================================\n");
    printf("        AquaDistrib - v1.0                          \n");
    printf("  Sistem Analisis & Optimasi Distribusi Air Bersih  \n");
    printf("        SDG 6: Clean Water & Sanitation             \n");
    printf("======================================================\n\n");
}

// ── MENU ───────────────────────────────────────────────────
void tampil_menu() {
    printf("\n+-----------------------------+\n");
    printf("|         MENU UTAMA          |\n");
    printf("+-----------------------------+\n");
    printf("| [1] Input Data Wilayah      |\n");
    printf("| [2] Tampilkan Data Wilayah  |\n");
    printf("| [3] Cari Wilayah            |\n");
    printf("| [4] Jalankan Distribusi     |\n");
    printf("| [5] Tampilkan Log           |\n");
    printf("| [0] Keluar                  |\n");
    printf("+-----------------------------+\n");
    printf("Pilihan: ");
}

// ── MAIN ─────────────────────────────────────────────────────
int main() {
    NodeWilayah *data_head = NULL; // Linked List 1: data wilayah
    NodeLog     *log_head  = NULL; // Linked List 2: log distribusi
    MaxHeap      heap;
    heap_init(&heap);

    float pasokan    = 0;
    int   sudah_dist = 0; // flag: apakah distribusi sudah dijalankan
    int   pilihan;

    tampil_banner();

    while (1) {
        tampil_menu();
        scanf("%d", &pilihan);

        switch (pilihan) {

        // ── MENU 1: INPUT DATA ──────────────────────────────
        case 1: {
            if (sudah_dist) {
                printf("[INFO] Distribusi sudah dijalankan. Reset dulu jika ingin input ulang.\n");
                break;
            }
            int n;
            printf("\nJumlah wilayah yang akan diinput: ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++) {
                printf("\n--- Wilayah %d ---\n", i + 1);
                Wilayah w;
                input_wilayah(&w);
                data_head = ll_insert(data_head, w);
            }

            printf("\nTotal pasokan air tersedia (liter): ");
            scanf("%f", &pasokan);

            printf("\n[OK] %d wilayah berhasil diinput.\n", n);
            break;
        }

        // ── MENU 2: TAMPILKAN DATA ──────────────────────────
        case 2: {
            if (!data_head) {
                printf("[INFO] Belum ada data wilayah.\n");
                break;
            }
            printf("\n=== DATA WILAYAH ===\n");
            // Hitung skor dulu sebelum tampil (jika belum)
            hitung_semua_skor(data_head);
            ll_print(data_head);
            break;
        }

        // ── MENU 3: CARI WILAYAH ────────────────────────────
        case 3: {
            if (!data_head) {
                printf("[INFO] Belum ada data wilayah.\n");
                break;
            }
            char nama[MAX_NAMA];
            printf("Masukkan nama wilayah: ");
            scanf("%s", nama);

            NodeWilayah *hasil = ll_search(data_head, nama);
            if (hasil) {
                printf("\n[DITEMUKAN]\n");
                printf("  Nama     : %s\n", hasil->data.nama);
                printf("  Penduduk : %d\n", hasil->data.penduduk);
                printf("  Stok air : %.0f L\n", hasil->data.stok);
                printf("  Urgensi  : %d\n", hasil->data.urgensi);
                printf("  Skor     : %.2f\n", hasil->data.skor);
            } else {
                printf("[INFO] Wilayah '%s' tidak ditemukan.\n", nama);
            }
            break;
        }

        // ── MENU 4: JALANKAN DISTRIBUSI ─────────────────────
        case 4: {
            if (!data_head) {
                printf("[INFO] Input data wilayah dulu (menu 1).\n");
                break;
            }
            if (sudah_dist) {
                printf("[INFO] Distribusi sudah pernah dijalankan.\n");
                printf("       Lihat laporan di menu 5 atau tampilkan log.\n");
                break;
            }
            if (pasokan <= 0) {
                printf("[INFO] Pasokan air belum diset. Input data dulu (menu 1).\n");
                break;
            }

            printf("\n[PROSES] Menghitung skor prioritas...\n");
            hitung_semua_skor(data_head);

            printf("[PROSES] Mengurutkan wilayah (Insertion Sort)...\n");
            ll_insertion_sort(data_head);

            printf("[PROSES] Membangun Priority Queue (Max-Heap)...\n");
            // Masukkan semua wilayah dari linked list ke heap
            NodeWilayah *curr = data_head;
            while (curr != NULL) {
                heap_insert(&heap, curr->data);
                curr = curr->next;
            }

            printf("[PROSES] Menjalankan Greedy Allocation...\n");
            log_head = distribusi_greedy(&heap, pasokan);
            sudah_dist = 1;

            printf("\n[OK] Distribusi selesai! Lihat laporan lengkap di menu 5.\n");
            break;
        }

        // ── MENU 5: LAPORAN & LOG ───────────────────────────
        case 5: {
            if (!sudah_dist) {
                printf("[INFO] Jalankan distribusi dulu (menu 4).\n");
                break;
            }
            cetak_laporan(data_head, log_head, pasokan);
            log_print(log_head);
            break;
        }

        // ── MENU 0: KELUAR ──────────────────────────────────
        case 0: {
            printf("\nTerima kasih telah menggunakan AquaDistrib!\n");
            printf("Membebaskan memori...\n");
            ll_free(data_head);
            log_free(log_head);
            return 0;
        }

        default:
            printf("[ERROR] Pilihan tidak valid.\n");
        }
    }
}