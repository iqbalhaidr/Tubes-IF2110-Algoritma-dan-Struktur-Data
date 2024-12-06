#include "../modules/boolean.h"
#include "../modules/inbox.h"
#include "../pengguna/pengguna.h"
#include "../modules/listemail.h"
#include "../modules/mesinkata.h"
#include <stdlib.h>
#include <stdio.h>
#include "../globals.h"

// Variabel global untuk mencatat perintah saat ini
char currentCommand[50] = "";
int currentPage = 1;

// Fungsi untuk membagi dengan pembulatan ke atas
int ceil_division(int a, int b) {
    return (a + b - 1) / b;
}

// Fungsi untuk menampilkan garis pada inbox
void lineInbox() {
    printf("[--------------------------------------------------------------------------------]\n");
}

// Fungsi untuk memformat Email ID (e.g., EMAIL001)
void formatEmailID(int emailID, char* output) {
    output[0] = 'E';
    output[1] = 'M';
    output[2] = 'A';
    output[3] = 'I';
    output[4] = 'L';

    // Hitung digit
    int hundreds = emailID / 100;
    int tens = (emailID / 10) % 10;
    int ones = emailID % 10;

    // Isi digit ke output
    output[5] = hundreds + '0';
    output[6] = tens + '0';
    output[7] = ones + '0';
    output[8] = '\0'; // Null-terminate string
}

// Fungsi untuk memotong string tanpa menggunakan string.h
void truncateString(const char* input, char* output, int maxLength) {
    int i;
    for (i = 0; i < maxLength && input[i] != '\0'; i++) {
        output[i] = input[i];
    }
    output[i] = '\0'; // Null-terminate string
}

// Fungsi untuk menampilkan daftar inbox
void DisplayInbox(ListEmail listEmail) {
    // Jika tidak ada email
    if (isEmptyEmail(listEmail)) {
        printf("[--------------------------------[ Daftar Inbox ]--------------------------------]\n");
        lineInbox();
        printf("|                            Inbox Anda masih kosong                             |\n");
        lineInbox();
        return;
    }

    // Header untuk email yang tersedia
    printf("[------------------------ Anda memiliki %d pesan pada Inbox ----------------------]\n", listEmail.number);
    printf("[--------------------------------[ Daftar Inbox ]--------------------------------]\n");
    printf("| %-9s | %-20s | %-14s | %-7s | %-16s |\n", 
           "Email ID", "Subject", "Pengirim", "Status", "Timestamp");
    lineInbox();

    // Konfigurasi tampilan per halaman
    int perPage = 5;
    int totalPages = ceil_division(listEmail.number, perPage);
    int startIdx = listEmail.number - (currentPage - 1) * perPage;
    int endIdx = startIdx - perPage + 1;

    if (endIdx < 1) {
        endIdx = 1;
    }

    // Variabel sementara untuk format ID dan subyek
    char formattedID[10];
    char truncatedSubject[21];

    // Menampilkan email
    for (IdxType i = startIdx; i >= endIdx; i--) {
        formatEmailID(listEmail.data[i - 1].id, formattedID); // Format Email ID
        truncateString(listEmail.data[i - 1].subyek, truncatedSubject, 20); // Truncate Subject

        int IDPengirim = listEmail.data[i - 1].idPengirim;

        printf("| %-9s | %-20s | %-14s | %-7s | %-16s |\n",
               formattedID,
               truncatedSubject,
               listUser.data[IDPengirim - 1].email,
               listEmail.data[i - 1].read ? "Read" : "Unread",
               listEmail.data[i - 1].timestamp);
    }

    lineInbox();

    // Footer halaman
    printf("[-------------------------         Page [%d]/[%d]        --------------------------]\n", 
           currentPage, totalPages);
    lineInbox();
}

// Fungsi untuk bacaPesanInbox
void bacaPesanInbox(ListEmail listEmail, int emailID) {
    char formattedID[10]; // Buffer untuk menyimpan ID terformat
    formatEmailID(listEmail.data[emailID - 1].id, formattedID); // Format ID menjadi 'EMAILxxx'

    int IDPengirim = listEmail.data[emailID - 1].idPengirim;

    printf("[---------------------------------[ Baca Pesan ]--------------------------------]\n");
    printf(" Inbox ID: %s\n", formattedID); // Gunakan ID terformat
    printf(" Subject: %s\n", listEmail.data[emailID - 1].subyek);
    printf(" Pengirim: %s\n", listUser.data[IDPengirim - 1].email);
    printf(" Timestamp: %s\n", listEmail.data[emailID - 1].timestamp);
    printf("[-------------------------------------------------------------------------------]\n");
    printf(" %s\n", listEmail.data[emailID - 1].body);
    printf("[-------------------------------------------------------------------------------]\n\n");
}

