#include<stdio.h>

int main(){
    FILE *fd; //Puntero de la variable de tipo Archivo.
    char *cadena = "Hola desde c"; //Cadena de caracteres a escribir.

    char *filename = "archivo.dat"; //Nombre del archivo a crear.
    fd = fopen(filename, "w+"); //Abrimos el archivo en modo escritura.

    if (fd == NULL){ //Si el archivo no se pudo abrir.
        printf("Error al crear el archivo.\n", filename); //Imprimimos un mensaje de error.
        return 1; //Terminamos la ejecución del programa.
    }
    printf("El archivo %s se ha creado correctamente.\n", filename); //Imprimimos un mensaje de éxito.

    int tamInt = sizeof(int); //Obtenemos el tamaño de un entero.
    int i; //Declaramos una variable para iterar.

    for (i=0; i<50; i++){ //Iteramos 10 veces.
        fwrite(&i, tamInt, 1, fd); //Escribimos el entero en el archivo.
    }

    printf ("Se ha escrito correctamente en el archivo.\n"); //Imprimimos un mensaje de éxito.
    fclose(fd); //Cerramos el archivo.
    return 0; //Terminamos la ejecución del programa.
}