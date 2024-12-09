#ifndef _BALASEMAIL_H
#define _BALASEMAIL_H

#include "../modules/boolean.h"
#include "../modules/mesinkarakter.h"
#include "../modules/mesinkata.h"
#include "../modules/datetime.h"
#include "../modules/listdin.h"
#include "../modules/stack.h"
#include "../modules/prioqueue.h"
#include "../modules/tree.h"

#include "../modules/listuser.h"
#include "../modules/listemail.h"

void addReplies(Tree node, ListEmail listEmail);
IdxType indexOfEmail(ListEmail l, int emailID);
IdxType getRoot (ListEmail l, int emailID);
ListDin createPreorderList(Tree p) ;
void printEmailHead(ListEmail ListEmail,Tree emailTree,int emailID);
void printEmail(ListEmail ListEmail,Tree emailTree,int emailID);
int findDepth(Address root, int val, int depth);
void readEmail(ListEmail listEmail, int emailID);
void replyEmail(int id_user, ListUser list_user, ListEmail listEmail, int id_reply);

#endif // 