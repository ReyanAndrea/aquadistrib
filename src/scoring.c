//  scoring.c — Kalkulasi skor prioritas komposit
//
//  Formula:
//  Skor = (Urgensi × 0.5) + (Kebutuhan_per_kapita × 0.3)
//                         + (1/Stok_tersedia × 0.2)
//
//  Semakin tinggi urgensi dan kebutuhan, semakin besar skor.
//  Semakin sedikit stok, semakin besar skor (wilayah kritis).

#include <stdio.h>
#include "../include/aquadistrib.h"

// Asumsi kebutuhan standar per kapita per hari (liter)
#define KEBUTUHAN_STANDAR 60.0f

// ── HITUNG SKOR SATU WILAYAH ─────────────────────────────────
float hitung_skor(Wilayah w) {
    // Komponen 1: urgensi (bobot 50%)
    float komponen_urgensi = w.urgensi * 0.5f;

    // Komponen 2: rasio kebutuhan vs stok (bobot 30%)
    // Kebutuhan total = penduduk × standar per kapita
    float kebutuhan_total  = w.penduduk * KEBUTUHAN_STANDAR;
    float rasio_kebutuhan  = kebutuhan_total / (w.stok + 1.0f); // +1 hindari div/0
    // Normalisasi agar tidak terlalu dominan
    float komponen_kebutuhan = (rasio_kebutuhan / 1000.0f) * 0.3f;

    // Komponen 3: kelangkaan stok (bobot 20%)
    // Semakin kecil stok, semakin besar nilai ini
    float komponen_stok = (1.0f / (w.stok + 1.0f)) * 0.2f * 10000.0f;

    float skor = komponen_urgensi + komponen_kebutuhan + komponen_stok;
    return skor;
}

// ── HITUNG SKOR SEMUA WILAYAH DI LINKED LIST ─────────────────
// Traverse linked list, isi field skor tiap node
// Kompleksitas: O(n)
void hitung_semua_skor(NodeWilayah *head) {
    NodeWilayah *curr = head;
    while (curr != NULL) {
        curr->data.skor = hitung_skor(curr->data);
        curr = curr->next;
    }
}

