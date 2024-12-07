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
/* Deskripsi  : Implementasi ADT Linked List  */
/* PJ F00I    : 13523021 - M Raihan Nazhim O  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../modules/linkedlist.h"

Address newNode(ElType val) {
    Address p = (Address) malloc(sizeof(Node));
    if (p != NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}

void CreateList(List *l) {
    FIRST(*l) = NULL;
}

boolean isEmpty(List l) {
    return (FIRST(l) == NULL);
}

ElType getElmt(List l , int idx) {
    Address p = FIRST(l);
    while (idx > 0) {
        p = NEXT(p);
        idx--;
    }
    return (INFO(p));
}

void setElmt(List *l , int idx , ElType val) {
    Address p = FIRST(*l);
    while (idx > 0) {
        p = NEXT(p);
        idx--;
    }
    INFO(p) = val;
}

int indexOf(List l , ElType val) {
    Address p = FIRST(l);
    int idx = 0;
    while (p != NULL) {
        if (INFO(p) == val) {
            return idx;
        } else {
            p = NEXT(p);
            idx++;
        }
    }
    return IDX_UNDEF;
}

void insertFirst(List *l , ElType val) {
    Address p = newNode(val);
    if (p != NULL) {
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
}

void insertLast(List *l , ElType val) {
    if (isEmpty(*l)) {
        insertFirst(&*l , val);
    } else {
        Address p = newNode(val);
        if (p != NULL) {
            Address temp = FIRST(*l);
            while (NEXT(temp) != NULL) {
                temp = NEXT(temp);
            }
            NEXT(temp) = p;
        }
    }
}

void insertAt(List *l , ElType val , int idx) {
    if (idx == 0) {
        insertFirst(&*l , val);
    } else {
        Address p = newNode(val);
        if (p != NULL) {
            Address temp = FIRST(*l);
            while (idx > 1) {
                temp = NEXT(temp);
                idx--;
            }
            NEXT(p) = NEXT(temp);
            NEXT(temp) = p;
        }
    }
}

void deleteFirst(List *l , ElType *val) {
    Address p = FIRST(*l);
    *val = INFO(p);
    FIRST(*l) = NEXT(p);
    free(p);
}

void deleteLast(List *l , ElType *val) {
    if (NEXT(FIRST(*l)) == NULL) {
        deleteFirst(&*l , &*val);
    } else {
        Address temp = FIRST(*l);
        while (NEXT(NEXT(temp)) != NULL) {
            temp = NEXT(temp);
        }
        *val = INFO(NEXT(temp));
        free(NEXT(temp));
        NEXT(temp) = NULL;
    }
}

void deleteAt(List *l , int idx , ElType *val) {
    if (idx == 0) {
        deleteFirst(&*l , &*val);
    } else {
        Address temp = FIRST(*l);
        while (idx > 1) {
            temp = NEXT(temp);
            idx--;
        }
        Address p = NEXT(temp);
        *val = INFO(p);
        NEXT(temp) = NEXT(p);
        free(p);
    }
}

void displayList(List l) {
    if (isEmpty(l)) {
        printf("[]");
    } else {
        printf("[");
        Address p = FIRST(l);
        if (p != NULL) {
            printf("%d" , INFO(p));
            p = NEXT(p);
        }
        while (p != NULL) {
            printf(",%d" , INFO(p));
            p = NEXT(p);
        }
        printf("]");
    }
}

int length(List l) {
    Address p = FIRST(l);
    int res = 0;
    while (p != NULL) {
        p = NEXT(p);
        res++;
    }
    return res;
}

List concat(List l1 , List l2) {
    List l3;
    CreateList(&l3);
    Address p1 = FIRST(l1);
    while (p1 != NULL) {
        insertLast(&l3 , INFO(p1));
        p1 = NEXT(p1);
    }
    Address p2 = FIRST(l2);
    while (p2 != NULL) {
        insertLast(&l3 , INFO(p2));
        p2 = NEXT(p2);
    }
    return l3;
}

boolean fSearch(List l , Address p) {
    Address temp = FIRST(l);
    while (temp != NULL && temp != p) {
        temp = NEXT(temp);
    }
    return (temp == p);
}

Address searchPrec(List l , ElType x) {
    if (length(l) <= 1) {
        return NULL;
    } else {
        Address p = l;
        Address prev = NULL;
        while((p != NULL) && (INFO(p) != x)) {
            prev = p;
            p = NEXT(p);
        }
        if (p == NULL) {
            return NULL;
        } else {
            return prev;
        }
    }
}

void deleteAll(List *l) {
    Address p = FIRST(*l);
    while (p != NULL) {
        Address temp = p;
        p = NEXT(p);
        free(temp);
    }
    FIRST(*l) = NULL;
}

void copyList(List *l1 , List *l2) {
    FIRST(*l2) = FIRST(*l1);
}

void inverseList(List *l) {
    Address current = FIRST(*l);
    Address prev = NULL;
    while (current != NULL) {
        Address next = NEXT(current);
        NEXT(current) = prev;
        prev = current;
        current = next;
    }
    FIRST(*l) = prev;
}