#include <stdio.h>
#include "loadData.c"
#include "./datatypes/tree.c"
#include "./datatypes/listdin.c"
#include "draftemail.c"

// Fungsi untuk membentuk emailtree dengan menambah semua reply ke subjek utama
void addReplies(Tree node, ListEmail listEmail, int idUser) {
    for (int i = 0; i < listEmail.number; i++) { // Mencari semua reply dari email
        if (listEmail.data[i].reply == node->info) {
            if (listEmail.data[i].idPenerima == idUser || listEmail.data[i].idCC == idUser) {
                Address newNode = newTreeNode(listEmail.data[i].id);
                if (newNode != NULL) {
                    if (LEFT (node) == NULL) {
                        LEFT(node) = newNode;
                        addReplies(newNode, listEmail);
                    } else if (RIGHT(node) == NULL) {
                        RIGHT(node) = newNode;
                        addReplies(newNode, listEmail);
                    } else {
                        printf("Error: Node is full\n");
                    }
                }
            }
        }
    }
}

// Fungsi untuk mencari indeks email berdasarkan emailID
IdxType indexOfEmail(ListEmail l, int emailID) {
    boolean found;
    IdxType i = 0;
   
    if(isEmptyEmail(l)){ // Jika list kosong
        return IDX_UNDEF;
    } else{
        found = 0;
        while(!found && i<=l.number){
            if (ELMT_EMAIL(l, i).id == emailID){
                found = 1;
            } else{
                found = 0;
                i++;
            }
        }
        if(found){
            return i;
        } else{ // Jika tidak ditemukan
            return IDX_UNDEF;
        }
    }
}

// Fungsi untuk mencari indeks email root dari emailID
IdxType getRoot (ListEmail l, int emailID){
    IdxType i = indexOfEmail(l, emailID);
    while (l.data[i].reply != -1){
        i = indexOfEmail(l, l.data[i].reply);
    }
    return i;
}

// Fungsi untuk membuat list preorder dari emailTree
ListDin createPreorderList(Tree p) {
    ListDin l;
    CreateListDin(&l, 100);
    if (isTreeEmpty(p)) {
        return l;
    } else {
        insertLast(&l, ROOT(p));
        ListDin left = createPreorderList(LEFT(p));
        ListDin right = createPreorderList(RIGHT(p));
        for (int i = 0; i < left.nEff; i++) {
            insertLast(&l, left.buffer[i]);
        }
        for (int i = 0; i < right.nEff; i++) {
            insertLast(&l, right.buffer[i]);
        }
        return l;
    }
}

// Fungsi untuk mencetak email head
void printEmailHead(ListEmail ListEmail,Tree emailTree,int emailID){
    emailType email = ELMT_EMAIL(ListEmail, indexOfEmail(ListEmail, emailID));
    printf("[----------------------------[ Baca Pesan ]---------------------------]\n");
    printf(" Inbox ID: EMAIL%d\n",email.id);
    printf(" Subject: %s\n",email.subyek);
    printf(" Pengirim: %d\n",email.idPengirim);
    printf(" Timestamp: %s\n",email.timestamp);
    printf("[---------------------------------------------------------------------]\n");
}

// Fungsi untuk mencetak email
void printEmail(ListEmail ListEmail,Tree emailTree,int emailID){
    emailType email = ELMT_EMAIL(ListEmail, indexOfEmail(ListEmail, emailID));
    printf("\n[%s]\n",email.subyek);
    printf("[---------------------------------------------------------------------]\n");
    printf(" %s\n",email.body);
    printf("[---------------------------------------------------------------------]\n");
}

// Fungsi untuk mencari kedalaman dari suatu node
int findDepth(Address root, int val, int depth) { 
    if (root == NULL) { // Jika root kosong
        return -1;  
    } 
    if (root->info == val) { 
        return depth; 
    } 
    int leftDepth = findDepth(root->left, val, depth + 1); 
    if (leftDepth != -1) { // Jika node ditemukan di subtree kiri
        return leftDepth; 
    } 
    return findDepth(root->right, val, depth + 1);
}

// Fungsi untuk membaca email
void readEmail(ListEmail listEmail, int emailID) {
    if (indexOfEmail(listEmail, emailID) == IDX_UNDEF) {
        printf("Email tidak ditemukan\n");
        return;
    } else if (listEmail.data[indexOfEmail(listEmail, emailID)].idPenerima != 0) {
        printf("Email tidak diperuntukkan untuk Anda\n");
        return;
    }

    IdxType root = getRoot(listEmail, emailID);
    Tree emailTree = newTreeNode(listEmail.data[root].id);
    addReplies(emailTree, listEmail);
    printEmailHead(listEmail,emailTree,emailID);
    ListDin l = createPreorderList(emailTree);
    for (int i = 0; i < l.nEff; i++) {
        printEmail(listEmail, emailTree, l.buffer[i]);
    }
}

// Fungsi untuk membalas email
void replyEmail(int id_user, ListUser list_user, ListEmail listEmail, int id_reply) {
    if (indexOfEmail(listEmail, id_reply) == IDX_UNDEF) {
        printf("Email tidak ditemukan\n");
        return;
    } else if (listEmail.data[indexOfEmail(listEmail, id_reply)].idPenerima != id_user) {
        printf("Email tidak diperuntukkan untuk Anda\n");
        return;
    }
    
    IdxType root = getRoot(listEmail, id_reply);
    Tree emailTree = newTreeNode(listEmail.data[root].id);
    addReplies(emailTree, listEmail);
    int reply = findDepth(emailTree, id_reply, 0) + 1;
    int id_old = listEmail.data[root].id;
    DraftEmail(id_user, list_user, &listEmail, reply, id_reply, id_old);
}