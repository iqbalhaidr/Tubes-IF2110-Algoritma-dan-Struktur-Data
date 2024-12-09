#include <stdio.h>
#include <stdlib.h>
#include "balasemail.h"
#include "draftemail.h"
#include "../globals.h"

// Fungsi untuk membentuk emailtree dengan menambah semua reply ke subjek utama
void addReplies(Tree node, ListEmail listEmail) {
    for (int i = 0; i < listEmail.number; i++) { // Mengecek setiap email pada listEmail
        if (listEmail.data[i].reply == node->info) { // Jika email merupakan reply dari email yang sedang dicek
            if (listEmail.data[i].idPenerima == user.id || listEmail.data[i].idCC == user.id) {
                Address newNode = newTreeNode(listEmail.data[i].id);

                if (newNode != NULL) {
                    if (LEFT (node) == NULL) { // Jika email belum memiliki balasan sama sekali
                        LEFT(node) = newNode;
                        addReplies(newNode, listEmail);
                    } else  { // Jika email sudah memiliki balasan
                        Address nextNode = LEFT(node);

                        while (RIGHT(nextNode) != NULL) {
                            nextNode = RIGHT(nextNode);
                        }

                        RIGHT(nextNode) = newNode;
                        addReplies(newNode, listEmail);
                    } 
                }
            }
        }
    }
}

// Fungsi untuk mencari indeks email pada listEmail berdasarkan idnya
IdxType indexOfEmail(int emailID, ListEmail listEmail) {
    boolean found;
    IdxType i = 0;
   
    if(isEmptyEmail(listEmail)){ // Jika list kosong
        return IDX_UNDEF;
    } else{
        found = 0;

        while(!found && i<listEmail.number){
            if (ELMT_EMAIL(listEmail, i).id == emailID){
                found = 1;
            } else{
                found = 0;
                i++;
            }
        }

        if(found) {
            return i;
        } else{ // Jika email tidak ditemukan
            return IDX_UNDEF;
        }
    }
}

// Fungsi untuk mencari indeks email root dari email dengan id tertentu
IdxType indexOfRoot (int emailID, ListEmail listEmail) {
    IdxType i = indexOfEmail(emailID, listEmail);

    while (listEmail.data[i].reply != -1) {
        i = indexOfEmail(listEmail.data[i].reply, listEmail);
    }
    return i;
}

// Fungsi membentuk list dari semua email pada binary tree seakan n-ary tree
ListDin createListOfNary(Tree root) {
    ListDin l;
    CreateListDin(&l, 100);

    if (root == NULL) return l;

    insertLast(&l, root->info); // Menambahkan root ke list

    // Melakukan proses rekursif untuk setiap child
    Address child = root->left;
    while (child != NULL) {
        ListDin childList = createListOfNary(child);// Mendapatkan list dari child

        for (int i = 0; i < childList.nEff; i++) { //  Memasukkan semua elemen child ke list
            insertLast(&l, childList.buffer[i]);
        }

        child = child->right; // Melanjutkan ke child selanjutnya
    }

    return l;
}

// Fungsi untuk mencetak email head
void printEmailHead(Tree emailTree, int emailID, ListEmail listEmail){
    emailType email = ELMT_EMAIL(listEmail, indexOfEmail(emailID, listEmail));
    printf("[----------------------------[ Baca Pesan ]---------------------------]\n");
    printf(" Inbox ID: EMAIL%d\n",email.id);
    printf(" Subject: %s\n",email.subyek);
    printf(" Pengirim: %d\n",email.idPengirim);
    printf(" Timestamp: %s\n",email.timestamp);
    printf("[---------------------------------------------------------------------]\n");
}

// Fungsi untuk mencetak email
void printEmail(Tree emailTree, int emailID, ListEmail listEmail){
    emailType email = ELMT_EMAIL(listEmail, indexOfEmail(emailID, listEmail));
    printf("\n[%s]\n",email.subyek);
    printf("[---------------------------------------------------------------------]\n");
    printf(" %s\n",email.body);
    printf("[---------------------------------------------------------------------]\n");
}

// Fungsi untuk mencari node pada tree
int getNextReplyNumber(Tree parent) {
    int replyNumber = 1;

    // Menghitung jumlah balasan yang sudah ada
    Address child = parent->left; 
    while (child != NULL) {
        replyNumber++;
        child = child->right;
    }

    return replyNumber;
}

void BacaEmail(int emailID, ListEmail listEmail, ListUser listUser) {
    if (indexOfEmail(emailID, listEmail) == IDX_UNDEF) {
        printf("Email tidak ditemukan\n");
        return;
    }
    // } else if (listEmail.data[indexOfEmail(emailID, listEmail)].idPenerima != user.id) {
    //     printf("Email tidak diperuntukkan untuk Anda\n");
    //     return;
    // }

    IdxType root = indexOfRoot(emailID, listEmail); 

    Tree emailTree = newTreeNode(listEmail.data[root].id);

    addReplies(emailTree, listEmail); 

    printEmailHead(emailTree, emailID, listEmail); 
    
    ListDin listNary = createListOfNary(emailTree); 

    for (int i = 0; i < listNary.nEff; i++) { 
        printEmail(emailTree, listNary.buffer[i], listEmail);
    }
}

