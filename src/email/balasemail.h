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

#include "../program/utility.h"
#include "../pengguna/pengguna.h"
#include "../program/program.h"

void addReplies(Tree node, ListEmail listEmail);
IdxType indexOfEmail(int emailID, ListEmail listEmail);
IdxType indexOfRoot (int emailID, ListEmail listEmail);
ListDin createListOfNary(Tree root);
void printEmailHead(Tree emailTree, int emailID, ListEmail listEmail);
void printEmail(Tree emailTree, int emailID, ListEmail listEmail);
void BacaEmail(int emailID, ListEmail listEmail, ListUser listUser);
void BalasEmail(int id_reply, ListEmail listEmail, ListUser listUser);
void StartBalasEmail ();

#endif // 