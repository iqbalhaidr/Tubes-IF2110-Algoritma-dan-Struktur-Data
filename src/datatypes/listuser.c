#include <stdio.h>
#include "../modules/boolean.h"
#include "../modules/listuser.h"
#include "../modules/mesinkata.h"

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
    return l.number == CAPACITY_USER;
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

/* ********** SEARCHING ********** */
int idUser(ListUser l, Word word) {
    boolean found;
    int i = 0;

    if(isEmptyUser(l)){
        return IDX_UNDEF_USER;
    } else{
        found = false;
        while(!found && i < l.number) {
            // printf("is equal email: cur word %s and data %s\n", toString(word), l.data[i].email);
            if (isEqual(word, l.data[i].email)){
                found = true;
            } else{
                found = false;
                i++;
            }
        }
        if(found) {
            return i++;
        } else {
            return IDX_UNDEF_USER;
        }
    }
}