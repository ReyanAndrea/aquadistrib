//  utils.c — Fungsi utilitas: input, laporan, tampilan
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aquadistrib.h"

// ── INPUT SATU WILAYAH ───────────────────────────────────────
void input_wilayah(Wilayah *w) {
    printf("  Nama wilayah   : ");
    scanf("%s", w->nama);
    printf("  Jumlah penduduk: ");
    scanf("%d", &w->penduduk);
    printf("  Stok air (L)   : ");
    scanf("%f", &w->stok);
    printf("  Urgensi (1-5)  : ");
    scanf("%d", &w->urgensi);

    // Validasi urgensi
    if (w->urgensi < 1) w->urgensi = 1;
    if (w->urgensi > 5) w->urgensi = 5;

    w->skor    = 0;
    w->alokasi = 0;
    w->status  = STATUS_BELUM;
}

// ── CETAK LAPORAN AKHIR ──────────────────────────────────────
// Menampilkan hasil distribusi dalam format tabel rapi
void cetak_laporan(NodeWilayah *data_head, NodeLog *log_head, float pasokan) {
    printf("\n");
    printf("==================================================================\n");
    printf("         LAPORAN DISTRIBUSI AIR BERSIH - AquaDistrib             \n");
    printf("==================================================================\n");
    printf("| %-4s %-20s %-6s %-10s %-13s |\n",
           "No", "Wilayah", "Skor", "Alokasi(L)", "Status");
    printf("==================================================================\n");

    NodeLog *curr = log_head;
    float total_alokasi = 0;
    int terlayani = 0, sebagian = 0, tidak = 0;

    #define MAX_LOG 100
    NodeLog *arr[MAX_LOG];
    int count = 0;
    while (curr && count < MAX_LOG) {
        arr[count++] = curr;
        curr = curr->next;
    }

    for (int i = count - 1; i >= 0; i--) {
        char *label;
        if      (arr[i]->status == STATUS_TERLAYANI) { label = "TERLAYANI    "; terlayani++; }
        else if (arr[i]->status == STATUS_SEBAGIAN)  { label = "SEBAGIAN     "; sebagian++;  }
        else                                          { label = "TDK TERLAYANI"; tidak++;     }

        float skor = 0;
        NodeWilayah *cari = ll_search(data_head, arr[i]->nama);
        if (cari) skor = cari->data.skor;

        printf("| %-4d %-20s %-6.2f %-10.0f %-13s |\n",
            count - i, arr[i]->nama, skor, arr[i]->alokasi, label);
        total_alokasi += arr[i]->alokasi;
    }

    printf("==================================================================\n");
    printf("| Total pasokan   : %-10.0f L                               |\n", pasokan);
    printf("| Terdistribusi   : %-10.0f L                               |\n", total_alokasi);
    printf("| Terlayani penuh : %-3d wilayah                               |\n", terlayani);
    printf("| Sebagian        : %-3d wilayah                               |\n", sebagian);
    printf("| Tidak terlayani : %-3d wilayah                               |\n", tidak);
    printf("==================================================================\n");
}

// ── CLEAR SCREEN ─────────────────────────────────────────────
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
