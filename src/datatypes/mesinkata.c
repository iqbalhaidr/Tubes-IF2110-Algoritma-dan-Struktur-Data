#include "../modules/boolean.h"
#include "../modules/mesinkata.h"
#include "../modules/mesinkarakter.h"
#include <stdio.h>

boolean EndWord;
Word currentWord;

void IgnoreBlanks() {
    while (currentChar == BLANK) {
        ADV();
    }
}

void STARTWORD() {
    START();
    IgnoreBlanks();
    if (currentChar == MARK) {
        EndWord = true;
    } else { //!=mark
        EndWord = false;
        CopyWord();
    }
}

void ADVWORD() {
    IgnoreBlanks();
    if (currentChar == MARK) {
        EndWord = true;
    } else {
        CopyWord();
        IgnoreBlanks();
    }
}

void CopyWord() {
    int i = 0;
    while ((currentChar != MARK) && (currentChar != BLANK) && i<= NMax) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    currentWord.TabWord[i] = '\0';
    if (i > NMax) {
        currentWord.Length = NMax;
    } else {
        currentWord.Length = i;
    }
}

void DisplayCurrentWord() {
    for (int i = 0; i < currentWord.Length; i++) {
        printf("%c", currentWord.TabWord[i]);
    }
}

int lenWord(char* word) {
    int i = 0;
    while (word[i] != '\0') {
        i++;
    }
    return i;
}

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