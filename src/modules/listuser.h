#ifndef LISTUSER_H
#define LISTUSER_H

#include "boolean.h"
#include "mesinkata.h"
#include "../program/utility.h"

/*  Kamus Umum */
#define CAPACITY_USER 20
#define IDX_MIN 0
#define IDX_UNDEF -1

/* Definisi elemen dan koleksi objek */
typedef struct {
    int id;
    char* email;
    char* password;    
} userType;

typedef int IdxType;

typedef struct {
    int number;
    userType data[CAPACITY_USER]; /* memori tempat penyimpan elemen (container) */
} ListUser;

/* ********** SELEKTOR ********** */
#define ELMT(l, i) (l).data[(i)]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListUser(ListUser *l);
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan MARK */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyUser(ListUser l);
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
boolean isFullUser(ListUser l);
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void printListUser(ListUser l);


/* ********** MENAMBAH ELEMEN ********** */
void addUser(ListUser *l, userType user);
/* Proses: Menambahkan user sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */

/* ********** SEARCHING ********** */
int idUser(ListUser l, Word word);

#endif