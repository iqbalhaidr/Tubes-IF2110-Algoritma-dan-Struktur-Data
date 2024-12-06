#include <stdio.h>

// INI INCLUDE ATUR AJA LAH
// #include "./datatypes/datetime.c"
// #include "./datatypes/listemail.c"
// #include "./datatypes/listuser.c"
// #include "./datatypes/matrix.c"
#include "./datatypes/prioqueue.c"
// #include "./loadData.c"
// #include "./modules/boolean.h"
#include "./statusKepentingan.c"

#define TIMESTAMP(l, i) (l).data[(i)].timestamp
#define SUBJECT(l, i) (l).data[(i)].subyek
#define READPENERIMA(l, i) (l).data[(i)].read

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
        if (IDPENERIMA(LE, i) != userID) {
            continue;
        }

        if (READPENERIMA(LE, i)) {
            continue;
        }

        idPengirim = IDPENGIRIM(LE, i);
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

/*Driver*/
/*
int main() {
    ListUser listUser = loadUser();
    ListEmail listEmail = loadEmail();
    notifikasi(listEmail, listUser, 2, 1);

    return 0;
}
*/