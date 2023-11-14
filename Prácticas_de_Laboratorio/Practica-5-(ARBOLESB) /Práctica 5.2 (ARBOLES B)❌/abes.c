//
// Created by Bezaleel on 27/09/23.
//
#include "ab.h"
#include <stdio.h>
#include <arches.h>

int daab; //daab es el descriptor del archivo que contiene el árbol.

abreab(){ //Esta función abre el archivo que contiene el árbol.
    daab = open ("arbolb.dat", READWRITE);
    return (daab > 0);
}

cierraab(){ //Esta función cierra el archivo que contiene el árbol.
    close (daab);
}

short tomaraiz (){ //Esta función toma la raíz del árbol.
    short raiz;
    long lseek ();
    lseek (daab, 0L, 0);
    if (read (daab,&raiz, 2)==0){ //Si el archivo está vacío, se imprime un mensaje de error.
        printf ("Error: archivo vacio\n\007");
        exit (1);
    }
    return (raiz);
}

colocaraiz (raiz) //Esta función coloca la raíz del árbol.
short raiz;
{
    long lseek ();
    lseek (daab, 0L, 0);
    write (daab, &raiz, 2);
}

short crea_arbol(){ //Esta función crea el árbol.
    char llave;
    daab = creat ("arbolb.dat", PMODE);
    close(daab);
    abreab();
    llave = getchar();
    return (crea_raiz(llave, NULO, NULO));
}

short tomapag() //Esta función toma una página del árbol.
{
    long lseek(), dir;
    dir = lseek(daab, 0L, 2) -2L;
    return ((short) dir/ TAMPAGINA);
}

leeab(nrr, apunt_pagina) //Esta función lee una página del árbol.
short nrr;
PAGINAAB *apunt_pagina;
{
    long lseek(), dir;
    dir = (long)nrr * (long)TAMPAGINA + 2L;
    lseek(daab, dir, 0);
    return (read(daab, apunt_pagina, TAMPAGINA));
}

escribreab (nrr, apunt_pagina) //Esta función escribe una página del árbol.
short nrr;
PAGINAAB *apunt_pagina;
{
    long lseek(), dir;
    dir = (long)nrr * (long)TAMPAGINA + 2L;
    lseek(daab, dir, 0);
    return (write(daab, apunt_pagina, TAMPAGINA));
}