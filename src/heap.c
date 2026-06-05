//  heap.c — Priority Queue berbasis Max-Heap
//
//  Kenapa Max-Heap?
//  → Extract wilayah prioritas tertinggi: O(log n)
//  → Lebih efisien dari cari max di array biasa: O(n)
//
//  Representasi: array, parent di index i → anak di 2i+1, 2i+2

#include <stdio.h>
#include "../include/aquadistrib.h"

// Helper: tukar dua elemen heap
static void swap(Wilayah *a, Wilayah *b) {
    Wilayah temp = *a;
    *a = *b;
    *b = temp;
}

// ── HEAP INIT ────────────────────────────────────────────────
void heap_init(MaxHeap *h) {
    h->size = 0;
}

// ── HEAPIFY UP ───────────────────────────────────────────────
// Setelah insert, naikkan node ke posisi yang benar
// Parent selalu lebih besar dari anak (properti max-heap)
static void heapify_up(MaxHeap *h, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[i].skor > h->data[parent].skor) {
            swap(&h->data[i], &h->data[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

// ── HEAPIFY DOWN ─────────────────────────────────────────────
// Setelah extract, turunkan root ke posisi yang benar
static void heapify_down(MaxHeap *h, int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < h->size && h->data[left].skor  > h->data[largest].skor) largest = left;
    if (right < h->size && h->data[right].skor > h->data[largest].skor) largest = right;

    if (largest != i) {
        swap(&h->data[i], &h->data[largest]);
        heapify_down(h, largest);
    }
}

// ── INSERT ───────────────────────────────────────────────────
// Tambahkan wilayah ke heap, lalu perbaiki posisinya
// Kompleksitas: O(log n)
void heap_insert(MaxHeap *h, Wilayah w) {
    if (h->size >= MAX_HEAP) {
        printf("[ERROR] Heap penuh!\n");
        return;
    }
    h->data[h->size] = w;
    heapify_up(h, h->size);
    h->size++;
}

// ── EXTRACT MAX ──────────────────────────────────────────────
// Ambil wilayah dengan skor tertinggi (root)
// Lalu perbaiki heap agar properti max-heap tetap terjaga
// Kompleksitas: O(log n)
Wilayah heap_extract_max(MaxHeap *h) {
    Wilayah max = h->data[0];           // simpan root (nilai terbesar)
    h->data[0]  = h->data[h->size - 1]; // pindahkan elemen terakhir ke root
    h->size--;
    heapify_down(h, 0);                 // perbaiki posisi root baru
    return max;
}

// ── IS EMPTY ─────────────────────────────────────────────────
int heap_is_empty(MaxHeap *h) {
    return h->size == 0;
}
