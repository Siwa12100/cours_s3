#include "abr.h"
#include <stdio.h>
#include <stdlib.h>

ArbreBin creerArbreVide(void) {
    return NULL;
}

Booleen estArbreVide(ArbreBin b) {
    if (b == NULL) return 1; 
    return 0; 
}