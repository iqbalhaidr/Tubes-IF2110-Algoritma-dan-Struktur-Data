#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "balasemail.h"
#include "draftemail.h"
#include "inbox.h"
#include "../globals.h"

// Fungsi untuk membentuk emailtree dengan menambah semua reply ke subjek utama
void addReplies(Tree node, ListEmail listEmail) {
    for (int i = 0; i < listEmail.number; i++) { // Mengecek setiap email pada listEmail
        if (listEmail.data[i].reply == node->info) { // Jika email merupakan reply dari email yang sedang dicek
            if (listEmail.data[i].idPenerima == user.id || listEmail.data[i].idCC == user.id || listEmail.data[i].idPengirim == user.id) { // Jika email diperuntukkan untuk user
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
    char formattedID[10]; // Buffer untuk menyimpan ID terformat
    formatEmailID(listEmail.data[emailID - 1].id, formattedID); // Format ID menjadi 'EMAILxxx'

    int IDPengirim = listEmail.data[emailID - 1].idPengirim;

    printf("[-----------------------------------[ Baca Pesan ]----------------------------------]\n");
    printf(" Inbox ID: %s\n", formattedID); // Gunakan ID terformat
    printf(" Subject: %s\n", listEmail.data[emailID - 1].subyek);
    printf(" Pengirim: %s\n", listUser.data[IDPengirim - 1].email);
    printf(" Timestamp: %s\n", listEmail.data[emailID - 1].timestamp);
    printf("[-----------------------------------------------------------------------------------]\n");
}

// Fungsi untuk mencetak email
void printEmail(Tree emailTree, int emailID, ListEmail listEmail){
    emailType email = ELMT_EMAIL(listEmail, indexOfEmail(emailID, listEmail));
    printf("\n[%s]\n",email.subyek);
    printf("[-----------------------------------------------------------------------------------]\n");
    printf(" %s\n",email.body);
    printf("[-----------------------------------------------------------------------------------]\n");
}

void BacaEmail(int emailID, ListEmail listEmail, ListUser listUser) {
    int idx = indexOfEmail(emailID, listEmail);
    if (idx == IDX_UNDEF) {
        printf("Email tidak ditemukan\n");
        return;
    } else if (listEmail.data[idx].idPenerima != user.id && listEmail.data[idx].idCC != user.id) {
        printf("Email tidak diperuntukkan untuk Anda\n");
        return;
    }

    // Tandai pesan sebagai sudah dibaca krn idPenerima == user.id atau idCC == user.id
    if (listEmail.data[idx].idPenerima == user.id) {
        listEmail.data[idx].read = 1;
    } else if (listEmail.data[idx].idCC == user.id) {
        listEmail.data[idx].readCC = 1;
    } 

    IdxType root = indexOfRoot(emailID, listEmail); 

    Tree emailTree = newTreeNode(listEmail.data[root].id);

    addReplies(emailTree, listEmail); 

    printEmailHead(emailTree, emailID, listEmail); 
    
    ListDin listNary = createListOfNary(emailTree); 

    for (int i = 0; i < listNary.nEff; i++) { 
        printEmail(emailTree, listNary.buffer[i], listEmail);
    }
}

void BalasEmail(int id_reply, ListEmail *listEmail, ListUser listUser) {
    int idx = indexOfEmail(id_reply, *listEmail);
    if (idx == IDX_UNDEF) {
        printf("Email tidak ditemukan\n");
        return;
    } else if (listEmail->data[idx].idPenerima != user.id && listEmail->data[idx].idCC != user.id && listEmail->data[idx].idPengirim != user.id) {
        printf("Email tidak diperuntukkan untuk Anda\n");
        return;
    }

    IdxType root = indexOfRoot(id_reply, *listEmail);

    Tree emailTree = newTreeNode(listEmail->data[root].id);

    addReplies(emailTree, *listEmail);

    ListDin listNary = createListOfNary(emailTree); 

    int reply = listLength(listNary);

    int id_old = listEmail->data[root].id;
    
    DraftEmail(user.id, listUser, listEmail, reply, id_reply, id_old);
}

