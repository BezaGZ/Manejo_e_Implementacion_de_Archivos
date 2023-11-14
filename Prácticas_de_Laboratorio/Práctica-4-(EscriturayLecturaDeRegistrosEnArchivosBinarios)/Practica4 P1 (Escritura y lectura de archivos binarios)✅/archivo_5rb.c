//
// Created by Bezaleel on 1/09/23.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct //Estructura de tipo Articulo
{
    int codART; //Codigo del articulo
    float precio; //Precio del articulo
    char descrip [50]; //Descripcion del articulo
} Articulo; //Tipo de dato Articulo

int main ()
{
    Articulo articulos [10]= {
            {1,  10.0,  "Pelota de futbol"},
            {2,  20.0,  "Raqueta de tenis"},
            {3,  30.0,  "Pelota de baloncesto"},
            {4,  40.0,  "Bicicleta"},
            {5,  50.0,  "Guantes de boxeo"},
            {6,  60.0,  "Gafas de natacion"},
            {7,  70.0,  "Zapatillas de correr"},
            {8,  80.0,  "Casco para ciclismo"},
            {9,  90.0,  "Pelota de voleibol"},
            {10, 100.0, "Equipo de golf"},
    };

    FILE * pf = fopen ("Articulos.dat", "rb"); //Declaracion de un archivo binario
    if (pf == NULL) //Si el archivo no se abre correctamente
        printf ("Error al abrir el archivo. \n"); //Se imprime un mensaje de error en pantalla

    Articulo aux; //Declaracion de una variable auxiliar de tipo Articulo
    fseek(pf, 01, SEEK_END);//Se posiciona el puntero en el segundo articulo del archivo binario
    int cant_registros = ftell(pf) / sizeof(Articulo); //Se calcula la cantidad de registros del archivo binario
    rewind(pf); //Se posiciona el puntero al inicio del archivo binario
    fread(&aux, sizeof(Articulo), 1, pf); //Se lee el segundo articulo del archivo binario
    printf("------CANTIDAD DE REGISTROS EN EL FICHERO ------\n"); //Se imprime un mensaje en pantalla
    printf("------ %d ------\n", cant_registros); //Se imprime la cantidad de registros en pantalla
    printf("------EL ARTICULO SOLICITADO ES ------\n"); //Se imprime un mensaje en pantalla
    printf("CODIGO_ARTICULO : %d\n", aux.codART); //Se imprime el codigo del articulo en pantalla
    printf("PRECIO_ARTICULO : %.2f\n", aux.precio); //Se imprime el precio del articulo en pantalla
    printf("DESCRIPCION_ARTICULO : %-20s \n \n", aux.descrip); //Se imprime la descripcion del articulo en pantalla
    return 0;
};

