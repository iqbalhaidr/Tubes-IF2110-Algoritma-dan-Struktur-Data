#include <stdio.h>
#include "prioqueue.h"
#include "boolean.h"

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq){
    IDX_HEAD(*pq) = IDX_UNDEF;
    IDX_TAIL(*pq) = IDX_UNDEF;
}
/* I.S. sembarang */
/* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */

/* ********* Prototype ********* */
boolean isEmpty(PrioQueue pq){
    return (IDX_HEAD(pq) == IDX_UNDEF && IDX_TAIL(pq) == IDX_UNDEF);
}
/* Mengirim true jika pq kosong: lihat definisi di atas */
boolean isFull(PrioQueue pq){
    return ((IDX_TAIL(pq) + 1) % CAPACITY == IDX_HEAD(pq));
}
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu IDX_TAIL akan selalu di belakang IDX_HEAD dalam buffer melingkar*/

int length(PrioQueue pq){
    if (isEmpty(pq)) {
        return 0;
    } else if (IDX_TAIL(pq) >= IDX_HEAD(pq)) {
        return IDX_TAIL(pq) - IDX_HEAD(pq) + 1;
    } else {
        return CAPACITY - IDX_HEAD(pq) + IDX_TAIL(pq) + 1;
    }
}
/* Mengirimkan banyaknya elemen prioqueue. Mengirimkan 0 jika pq kosong. */

/* *** Primitif Add/Delete *** */
void enqueue(PrioQueue *pq, ElType val){
    if (isEmpty(*pq)) {
        IDX_HEAD(*pq) = 0;
        IDX_TAIL(*pq) = 0;
        TAIL(*pq) = val;
    } else {
        
        int tempval;
        int i=IDX_HEAD(*pq);
        IDX_TAIL(*pq) = (IDX_TAIL(*pq) + 1) % CAPACITY;
        
        
        
        while (i!=IDX_TAIL(*pq) && (*pq).buffer[i]>val){
            i = (i + 1) % CAPACITY;
        }
        if (i == IDX_TAIL(*pq) ){
            (*pq).buffer[i] = val;
        }else{
            ElType temp ;
            temp = (*pq).buffer[i];
            (*pq).buffer[i]=val;
            val=temp;
            i = (i + 1) % CAPACITY;
            while (i != (IDX_TAIL(*pq) +1)%CAPACITY ){
                temp = (*pq).buffer[i];
                (*pq).buffer[i]=val;
                val=temp;
                i = (i + 1) % CAPACITY;
            }
        }

        
    }
    
}
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val disisipkan pada posisi yang sesuai, IDX_TAIL "mundur" dalam buffer melingkar.,
    pq terurut mengecil */

void dequeue(PrioQueue *pq, ElType *val){
    *val = HEAD(*pq);
    if (IDX_HEAD(*pq) == IDX_TAIL(*pq)) {
        IDX_HEAD(*pq) = IDX_UNDEF;
        IDX_TAIL(*pq) = IDX_UNDEF;
    } else {
        IDX_HEAD(*pq) = (IDX_HEAD(*pq) + 1) % CAPACITY;
    }
}

/* Proses: Menghapus val pada pq dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., IDX_HEAD "mundur";
        pq mungkin kosong */

/* *** Display Queue *** */
void displayPrioQueue(PrioQueue pq){
    printf("[");
    if (!isEmpty(pq)) {
        int i = IDX_HEAD(pq);
        while (1) {
            printf("%d", pq.buffer[i]);
            if (i == IDX_TAIL(pq)) {
                break;
            }
            printf(",");
            i = (i + 1) % CAPACITY;
        }
    }
    printf("]\n");
}
/* Proses : Menuliskan isi PrioQueue dengan traversal, PrioQueue ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. pq boleh kosong */
/* F.S. Jika pq tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 30, 20, 1 akan dicetak: [30,20,1] */
/* Jika Queue kosong : menulis [] */