#ifndef _NOTIFIKASI_H
#define _NOTIFIKASI_H

#include "../modules/boolean.h"
#include "../modules/mesinkarakter.h"
#include "../modules/mesinkata.h"
#include "../modules/datetime.h"
#include "../modules/listdin.h"
#include "../modules/stack.h"
#include "../modules/prioqueue.h"
#include "../modules/tree.h"
#include "../modules/matrix.h"

#include "../modules/listuser.h"
#include "../modules/listemail.h"
#include "statuskepentingan.h"

boolean isImportant(int interaction, int minInteraction);

void readNotifikasi(ListEmail LE, ListUser LU, int userID, int minInteraction,PrioQueue *importantQ, PrioQueue *normalQ);

void displayNotifikasi(PrioQueue *importantQ, PrioQueue *normalQ);

void notifikasi(ListEmail LE, ListUser LU, int userID, int minInteraction);

void StartNotifikasi();


#endif 

