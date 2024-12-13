#include "inbox.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
int cekStartidx;
int topIndexDisplay;
int bottomIndexDisplay;

// fungsi untuk mencari start index untuk perintah sebelum
int cekStartIndexComBefore(ListEmail listEmail, int page, int cekStartIndex){
    int targetNumEmail = pagination * currentPage;
    int idx = cekStartidx, count = 0;

    while (count <= targetNumEmail){
        if (listEmail.data[idx].idPenerima == user.id || listEmail.data[idx].idCC == user.id) {
            count++;
        }
        idx++;
    }
    return idx;
}

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

// Fungsi untuk mengubah format timestamp dari "YYYY-MM-DD HH.MM.SS" menjadi "YYYY-MM-DD @ HH.MM.SS"
void formatDateTime(char* input, char* output) {
    int i = 0, j = 0;

    // Salin bagian tanggal "YYYY-MM-DD"
    while (input[i] != '\0' && input[i] != ' ') {
        output[j++] = input[i++];
    }

    if (input[i] == ' ') {
        output[j++] = ' ';
        output[j++] = '@';
        output[j++] = ' ';
        i++; // Lewati spasi
    }

    // Salin bagian waktu "HH.MM.SS"
    while (input[i] != '\0') {
        output[j++] = input[i++];
    }

    // Null-terminate string output
    output[j] = '\0';
}

