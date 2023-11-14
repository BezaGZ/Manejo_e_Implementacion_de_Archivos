//
// Created by Bezaleel on 27/09/23.
//
#include "ab.h"

crea-raiz(llave, izq, der)
char llave;
short izq, der;
{ //Esta funcion crea la raíz del árbol.
    PAGINAAB pagina;
    short nrr;
    inciapag(&pagina);
    pagina.llave[0] = llave;
    pagina.hijo[0] = izq;
    pagina.hijo[1] = der;
    pagina.contllave = 1;
    escribeab(nrr, &pagina);
    colocaraiz(nrr);
    return (nrr);
}

iniciapag(a_pagina) //Esta función inicializa una página del árbol.
PAGINAAB *a_pagina;
{ //Esta función inicializa una página del árbol.
    int j;
    for (j=0; j<MAXLLAVES; j++) {
        a_pagina->llave[j] = SINLLAVE;
        a_pagina->hijo[j] = NULO;
    }
    a_pagina -> hijo[MAXLLAVES] = NULO;
}

busca_nodo (llave, a_pagina, pos) //Esta función busca una llave en una página del árbol.
char llave;
PAGINAAB *a_pagina;
short *pos; //pos es un apuntador a la posición de la llave en la página.
{
    int i;
    for (i=0; i<a_pagina->contllave && llave > a_pagina -> llave[i]; i++);
    *pos = i;
    if (*pos < a_pagina->contllave && llave == a_pagina->llave[*pos])
        return (SI);
    else
        return (NO);

}

ins_en_pag(llave, hijo_d, a_pagina) //Esta función inserta una llave en una página del árbol.
char llave;
short hijo_d;
PAGINAAB *a_pagina;
{ //Esta función inserta una llave en una página del árbol.
    int I;
    for(i=a_pagina -> contllave; llave < a_pagina -> llave[i-1] && i>0; i--) {
        a_pagina -> llave[i] = a_pagina -> llave[1 - 1];
        a_pagina -> hijo[i+1] = a_pagina -> hijo[i];
    }
    a_pagina -> contllave++;
    a_pagina -> llave[i] = llave;
    a_pagina -> hijo[i+1] = hijo_d;
}

divide (llave, hijo_d, a_pagant, llave_promo, hijo_d_promo, a_panue) //Esta función divide una página del árbol.
char llave, *llave_promo;
short hijo_d, *hijo_d_promo;

PAGINAAB *a_pagant, *a_pagnue;
{//Esta función divide una página del árbol.
    int i;
    short mitad;
    char llavesaux[MAXLLAVES+1];
    short caraux[MAXLLAVES+2];

    for (i=0; i<MAXLLAVES; i++) { //Se copian las llaves y los hijos de la página en un arreglo auxiliar.
        llavesaux[i] = a_pagant -> llave[i];
        caraux[i] = a_pagant -> hijo[i];
    }
    llavesaux[i] = a_pagant -> llave[i];
    for (i=MAXLLAVES; llave < llavesaux[i-1] && i>0; i--) { //Se inserta la llave en el arreglo auxiliar.
        llavesaux[i] = llavesaux[i-1];
        caraux[i+1] = caraux[i];
    }
    llavesaux[i] = llave;
    caraux[i+1] = hijo_d;

    *hijo_d_promo = tomapag();
    iniciapag(a_panue); //Se inicializa la página nueva.

    for(i=0; i<MINLLAVES; i++) { //Se copian las llaves y los hijos del arreglo auxiliar en la página antigua y en la página nueva.
        a_pagant -> llave[i] = llavesaux[i];
        a_pagant -> hijo[i] = caraux[i];
        a_pagnue -> llave[i] = llavesaux[i+1+MINLLAVES];
        a_pagnue -> hijo[i] = caraux[i+1+MINLLAVES];
        a_pagant->llave[i+MINLLAVES]=SINLLAVE;
        a_pagant->hijo[i+1+MINLLAVES]=NULO;
    }

    a_pagant -> hijo[MINLLAVES] = caraux[MINLLAVES];
    a_pagant -> hijo[MINLLAVES] = caraux[i+1+MINLLAVES];
    a_pagnue -> contllave = MAXLLAVES-MINLLAVES;
    a_pagant -> contllave = MINLLAVES;

    *llave_promo = llavesaux[MINLLAVES];
}