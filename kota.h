#ifndef KOTA_H
#define KOTA_H
#define MIN_KOTA 5
#define MAX_KOTA 10

#include "Sll.h"
typedef struct {
    char namaKota[100];
    List daftarWarga;
} Kota;

Kota* buatKota(const char* nama);
void tambahWargaKota(Kota* kota, const char* namaWarga);
void hapusWargaKota(Kota* kota, const char* namaWarga);
void cetakKota(Kota* kota);
void freeKota(Kota* kota);

#endif




