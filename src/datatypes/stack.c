#include <stdio.h>
#include "../modules/stack.h"
#include "../modules/boolean.h"

/* *** Konstruktor/Kreator *** */
void CreateEmptyStack(Stack *S) {
    Top(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack(Stack S) {
    return Top(S) == Nil;
}

boolean IsFullStack(Stack S) {
    return Top(S) == MaxEl - 1;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushStack(Stack * S, infotype X) {
    if (!IsFullStack(*S)) {
        Top(*S)++;
        InfoTop(*S) = X;
    } 
}

/* ************ Menghapus sebuah elemen Stack ************ */
void PopStack(Stack * S, infotype* X) {
    if (!IsEmptyStack(*S)) {
        *X = InfoTop(*S);
        Top(*S)--;
    } 
}