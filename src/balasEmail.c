#include <stdio.h>
#include "loadData.c"
#include "./datatypes/tree.c"
#include "./datatypes/listdin.c"

void addReplies(Address node, ListEmail listEmail) {
    for (int i = 0; i < listEmail.number; i++) {
        if (listEmail.data[i].reply == node->info) {
            Address newNode = newTreeNode(listEmail.data[i].id);
            if (newNode != NULL) {
                if (LEFT(node) == NULL) {
                    LEFT(node) = newNode;
                } else if (RIGHT(node) == NULL) {
                    RIGHT(node) = newNode;
                } else {
                    // Tambahkan balasan ke sub-tree
                    addReply(&LEFT(node), listEmail.data[i].id);
                }
            }
            addReplies(newNode, listEmail);
        }
    }
}

IdxType indexOfEmail(ListEmail l, int emailID) {
    boolean found;
    IdxType i = 0;
   
    if(isEmptyEmail(l)){
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
        } else{
            return IDX_UNDEF;
        }
    }
}

IdxType getRoot (ListEmail l, int emailID){
    IdxType i = indexOfEmail(l, emailID);
    while (l.data[i].reply != -1){
        i = indexOfEmail(l, l.data[i].reply);
    }
    return i;
}

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

void printEmailHead(ListEmail ListEmail,Tree emailTree,int emailID){
    emailType email = ELMT_EMAIL(ListEmail, indexOfEmail(ListEmail, emailID));
    printf("[----------------------------[ Baca Pesan ]---------------------------]\n");
    printf(" Inbox ID: EMAIL%d\n",email.id);
    printf(" Subject: %s\n",email.subyek);
    printf(" Pengirim: %d\n",email.idPengirim);
    printf(" Timestamp: %s\n",email.timestamp);
    printf("[---------------------------------------------------------------------]\n");
}

void printEmail(ListEmail ListEmail,Tree emailTree,int emailID){
    emailType email = ELMT_EMAIL(ListEmail, indexOfEmail(ListEmail, emailID));
    printf("\n[%s]\n",email.subyek);
    printf("[---------------------------------------------------------------------]\n");
    printf(" %s\n",email.body);
    printf("[---------------------------------------------------------------------]\n");
}

void readEmail(ListEmail listEmail, int emailID) {
    // Menemukan root dari emailID
    IdxType root = getRoot(listEmail, emailID);
    
    // Buat tree dari daftar email
    Tree emailTree = newTreeNode(listEmail.data[root].id);
    
    // Tambahkan balasan untuk root
    addReplies(emailTree, listEmail);
    
    // Cetak email
    printEmailHead(listEmail,emailTree,emailID);

    ListDin l = createPreorderList(emailTree);
    for (int i = 0; i < l.nEff; i++) {
        printEmail(listEmail, emailTree, l.buffer[i]);
    }
}


int main(){
    ListEmail l = loadEmail();
    printListEmail(l);
    
    IdxType root = getRoot(l, 3);
    printf("indeks root : %d\n", root);

    readEmail(l, 3);
    return 0;
}
