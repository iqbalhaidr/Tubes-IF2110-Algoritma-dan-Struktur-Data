#ifndef _DRAFTEMAIL_H
#define _DRAFTEMAIL_H

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

int FindIdBasedEmail(ListUser l , Word e);
char* FindEmailBasedId(ListUser l , int e);
int FindIdPengirimBasedIdEmail(ListEmail l , int e);
char* FindSubyekBasedIdEmail(ListEmail l , int e);
boolean CheckEmptyEmail(ListDin l) ;
char* MakeNewSubyekEmail(int reply , char* email_old_subyek);
emailType BuatDraftEmail(int id_user , ListUser list_user);
emailType BuatDraftBalasEmail(int id_user , ListUser list_user , ListEmail list_email , int reply , int id_reply , int id_old) ;
void BatalDraftEmail(emailType *email , int reply);
void UbahDraftEmail(emailType *email , int id_user , ListUser list_user);
void UbahDraftBalasEmail(emailType *email , int id_user , ListUser list_user) ;
void KirimDraftEmail(ListEmail *list_email , emailType *email);
void LihatDraftEmail(ListUser list_user , emailType email);
void UndoDraftEmail(emailType *email , Stack *stack_main , Stack *stack_temp);
void RedoDraftEmail(emailType *email , Stack *stack_main , Stack *stack_temp) ;
void DraftEmail(int id_user , ListUser list_user , ListEmail *list_email , int reply , int id_reply , int id_old);
void StartDraftEmail();

#endif // 