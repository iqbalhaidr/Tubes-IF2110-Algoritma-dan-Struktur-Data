#include "inbox.h"
#include <stdlib.h>
#include <stdio.h>

#include "../globals.h"

#include "../modules/boolean.h"
#include "../modules/mesinkarakter.h"
#include "../modules/mesinkata.h"
#include "../modules/datetime.h"
#include "../modules/listdin.h"
#include "../modules/stack.h"
#include "../modules/prioqueue.h"
#include "../modules/tree.h"

#include "../modules/listuser.h"
#include "../modules/listemail.h"
#include "../email/draftemail.h"

#include "../program/utility.h"
#include "../pengguna/pengguna.h"
#include "../program/program.h"

// Variabel global untuk mencatat perintah saat ini
// char currentCommand[50] = "";
int currentPage = 1;

// Fungsi untuk membagi dengan pembulatan ke atas
int ceil_division(int a, int b) {
    return (a + b - 1) / b;
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

// Fungsi untuk memotong string
void truncateString(const char* input, char* output, int maxLength) {
    int i;
    for (i = 0; i < maxLength && input[i] != '\0'; i++) {
        output[i] = input[i];
    }
    output[i] = '\0'; // Null-terminate string
}

// Fungsi untuk memformat Email ID (e.g., EMAIL001)
void formatEmailIDCC(int emailID, char* output) {
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

// Fungsi untuk memotong string
void truncateStringCC(const char* input, char* output, int maxLength) {
    int i;
    for (i = 0; i < maxLength && input[i] != '\0'; i++) {
        output[i] = input[i];
    }
    output[i] = '\0'; // Null-terminate string
}

// Fungsi untuk menghitung jumlah email pada inbox berdasarkan idPenerima == user.id
int countEmailInbox(ListEmail listEmail) {
    int count = 0;
    for (int i = 0; i < listEmail.number; i++) {
        if (listEmail.data[i].idPenerima == user.id || listEmail.data[i].idCC == user.id) {
            count++;
        }
    }
    return count;
}

// Fungsi untuk menampilkan daftar inbox
void DisplayInbox(ListEmail listEmail) {
    // Jika tidak ada email
    if (countEmailInbox(listEmail) == 0) {
        printf("[----------------------------------[ Daftar Inbox ]---------------------------------]\n");
        printf("[-----------------------------------------------------------------------------------]\n");
        printf("|                              Inbox Anda masih kosong                              |\n");
        printf("[-----------------------------------------------------------------------------------]\n");
        return;
    } else {
        printf("[-------------------------- Anda memiliki %d pesan pada Inbox -----------------------]\n", countEmailInbox(listEmail));
        printf("[----------------------------------[ Daftar Inbox ]---------------------------------]\n");
        printf("| %-9s | %-20s | %-14s | %-7s | %-19s |\n", 
            "Email ID", "Subject", "Pengirim", "Status", "Timestamp");
        printf("[-----------------------------------------------------------------------------------]\n");

        // Konfigurasi tampilan per halaman
        int totalPages = ceil_division(countEmailInbox(listEmail), pagination);
        int startIdx = listEmail.number - (currentPage - 1) * pagination;
        int endIdx = startIdx - pagination + 1;

        if (endIdx < 1) {
            endIdx = 1;
        }

        // Variabel sementara untuk format ID dan subyek berdasarkan idPenerima == user.id
        char formattedID[10];
        char truncatedSubject[21];

        for (int i = startIdx; i >= endIdx; i--) {
            int idx = i - 1;
            int isRelevant = (listEmail.data[idx].idPenerima == user.id || listEmail.data[idx].idCC == user.id);

            if (isRelevant) {
                formatEmailID(listEmail.data[idx].id, formattedID);
                truncateString(listEmail.data[idx].subyek, truncatedSubject, 20);

                printf("| %-9s | %-20s | %-14s | %-7s | %-19s |\n",
                    formattedID,
                    truncatedSubject,
                    FindEmailBasedId(listUser, listEmail.data[idx].idPengirim),
                    listEmail.data[idx].read ? "Read" : "Unread",
                    listEmail.data[idx].timestamp);
            } else {
                printf("DEBUG: Email dengan ID %d tidak relevan untuk user.id %d\n", listEmail.data[idx].id, user.id);
            }
        }
        printf("[-----------------------------------------------------------------------------------]\n");
        printf("[---------------------------         Page [%d]/[%d]        ---------------------------]\n", currentPage, totalPages);
        printf("[-----------------------------------------------------------------------------------]\n");

    }
}

// Fungsi untuk bacaPesanInbox
void bacaPesanInbox(ListEmail listEmail, int emailID) {
    char formattedID[10];
    formatEmailID(emailID, formattedID);

    int idx = -1;

    // Cari indeks berdasarkan emailID
    for (int i = 0; i < listEmail.number; i++) {
        if (listEmail.data[i].id == emailID) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Email tidak ditemukan.\n");
        return;
    }

    // Data ditemukan, tampilkan pesan
    int IDPengirim = listEmail.data[idx].idPengirim;
    printf("[---------------------------------[ Baca Pesan ]-------------------------------]\n");
    printf(" Inbox ID: %s\n", formattedID);
    printf(" Subject: %s\n", listEmail.data[idx].subyek);
    printf(" Pengirim: %s\n", FindEmailBasedId(listUser, IDPengirim));
    printf(" Timestamp: %s\n", listEmail.data[idx].timestamp);
    printf("[------------------------------------------------------------------------------]\n");
    printf(" %s\n", listEmail.data[idx].body);
    printf("[------------------------------------------------------------------------------]\n\n");

    // Tandai pesan sebagai sudah dibaca krn idPenerima == user.id atau idCC == user.id
    if (listEmail.data[idx].idPenerima == user.id) {
        listEmail.data[idx].read = 1;
    } else if (listEmail.data[idx].idCC == user.id) {
        listEmail.data[idx].readCC = 1;
    }
}

// Fungsi untuk membaca pesan, yang menerima parameter berupa email ID setelah proses validasi berhasil dilakukan.
void bacaPesan(int emailID) {
    bacaPesanInbox(listEmail,emailID);
}

void balasPesan(int emailID) {
    printf("Balas Pesan niiiiii\n");
}

// Fungsi menjalankan perintah inbox
void StartInbox() {
    do {
        Word input = perintah();
        int totalPages = ceil_division(countEmailInbox(listEmail), pagination);
        if (isEqual(input, "DAFTAR_INBOX") || isEqual(input, "LANJUT") ||
            isEqual(input, "SEBELUM") || isEqual(input, "KELUAR")) {

            if (isEqual(currentWord, "DAFTAR_INBOX")) {
                DisplayInbox(listEmail);

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
                currentPage = 1; // Reset halaman
                printf("Keluar dari mode INBOX.\n");
                break;
            }
        } else if (currentWord.Length == 19) { //BACA_PESAN
            Word temp;
            temp.Length = currentWord.Length - 3;

            // Salin bagian dari currentWord ke temp.TabWord
            for (int i = 0; i < temp.Length; i++) {
                temp.TabWord[i] = currentWord.TabWord[i];
            }

            if (isEqual(temp, "BACA_PESAN EMAIL")) {
                int emailID = 0;

                // Menggabungkan angka setelah perintah "BACA_PESAN EMAIL"
                for (int i = temp.Length; i < currentWord.Length; i++) {
                    if (currentWord.TabWord[i] < '0' || currentWord.TabWord[i] > '9') {
                        break;
                    } else {
                        emailID = emailID * 10 + (currentWord.TabWord[i] - '0');
                    }
                }

                printf("Email ID: %d\n", emailID);

                // Menghitung rentang email pada halaman saat ini
                int startIdx = (currentPage - 1) * pagination + 1;
                int endIdx = startIdx + pagination - 1;

                if (endIdx > listEmail.number) {
                    endIdx = listEmail.number;
                }

                int found = 0;

                // Mencari emailID dalam rentang indeks yang valid
                for (int i = startIdx; i <= endIdx; i++) {
                    if (listEmail.data[i - 1].id == emailID) {
                        found = 1;
                        break;
                    }
                }

                if (found) {
                    bacaPesan(emailID);  // Fungsi untuk membaca pesan
                } else {
                    printf("Email tidak ditemukan. Pastikan email yang ingin dibaca berada pada halaman DAFTAR_INBOX yang sedang dibuka.\n");
                }
            } else {
                printf("Perintah tidak valid dalam mode INBOX.\n");
            }
        } else if (currentWord.Length == 20) { //BALAS_PESAN
            Word temp;
            temp.Length = currentWord.Length - 3;
            // Salin bagian dari currentWord ke temp.TabWord
            for (int i = 0; i < temp.Length; i++) {
                temp.TabWord[i] = currentWord.TabWord[i];
            }

            if (isEqual(temp, "BALAS_PESAN EMAIL")) {
                int emailID = 0;

                // Menggabungkan angka setelah perintah "BACA_PESAN EMAIL"
                for (int i = temp.Length; i < currentWord.Length; i++) {
                    if (currentWord.TabWord[i] < '0' || currentWord.TabWord[i] > '9') {
                        break;
                    } else {
                        emailID = emailID * 10 + (currentWord.TabWord[i] - '0');
                    }
                }

                // Menghitung rentang email pada halaman saat ini
                int startIdx = (currentPage - 1) * pagination + 1;
                int endIdx = startIdx + pagination - 1;

                if (endIdx > listEmail.number) {
                    endIdx = listEmail.number;
                }

                int found = 0;
                // Mencari emailID dalam rentang indeks yang valid
                for (int i = startIdx; i <= endIdx; i++) {
                    if (listEmail.data[i - 1].id == emailID) {
                        found = 1;
                        break;
                    }
                }

                if (found) {
                    printf("Email ID: %d\n", emailID);
                    balasPesan(emailID);  // Fungsi untuk membalas pesan
                } else {
                    printf("Email tidak ditemukan. Pastikan email yang ingin dibaca berada pada halaman DAFTAR_INBOX yang sedang dibuka.\n");
                }
            } else {
                printf("Perintah tidak valid dalam mode INBOX.\n");
            }

        } else {
            printf("Perintah tidak valid dalam mode INBOX.\n");
        }
    } while (1); // Loop berjalan hingga perintah "KELUAR" diterima
}