void bacaPesan(int emailID) {
    bacaPesanInbox(listEmail,emailID);
}

void Inbox(Word w1, Word w2) {
    do {
        printf("Masukkan perintah dalam mode INBOX: ");
        STARTWORD();  // Memulai input perintah

        int totalPages = ceil_division(listEmail.number, 5); // Hitung total halaman

        if (isEqual(currentWord, "DAFTAR_INBOX") || isEqual(currentWord, "LANJUT") ||
            isEqual(currentWord, "SEBELUM") || isEqual(currentWord, "BACA_PESAN") ||
            isEqual(currentWord, "KELUAR")) {

            if (isEqual(currentWord, "DAFTAR_INBOX")) {
                DisplayInbox(listEmail);

            } else if (isEqual(currentWord, "BACA_PESAN")) {
                ADVWORD();  // Ambil kata kedua
                if (!EndWord) {  // Memastikan ada kata kedua
                    // Validasi format "EMAILxxx"
                    int isValid = 1;
                    if (currentWord.Length == 8) {
                        // Pastikan 5 karakter pertama adalah "EMAIL"
                        int i;
                        for (i = 0; i < 5; i++) {
                            if (currentWord.TabWord[i] != "EMAIL"[i]) {
                                isValid = 0;
                                break;
                            }
                        }
                        // Pastikan karakter ke-6 hingga ke-8 adalah angka
                        if (isValid) {
                            for (i = 5; i < currentWord.Length; i++) {
                                if (currentWord.TabWord[i] < '0' || currentWord.TabWord[i] > '9') {
                                    isValid = 0;
                                    break;
                                }
                            }
                        }
                    } else {
                        isValid = 0;
                    }

                    if (isValid) {
                        // Konversi angka dari "EMAILxxx"
                        int emailID = 0;
                        for (int i = 5; i < currentWord.Length; i++) {
                            emailID = emailID * 10 + (currentWord.TabWord[i] - '0');
                        }

                        // Hitung rentang email di halaman saat ini
                        int perPage = 5;
                        int startIdx = listEmail.number - (currentPage - 1) * perPage;
                        int endIdx = startIdx - perPage + 1;
                        if (endIdx < 1) {
                            endIdx = 1;
                        }

                        // Cek apakah email ada di halaman yang sedang ditampilkan
                        int found = 0;
                        for (int i = startIdx; i >= endIdx; i--) {
                            if (listEmail.data[i - 1].id == emailID) {
                                found = 1;
                                break;
                            }
                        }

                        if (found) {
                            bacaPesan(emailID);  // Fungsi untuk membaca pesan
                        } else {
                            printf("Email tidak ditemukan di halaman %d.\n", currentPage);
                        }
                    } else {
                        printf("Perintah tidak valid. Format harus 'EMAILxxx'.\n");
                    }
                } else {
                    printf("Perintah tidak valid. Harus ada dua kata.\n");
                }
            } else if (isEqual(currentWord, "LANJUT")) {
                if (currentPage < totalPages) {
                    currentPage++;
                    printf("Halaman telah berganti ke %d.\n", currentPage);
                    DisplayInbox(listEmail);
                } else {
                    printf("Sudah merupakan halaman yang paling terakhir.\n");
                }

            } else if (isEqual(currentWord, "SEBELUM")) {
                if (currentPage > 1) {
                    currentPage--;
                    printf("Halaman telah berganti ke %d.\n", currentPage);
                    DisplayInbox(listEmail);
                } else {
                    printf("Sudah merupakan halaman yang paling pertama.\n");
                }

            } else if (isEqual(currentWord, "KELUAR")) {
                currentPage = 1;  // Reset halaman
                printf("Keluar dari mode INBOX.\n");
                break;
            }
        } else {
            printf("Perintah tidak valid dalam mode INBOX.\n");
        }
    } while (1);  // Loop berjalan hingga perintah "KELUAR" diterima
}
