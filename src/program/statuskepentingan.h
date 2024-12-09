#ifndef _STATUSKEPENTINGAN_H
#define _STATUSKEPENTINGAN_H

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

#include "../program/utility.h"
#include "../pengguna/pengguna.h"
#include "../program/program.h"

#define KEPENTINGAN(M, A, B) \
    ELMTMATRIX(M, (A - 1), (B - 1))  // Kepentingan USER ID A terhadap B
#define IDPENGIRIM(l, i) (l).data[(i)].idPengirim  // Akses ID Pengirim
#define IDPENERIMA(l, i) (l).data[(i)].idPenerima  // Akses ID Penerima
#define IDCC(l, i) (l).data[(i)].idCC              // Akses ID CC

void readStatusKepentingan(ListUser LU, ListEmail LE, Matrix *m);
void displaySeparator(int userCount, int padding);
void displayStatusKepentingan(Matrix m);
void statusKepentingan(ListUser listUser, ListEmail listEmail);
void StartStatusKepentingan();

#endif 