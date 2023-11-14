#include<stdio.h>
#include<string.h>

int main(){
    FILE *fd; //Puntero de la variable de tipo Archivo.
    char *cadena = "Hola desde c"; //Cadena de caracteres a escribir.

    char *filename = "archivo.txt"; //Nombre del archivo a crear.
    fd = fopen(filename, "w+"); //Abrimos el archivo en modo escritura.

    if (fd == NULL){ //Si el archivo no se pudo abrir.
        printf("Error al crear el archivo.\n", filename); //Imprimimos un mensaje de error.
        return 1; //Terminamos la ejecución del programa.
    }
    printf("El archivo %s se ha creado correctamente.\n", filename); //Imprimimos un mensaje de éxito.



    int l = strlen(cadena); //Obtenemos la longitud de la cadena.
    int i; //Declaramos una variable para iterar.

    for (i = 0; i < l; i++){ //Iteramos sobre la cadena.
        fputc(cadena[i], fd); //Escribimos el caracter en el archivo.
    }

    fputc('\n', fd); //Escribimos un salto de línea en el archivo.

    printf("Se ha escrito correctamente en el archivo.\n"); //Imprimimos un mensaje de éxito.
    fclose(fd); //Cerramos el archivo.
    return 0; //Terminamos la ejecución del programa.
}