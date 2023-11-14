#include <stdio.h>

#define FILAS 6
#define COLUMNAS 7

// Función para imprimir el tablero
void imprimirTablero(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) { // Recorrer las filas
        for (int j = 0; j < COLUMNAS; j++) { // Recorrer las columnas
            printf("%c ", tablero[i][j]); // Imprimir el valor de la celda
        }
        printf("\n"); // Imprimir un salto de línea al final de cada fila
    }
    printf("\n"); // Imprimir un salto de línea al final del tablero
}

// Función para verificar si hay un ganador
int verificarGanador(char tablero[FILAS][COLUMNAS], char jugador) { // jugador = 'X' o 'O'
    // Verificar filas 
    for (int i = 0; i < FILAS; i++) { // Recorrer las filas
        for (int j = 0; j < COLUMNAS - 3; j++) { // Recorrer las columnas
            if (tablero[i][j] == jugador && tablero[i][j+1] == jugador && // Verificar si hay 4 fichas iguales
                tablero[i][j+2] == jugador && tablero[i][j+3] == jugador) { // en una misma fila
                return 1; // Retornar 1 si hay un ganador
            }
        }
    }

    // Verificar columnas
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == jugador && tablero[i+1][j] == jugador &&
                tablero[i+2][j] == jugador && tablero[i+3][j] == jugador) {
                return 1;
            }
        }
    }

    // Verificar diagonales hacia abajo
    for (int i = 0; i < FILAS - 3; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] == jugador && tablero[i+1][j+1] == jugador &&
                tablero[i+2][j+2] == jugador && tablero[i+3][j+3] == jugador) {
                return 1;
            }
        }
    }

    // Verificar diagonales hacia arriba
    for (int i = 3; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS - 3; j++) {
            if (tablero[i][j] == jugador && tablero[i-1][j+1] == jugador &&
                tablero[i-2][j+2] == jugador && tablero[i-3][j+3] == jugador) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    char tablero[FILAS][COLUMNAS];  // Tablero de juego
    char jugador = 'X';  // Jugador actual
    int columna;  // Columna elegida por el jugador
    // Abrir el archivo de texto que contiene el mapa

    FILE *archivo = fopen("mapa.txt", "r"); // "r" = read (lectura)
    if (archivo == NULL) { // Verificar si el archivo se abrió correctamente
        printf("Error al abrir el archivo.\n"); // Imprimir un mensaje de error
        return 1; // Terminar el programa con un código de error
    }

    // Leer el mapa del archivo y cargarlo en el tablero
    for (int i = 0; i < FILAS; i++) { // Recorrer las filas
        for (int j = 0; j < COLUMNAS; j++) { // Recorrer las columnas
            fscanf(archivo, " %c", &tablero[i][j]); // Leer el valor de la celda
        } 
    }

    // Cerrar el archivo
    fclose(archivo);

    // Juego principal
    while (1) { 
        // Imprimir el tablero
        imprimirTablero(tablero); // Llamar a la función imprimirTablero

        // Solicitar al jugador que elija una columna
        printf("Turno del jugador %c. Elija una columna (0-%d): ", jugador, COLUMNAS - 1); // Imprimir un mensaje
        scanf("%d", &columna); // Leer la columna elegida por el jugador

        // Verificar si la columna elegida es válida
        if (columna < 0 || columna >= COLUMNAS) { // Si la columna es inválida
            printf("Columna inválida. Por favor, elija otra.\n"); // Imprimir un mensaje de error
            continue; // Volver a solicitar al jugador que elija una columna
        }

        // Buscar la fila disponible en la columna elegida (Si la fila está llena, buscar la siguiente fila disponible)
        int fila = FILAS - 1; // Comenzar desde la última fila
        while (fila >= 0 && tablero[fila][columna] != '-') { // Mientras la fila no esté disponible
            fila--; // Ir a la fila anterior
        }

        // Verificar si la columna está llena
        if (fila < 0) { // Si la fila es inválida
            printf("La columna está llena. Por favor, elija otra.\n"); // Imprimir un mensaje de error
            continue; // Volver a solicitar al jugador que elija una columna
        }

        // Colocar la ficha en el tablero
        tablero[fila][columna] = jugador; // Colocar la ficha del jugador en la fila y columna elegidas

        // Verificar si hay un ganador
        if (verificarGanador(tablero, jugador)) { // Si hay un ganador
            printf("¡El jugador %c ha ganado!\n", jugador); // Imprimir un mensaje de victoria
            break; // Terminar el juego
        }

        // Cambiar al siguiente jugador
        jugador = (jugador == 'X') ? 'O' : 'X';
    }

    // Imprimir el tablero final
    imprimirTablero(tablero); // Llamar a la función imprimirTablero

    // Abrir el archivo en modo escritura
    archivo = fopen("mapa.txt", "w"); // "w" = write (escritura)
    if (archivo == NULL) { // Verificar si el archivo se abrió correctamente
        printf("Error al abrir el archivo.\n"); // Imprimir un mensaje de error
        return 1; // Terminar el programa con un código de error
    }

    // Guardar el tablero actualizado en el archivo
    for (int i = 0; i < FILAS; i++) { // Recorrer las filas
        for (int j = 0; j < COLUMNAS; j++) { // Recorrer las columnas
            fprintf(archivo, "%c ", tablero[i][j]); // Escribir el valor de la celda en el archivo
        }
        fprintf(archivo, "\n"); // Escribir un salto de línea al final de cada fila
    }

    // Cerrar el archivo
    fclose(archivo);

    return 0; // Terminar el programa con un código de éxito
}