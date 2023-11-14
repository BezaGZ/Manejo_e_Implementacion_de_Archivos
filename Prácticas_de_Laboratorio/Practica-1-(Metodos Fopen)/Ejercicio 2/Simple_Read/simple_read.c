#include<stdio.h>

int main (){
        FILE *fd; //Puntero de la variable de tipo Archivo.
        char c; //Variable para almacenar el caracter leído.

        char *filename = "archivo.txt"; //Nombre del archivo a leer.
        fd = fopen(filename, "r"); //Abrimos el archivo en modo lectura.

        if (fd == NULL){ //Si el archivo no se pudo abrir.
                printf("Error al abrir el archivo %s.\n", filename); //Imprimimos un mensaje de error.
                return 1; //Terminamos la ejecución del programa.
        }

        c = fgetc(fd); //Leemos el primer caracter del archivo.
        while (c != EOF){ //Mientras no sea el final del archivo.
                printf("%c", c); //Imprimimos el caracter leído.
                c = fgetc(fd); //Leemos el siguiente caracter del archivo.
        }

        fclose(fd); //Cerramos el archivo.
        return 0; //Terminamos la ejecución del programa.
}

