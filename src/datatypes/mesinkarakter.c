#include "../modules/boolean.h"
#include "../modules/mesinkarakter.h"
#include <stdio.h>

static FILE *pita;
static int retval;
char currentChar;
boolean EOP;

void START() {
    if (pita == NULL) {
        pita = stdin;
    }
    ADV();
}

void ADV() {
    retval = fscanf(pita, "%c", &currentChar);
    EOP = (currentChar == MARK);
    if (EOP) {
        pita = NULL;
    }
}