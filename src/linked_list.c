//  linked_list.c — Linked List untuk data utama wilayah
//
//  Kenapa Linked List?
//  → Jumlah wilayah tidak harus diketahui di awal
//  → Insert O(1) di head, tidak perlu geser elemen seperti array
//  → Di C tidak ada dynamic array bawaan, LL lebih natural

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/aquadistrib.h"

// ── INSERT ───────────────────────────────────────────────────
// Menyisipkan wilayah baru di HEAD linked list
// Kompleksitas: O(1)
NodeWilayah* ll_insert(NodeWilayah *head, Wilayah w) {
    NodeWilayah *baru = (NodeWilayah*)malloc(sizeof(NodeWilayah));
    if (!baru) {
        printf("[ERROR] Gagal alokasi memori!\n");
        return head;
    }
    baru->data = w;
    baru->next = head;  // node baru menunjuk ke head lama
    return baru;        // node baru jadi head baru
}

// ── INSERTION SORT ───────────────────────────────────────────
// Mengurutkan linked list secara descending berdasarkan skor
// Cara: swap VALUE antar node (lebih simpel dari swap pointer)
// Kompleksitas: O(n^2) worst case, O(n) best case (sudah terurut)
void ll_insertion_sort(NodeWilayah *head) {
    if (!head || !head->next) return; // 0 atau 1 node, skip

    NodeWilayah *i, *j;
    Wilayah temp;

    // Mirip bubble sort tapi lebih efisien untuk data hampir terurut
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            // Jika skor node j lebih besar, tukar nilainya
            if (j->data.skor > i->data.skor) {
                temp    = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// ── SEARCH ───────────────────────────────────────────────────
// Mencari wilayah berdasarkan nama (Linear Search)
// Kompleksitas: O(n)
NodeWilayah* ll_search(NodeWilayah *head, char *nama) {
    NodeWilayah *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->data.nama, nama) == 0)
            return curr; // ditemukan
        curr = curr->next;
    }
    return NULL; // tidak ditemukan
}

// ── PRINT ────────────────────────────────────────────────────
// Menampilkan semua data wilayah (sebelum distribusi)
void ll_print(NodeWilayah *head) {
    NodeWilayah *curr = head;
    int no = 1;
    printf("\n%-4s %-20s %-10s %-8s %-8s %-6s\n",
           "No", "Nama Wilayah", "Penduduk", "Stok(L)", "Urgensi", "Skor");
    printf("%-4s %-20s %-10s %-8s %-8s %-6s\n",
           "----", "--------------------", "----------", "--------", "--------", "------");
    while (curr != NULL) {
        printf("%-4d %-20s %-10d %-8.0f %-8d %-6.2f\n",
               no++,
               curr->data.nama,
               curr->data.penduduk,
               curr->data.stok,
               curr->data.urgensi,
               curr->data.skor);
        curr = curr->next;
    }
}

// ── FREE MEMORY ──────────────────────────────────────────────
// Bebaskan semua node agar tidak memory leak
void ll_free(NodeWilayah *head) {
    NodeWilayah *curr = head;
    while (curr != NULL) {
        NodeWilayah *next = curr->next;
        free(curr);
        curr = next;
    }
}