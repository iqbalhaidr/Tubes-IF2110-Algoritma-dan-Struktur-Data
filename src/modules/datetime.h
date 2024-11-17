/* File: datetime.h */
/* Tanggal: 15 November 2024 */
/* *** ADT DATETIME *** */

#ifndef DATETIME_H
#define DATETIME_H

#include <stdio.h>
#include <time.h>
#include "boolean.h"

#define NIL -1

/* *** DEFINISI *** */
typedef struct {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
    int epoch;
} Datetime;

/* ********* AKSES (Selektor) ********* */
/* Jika t adalah Datetime, maka akses elemen : */
#define DAY(t)    (t).day
#define MONTH(t)  (t).month
#define YEAR(t)   (t).year
#define HOUR(t)   (t).hour
#define MINUTE(t) (t).minute
#define SECOND(t) (t).second
#define EPOCH(t)  (t).epoch

/* *** KONSTRUKTOR *** */
void CreateDatetime(Datetime *t);
/* I.S. Sembarang */
/* F.S. Sebuah t kosong, dimana semua komponen t bernilai NIL */
/* Proses : Membuat t kosong sesuai definisi */

/* *** TES KOSONG *** */
boolean isEmptyDatetime(Datetime t);
/* Mengirim true jika t kosong : lihat definisi di atas */

/* *** MENCATAT WAKTU TERKINI *** */
void getDatetime(Datetime *t);
/* I.S. t kosong */
/* F.S. t berisi waktu terkini */
/* Proses : Mengambil waktu terkini dan memasukkannya ke t */

/* *** KONVERSI *** */
int toSecond(Datetime t);
/* Mengembalikan detik sejak Unix Epoch sampai t */

/* *** DISPLAY *** */
void displayDatetime(Datetime t);
/* I.S. t tidak boleh kosong */
/* F.S. Menulis waktu dengan format DD-MM-YYYY @ HH.MM  */
/* Proses : Menulis waktu sesuai format dari data t */

#endif
