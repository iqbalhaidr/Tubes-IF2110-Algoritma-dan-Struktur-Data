#ifndef _UTILITY_H
#define _UTILITY_H

#include "../modules/mesinkarakter.h"
#include "../modules/mesinkata.h"

int stringToInt(char* str);
char* store(char *word);
int lenWord(char *word);
/* Mengembalikan nilai panjang dari string word*/

boolean isEqual(Word currentWord, char *word);
/* Mengembalikan nilai true jika currentWord == word, mengembalikan false jika tidak.
   I.S.  : currentWord terdefinisi
   F.S.  : mengembalikan nilai sesuai komparasi
*/

char* toString(Word currentWord);

#endif