void BalasEmail(int id_reply, ListEmail listEmail, ListUser listUser) {
    if (indexOfEmail(id_reply, listEmail) == IDX_UNDEF) {
        printf("Email tidak ditemukan\n");
        return;
    } else if (listEmail.data[indexOfEmail(id_reply, listEmail)].idPenerima != user.id) {
        printf("Email tidak diperuntukkan untuk Anda\n");
        return;
    }

    IdxType root = indexOfRoot(id_reply, listEmail);

    Tree emailTree = newTreeNode(listEmail.data[root].id);

    addReplies(emailTree, listEmail);

    int reply = getNextReplyNumber(findNode(emailTree, id_reply));

    int id_old = listEmail.data[root].id;
    
    DraftEmail(user.id, listUser, &listEmail, reply, id_reply, id_old);
}

void StartBalasEmail () {
    printf("Pilihan Opsi :\n");
    printf("     --- BACA_PESAN\n");
    printf("     --- BALAS_PESAN\n");
    do {
        printf("Masukkan perintah dalam mode BALAS_PESAN: ");
        Word input = perintah();  // Memulai input perintah

        if (isEqual(input, "BALAS_PESAN") || isEqual(input, "BACA_PESAN")) {

            if (isEqual(currentWord, "BACA_PESAN")) {
                ADVWORD();  // Ambil kata kedua
                if (!EndWord) {  // Memastikan ada kata kedua
                    // Validasi format "EMAILxxx"
                    int isValid = 1;
                    if (currentWord.Length == 8) {
                        // Pastikan 5 karakter pertama adalah "EMAIL"
                        int i;
                        for (i = 0; i < 5; i++) {
                            if (currentWord.TabWord[i] != "EMAIL"[i]) {
                                isValid = 0;
                                break;
                            }
                        }
                        // Pastikan karakter ke-6 hingga ke-8 adalah angka
                        if (isValid) {
                            for (i = 5; i < currentWord.Length; i++) {
                                if (currentWord.TabWord[i] < '0' || currentWord.TabWord[i] > '9') {
                                    isValid = 0;
                                    break;
                                }
                            }
                        }
                    } else {
                        isValid = 0;
                    }

                    if (isValid) {
                        // Konversi angka dari "EMAILxxx"
                        int emailID = 0;
                        for (int i = 5; i < currentWord.Length; i++) {
                            emailID = emailID * 10 + (currentWord.TabWord[i] - '0');
                        }

                        BacaEmail(emailID, listEmail, listUser);  // Fungsi untuk membaca pesan
                        
                    } else {
                        printf("Perintah tidak valid. Format harus 'EMAILxxx'.\n");
                    }
                } else {
                    printf("Perintah tidak valid. Harus ada dua kata.\n");
                }
            } else if (isEqual(currentWord, "BALAS_PESAN")) {
                ADVWORD();  // Ambil kata kedua
                if (!EndWord) {  // Memastikan ada kata kedua
                    // Validasi format "EMAILxxx"
                    int isValid = 1;
                    if (currentWord.Length == 8) {
                        // Pastikan 5 karakter pertama adalah "EMAIL"
                        int i;
                        for (i = 0; i < 5; i++) {
                            if (currentWord.TabWord[i] != "EMAIL"[i]) {
                                isValid = 0;
                                break;
                            }
                        }
                        // Pastikan karakter ke-6 hingga ke-8 adalah angka
                        if (isValid) {
                            for (i = 5; i < currentWord.Length; i++) {
                                if (currentWord.TabWord[i] < '0' || currentWord.TabWord[i] > '9') {
                                    isValid = 0;
                                    break;
                                }
                            }
                        }
                    } else {
                        isValid = 0;
                    }

                    if (isValid) {
                        // Konversi angka dari "EMAILxxx"
                        int emailID = 0;
                        for (int i = 5; i < currentWord.Length; i++) {
                            emailID = emailID * 10 + (currentWord.TabWord[i] - '0');
                        }
                        
                        BalasEmail(emailID, listEmail, listUser);  // Fungsi untuk membalas pesan

                    } else {
                        printf("Perintah tidak valid. Format harus 'EMAILxxx'.\n");
                    }
                } else {
                    printf("Perintah tidak valid. Harus ada dua kata.\n");
                }
            } else if (isEqual(currentWord, "KELUAR dari mode BALAS_PESAN.")) {
                printf("Keluar...\n");
                break;
            }
        } else {
            printf("Perintah tidak valid.\n");
        }
    } while (1);  // Loop berjalan hingga perintah "KELUAR" diterima
}
