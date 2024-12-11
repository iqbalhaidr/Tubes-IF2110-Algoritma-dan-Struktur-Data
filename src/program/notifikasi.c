#include <stdio.h>

// INCLUDE INI DISESUAIKAN SAJA
#include "../globals.h"
#include "notifikasi.h"

#define TIMESTAMP(l, i) (l).data[(i)].timestamp
#define SUBJECT(l, i) (l).data[(i)].subyek
#define READPENERIMA(l, i) (l).data[(i)].read
#define READCC(l, i) (l).data[(i)].readCC

/* Mengembalikan true jika jumlah interaksi melebihi batas minimum interaksi */
boolean isImportant(int interaction, int minInteraction) {
    return interaction > minInteraction;
}

/* I.S. LE data email terkini, LU data user terkini (TIDAK KOSONG), userID
 * adalah ID user yang sedang login, minInteraction adalah jumlah minimal agar
 * dihitung [IMPORTANT], importantQ dan normalQ terdefinisi kosong */

/* F.S. importantQ berisi <timestamp, subject> [IMPORTANT] waktu terurut menaik
 * & normalQ berisi <timestamp, subject> [NOT IMPORTANT] waktu terurut menaik */

/* Catatan: Diasumsikan jumlah email yang diterima <= CAPACITY PrioQueue*/
void readNotifikasi(ListEmail LE, ListUser LU, int userID, int minInteraction,
                    PrioQueue *importantQ, PrioQueue *normalQ) {
    int emailCount, i, idPengirim, interaction;
    ElTypePrioQ val;
    Matrix m;

    CreatePrioQueue(importantQ);
    CreatePrioQueue(normalQ);
    emailCount = NUMBER(LE);
    readStatusKepentingan(LU, LE, &m);

    for (i = 0; i < emailCount; ++i) {
        if (listEmail.data[i].idPenerima == userID) {
            if (READPENERIMA(LE, i)) {
                continue;
            }
        } else if (listEmail.data[i].idCC == userID) {
            if (READCC(LE, i)) {
                continue;
            }
        } else {
            continue;
        }

        idPengirim = listEmail.data[i].idPengirim;
        interaction = KEPENTINGAN(m, idPengirim, userID);
        val.timeEpoch = toEpoch(TIMESTAMP(LE, i));
        val.timestamp = TIMESTAMP(LE, i);
        val.subject = SUBJECT(LE, i);

        if (isImportant(interaction, minInteraction)) {
            enqueueAscending(importantQ, val);
        } else {
            enqueueAscending(normalQ, val);
        }
    }
}

/* I.S. importantQ dan normalQ terdefinisi dan berisi data notifikasi USERXXX */
/* F.S. Notifikasi muncul sesuai dengan format */
void displayNotifikasi(PrioQueue *importantQ, PrioQueue *normalQ) {
    ElTypePrioQ val;

    if (isEmpty(*importantQ) && isEmpty(*normalQ)) {
        printf("Tidak ada notifikasi.\n");
        return;
    }

    printf("Notifikasi:\n");
    while (!isEmpty(*importantQ)) {
        printf("%s [IMPORTANT] %s\n", HEAD(*importantQ).timestamp,
               HEAD(*importantQ).subject);
        dequeue(importantQ, &val);
    }

    while (!isEmpty(*normalQ)) {
        printf("%s %s\n", HEAD(*normalQ).timestamp, HEAD(*normalQ).subject);
        dequeue(normalQ, &val);
    }
}

/* I.S. LE data email terkini, LU data user terkini, userID ID user yang sedang
 * login, minInteraction adalah jumlah minimal agar dihitung [IMPORTANT] */

/* F.S. Menjalankan fungsi notifikasi dan mendisplay sesuai format */
/* Catatan: Cukup hanya fungsi ini yang dipanggil pada program utama */
void notifikasi(ListEmail LE, ListUser LU, int userID, int minInteraction) {
    PrioQueue importantQ;
    PrioQueue normalQ;

    if (isEmptyUser(LU)) {
        printf("Belum ada user terdaftar.\n");
    }

    readNotifikasi(LE, LU, userID, minInteraction, &importantQ, &normalQ);
    displayNotifikasi(&importantQ, &normalQ);
}

void StartNotifikasi() {
    notifikasi(listEmail, listUser, user.id, importantInteraction);
}

/*Driver*/
/*
int main() {
    (<minInteraction> adalah jumlah minimum interaksi agar dianggap penting, ada
    pada file konfigurasi umum),
    (<userID> adalah ID user yang ingin ditampilkan notifikasinya/ID user yang
    sedang login)

    <kondisi listUser, listEmail sudah di load data>

    notifikasi(listEmail, listUser, <userID>, <minInteraction>);

    return 0;
}
*/