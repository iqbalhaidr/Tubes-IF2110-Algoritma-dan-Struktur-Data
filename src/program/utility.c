#ifndef UTILITY_H
#define UTILITY_H

#include "utility.h"
#include "../modules.h"
#include "../modules/mesinkata.h"
#include <stdlib.h>
#include <stdio.h>

char* storedWord;

Word perintah() {
    printf(">> ");
    STARTWORDDraft();
    return currentWord;
}

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
    storedWord = (char *) malloc(1001);
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

boolean isEqualStr(char* word1, char* word2) {
     if (lenWord(word1) == lenWord(word2)) {
        for (int k = 0; k < lenWord(word1); k++) {
            if (word1[k] != word2[k])
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
    while (i < currentWord.Length) {
        string[i] = currentWord.TabWord[i];
        i++;
    }
    string[i] = '\0';
    return string;
}

// Function to concatenate two strings
char* concat(char *str1, char *str2) {
    int length1 = lenWord(str1);
    int length2 = lenWord(str2);

    char *result = (char *)malloc(length1 + length2 + 1);

    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < length1; i++) {
        result[i] = str1[i];
    }

    for (int i = 0; i < length2; i++) {
        result[length1 + i] = str2[i];
    }

    result[length1 + length2] = '\0';

    return result;
}

void red(){
    printf("\033[0;31m");
}

void green(){
    printf("\033[0;32m");
}

void yellow(){
    printf("\033[0;33m"); 
}

void blue(){
    printf("\033[0;34m");
}

void defaultp(){
    printf("\033[0m");
}

void bold() {
    printf("\033[1m");
}

#endif
