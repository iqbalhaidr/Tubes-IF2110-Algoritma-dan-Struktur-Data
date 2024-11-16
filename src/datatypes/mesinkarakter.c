#include "boolean.h"
#include "mesinkarakter.h"
#include <stdio.h>

static FILE *pita;
static int retval;
char currentChar;
boolean EOP;

void START() {
    pita = stdin;
    ADV();
}

void ADV() {
    retval = fscanf(pita, "%c", &currentChar);
    EOP = (currentChar == MARK);
    if (EOP) {
        fclose(pita);
    }
}