// Fungsi hitung panjang char
int len(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int min(int a, int b) {
    return a < b ? a : b;
}


// Fungsi untuk menampilkan daftar inbox
void DisplayInbox(ListEmail listEmail) {
    if (countEmailInbox(listEmail) == 0) {
        printf("[-----------------------------------------[ Daftar Inbox ]----------------------------------------]\n");
        printf("[-------------------------------------------------------------------------------------------------]\n");
        printf("|                                      Inbox Anda masih kosong                                    |\n");
        printf("[-------------------------------------------------------------------------------------------------]\n\n");
        return;
    } else {
        printf("[-------------------------------- Anda memiliki %d pesan pada Inbox ------------------------------]\n", countEmailInbox(listEmail));
        printf("[----------------------------------------[ Daftar Inbox ]----------------------------------------]\n");
        printf("| %-9s | %-20s | %-15s | %-7s | %-21s | %-7s |\n", 
            "Email ID", "Subject", "Pengirim", "Status", "Timestamp", "Starred");
        printf("[------------------------------------------------------------------------------------------------]\n");

        int totalPages = ceil_division(countEmailInbox(listEmail), pagination);

        char truncatedSubject[21];
        char formattedTimestamp[21];
        int countEmailShown = 0;
        int idx = cekStartidx - 1;
        int lastVerifiedIndexDisplayed;

        while (countEmailShown < pagination && idx >= 0) {
            if (listEmail.data[idx].idPenerima == user.id || listEmail.data[idx].idCC == user.id) {
                lastVerifiedIndexDisplayed = idx;
                if (countEmailShown == 0){
                    topIndexDisplay = listEmail.data[idx].id;
                }
                if (countEmailShown == pagination-1){
                    bottomIndexDisplay = listEmail.data[idx].id;
                }
                countEmailShown++;
                truncateString(listEmail.data[idx].subyek, truncatedSubject, 20);
                formatDateTime(listEmail.data[idx].timestamp, formattedTimestamp);

                int size = 2 + 9 + 3 + 20 + 3 + 15 + 3 + 7 + 3 + 21 + 3 + 7 + 2 + 1;
                char arr[size];

                for (int i = 0 ; i < size ; i++) {
                    arr[i] = ' '; // Gunakan spasi untuk inisialisasi
                }
                arr[size - 1] = '\0';
                arr[size - 2] = '\n';

                arr[0] = arr[12] = arr[35] = arr[53] = arr[63] = arr[87] = arr[97] = '|';
                for (int i = 2 ; i <= 9 ; i++) {
                    if (i == 2) {
                        arr[i] = 'E';
                    } else if (i == 3) {
                        arr[i] = 'M';
                    } else if (i == 4) {
                        arr[i] = 'A';
                    } else if (i == 5) {
                        arr[i] = 'I';
                    } else if (i == 6) {
                        arr[i] = 'L';
                    } else if (i == 7) {
                        arr[i] = ((idx + 1) / 100) + '0';
                    } else if (i == 8) {
                        arr[i] = (((idx + 1) / 10) % 10) + '0';
                    } else if (i == 9) {
                        arr[i] = ((idx + 1) % 10) + '0';
                    }
                }
                // arr[2] = 'E';
                // arr[3] = 'M';
                // arr[4] = 'A';
                // arr[5] = 'I';
                // arr[6] = 'L';

                // arr[7] = ((idx + 1) / 100) + '0';
                // arr[8] = (((idx + 1) / 10) % 10) + '0';
                // arr[9] = ((idx + 1) % 10) + '0';

                // Debug untuk memeriksa isi arr setelah mengisi EMAIL
                // printf("Debug arr setelah EMAIL: %s\n", arr);

                // Lanjutkan untuk mengisi elemen lain seperti truncatedSubject, timestamp, dsb.             
                for (int i = 14 ; i < min(32 , len(truncatedSubject) + 14) ; i++) {
                    arr[i] = truncatedSubject[i - 14];
                }
                for (int i = 37 ; i < min(52 , len(FindEmailBasedId(listUser, listEmail.data[idx].idPengirim)) + 37) ; i++) {
                    arr[i] = FindEmailBasedId(listUser, listEmail.data[idx].idPengirim)[i - 37];
                }
                if (listEmail.data[idx].read) {
                    arr[55] = 'R';
                    arr[56] = 'e';
                    arr[57] = 'a';
                    arr[58] = 'd';
                } else {
                    arr[55] = 'U';
                    arr[56] = 'n';
                    arr[57] = 'r';
                    arr[58] = 'e';
                    arr[59] = 'a';
                    arr[60] = 'd';
                }
                for (int i = 65 ; i < min(86 , len(formattedTimestamp) + 65) ; i++) {
                    arr[i] = formattedTimestamp[i - 65];
                }

                if (listEmail.data[idx].starred) {
                    arr[89] = 'Y';
                    arr[90] = 'e';
                    arr[91] = 's';
                } else {
                    arr[89] = 'N';
                    arr[90] = 'o';
                }

                printf("%s\n", arr);
                    // formattedID,
                    // truncatedSubject,
                    // FindEmailBasedId(listUser, listEmail.data[idx].idPengirim),
                    // listEmail.data[idx].read ? "Read" : "Unread",
                    // formattedTimestamp,
                    // listEmail.data[idx].starred ? "Yes" : "No");
            }
            cekStartidx--;
            idx--;
        }

        if (countEmailShown != pagination-1){
            bottomIndexDisplay = lastVerifiedIndexDisplayed;
        }

        printf("[------------------------------------------------------------------------------------------------]\n");
        printf("[-----------------------------------         Page [%d]/[%d]        --------------------------------]\n", currentPage, totalPages);
        printf("[------------------------------------------------------------------------------------------------]\n\n");
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

void starEmailInbox(ListEmail *listEmail, int emailID) {
    char formattedID[10];
    formatEmailID(emailID, formattedID);

    int idx = -1;

    // Cari indeks berdasarkan emailID
    for (int i = 0; i < listEmail->number; i++) {
        if (listEmail->data[i].id == emailID) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Email tidak ditemukan.\n");
        return;
    }

    if((*listEmail).data[emailID].starred == 1){
        printf("%s sudah berada di STARRED.\n", formattedID);
    } else if (listEmail->data[emailID].starred == 0) {
        listEmail->data[emailID].starred = 1;
        printf("%s berhasil dipindahkan ke STARRED.\n", formattedID);
    }
}

void starEmail(int emailID) {
    starEmailInbox(&listEmail,emailID);
}

void unStarEmailInbox(ListEmail listEmail, int emailID) {
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

    if(listEmail.data[emailID].starred == 1){
        listEmail.data[emailID].starred = 0;
        printf("%s berhasil dihapus dari daftar STARRED.\n", formattedID);
    } else if (listEmail.data[emailID].starred == 0) {
        printf("%s tidak berada di daftar STARRED.\n", formattedID);
    }
}

void unStarEmail(int emailID) {
    unStarEmailInbox(listEmail,emailID);
}

// Fungsi untuk menghitung jumlah email pada inbox berdasarkan idPenerima == user.id
int countEmailStarredInbox(ListEmail listEmail) {
    int count = 0;
    for (int i = 0; i < listEmail.number; i++) {
        if ((listEmail.data[i].idPenerima == user.id && listEmail.data[i].starred) || (listEmail.data[i].idCC == user.id && listEmail.data[i].starred)) {
            count++;
        }
    }
    return count;
}

// Fungsi untuk menampilkan daftar starred inbox
void StarredInbox(ListEmail listEmail) {
    if (countEmailInbox(listEmail) == 0) {
        printf("[--------------------------------[ Daftar Starred ]--------------------------------]\n");
        printf("[----------------------------------------------------------------------------------]\n");
        printf("|                             Inbox Anda masih kosong                              |\n");
        printf("[----------------------------------------------------------------------------------]\n\n");
        return;
    } else {
        printf("[----------------------- Anda memiliki %d pesan pada Inbox -------------------------]\n", countEmailStarredInbox(listEmail));
        printf("[----------------------------------[ Daftar Inbox ]---------------------------------]\n");
        printf("| %-9s | %-20s | %-14s | %-7s | %-21s\n", 
            "Email ID", "Subject", "Pengirim", "Status", "Timestamp");
        printf("[----------------------------------------------------------------------------------]\n");

        int totalPages = ceil_division(countEmailInbox(listEmail), pagination);
        int startIdx = listEmail.number - (currentPage - 1) * pagination;
        int endIdx = startIdx - pagination + 1;

        if (endIdx < 1) {
            endIdx = 1;
        }

        char formattedID[10];
        char truncatedSubject[21];
        char formattedTimestamp[21];

        for (int i = startIdx; i >= endIdx; i--) {
            int idx = i - 1;
            if (listEmail.data[idx].idPenerima == user.id || listEmail.data[idx].idCC == user.id) {
                formatEmailID(listEmail.data[idx].id, formattedID);
                truncateString(listEmail.data[idx].subyek, truncatedSubject, 20);
                formatDateTime(listEmail.data[idx].timestamp, formattedTimestamp);

                printf("| %-9s | %-20s | %-14s | %-7s | %-21s |\n",
                    formattedID,
                    truncatedSubject,
                    FindEmailBasedId(listUser, listEmail.data[idx].idPengirim),
                    listEmail.data[idx].read ? "Read" : "Unread",
                    formattedTimestamp);
            }
        }

        printf("[----------------------------------------------------------------------------------]\n");
        printf("[-------------------------         Page [%d]/[%d]        --------------------------]\n", currentPage, totalPages);
        printf("[----------------------------------------------------------------------------------]\n\n");
    }
}

// Fungsi menjalankan perintah inbox
void StartInbox() {
    do {
        sleep(1);
        // system("clear");
        headerInbox();
        printf("Selamat datang di Menu Inbox!\n");
        menuInbox();
        Word input = perintah();
        int totalPages = ceil_division(countEmailInbox(listEmail), pagination);
        if (isEqual(input, "DAFTAR_INBOX") || isEqual(input, "LANJUT") ||
            isEqual(input, "SEBELUM") || isEqual(input, "KELUAR") || isEqual(input, "DAFTAR_STARRED")) {

            if (isEqual(currentWord, "DAFTAR_INBOX")) {
                cekStartidx = listEmail.number;
                DisplayInbox(listEmail);

            } else if (isEqual(currentWord, "DAFTAR_STARRED")) {
                StarredInbox(listEmail);

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
                    cekStartidx = cekStartIndexComBefore(listEmail, pagination, cekStartidx);
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

                // Menghitung rentang email pada halaman saat ini

                int found = 0;

                // Mencari emailID dalam rentang indeks yang valid
                printf("bottom: %d\n", bottomIndexDisplay);
                printf("top: %d\n", topIndexDisplay);
                for (int i = bottomIndexDisplay; i <= topIndexDisplay; i++) {
                    if (listEmail.data[i - 1].id == emailID && (listEmail.data[i - 1].idPenerima == user.id || listEmail.data[i-1].idCC == user.id)) {
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

        } else if (currentWord.Length == 13) { //Baca starred
            Word temp;
            temp.Length = currentWord.Length - 3;

            // Salin bagian dari currentWord ke temp.TabWord
            for (int i = 0; i < temp.Length; i++) {
                temp.TabWord[i] = currentWord.TabWord[i];
            }

            if (isEqual(temp, "STAR EMAIL")) {
                int emailID = 0;

                // Menggabungkan angka setelah perintah "STAR EMAIL"
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
                    starEmail(emailID);
                } else {
                    printf("Email tidak ditemukan. Pastikan email yang ingin dibaca berada pada halaman DAFTAR_INBOX yang sedang dibuka.\n");
                }
            } else {
                printf("Perintah tidak valid dalam mode INBOX.\n");
            }

        } else if (currentWord.Length == 15) { //Baca unstarred
            Word temp;
            temp.Length = currentWord.Length - 3;

            // Salin bagian dari currentWord ke temp.TabWord
            for (int i = 0; i < temp.Length; i++) {
                temp.TabWord[i] = currentWord.TabWord[i];
            }

            if (isEqual(temp, "UNSTAR EMAIL")) {
                int emailID = 0;

                // Menggabungkan angka setelah perintah "UNSTAR EMAIL"
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
                    unStarEmail(emailID); 
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
