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

void mostrarArticulo (void* dato); //Prototipo de la funcion mostrarArticulo
void mostrarArchivo (const char* nombre); //Prototipo de la funcion mostrarArchivo
int generarArchivo(const char* nombre); //Prototipo de la funcion generarArchivo

void actualizarPrecios (const char* nombre, int cantRegistros){ //Funcion actualizarArchivo
    FILE *arch = fopen(nombre, "r+b" ); //Declaracion de un archivo binario en modo lectura y escritura
    if(arch == NULL){ //Si el archivo no se abre correctamente
        printf("Error al abrir el archivo. %s \n", nombre); //Se imprime un mensaje de error en pantalla
        return; //Se retorna
    }

    Articulo aux; //Declaracion de una variable auxiliar de tipo Articulo
    int tam = sizeof(Articulo); //Declaracion de una variable de tipo unsigned
    for (int i = 0; i < cantRegistros; i++){ //Ciclo for para recorrer el archivo
        fflush(arch); //Se limpia el buffer del archivo
        fread(&aux, tam, 1, arch); //Se lee el articulo del archivo
        aux.precio *= 1.10; //Se actualiza el precio del articulo
        fseek(arch, -tam, SEEK_CUR); //Se posiciona el puntero en el articulo leido
        fwrite(&aux, tam, 1, arch); //Se escribe el articulo en el archivo
    }
    fclose(arch); //Se cierra el archivo
}


int main() //Funcion principal
{
    int cantRegistros; //Declaracion de una variable de tipo entero
    cantRegistros = generarArchivo("Articulos2.dat"); //Se llama a la funcion generarArchivo
    mostrarArchivo("Articulos2.dat"); //Se llama a la funcion mostrarArchivo
    actualizarPrecios("Articulos2.dat", cantRegistros); //Se llama a la funcion actualizarArchivo
    printf("Articulos con precios actualizados: \n");   //Se imprime un mensaje en pantalla
    mostrarArchivo("Articulos2.dat"); //Se llama a la funcion mostrarArchivo
    return 0; //Se retorna 0
}

int generarArchivo(const char* nombre){

    Articulo articulos [10]= { //Declaracion de un arreglo de tipo Articulo
        {1,  10.0,  "Pelota de futbol"}, //Inicializacion de los articulos
        {2,  20.0,  "Raqueta de tenis"}, //Inicializacion de los articulos
        {3,  30.0,  "Pelota de baloncesto"}, //Inicializacion de los articulos
        {4,  40.0,  "Bicicleta"}, //Inicializacion de los articulos
        {5,  50.0,  "Guantes de boxeo"}, //Inicializacion de los articulos
        {6,  60.0,  "Gafas de natacion"}, //Inicializacion de los articulos
        {7,  70.0,  "Zapatillas de correr"}, //Inicializacion de los articulos
        {8,  80.0,  "Casco para ciclismo"}, //Inicializacion de los articulos
        {9,  90.0,  "Pelota de voleibol"}, //Inicializacion de los articulos
        {10, 100.0, "Equipo de golf"}, //Inicializacion de los articulos
    };

    int ce = sizeof(articulos) / sizeof(articulos[0]); //Declaracion de una variable de tipo entero
    printf("ce: %d\n", ce); //Se imprime la cantidad de elementos del arreglo en pantalla

    FILE* pf = fopen(nombre, "wb"); //Declaracion de un archivo binario en modo escritura
    if (!pf) //Si el archivo no se abre correctamente
    {
        printf("Fallo al escribir. %s \n", nombre); //Se imprime un mensaje de error en pantalla
        return 0; //Se retorna 0
    }
    fwrite(articulos, sizeof(Articulo), ce, pf); //Se escribe el arreglo en el archivo binario
    fclose(pf); //Se cierra el archivo
    return ce; //Se retorna la cantidad de elementos del arreglo
};

void mostrarArchivo (const char* nombre){ //Funcion mostrarArchivo
    FILE* pf = fopen(nombre, "rb"); //Declaracion de un archivo binario en modo lectura
    if (!pf) //Si el archivo no se abre correctamente
    {
        printf("Fallo al escribir el archivo. %s \n", nombre); //Se imprime un mensaje de error en pantalla
        return; //Se retorna
    }
    Articulo aux; //Declaracion de una variable auxiliar de tipo Articulo
    printf("Cod\t Precio Descripcion "); //Se imprime un mensaje en pantalla
    while (fread(&aux, sizeof(Articulo),1,pf)) //Ciclo while para recorrer el archivo
        mostrarArticulo(&aux); //Se llama a la funcion mostrarArticulo
    fclose(pf); //Se cierra el archivo
}

void mostrarArticulo (void* dato){ //Funcion mostrarArticulo
    Articulo* aux = (Articulo*) dato; //Declaracion de una variable auxiliar de tipo Articulo
    printf("%d\t %.2f %-20s \n", aux->codART, aux->precio, aux->descrip); //Se imprime el articulo en pantalla
}

