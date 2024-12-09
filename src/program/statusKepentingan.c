#include <stdio.h>
#include <stdlib.h>

// INCLUDE INI DISESUAIKAN SAJA

#include "statuskepentingan.h"
#include "../modules/matrix.h"
#include "../globals.h"

/* I.S. m terdefinisi rowEff dan colEff */
/* F.S. Semua elemen m bernilai 0 */
void initMatrix(Matrix *m) {
    int i, j;

    for (i = 0; i < ROW_EFF(*m); ++i) {
        for (j = 0; j < COL_EFF(*m); ++j) {
            ELMTMATRIX(*m, i, i) = 0;
        }
    }
}

/* prekondisi: Matrix m tidak boleh kosong */
/* Mengembalikan elemen terbesar m */
ElType maxEl(Matrix m) {
    int i, j;
    ElType maxElmt = ELMTMATRIX(m, 0, 0);

    for (i = 0; i < ROW_EFF(m); ++i) {
        for (j = 0; j < COL_EFF(m); ++j) {
            if (ELMTMATRIX(m, i, i) > maxElmt) {
                maxElmt = ELMTMATRIX(m, i, j);
            }
        }
    }

    return maxElmt;
}

/* Mengembalikan banyaknya digit pada angka. (123 -> 3 digit) */
int countDigit(int num) {
    int ctr = 0;

    if (num == 0) {
        return 1;
    }

    while (num != 0) {
        num /= 10;
        ++ctr;
    }

    return ctr;
}

/* I.S. m sembarang, LU data user terkini, LE data email terkini */
/* F.S. m berisi status kepentingan tiap user (<col> mengirim ke <row>)
        atau (kepentingan <col> terhadap <row>) */
/* Catatan: <col> dan <row> dimulai dari 0. Misal USER001 -> col/row = 0 */
void readStatusKepentingan(ListUser LU, ListEmail LE, Matrix *m) {
    int userCount, emailCount, i;
    userCount = LU.number;
    emailCount = NUMBER(LE);

    createMatrix(userCount, userCount, m);
    initMatrix(m);

    for (i = 0; i < emailCount; ++i) {
        ELMTMATRIX(*m, IDPENGIRIM(LE, i) - 1, IDPENERIMA(LE, i) - 1) += 1;
        if (IDCC(LE, i) != -1) {
            ELMTMATRIX(*m, IDPENGIRIM(LE, i) - 1, IDCC(LE, i) - 1) += 1;
        }
    }
}

/* Fungsi pembantu untuk display separator [----] */
void displaySeparator(int userCount, int padding) {
    int i, lenLine;
    lenLine = 6 + (userCount * (3 + padding));

    printf("[");
    for (i = 0; i < (lenLine - 2); i++) {
        printf("-");
    }
    printf("]\n");
}

/* I.S. Matrix m terdefinisi dan berisi status kepentingan tiap user */
/* F.S. Menampilkan tabel status kepentingan sesuai format ke layar */
void displayStatusKepentingan(Matrix m) {
    int i, j, padding, userCount, extraSpace;
    ElType maxElmt;

    userCount = ROW_EFF(m);
    maxElmt = maxEl(m);
    padding = countDigit(maxElmt);
    if (padding < 2) {  // Default padding = 2
        padding = 2;
    }
    extraSpace = padding - 2;

    displaySeparator(userCount, padding);

    printf("| ID |");  // Display Baris ID
    for (i = 1; i <= userCount; ++i) {
        printf(" %.2d ", i);
        printf("%*s|", extraSpace, "");
    }
    printf("\n");

    displaySeparator(userCount, padding);

    for (i = 1; i <= userCount; i++) {
        printf("| %.2d |", i);  // Display Kolom ID
        for (j = 1; j <= userCount; j++) {
            printf(" %0*d |", padding, KEPENTINGAN(m, i, j));
        }
        printf("\n");
    }

    displaySeparator(userCount, padding);
}

/* I.S. LU data user terkini, LE data email terkini */
/* F.S. Menampilkan tabel status kepentingan */
/* Catatan: Cukup hanya fungsi ini yang dipanggil pada program utama */
void statusKepentingan(ListUser listUser, ListEmail listEmail) {
    Matrix m;

    if (listUser.number <= 0) {
        printf("Belum ada user terdaftar.\n");
        return;
    }

    readStatusKepentingan(listUser, listEmail, &m);
    displayStatusKepentingan(m);
}

void StartStatusKepentingan() {
    statusKepentingan(listUser, listEmail);
}

/* DRIVER */
/*
int main() {
    <kondisi listUser, listEmail sudah di load data>

    statusKepentingan(listUser, listEmail);

    return 0;
}
*/