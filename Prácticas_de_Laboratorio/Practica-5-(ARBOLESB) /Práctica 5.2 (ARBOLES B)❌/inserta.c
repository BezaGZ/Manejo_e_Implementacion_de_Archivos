//
// Created by Bezaleel on 27/09/23.
//
#include <ab.h>

inserta (nrr, llave, hijo_d_plomo, llave_plomo) //Esta función inserta una llave en el árbol.
short nrr
     *hijo_d_plomo
char llave
     *llave_plomo;

{
        PAGINAAB pagina,
        pagnueva; //pagnueva es la página que se crea al dividir una página llena.

        int encontro //Encontro es una bandera que indica si se encontró la llave en la página.
        shor poss,
            nrr_p_a;
        char llave_p_a;

        if (nrr == NULO) { //Si el árbol está vacío, se crea la raíz.
            *llave_plomo = llave;
            *hijo_d_plomo = NULO;
            return (SI);
        }

        leeab (nrr, &pagina); //Se lee la página.
        encontro = busca_nodo (llave, &pagina, &poss);
        if (encontro){ //Si se encontró la llave en la página, se imprime un mensaje de error.
            printf ("Error: intento de insercion de llave duplicada: %c\n\007", llave);
            return (0);
        }

        promocion = inserta (pagina.hijo[pos], llave, &nrr_p_a, &llave_p_a); //Se inserta la llave en la página.
        if (!promocion) //Si no hay promoción, se regresa un cero.
            return (NO);
        if (pagina.contllave < MAXLLAVES) { //Si la página no está llena, se inserta la llave.
            ins_en_pag (llave_p_a, nrr_p_a, &pagina);
            escribeab(nrr, &pagina);
            return (NO);
        } else { //Si la página está llena, se divide la página.
            divide(llave_p_a, nrr_p_a, &pagina, nrr_plomo, llave_plomo, &pagnueva);
            escribeab(nrr, &pagina);
            escribeab(*hijo_d_plomo, &pagnueva);
            return (SI);
        }
}