#include "avl.h"
#include <stdio.h>
#include <stdlib.h>


void mettreAjourHauteur(Noeud * ptn) {

    int hg, hd;

    hg = (ptn -> fg == NULL)? -1 : ptn -> fg -> h;
    hd = (ptn -> fd == NULL)? -1 : ptn -> fd -> h;

    ptn -> h = (hg>hd)? 1 + hg : 1 + hd;
}
