//
// Created by Bezaleel on 27/09/23.
//
#include <stdio.h>
#include <ab.h>

main (){ // main function
    int promovido;

    short raiz,
          nrr_plomo;

    char llave_plomo
         llave;

    if (abreab())
        raiz = tomaraiz ();
    else
        raiz = crea-arbol ();

    while ((llave = getchar ()) ! = 'q') {
        promovido = inserta (raiz, llave, &nrr_plomo, &llave_plomo);
    }
    cierraab ();
}


