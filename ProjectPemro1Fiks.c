#include <stdio.h>
#include <stdlib.h>

// Struktur untuk Makanan dan Minuman
struct Item {
    int kode;
    char nama[50];
    int harga;
};

// Struktur untuk Pesanan
struct Pesanan {
    int kodeItem[20];   // Menyimpan kode item yang dipesan (baik makanan atau minuman)
    int jumlahItem[20]; // Menyimpan jumlah item yang dipesan
    int jenisItem[20];  // Menyimpan jenis item (1 untuk makanan, 2 untuk minuman)
    int totalHarga;     // Menyimpan total harga
    int totalItem;      // Menyimpan jumlah item yang dipesan
    int bayar;          // Menyimpan jumlah uang yang dibayar
    int kembalian;      // Menyimpan jumlah kembalian
};

// Fungsi Prototipe
void tampilMenu(struct Item item[], int n, const char* kategori);
void tampilStruk(struct Pesanan pesanan, struct Item makanan[], struct Item minuman[], int nMakanan, int nMinuman);
void tambahPesanan(int kode, int jumlah, int jenis, struct Pesanan *pesanan, struct Item makanan[], struct Item minuman[], int nMakanan, int nMinuman);
void hitungTotal(struct Pesanan *pesanan, struct Item makanan[], struct Item minuman[], int nMakanan, int nMinuman);
void resetPesanan(struct Pesanan *pesanan);



