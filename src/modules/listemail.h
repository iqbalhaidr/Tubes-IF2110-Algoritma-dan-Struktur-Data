#ifndef _LISTEMAIL_H
#define _LISTEMAIL_H

#include "boolean.h"

/*  Kamus Umum */
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef struct {
   int id;
   int idPengirim;
   int idPenerima;
   int idCC;
   char* timestamp;
   char* subyek;
   char* body;
   int reply;
   boolean read;
   boolean readCC;
   boolean starred;
} emailType ;

typedef int IdxType;
typedef struct
{
    emailType *data; /* memori tempat penyimpan elemen (container) */
    int number;       /* >=0, banyaknya elemen efektif */
    int capacity;   /* ukuran elemen */
} ListEmail;

/* ********** SELEKTOR ********** */
#define NUMBER(l) (l).number
#define DATA(l) (l).data
#define ELMT_EMAIL(l, i) (l).data[i]
#define CAPACITY_EMAIL(l) (l).capacity

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListEmail(ListEmail *l, int capacity);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

void dealocateListEmail(ListEmail *l);
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmptyEmail(ListEmail l);
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
/* *** Test list penuh *** */
boolean isFullEmail(ListEmail l);
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

void printListEmail(ListEmail l);

/* ********** MENAMBAH ELEMEN ********** */
void addEmail(ListEmail *l, emailType email);

/* ********** OPERASI LAIN ********** */
void copyListEmail(ListEmail lIn, ListEmail *lOut);
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */ 

/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandListEmail(ListEmail *l, int num);
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

#endif