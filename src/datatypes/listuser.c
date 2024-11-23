#include "../modules/boolean.h"
#include <stdio.h>
#include "../modules/listuser.h"

/* ********** KONSTRUKTOR ********** */
void CreateListUser(ListUser *l) {
    l->number = 0;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyUser(ListUser l) {
    return l.number == 0;
}

boolean isFullUser(ListUser l) {
    return l.number == CAPACITY;
}

void printListUser(ListUser l) {
    IdxType i;
    userType user;
    if (isEmptyUser(l)){
        printf("List User Kosong.\n");
    } else{
        for(i = 0; i < l.number; i++){
            user = ELMT(l, i);
            printf("-----\n%d\n%s\n%s\n", user.id, user.email, user.password);
        }
        printf("-----\n");
    }
}

void addUser(ListUser *l, userType user) {
    if (!isFullUser(*l)) {
        l->data[l->number] = user;
        l->number++;
    }
}