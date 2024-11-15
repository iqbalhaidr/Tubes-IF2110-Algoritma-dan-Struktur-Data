/* File: datetime.h */
/* Tanggal: 15 November 2024 */
/* *** ADT DATETIME *** */

#ifndef DATETIME_H
#define DATETIME_H

#include <stdio.h>
#include <time.h>
#include "boolean.h"

#define NIL -1

/* *** Definisi *** */
typedef struct {
    int day;
    int month;
    int year;
    int hour;
    int minute;
} Datetime;

/* ********* AKSES (Selektor) ********* */
/* Jika t adalah Datetime, maka akses elemen : */
#define DAY(t)    (t).day
#define MONTH(t)  (t).month
#define YEAR(t)   (t).year
#define HOUR(t)   (t).hour
#define MINUTE(t) (t).minute

/* *** Konstruktor *** */
/* I.S. Sembarang */
/* F.S. Sebuah t kosong, dimana semua komponen t bernilai NIL */
/* Proses : Membuat t kosong sesuai definisi */
void CreateDatetime(Datetime *t) {
    DAY(*t) = NIL;
    MONTH(*t) = NIL;
    YEAR(*t) = NIL;
    HOUR(*t) = NIL;
    MINUTE(*t) = NIL;
}

/* Mengirim true jika t kosong : lihat definisi di atas */
boolean isEmptyDatetime(Datetime t) {
    return (DAY(t) == NIL && MONTH(t) == NIL && YEAR(t) == NIL 
            && HOUR(t) == NIL && MINUTE(t) == NIL);
}

/* *** Mencatat Waktu Terkini *** */
/* I.S. t kosong */
/* F.S. t berisi waktu terkini */
/* Proses : Mengambil waktu terkini dan memasukkannya ke t */
void getDatetime(Datetime *t) {
    time_t now = time(NULL);
    //time_t time(time_t *x) 
    //both assign to *x and return, seconds since Unix Epoch
    if (now == (time_t)(-1)) {
        return;
    }

    //tm* localtime(time_t *x) convert seconds to readable-format
    struct tm *tm_info = localtime(&now);
    if (tm_info == NULL) {
        return;
    }

    t->day = tm_info->tm_mday;
    t->month = tm_info->tm_mon + 1;      // tm_mon ranges 0 to 11
    t->year = tm_info->tm_year + 1900;   // tm_year years since 1900
    t->hour = tm_info->tm_hour;
    t->minute = tm_info->tm_min;
}

/* *** Display *** */
/* I.S. t tidak boleh kosong */
/* F.S. Menulis waktu dengan format DD-MM-YYYY @ HH.MM  */
/* Proses : Menulis waktu sesuai format dari data t */
void displayDatetime(Datetime t) {
    printf("%02d-%02d-%d @ %02d.%02d", DAY(t), MONTH(t), YEAR(t)
                                     , HOUR(t), MINUTE(t));
}

#endif


/* DRIVER

#include "datetime.h"

int main() {
    Datetime t;
    CreateDatetime(&t);
    getDatetime(&t);
    displayDatetime(t);

    return 0;
}
