#include "../modules/boolean.h"
#include "../modules/mesinkarakter.h"
#include <stdio.h>

static FILE *pita;
int retval;
char currentChar;
boolean EOP;
boolean isInputFile;
boolean EndWord;

void START() {
    if (pita == NULL) {
        pita = stdin;
    }
    ADV();
}

void ADV() {
    retval = fscanf(pita, "%c", &currentChar);
    if (!isInputFile){
        //default
        EOP = (currentChar == MARK);
        if (EOP) {
            pita = NULL;
        }
    } else {
        if (retval == EOF){
            pita = NULL;
            fclose(pita);
        }
    }
}

int StartFromFile(char *filePath){
    isInputFile = true;
    pita = fopen(filePath, "r");
    if (pita == NULL){
        printf("Gagal memuat file.\n");
        return 0;
    }
    ADV();
    return 1;
}