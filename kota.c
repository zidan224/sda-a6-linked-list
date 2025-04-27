#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kota.h"

Kota* buatKota(const char* nama) {
    Kota* baru = (Kota*)malloc(sizeof(Kota));
    if (!baru) {
        printf("Gagal alokasi kota.\n");
        exit(1);
    }
    strcpy(baru->namaKota, nama);
    CreateList(&(baru->daftarWarga));
    return baru;
}

void tambahWargaKota(Kota* kota, const char* namaWarga) {
    infotype warga;
    strcpy(warga.nama, namaWarga);
    InsVLast(&(kota->daftarWarga), warga);
}

void hapusWargaKota(Kota* kota, const char* namaWarga) {
    address p = First(kota->daftarWarga);
    while (p != Nil) {
        if (strcmp(Info(p).nama, namaWarga) == 0) {
            DelP(&(kota->daftarWarga), Info(p));
            break;
        }
        p = Next(p);
    }
}

void cetakKota(Kota* kota) {
    printf("Kota: %s\n", kota->namaKota);
    PrintInfo(kota->daftarWarga);
}

void freeKota(Kota* kota) {
    DelAll(&(kota->daftarWarga));
    free(kota);
}