int main() {
    int pilihan, jumlah;
    // Data Makanan
    struct Item makanan[] = {
        {1, "Soto", 3500},
        {2, "Bakso", 7500},
        {3, "Pecel", 4000},
        {4, "Mie Ayam", 6500},
        {5, "Nasi Goreng", 4500}
    };
    
    // Data Minuman
    struct Item minuman[] = {
        {1, "Es Teh", 1500},
        {2, "Es Jeruk", 2500},
        {3, "Es Sirup", 2000},
        {4, "Soda Gembira", 5000},
        {5, "Es Degan", 3500}
    };

    struct Pesanan pesanan;
    resetPesanan(&pesanan);


    while(1) {
        printf("\n\t\t\tAplikasi Pemesanan Restoran\n");
        printf("\n1. Pesan Makanan\n2. Pesan Minuman\n3. Lihat Struk Pembelian\n4. Reset Pesanan\n5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                tampilMenu(makanan, 5, "Makanan");
                
                while (1) {
                    printf("Masukkan kode makanan yang ingin dipesan (00 untuk selesai): ");
                    scanf("%d", &pilihan);
                    if (pilihan == 00) break;
                    if (pilihan >= 1 && pilihan <= 5) {
                        printf("Masukkan jumlah pesanan: ");
                        scanf("%d", &jumlah);
                        if (jumlah > 0) {
                            tambahPesanan(pilihan, jumlah, 1, &pesanan, makanan, minuman, 5, 5);  // Makanan
                        } else {
                            printf("Jumlah pesanan tidak valid.\n");
                        }
                    } else {
                        printf("Kode makanan tidak valid.\n");
                    }
                }
                break;
            case 2:
                tampilMenu(minuman, 5, "Minuman");
                
                while (1) {
                    printf("Masukkan kode minuman yang ingin dipesan (00 untuk selesai): ");
                    scanf("%d", &pilihan);
                    if (pilihan == 00) break;
                    if (pilihan >= 1 && pilihan <= 5) {
                        printf("Masukkan jumlah pesanan: ");
                        scanf("%d", &jumlah);
                        if (jumlah > 0) {
                            tambahPesanan(pilihan, jumlah, 2, &pesanan, makanan, minuman, 5, 5);  // Minuman
                        } else {
                            printf("Jumlah pesanan tidak valid.\n");
                        }
                    } else {
                        printf("Kode minuman tidak valid.\n");
                    }
                }
                break;
            case 3:
                hitungTotal(&pesanan, makanan, minuman, 5, 5);
                tampilStruk(pesanan, makanan, minuman, 5, 5);
                break;
            case 4:
                resetPesanan(&pesanan);
                printf("Pesanan telah direset.\n");
                break;
            case 5:
                printf("Terima kasih telah menggunakan aplikasi pemesanan restoran!\n");
                exit(0);
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }
    return 0;
}

// Fungsi untuk menampilkan menu makanan atau minuman
void tampilMenu(struct Item item[], int n, const char* kategori) {
    printf("\n=== Menu %s ===\n", kategori);
    for (int i = 0; i < n; i++) {
        printf("%d. %s - Rp. %d\n", item[i].kode, item[i].nama, item[i].harga);
    }
}

// Fungsi untuk menambah pesanan (baik makanan atau minuman)
void tambahPesanan(int kode, int jumlah, int jenis, struct Pesanan *pesanan, struct Item makanan[], struct Item minuman[], int nMakanan, int nMinuman) {
    int index = pesanan->totalItem; // Menentukan index untuk pesanan baru
    pesanan->kodeItem[index] = kode;
    pesanan->jumlahItem[index] = jumlah;
    pesanan->jenisItem[index] = jenis;

    // Menambahkan harga berdasarkan jenis pesanan
    if (jenis == 1) {  // Makanan
        pesanan->totalHarga += makanan[kode-1].harga * jumlah;
    } else {  // Minuman
        pesanan->totalHarga += minuman[kode-1].harga * jumlah;
    }

    pesanan->totalItem++; // Menambah jumlah item yang dipesan
}

// Fungsi untuk menghitung total harga
void hitungTotal(struct Pesanan *pesanan, struct Item makanan[], struct Item minuman[], int nMakanan, int nMinuman) {
    pesanan->totalHarga = 0;
    for (int i = 0; i < pesanan->totalItem; i++) {
        if (pesanan->jenisItem[i] == 1) {
            pesanan->totalHarga += makanan[pesanan->kodeItem[i]-1].harga * pesanan->jumlahItem[i];
        } else if (pesanan->jenisItem[i] == 2) {
            pesanan->totalHarga += minuman[pesanan->kodeItem[i]-1].harga * pesanan->jumlahItem[i];
        }
    }
}

/// Fungsi untuk menampilkan struk pembelian
void tampilStruk(struct Pesanan pesanan, struct Item makanan[], struct Item minuman[], int nMakanan, int nMinuman) {
    printf("\n =============== STRUK PEMBELIAN ==============\n");
    printf("| No |  Nama Item   | Jumlah | Harga  | Total  |\n");

    // Menampilkan makanan yang dipesan
    for (int i = 0; i < pesanan.totalItem; i++) {
        if (pesanan.jenisItem[i] == 1) {  // Makanan
            printf("| %-2d | %-12s | %-6d | %-6d | %-6d |\n", pesanan.kodeItem[i], makanan[pesanan.kodeItem[i]-1].nama, pesanan.jumlahItem[i], makanan[pesanan.kodeItem[i]-1].harga, makanan[pesanan.kodeItem[i]-1].harga * pesanan.jumlahItem[i]);
        } else if (pesanan.jenisItem[i] == 2) {  // Minuman
            printf("| %-2d | %-12s | %-6d | %-6d | %-6d |\n", pesanan.kodeItem[i], minuman[pesanan.kodeItem[i]-1].nama, pesanan.jumlahItem[i], minuman[pesanan.kodeItem[i]-1].harga, minuman[pesanan.kodeItem[i]-1].harga * pesanan.jumlahItem[i]);
        }
    }

    printf("\n-----------------------------------------\n");
    printf("Total Harga: Rp. %d\n", pesanan.totalHarga);

    printf("Masukkan jumlah uang yang dibayar: Rp. ");
    scanf("%d", &pesanan.bayar);

    // Menghitung kembalian
    if (pesanan.bayar >= pesanan.totalHarga) {
        pesanan.kembalian = pesanan.bayar - pesanan.totalHarga;
        printf("Kembalian: Rp. %d\n", pesanan.kembalian);
    } else {
        printf("Uang yang dibayar tidak cukup!\n");
    }
}

// Fungsi untuk reset pesanan
void resetPesanan(struct Pesanan *pesanan) {
    pesanan->totalHarga = 0;
    pesanan->totalItem = 0;
    pesanan->bayar = 0;
    pesanan->kembalian = 0;
}
