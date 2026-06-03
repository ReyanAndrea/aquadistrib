//  log.c — Linked List kedua: audit trail distribusi
//
//  Setiap kali air didistribusikan ke suatu wilayah,
//  transaksinya dicatat di sini. Insert selalu di head → O(1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aquadistrib.h"

// ── INSERT LOG ───────────────────────────────────────────────
// Tambah entri log distribusi di depan (head)
// Kompleksitas: O(1)
NodeLog* log_insert(NodeLog *head, char *nama, float alokasi, int status) {
    NodeLog *baru = (NodeLog*)malloc(sizeof(NodeLog));
    if (!baru) {
        printf("[ERROR] Gagal alokasi memori log!\n");
        return head;
    }
    strncpy(baru->nama, nama, MAX_NAMA);
    baru->alokasi = alokasi;
    baru->status  = status;
    baru->next    = head;
    return baru;
}

// ── PRINT LOG ────────────────────────────────────────────────
// Tampilkan riwayat distribusi (dari yang paling akhir diproses)
void log_print(NodeLog *head) {
    NodeLog *curr = head;
    printf("\n=== LOG DISTRIBUSI (Audit Trail) ===\n");
    if (!curr) {
        printf("  (kosong)\n");
        return;
    }
    int no = 1;
    while (curr != NULL) {
        char *label;
        if      (curr->status == STATUS_TERLAYANI) label = "TERLAYANI";
        else if (curr->status == STATUS_SEBAGIAN)  label = "SEBAGIAN ";
        else                                        label = "TIDAK    ";

        printf("  %d. %-20s | %.0f L | %s\n",
               no++, curr->nama, curr->alokasi, label);
        curr = curr->next;
    }
}

// ── FREE MEMORY ──────────────────────────────────────────────
void log_free(NodeLog *head) {
    NodeLog *curr = head;
    while (curr != NULL) {
        NodeLog *next = curr->next;
        free(curr);
        curr = next;
    }
}
