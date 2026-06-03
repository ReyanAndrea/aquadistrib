#ifndef AQUADISTRIB_H
#define AQUADISTRIB_H

//  aquadistrib.h — Definisi struct & deklarasi semua fungsi
// ============================================================

#define MAX_NAMA 50

// ── STRUCT UTAMA ─────────────────────────────────────────────
// Satu wilayah menyimpan semua atribut yang dibutuhkan sistem
typedef struct Wilayah {
    char   nama[MAX_NAMA];
    int    penduduk;
    float  stok;       // stok air saat ini (liter)
    int    urgensi;    // skala 1-5
    float  skor;       // dihitung otomatis oleh sistem
    float  alokasi;    // hasil distribusi
    int    status;     // 0=belum, 1=terlayani, 2=sebagian
} Wilayah;

// ── NODE LINKED LIST ─────────────────────────────────────────
typedef struct NodeWilayah {
    Wilayah data;
    struct NodeWilayah *next;
} NodeWilayah;

// ── NODE LOG (Linked List kedua untuk audit trail) ───────────
typedef struct NodeLog {
    char   nama[MAX_NAMA];
    float  alokasi;
    int    status;
    struct NodeLog *next;
} NodeLog;

// ── MAX-HEAP (Priority Queue) ─────────────────────────────────
#define MAX_HEAP 100
typedef struct {
    Wilayah data[MAX_HEAP];
    int     size;
} MaxHeap;

// ── STATUS LABEL ─────────────────────────────────────────────
#define STATUS_BELUM     0
#define STATUS_TERLAYANI 1
#define STATUS_SEBAGIAN  2

//  DEKLARASI FUNGSI (implementasi di masing-masing .c)
// =============================================================

// linked_list.c
NodeWilayah* ll_insert(NodeWilayah *head, Wilayah w);
void         ll_print(NodeWilayah *head);
NodeWilayah* ll_search(NodeWilayah *head, char *nama);
void         ll_insertion_sort(NodeWilayah *head);
void         ll_free(NodeWilayah *head);

// log.c
NodeLog*     log_insert(NodeLog *head, char *nama, float alokasi, int status);
void         log_print(NodeLog *head);
void         log_free(NodeLog *head);

// heap.c
void         heap_insert(MaxHeap *h, Wilayah w);
Wilayah      heap_extract_max(MaxHeap *h);
int          heap_is_empty(MaxHeap *h);
void         heap_init(MaxHeap *h);

// scoring.c
float        hitung_skor(Wilayah w);
void         hitung_semua_skor(NodeWilayah *head);

// greedy.c
NodeLog*     distribusi_greedy(MaxHeap *h, float pasokan);

// utils.c
void         cetak_laporan(NodeWilayah *data_head, NodeLog *log_head, float pasokan);
void         input_wilayah(Wilayah *w);
void         clear_screen();

#endif