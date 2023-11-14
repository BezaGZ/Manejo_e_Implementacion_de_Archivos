#include<stdio.h>

int main(){
    FILE *fd; //Puntero de la variable de tipo Archivo.
    char *filename = "archivo.dat"; //Nombre del archivo a abrir.
    fd = fopen(filename, "r"); //Abrimos el archivo en modo lectura.

    if (fd==NULL){ //Si el archivo no se pudo abrir.
        printf("Error al abrir el archivo %s.\n", filename); //Imprimimos un mensaje de error.
        return 1; //Terminamos la ejecución del programa.
    }

    printf("El archivo %s se ha abierto correctamente.\n", filename); //Imprimimos un mensaje de éxito.

    int tamInt = sizeof(int); //Obtenemos el tamaño de un entero.
    int i; //Declaramos una variable para iterar.
    int r = fread(&i, tamInt, 1, fd); //Leemos el archivo.

    while (r!=0){ //Mientras no se llegue al final del archivo.
        printf("Se ha leido el entero %d.\n", i); //Imprimimos el entero leído.
        r = fread(&i, tamInt, 1, fd); //Leemos el archivo.
    }
    fclose(fd); //Cerramos el archivo.
    return 0; //Terminamos la ejecución del programa.
}