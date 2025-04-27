#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kota.h"



int main() {
    int kapasitasKota = 0; // Banyaknya kota yang boleh ditambah
    int jumlahKota = 0;    // Kota yang sudah ditambah
    Kota** daftarKota = NULL;
    int pilihan;
    int i;

    // Input jumlah kota (kapasitas)
    do {
        printf("Masukkan berapa kota yang ingin dimasukkan (minimal %d, maksimal %d): ", MIN_KOTA, MAX_KOTA);
        scanf("%d", &kapasitasKota);
        getchar();
        if (kapasitasKota < MIN_KOTA || kapasitasKota > MAX_KOTA) {
            printf("Input tidak valid! Harus antara %d dan %d.\n", MIN_KOTA, MAX_KOTA);
        }
    } while (kapasitasKota < MIN_KOTA || kapasitasKota > MAX_KOTA);

    // Alokasikan array kota
    daftarKota = malloc(kapasitasKota * sizeof(Kota*));
    if (daftarKota == NULL) {
        printf("Error: Gagal alokasi memori.\n");
        return 1;
    }

    // Langsung masuk ke menu
    do {
        printf("\n=== Menu ===\n");
        printf("1. Tambah Kota\n");
        printf("2. Tambah Warga ke Kota\n");
        printf("3. Hapus Warga dari Kota\n");
        printf("4. Hapus Kota\n");
        printf("5. Tampilkan Data\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        if (pilihan == 1) {
            if (jumlahKota >= kapasitasKota) {
                printf("Sudah mencapai jumlah kota maksimum yang diinput (%d kota).\n", kapasitasKota);
                continue;
            }

            char namaKota[100];
            printf("Nama kota: ");
            fgets(namaKota, sizeof(namaKota), stdin);
            namaKota[strcspn(namaKota, "\n")] = 0;

            daftarKota[jumlahKota] = buatKota(namaKota);
            jumlahKota++;
            printf("Kota %s ditambahkan.\n", namaKota);

        } else if (pilihan == 2) {
            // Tambah Warga ke Kota
            char namaKota[100], namaWarga[100];
            printf("Nama kota: ");
            fgets(namaKota, sizeof(namaKota), stdin);
            namaKota[strcspn(namaKota, "\n")] = 0;

            int found = -1;
            for (i = 0; i < jumlahKota; i++) {
                if (strcmp(daftarKota[i]->namaKota, namaKota) == 0) {
                    found = i;
                    break;
                }
            }
            if (found == -1) {
                printf("Kota tidak ditemukan.\n");
                continue;
            }

            printf("Nama warga: ");
            fgets(namaWarga, sizeof(namaWarga), stdin);
            namaWarga[strcspn(namaWarga, "\n")] = 0;

            tambahWargaKota(daftarKota[found], namaWarga);

        } else if (pilihan == 3) {
            // Hapus Warga dari Kota
            char namaKota[100], namaWarga[100];
            printf("Nama kota: ");
            fgets(namaKota, sizeof(namaKota), stdin);
            namaKota[strcspn(namaKota, "\n")] = 0;

            int found = -1;
            for (i = 0; i < jumlahKota; i++) {
                if (strcmp(daftarKota[i]->namaKota, namaKota) == 0) {
                    found = i;
                    break;
                }
            }
            if (found == -1) {
                printf("Kota tidak ditemukan.\n");
                continue;
            }

            printf("Nama warga yang dihapus: ");
            fgets(namaWarga, sizeof(namaWarga), stdin);
            namaWarga[strcspn(namaWarga, "\n")] = 0;

            hapusWargaKota(daftarKota[found], namaWarga);

        } else if (pilihan == 4) {
            // Hapus Kota
            char namaKota[100];
            printf("Nama kota: ");
            fgets(namaKota, sizeof(namaKota), stdin);
            namaKota[strcspn(namaKota, "\n")] = 0;

            int found = -1;
            for (i = 0; i < jumlahKota; i++) {
                if (strcmp(daftarKota[i]->namaKota, namaKota) == 0) {
                    found = i;
                    break;
                }
            }
            if (found == -1) {
                printf("Kota tidak ditemukan.\n");
                continue;
            }

            freeKota(daftarKota[found]);
            for (i = found; i < jumlahKota - 1; i++) {
                daftarKota[i] = daftarKota[i + 1];
            }
            jumlahKota--;
            printf("Kota %s dihapus.\n", namaKota);

        } else if (pilihan == 5) {
            // Tampilkan Data
            for (i = 0; i < jumlahKota; i++) {
                cetakKota(daftarKota[i]);
            }
        }

    } while (pilihan != 0);

    // Bersihkan semua memori
    for (i = 0; i < jumlahKota; i++) {
        freeKota(daftarKota[i]);
    }
    free(daftarKota);

    printf("Program selesai.\n");
    return 0;
}
