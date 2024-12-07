#include "../modules/boolean.h"
#include "../modules/mesinkata.h"
#include "../modules/mesinkarakter.h"
#include <stdio.h>
#include <stdlib.h>

boolean over;
boolean EndWord;
Word currentWord;

void reset() {
    currentWord.Length = 0;
    for (int i = 0; i < NMax; i++) {
        currentWord.TabWord[i] = BLANK;
    }
    currentChar = BLANK;
    EOP = false;
    over = false;
    EndWord = false;
}


void IgnoreBlanks() {
    while (currentChar == BLANK || currentChar == '\n') {
        ADV();
    }
}

void STARTWORD() {
    reset();
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

void IgnoreEnter() {
    if (currentChar == '\n') {
        ADV();
    }
}

void STARTWORDDraft() {
    reset();
    START();
    IgnoreEnter();
    if (currentChar == MARK) {
        EndWord = true;
    } else {
        EndWord = false;
        CopyWordDraft();
    }
}
void CopyWordDraft() {
    int i = 0;
    while ((currentChar != MARK) && i < NMax) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    while (currentChar != MARK) {
        ADV();
        over = true;
    }
    currentWord.Length = i;
    currentWord.TabWord[i] = '\0';
}

void CopyWord() {
    int i = 0;
    while ((currentChar != MARK) && (currentChar != BLANK) && i < NMax) {
        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    currentWord.TabWord[i] = '\0';
    currentWord.Length = i;
}

void DisplayCurrentWord() {
    for (int i = 0; i < currentWord.Length; i++) {
        printf("%c", currentWord.TabWord[i]);
    }
}