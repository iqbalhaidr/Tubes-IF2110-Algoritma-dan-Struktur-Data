#include "../modules/boolean.h"
#include "../modules/mesinkata.h"
#include "../modules/mesinkarakter.h"
#include "../program/utility.h"
#include <stdio.h>
#include <stdlib.h>

boolean over;
boolean EndWord;
Word currentWord;
boolean isInputFile;
extern int retval;

void reset() {
    currentWord.Length = 0;
    for (int i = 0; i < currentWord.Length; i++) { //changed
        currentWord.TabWord[i] = BLANK;
    }
    currentChar = BLANK;
    EOP = false;
    over = false;
    EndWord = false;
    isInputFile = false;
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
    if (!isInputFile) {
        while ((currentChar != MARK) && (i < NMax)) {
            currentWord.TabWord[i] = currentChar;
            ADV();
            i++;
        }
        while (currentChar != MARK) {
            ADV();
            over = true;
        }
    } else {
        while (retval != EOF) {
            currentWord.TabWord[i] = currentChar;
            ADV();
            i++;
        }
    }
    currentWord.Length = i;
    currentWord.TabWord[i] = '\0';
}

void CopyWord() {
    int i = 0;
    if (!isInputFile){
        //default
        while ((currentChar != MARK) && (currentChar != BLANK) && i<= NMax) {
            currentWord.TabWord[i] = currentChar;
            ADV();
            i++;
        }
        currentWord.TabWord[i] = '\0';
        currentWord.Length = i;
    } else {
        //from file
        while ((currentChar != '\n') && (retval!=EOF)) {
            if (currentChar != '\r') {
                currentWord.TabWord[i] = currentChar;
                i++;
            }
            ADV();
        }
        if (EOF == true) {
            i++;
        }
        currentWord.TabWord[i] = '\0';
        currentWord.Length = i;
    }
}

void DisplayCurrentWord() {
    for (int i = 0; i < currentWord.Length; i++) {
        printf("%c", currentWord.TabWord[i]);
    }
}

int StartWordFromFile(char *filePath){
    int isSuccess = StartFromFile(filePath);
    if (isSuccess){
        if (currentChar == '\n'){
            EndWord = true;
        } else {
            EndWord = false;
            CopyWord();
        }
        return 1;
    }
    return 0;
}

void ADVNewLine() {
    if (currentChar == '\n') {
        reset();
        IgnoreBlanks(); //addition
        isInputFile = true;
        EndWord = false;     
        // ADV();

        if (retval == EOF) {
            EndWord = true; 
        } else {
            CopyWord();
        }
    }
}