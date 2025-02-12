#include "../modules/boolean.h"
#include "../modules/mesinkarakter.h"
#include <stdio.h>

static FILE *pita;
int retval;
char currentChar;
boolean EOP;
extern boolean isInputFile;

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
        // file
        if (retval == EOF){
            fclose(pita);
            pita = NULL;
        }
    }
}

int StartFromFile(char *filePath){
    isInputFile = true;
    pita = fopen(filePath, "r");
    if (pita == NULL){
        return 0;
    }
    ADV();
    return 1;
}