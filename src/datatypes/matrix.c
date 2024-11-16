#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "matrix.h"
#include <math.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m) {
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j) {
    return ( (i>= 0 && i < ROW_CAP && j>= 0 && j < COL_CAP));
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
/* Mengirimkan Index baris terbesar m */
IdxType getLastIdxRow(Matrix m) {
    return (m.rowEff - 1);
}
/* Mengirimkan Index kolom terbesar m */
IdxType getLastIdxCol(Matrix m) {
    return (m.colEff - 1);
}
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
boolean isIdxEff(Matrix m, IdxType i, IdxType j) {
    return (i >= 0 && i < m.rowEff && j >= 0 && j < m.colEff);
}
/* Mengirimkan elemen m(i,i) */
ElType getElmtDiagonal(Matrix m, IdxType i) {
    return (m.mem[i][i]);
}


/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut) {
    int i, j;
    createMatrix(mIn.rowEff, mIn.colEff, mOut);
    for (i = 0; i < mIn.rowEff; i++) {
        for (j = 0; j < mIn.colEff; j++) {
            mOut->mem[i][j] = mIn.mem[i][j];
        }
    }
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol) {
    createMatrix(nRow, nCol, m);
    int i, j;
    for (i = 0; i < nRow; i++) {
        for (j = 0; j < nCol; j++) {
            scanf("%d", &m->mem[i][j]);
        }
    }
}

void displayMatrix(Matrix m) {
   if (m.rowEff ==0 && m.colEff ==0) {
      return;
   } else {
      int i, j;
      for (i = 0; i < m.rowEff; i++) {
         for (j = 0; j < m.colEff; j++) {
            printf("%d", m.mem[i][j]);
            if (j < m.colEff - 1) {
               printf(" ");
            }
         }
         if (i != m.rowEff - 1) {
            printf("\n");
         }
      }
   }
}


/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
Matrix addMatrix(Matrix m1, Matrix m2) {
    Matrix m;
    createMatrix(m1.rowEff, m1.colEff, &m);
    int i, j;
    for (i = 0; i < m1.rowEff; i++) {
        for (j = 0; j < m1.colEff; j++) {
            m.mem[i][j] = m1.mem[i][j] + m2.mem[i][j];
        }
    }
    return m;
}
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
Matrix subtractMatrix(Matrix m1, Matrix m2) {
    Matrix m;
    createMatrix(m1.rowEff, m1.colEff, &m);
    int i, j;
    for (i = 0; i < m1.rowEff; i++) {
        for (j = 0; j < m1.colEff; j++) {
            m.mem[i][j] = m1.mem[i][j] - m2.mem[i][j];
        }
    }
    return m;
}
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
Matrix multiplyMatrix(Matrix m1, Matrix m2) {
    Matrix m;
    createMatrix(m1.rowEff, m2.colEff, &m);
    int i, j, k;
    for (i = 0; i < m1.rowEff; i++) {
        for (j = 0; j < m2.colEff; j++) {
            m.mem[i][j] = 0;
            for (k = 0; k < m2.rowEff;k++) {
                m.mem[i][j] += m1.mem[i][k] * m2.mem[k][j];
            }
        }
    }
    return m;
}
/* Mengirim hasil perkalian setiap elemen m dengan x */
Matrix multiplyByConst(Matrix m, ElType x) {
    Matrix mR;
    createMatrix(m.rowEff, m.colEff, &mR);
    int i, j;
    for (i = 0; i < m.rowEff; i++) {
        for (j = 0; j < m.colEff; j++) {
            mR.mem[i][j] = x*m.mem[i][j];
        }
    }
    return mR;
}
/* F.S. Mengalikan setiap elemen m dengan k */
void pMultiplyByConst(Matrix *m, ElType k) {
    int i, j;
    for (i = 0; i < m->rowEff; i++) {
        for (j = 0; j < m->colEff; j++) {
            m->mem[i][j] *= k;
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isMatrixEqual(Matrix m1, Matrix m2) {
    if (!isMatrixSizeEqual(m1, m2)) {
        return false;
    } else {
        int i, j;
        for (i = 0; i < m1.rowEff; i++) {
            for (j = 0; j < m2.colEff; j++) {
                if (m1.mem[i][j] != m2.mem[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
}
/* Mengirimkan true jika m1 tidak sama dengan m2 */
boolean isMatrixNotEqual(Matrix m1, Matrix m2) {
    return (!isMatrixEqual(m1, m2));
}

boolean isMatrixSizeEqual(Matrix m1, Matrix m2) {
    return (m1.rowEff == m2.rowEff && m1.colEff == m2.colEff);
}

/* ********** Operasi lain ********** */
/* Mengirimkan banyaknya elemen m */
int countElmt(Matrix m) {
    return (m.colEff*m.rowEff);
}

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
boolean isSquare(Matrix m) {
    return (m.colEff == m.rowEff);
}
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) dan untuk setiap elemen m, m(i,j)=m(j,i) */
boolean isSymmetric(Matrix m) {
    if (!isSquare(m)) {
        return false;
    } else {
        int i, j;
        for (i = 0; i < m.rowEff; i++) {
            for (j = 0; j < m.colEff; j++) {
                if (m.mem[i][j] != m.mem[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }
}
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
boolean isIdentity(Matrix m) {
    if (!isSquare(m)) {
        return false;
    } else {
        int i, j;
        for (i = 0; i < m.rowEff; i++) {
            for (j = 0; j < m.colEff; j++) {
                if (i == j) {
                    if (m.mem[i][j] != 1) return false;
                } else {
                    if (m.mem[i][j] != 0) return false;
                }
            }
        }
        return true;
    }
}
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
boolean isSparse(Matrix m) { //60-62
    int i, j, count = 0;
    for (i = 0; i < m.rowEff; i++) {
        for (j = 0; j < m.colEff; j++) {
            if (m.mem[i][j] != 0) count ++;
        }
    }
    return(count*100 <= (countElmt(m)*5));
}
/* Menghasilkan salinan m dengan setiap elemen dinegasikan (dikalikan -1) */
Matrix negation(Matrix m) {
    return multiplyByConst(m, -1);
}
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
void pNegation(Matrix *m) {
    pMultiplyByConst(m, -1);
}
/* Menghitung nilai determinan m */
float determinant(Matrix m) {
   float det = 0.0;
   int r, n = m.colEff;
   if (n == 1) {
      return m.mem[0][0];
   }

   Matrix temp;
   createMatrix(n-1, n-1, &temp);
   int sign = 1;
   for (r = 0; r < n; r++) {
      int row, col;
      int i = 0, j = 0;
      //getCofactor
      for (row = 0; row < n; row++) {
         for (col = 0; col < n; col++) {
            if (row != 0 && col != r) {
               temp.mem[i][j++] = m.mem[row][col];
               if (j == n-1) {
                  j = 0;
                  i++;
               }
            }
         }
      }
      det += sign * m.mem[0][r] * determinant(temp);
      sign = -sign;
   }
   return det;
}

/* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
Matrix transpose(Matrix m) {
    Matrix mR;
    createMatrix(m.rowEff, m.colEff, &mR);
    int i, j;
    for (i = 0; i < m.rowEff; i++) {
        for (j = 0; j < m.colEff; j++) {
            mR.mem[i][j] = m.mem[j][i];
        }
    }
    return mR;
}
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
void pTranspose(Matrix *m) {
   int i, j;
   for (i=0; i< m->rowEff; i++){
      for (j=i+1; j< m->colEff; j++){
         int temp = m->mem[i][j];
         m->mem[i][j] = m->mem[j][i];
         m->mem[j][i] = temp;
      }
   }
}
