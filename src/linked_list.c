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