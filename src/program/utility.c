#ifndef UTILITY_H
#define UTILITY_H

#include "utility.h"
#include "../modules.h"
#include <stdlib.h>
#include <stdio.h>

char* storedWord;

/* String to Integer */
int stringToInt(char* str) {
    int result = 0, sign = 1, i = 0;
    
     if (str[0] == '-') {
        sign = -1; i++;
    }
    
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
        i++;
    } 
    return sign * result;
}

/* Store word yang dibaca pada file */
char* store(char *word){
    storedWord = (char *) malloc(CAPACITY_CHAR_EMAIL);
    int i = 0;
    while (word[i] != '\0'){
        storedWord[i] = word[i];
        i++;
    }
    storedWord[i] = '\0';
    return storedWord;
}

/* Panjang String */
int lenWord(char* word) {
    int i = 0;
    while (word[i] != '\0') {
        i++;
    }
    return i;
}

/* Kesamaan Word */
boolean isEqual(Word currentWord, char *word){
    if (currentWord.Length == lenWord(word)) {
        for (int k = 0; k < lenWord(word); k++) {
            if (currentWord.TabWord[k] != word[k])
                return false;
        }
        return true;
    }
    return false;
}

/* Convert to String */
char* toString(Word currentWord){
    char* string = malloc(256 * sizeof(char));
    int i = 0;
    while (currentWord.TabWord[i] != '\0') {
        string[i] = currentWord.TabWord[i];
        i++;
    }
    string[i] = '\0';
    return string;
}

#endif
