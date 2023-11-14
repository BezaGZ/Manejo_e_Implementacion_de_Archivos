//
// Created by Bezaleel on 27/09/23.
//

#ifndef PRÁCTICA_5_2_AB_H
#define PRÁCTICA_5_2_AB_H
#endif //PRÁCTICA_5_2_AB_H

#define MAXLLAVES 4
#define MINLLAVES MAXLLAVES/2
#define NULO (-1)
#define SINLLAVE '@'

typedef struct { //Esta estructura define una página del árbol.
    short contllave:
    char llave [MAXLLAVES];
    short hijo [MAXLLAVES+1];

} PAGINAAB;

#define TAMPAGINA sizeof (PAGINAAB)


