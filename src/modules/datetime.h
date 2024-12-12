#ifndef _DATETIME_H
#define _DATETIME_H

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
#define DAY(t) (t).day
#define MONTH(t) (t).month
#define YEAR(t) (t).year
#define HOUR(t) (t).hour
#define MINUTE(t) (t).minute
#define SECOND(t) (t).second
#define EPOCH(t) (t).epoch

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
int isLeap(int year);
/* Mengembalikan true/false (1/0) jika year adalah tahun kabisat */

int daysInMonth(int year, int month);
/* Mengembalikan jumlah hari pada bulan dan tahun sesuai parameter */

int parseInt(const char *str, int start, int length);
/* Mengembalikan nilai integer dari string angka dimulai dari idx=start
   sepanjang length */

int toEpoch(const char *timestamp);
/* Mengembalikan timestamp yang berbentuk char YYYY-MM-DD HH:MM:SS */

/* *** DISPLAY *** */
void displayDatetime(Datetime t);
/* I.S. t tidak boleh kosong */
/* F.S. Menulis waktu dengan format DD-MM-YYYY @ HH.MM  */
/* Proses : Menulis waktu sesuai format dari data t */

#endif
