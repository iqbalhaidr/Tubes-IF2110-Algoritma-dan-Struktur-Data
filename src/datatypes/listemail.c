#include "../modules/boolean.h"
#include "../modules/listemail.h"
#include <stdio.h>
#include <stdlib.h>

/* ********** KONSTRUKTOR ********** */
void CreateListEmail(ListEmail *l, int capacity) {
    DATA(*l) = (emailType*) malloc(capacity*sizeof(emailType));
    CAPACITY_EMAIL(*l) = capacity;
    NUMBER(*l) = 0;
}

void dealocateListEmail(ListEmail *l) {
    free(DATA(*l));
    CAPACITY_EMAIL(*l) = 0;
    NUMBER(*l) = 0;
}

/* ********** TEST KOSONG/PENUH ********** */
boolean isEmptyEmail(ListEmail l) {
    return (l.number == 0);
}

boolean isFullEmail(ListEmail l) {
    return (l.number == CAPACITY_EMAIL(l));

}

void printListEmail(ListEmail l) {
    IdxType i;
    emailType email;
    if (isEmptyEmail(l)){
        printf("List Email Kosong.\n");
    } else{
        for(i = 0; i < l.number; i++){
            email = ELMT_EMAIL(l, i);
            printf("-----\n");
            printf("%d\n%d\n%d\n%d\n%s\n", email.id, email.idPengirim, email.idPenerima, email.idCC,email.timestamp);
            printf("%s\n%s\n%d\n%d\n%d\n", email.subyek, email.body, email.reply, email.read, email.readCC);
        }
        printf("-----\n");
    }
}

void addEmail(ListEmail *l, emailType email){
    if (!isFullEmail(*l)) {
        l->data[l->number] = email;
        l->number++;
    } else {
        expandListEmail(l, CAPACITY_EMAIL(*l));
        l->data[l->number] = email;
        l->number++;
    }
}

/* ********** OPERASI LAIN ********** */
void copyListEmail(ListEmail lIn, ListEmail *lOut) {
    IdxType i;
    dealocateListEmail(lOut);
    CreateListEmail(lOut, CAPACITY_EMAIL(lIn));

    for(i = 0; i < lIn.number; i++){
        ELMT_EMAIL(*lOut, i) = ELMT_EMAIL(lIn, i);
    }
    NUMBER(*lOut) = NUMBER(lIn);
}

void expandListEmail(ListEmail *l, int num) {
    ListEmail new;
    int newNumber;
    IdxType i;

    CreateListEmail(&new, CAPACITY_EMAIL(*l));
    copyListEmail(*l,&new);
    newNumber = NUMBER(*l);
    dealocateListEmail(l);
    CreateListEmail(l, CAPACITY_EMAIL(new)+num);
    NUMBER(*l) = newNumber;

    for(i = 0; i < newNumber; i++){
        ELMT_EMAIL(*l,i) = ELMT_EMAIL(new,i);
    }
    dealocateListEmail(&new);
}