#include <stdio.h>
#include <stdlib.h>
#include "../modules/boolean.h"
#include "../modules/listdin.h"

/* ********** KONSTRUKTOR ********** */
void CreateListDin(ListDin *l, int capacity) {
    BUFFER(*l) = (ElType*) malloc(capacity*sizeof(ElType));
    CAPACITYLD(*l) = capacity;
    NEFF(*l) = 0;
}

void dealocateList(ListDin *l) {
    free(BUFFER(*l));
    CAPACITYLD(*l) = 0;
    NEFF(*l) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
int listLength(ListDin l) {
    return NEFF(l);
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListDin l) {
    return IDX_MIN;
}

IdxType getLastIdx(ListDin l) {
    return NEFF(l)-1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, IdxType i) {
    return (i>=0) && (i<(CAPACITYLD(l)));
}

/* yaitu antara 0..NEFF(l) */
boolean isIdxEff(ListDin l, IdxType i) {
    return (i>=0 && i<=getLastIdx(l));
}

/* ********** TEST KOSONG/PENUH ********** */
boolean isEmptyLD(ListDin l) {
    return (listLength(l) == 0);
}

boolean isFullLD(ListDin l) {
    return (listLength(l) == CAPACITYLD(l));

}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void readList(ListDin *l) {
    int N, i;
    do {
        scanf("%d", &N);
    } while (!(N>=0 && N<=CAPACITYLD(*l)));
    
    NEFF(*l) = N;
    if (N!=0){
        for(i=0; i<NEFF(*l); i++){
            scanf("%hhd", &ELMTLD(*l, i));
        }
    }
}

void printList(ListDin l) {
    IdxType i;
    if (isEmptyLD(l)){
        printf("[]");
    } else{
        printf("[");
        for(i=0; i<listLength(l); i++){
            if (i!=getLastIdx(l)){
                printf("%c,", ELMTLD(l,i));
            } else{
                printf("%c", ELMTLD(l,i));
            }
        }
        printf("]");
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus) {
    IdxType i;
    ListDin l3;
    CreateListDin(&l3, CAPACITYLD(l1));
    NEFF(l3) = NEFF(l1);
    if (NEFF(l1) == NEFF(l2) && NEFF(l1) != 0 && NEFF(l2) != 0){
        for(i=0; i<NEFF(l3); i++){
            if(plus){
                ELMTLD(l3,i) = ELMTLD(l1,i) + ELMTLD(l2,i);
            } else{
                ELMTLD(l3,i) = ELMTLD(l1,i) - ELMTLD(l2,i);
            }
        }
    }
    return l3;
}

/* ********** OPERATOR RELASIONAL ********** */
boolean isListEqual(ListDin l1, ListDin l2) {
    boolean same = true;
    int i=0;
    
    if (NEFF(l1) != NEFF(l2)){
        return false;
    } else{
        while(same && i<listLength(l1)){
            if(ELMTLD(l1,i) == ELMTLD(l2,i)){
                same = true;
            } else{
                same = false;
            }
            i++;
        }
        return same;
    }
}

/* ********** SEARCHING ********** */
IdxType indexOf(ListDin l, ElType val) {
    boolean found;
    IdxType i = 0;

    if(listLength(l) == 0){
        return IDX_UNDEF;
    } else{
        found = false;
        while(!found && i<listLength(l)){
            if (ELMTLD(l,i) == val){
                found = true;
            } else{
                found = false;
                i++;
            }
        }

        if(found){
            return i;
        } else{
            return IDX_UNDEF;
        }
    }
}

/* ********** NILAI EKSTREM ********** */
void extremeValues(ListDin l, ElType *max, ElType *min) {
    IdxType i;
    *max = ELMTLD(l,0);
    *min = ELMTLD(l,0);

    for(i=0; i<listLength(l); i++){
        if(ELMTLD(l,i) > *max){
            *max = ELMTLD(l,i);
        }
        if(ELMTLD(l,i) < *min){
            *min = ELMTLD(l,i);
        }
    }
}

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut) {
    IdxType i;
    dealocateList(lOut);
    CreateListDin(lOut, CAPACITYLD(lIn));

    for(i=0; i<listLength(lIn); i++){
        ELMTLD(*lOut, i) = ELMTLD(lIn, i);
    }

    NEFF(*lOut) = NEFF(lIn);
}

ElType sumList(ListDin l){
    ElType sum = 0;
    IdxType i;
    for(i=0; i<listLength(l); i++){
        sum += ELMTLD(l,i);
    }
    return sum;
}

int countVal(ListDin l, ElType val){
    IdxType i;
    int count=0;

    for(i=0; i<listLength(l); i++){
        if(ELMTLD(l,i) == val){
            count ++;
        }
    }
    return count;
}

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc) {
    IdxType i, j;
    ElType temp;
    if(asc){
        for(i=0; i<listLength(*l)-1; i++){
            for(j=i+1; j<listLength(*l); j++){
                if(ELMTLD(*l,i)>ELMTLD(*l,j)){
                    temp = ELMTLD(*l,i);
                    ELMTLD(*l,i) = ELMTLD(*l,j);
                    ELMTLD(*l,j) = temp;
                }
            }
        }
    } else{
        for(i=0; i<listLength(*l)-1; i++){
            for(j=i+1; j<listLength(*l); j++){
                if(ELMTLD(*l,i)<ELMTLD(*l,j)){
                    temp = ELMTLD(*l,i);
                    ELMTLD(*l,i) = ELMTLD(*l,j);
                    ELMTLD(*l,j) = temp;
                }
            }
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
void insertLast(ListDin *l, ElType val) {
    ELMTLD(*l, getLastIdx(*l)+1) = val;
    NEFF(*l) ++;
}

void deleteLast(ListDin *l, ElType *val) {
    *val = ELMTLD(*l,getLastIdx(*l));
    NEFF(*l) --;
}

void expandList(ListDin *l, int num) {
    ListDin new;
    int newNEFF;
    IdxType i;

    CreateListDin(&new, CAPACITYLD(*l));
    copyList(*l,&new);
    newNEFF = NEFF(*l);
    dealocateList(l);
    CreateListDin(l, CAPACITYLD(new)+num);
    NEFF(*l) = newNEFF;

    for(i=0; i<listLength(new); i++){
        ELMTLD(*l,i) = ELMTLD(new,i);
    }
}

void shrinkList(ListDin *l, int num) {
    ListDin new;
    int newNEFF;
    IdxType i;

    CreateListDin(&new, CAPACITYLD(*l));
    copyList(*l,&new);
    newNEFF = NEFF(*l);
    CreateListDin(l, CAPACITYLD(new)-num);
    NEFF(*l) = newNEFF;

    if(CAPACITYLD(new) - num < NEFF(*l)){
        NEFF(*l) = CAPACITYLD(new) - num;
    }

    for(i=0; i<listLength(new); i++){
        ELMTLD(*l,i) = ELMTLD(new,i);
    }
}

void compressList(ListDin *l) {
    shrinkList(l, CAPACITYLD(*l) -  NEFF(*l));
}