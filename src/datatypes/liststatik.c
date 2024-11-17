#include "../modules/boolean.h"
#include <stdio.h>
#include "../modules/liststatik.h"

/* ********** KONSTRUKTOR ********** */
void CreateListStatik(ListStatik *l) {
    IdxType i;
    for (i=0; i<CAPACITY; i++){
        ELMT(*l,i) = MARK;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
int listLength(ListStatik l) {
    IdxType i, count=0 ;
    for (i=0; i<CAPACITY; i++){
        if (ELMT(l,i) != MARK) {
            count++;
        }
    }
    return count;
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListStatik l) {
    return IDX_MIN;
}

IdxType getLastIdx(ListStatik l) {
    return listLength(l) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListStatik l, IdxType i) {
    return i <= CAPACITY-1 && i >= IDX_MIN;
}

boolean isIdxEff(ListStatik l, IdxType i) {
    return i <= listLength(l) - 1 && i >= IDX_MIN;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListStatik l) {
    return listLength(l) == 0;
}

boolean isFull(ListStatik l) {
    return listLength(l) == CAPACITY;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void readList(ListStatik *l) {
    int n, i;
    CreateListStatik(l);
    scanf("%d", &n);
    while (!(n>=0 && n<=CAPACITY)){
        scanf("%d", &n);
    }
    for(i=0; i<n; i++){
        scanf("%d", &ELMT(*l,i));
    }
}

void printList(ListStatik l) {
    IdxType i;
    if (isEmpty(l)){
        printf("[]");
    } else{
        printf("[");
        for(i=0; i<listLength(l); i++){
            if (i!=getLastIdx(l)){
                printf("%d,", ELMT(l,i));
            } else{
                printf("%d", ELMT(l,i));
            }
        }
        printf("]");
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
ListStatik plusMinusList(ListStatik l1, ListStatik l2, boolean plus) {
    ListStatik l3;
    int i;
    CreateListStatik(&l3);
    if (plus){
        for (i=0; i<listLength(l1); i++){
            ELMT(l3,i) = ELMT(l1,i) + ELMT(l2,i);
        }
    } else{
        for (i=0; i<listLength(l1); i++){
            ELMT(l3,i) = ELMT(l1,i) - ELMT(l2,i);
        }
    }
    return l3;
}

/* ********** OPERATOR RELASIONAL ********** */
boolean isListEqual(ListStatik l1, ListStatik l2) {
    boolean checker = true;
    int i = 0;

    if(listLength(l1) == listLength(l2)){
        while(checker && i<listLength(l1)){
            if (ELMT(l1, i) == ELMT(l2,i)){
                checker = true;
            } else{
                checker = false;
            }
            i ++;
        }
        return checker;
    } else{
        return false;
    }
}

/* ********** SEARCHING ********** */
int indexOf(ListStatik l, ElType val) {
    boolean found;
    int i = 0;

    if(listLength(l) == 0){
        return IDX_UNDEF;
    } else{
        found = false;
        while(!found && i<listLength(l)) {
            if (ELMT(l,i) == val){
                found = true;
            } else{
                found = false;
                i++;
            }
        }

        if(found) {
            return i;
        } else {
            return IDX_UNDEF;
        }
    }
}

/* ********** NILAI EKSTREM ********** */
void extremeValues(ListStatik l, ElType *max, ElType *min) {
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
    IdxType i;
    *min = ELMT(l,0);
    *max = ELMT(l,0);

    for(i=0; i<listLength(l); i++){
        if (ELMT(l,i)>*max) {
            *max = ELMT(l,i);
        }
        if (ELMT(l,i)<*min) {
            *min = ELMT(l,i);
        }
    }
}

/* ********** MENAMBAH ELEMEN ********** */
void insertFirst(ListStatik *l, ElType val) {
    IdxType i;
    for(i=listLength(*l); i>0; i--) {
        ELMT(*l,i) = ELMT(*l, i-1);
    }
    ELMT(*l, 0) = val;
}

void insertAt(ListStatik *l, ElType val, IdxType idx) {
    IdxType i;
    for(i=listLength(*l); i>idx; i--){
        ELMT(*l, i) = ELMT(*l, i-1);
    }
    ELMT(*l, idx) = val;
}

void insertLast(ListStatik *l, ElType val) {
    if(listLength(*l) != CAPACITY){
        ELMT(*l, getLastIdx(*l) + 1) = val;
    }
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteFirst(ListStatik *l, ElType *val) {
    int i;
    if (!isEmpty(*l)){
        *val = ELMT(*l,0);
        for(i=0; i<getLastIdx(*l); i++){
            ELMT(*l, i) = ELMT(*l, i+1);
        }
        ELMT(*l,getLastIdx(*l)) = MARK;
    }
}

void deleteAt(ListStatik *l, ElType *val, IdxType idx) {
    IdxType i;
    if(!isEmpty(*l) && isIdxValid(*l, idx)){
        *val = ELMT(*l,idx);
        for(i=idx; i<getLastIdx(*l); i++){
            ELMT(*l, i) = ELMT(*l, i+1);
        }
        ELMT(*l,getLastIdx(*l)) = MARK;
    }
}

void deleteLast(ListStatik *l, ElType *val) {
    if(!isEmpty(*l)){
        *val = ELMT(*l,getLastIdx(*l));
        ELMT(*l, getLastIdx(*l)) = MARK;
    }
}

/* ********** SORTING ********** */
void sortList(ListStatik *l, boolean asc) {
    IdxType i, j;
    ElType temp;
    if(asc){
        for(i=0; i<listLength(*l)-1; i++){
            for(j=i+1; j<listLength(*l);j++){
                if(ELMT(*l,i) > ELMT(*l,j)){
                    temp = ELMT(*l,i);
                    ELMT(*l,i) = ELMT(*l,j);
                    ELMT(*l, j) = temp;
                }
            }
        }
    } else{
        for(i=0; i<listLength(*l)-1; i++){
            for(j=i+1; j<listLength(*l);j++){
                if(ELMT(*l,i) < ELMT(*l,j)){
                    temp = ELMT(*l,i);
                    ELMT(*l,i) = ELMT(*l,j);
                    ELMT(*l, j) = temp;
                }
            }
        }
    }
}