/* Kelompok   : IF2110-01-B (K01-B)           */
/* Anggota 1  : 13523019 - Shannon A A Lie    */
/* Anggota 2  : 13523021 - M Raihan Nazhim O  */
/* Anggota 3  : 13523025 - Joel Hotlan H S    */
/* Anggota 4  : 13523043 - Najwa Kahani F     */
/* Anggota 5  : 13523111 - M Iqbal Haidar     */
/* Tanggal    : Minggu, 17 November 2024      */
/* Proyek     : Alstrukdat - TB1 - Purry Mail */
/* Bagian     : ADT - Linked List - H         */
/* File       : linkedlist.h                  */
/* Deskripsi  : Definisi ADT Linked List      */
/* PJ F00I    : 13523021 - M Raihan Nazhim O  */

#ifndef listlinked_H
#define listlinked_H

#include "boolean.h"

typedef char* ElType;
typedef struct node *Address;
typedef struct node {
    ElType info;
    Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

Address newNode(ElType val);
typedef Address List;

#define IDX_UNDEF -1
#define FIRST(l) (l)

void CreateList(List *l);
boolean isEmpty(List l);
ElType getElmt(List l , int idx);
void setElmt(List *l , int idx , ElType val);
int indexOf(List l , ElType val);

void insertFirst(List *l , ElType val);
void insertLast(List *l , ElType val);
void insertAt(List *l , ElType val , int idx);
void deleteFirst(List *l , ElType *val);
void deleteLast(List *l , ElType *val);
void deleteAt(List *l , int idx , ElType *val);

void displayList(List l);
int length(List l);
List concat(List l1 , List l2);

boolean fSearch(List l , Address p);
Address searchPrec(List l , ElType x);
void deleteAll(List *l);
void copyList(List *l1 , List *l2);
void inverseList(List *l);

#endif