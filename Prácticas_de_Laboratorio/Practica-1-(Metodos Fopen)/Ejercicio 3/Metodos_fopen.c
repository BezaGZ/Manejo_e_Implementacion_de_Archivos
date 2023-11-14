#include<stdio.h>
#include<string.h>
#include <stdbool.h>

  //Funciones:
void simple_write(char *cadena, char *filename)
   {
        FILE *fd; //Puntero de la variable de tipo Archivo.
        fd = fopen(filename, "w+"); //Abrimos el archivo en modo escritura.

        if (fd == NULL){ //Si el archivo no se pudo abrir.
            printf("Error al crear el archivo. %s \n", filename); //Imprimimos un mensaje de error.
            return; //Terminamos la ejecución del programa.
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
    }
void simple_read()
{
    FILE *fd; // Puntero de la variable de tipo Archivo.
    char c; // Variable para almacenar el caracter leído.
    char *filename = "archivo.txt"; // Nombre del archivo a leer.
    
    fd = fopen(filename, "r"); // Abrimos el archivo en modo lectura.
    
    if (fd == NULL) { // Si el archivo no se pudo abrir.
        printf("Error al abrir el archivo %s.\n", filename); // Imprimimos un mensaje de error.
        return; // Terminamos la ejecución de la función.
    }
    
    c = fgetc(fd); // Leemos el primer caracter del archivo.
    while (c != EOF) { // Mientras no sea el final del archivo.
        printf("%c", c); // Imprimimos el caracter leído.
        c = fgetc(fd); // Leemos el siguiente caracter del archivo.
    }
    
    fclose(fd); // Cerramos el archivo.
}
void bin_write()
{
    FILE *fd; // Puntero de la variable de tipo Archivo.
    char *cadena = "Hola desde c"; // Cadena de caracteres a escribir.
    char *filename = "archivo.dat"; // Nombre del archivo a crear.
    fd = fopen(filename, "w+"); // Abrimos el archivo en modo escritura.
    if (fd == NULL) { // Si el archivo no se pudo abrir.
        printf("Error al crear el archivo.\n"); // Imprimimos un mensaje de error.
        return; // Terminamos la ejecución de la función.
    }
    printf("El archivo %s se ha creado correctamente.\n", filename); // Imprimimos un mensaje de éxito.
    int tamInt = sizeof(int); // Obtenemos el tamaño de un entero.
    int i; // Declaramos una variable para iterar.
    for (i = 0; i < 50; i++) { // Iteramos 50 veces.
        fwrite(&i, tamInt, 1, fd); // Escribimos el entero en el archivo.
    }
    printf("Se ha escrito correctamente en el archivo.\n"); // Imprimimos un mensaje de éxito.
    fclose(fd); // Cerramos el archivo.
}
void bin_read()
{
    FILE *fd; // Puntero de la variable de tipo Archivo.
    char *filename = "archivo.dat"; // Nombre del archivo a abrir.
    fd = fopen(filename, "r"); // Abrimos el archivo en modo lectura.
    if (fd == NULL) { // Si el archivo no se pudo abrir.
        printf("Error al abrir el archivo %s.\n", filename); // Imprimimos un mensaje de error.
        return; // Terminamos la ejecución de la función.
    }
    printf("El archivo %s se ha abierto correctamente.\n", filename); // Imprimimos un mensaje de éxito.
    int tamInt = sizeof(int); // Obtenemos el tamaño de un entero.
    int i; // Declaramos una variable para iterar.
    int r = fread(&i, tamInt, 1, fd); // Leemos el archivo.
    while (r != 0) { // Mientras no se llegue al final del archivo.
        printf("Se ha leido el entero %d.\n", i); // Imprimimos el entero leído.
        r = fread(&i, tamInt, 1, fd); // Leemos el archivo.
    }
    fclose(fd); // Cerramos el archivo.
}
void create_file(char nombre[100])
{
    FILE *archivo= fopen(nombre, "w");
    if (archivo == NULL)
    {
        printf("Ocurrio un error, no fue creado.\n");
    }else
        printf("El archivo fue creado.\n");
    fclose(archivo);
}
void write_file()
{
    char nombre[] = "texto.txt";
    FILE *archivo = fopen(nombre, "a");
    if (archivo == NULL)
    {
        printf("Ocurrió un error, el archivo no existe.\n");
    }
    else
    {
        char texto[200];
        printf("Ingrese la información: \n");
        fflush(stdin);
        fgets(texto, 199, stdin);
        fprintf(archivo, " %s", texto);
        printf("La información fue guardada.\n");
    }
    fclose(archivo);
}

int main(){

  
    //While Menu
    int opcion;
    char cadena[] = "Hola desde C", nombre[100];
    char filename[] = "archivo.txt";
    bool salir = false;

    while (!salir) {
            printf("--------------- Menu: ---------------\n");
            printf("1. Funcion Escribir W+\n");
            printf("2. Funcion Leer W+\n");
            printf("3. Funcion Escribir R\n");
            printf("4. Funcion Leer R\n");
            printf("5. Funcion Crear W\n");
            printf("6. Funcion Escribir A\n");
            printf("7. SALIR\n");
            printf("-------------------------------------\n");
            printf("Elige una opción: ");
            scanf("%d", &opcion);

        switch (opcion){
        case 1:
            simple_write(cadena, filename);
            break;
        case 2:
            simple_read();
            break;
        case 3:
            bin_write();
            break;
        case 4:
            bin_read();
            break;
        case 5:
            printf("Ingrese el nombre del archivo que desee crear (o escriba 'salir' para terminar):\n");
            scanf(" %[^\n]", nombre);

            if (strcmp(nombre, "salir\n") == 0) {
            salir = true;
                 } else {
                create_file(nombre);
             }
            break;

        case 6:
            write_file();
            break;
        case 7: 
            salir = true;
            break;
            
        default:
            printf("Opción inválida\n");
            break;
        }

    }

}