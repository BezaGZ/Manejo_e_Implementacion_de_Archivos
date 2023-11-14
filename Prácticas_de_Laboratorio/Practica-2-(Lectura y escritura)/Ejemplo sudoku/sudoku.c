#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void reglas(){
    printf("------------- SUDOKU --------------\n");
    printf("Reglas del juego:\n");
    printf("1. Para jugar, escoja el numero de sudoku de 1 a 9\n");
    printf("2. Para ganar debe cumplir las reglas que se especefican a continuacion\n");
    printf("3. Debe escoger numeros de 1 a 9\n");
    printf("4. No puede repetir numeros en la misma fila, columna ni cuadrilla\n");
    printf("5. No debe escoger posiciones fuera del mapa\n");
    printf("6. No debe sobreescribir numeros que son parte del mapa original\n");
    printf("7. Puede cambiar de valor los numeros que no sean parte del mapa original");
    printf("8. Los valores marcados en ceros son posiciones que puede editar, son parte del mapa vació\n");
    printf("9. En caso de que haya ganado se le notificará, sino no se le notificará nada\n");
    printf("10 En caso de necesitarlo se le facilitará la solución del mapa, puede verlo presionando la tecla 'v'\n");
    printf("11. Diviertasa\n");
    printf("------------------------------------\n");
}

int elegir_sudoku(){
    int eleccion = -1;
    int continuar = 1;
    while (continuar == 1)
    {
        printf("------------------------------------\n");
        printf("Escoja un mapa\n");
        scanf("%d", &eleccion);
        if (eleccion > 0 && eleccion < 10)
        {
            return eleccion;
        }
        else
        {
            printf("Eleccion invalida\n");
        }   
    } 
}

//Función para abrir el archivo que contiene el mapa.
char *cargar_eleccion(int valor){
    char *nombre_archivo = malloc(sizeof(char) * 21);
    switch (valor)
    {
    case 1:strcpy(nombre_archivo, "sudoku1_tablilla.txt");break;
    case 2:strcpy(nombre_archivo, "sudoku2_tablilla.txt");break;
    case 3:strcpy(nombre_archivo, "sudoku3_tablilla.txt");break;
    case 4:strcpy(nombre_archivo, "sudoku4_tablilla.txt");break;
    case 5:strcpy(nombre_archivo, "sudoku5_tablilla.txt");break;
    case 6:strcpy(nombre_archivo, "sudoku6_tablilla.txt");break;
    case 7:strcpy(nombre_archivo, "sudoku7_tablilla.txt");break;
    case 8:strcpy(nombre_archivo, "sudoku8_tablilla.txt");break;
    case 9:strcpy(nombre_archivo, "sudoku9_tablilla.txt");break;
    }
    return nombre_archivo;
}
void mostrar_mapa(int mapa[9][9]){
    int fila =0, columna = 0;
    printf("\n\n     ");
    while (fila < 9)
    {
        while (columna < 9)
        {
            printf("%d ", mapa[fila][columna]);
            columna++;
        }
        columna = 0;
        fila++;
        printf("\n     ");
    }
}

//Método para cargar archivo sobre una martriz
void cargar_sobre_matriz(char *nombre_archivo, int mapa[9][9]){
    FILE *archivo = fopen(nombre_archivo, "r");
    char letra = ' ';
    int contador_fila = 0;
    int contador_columna = 0;
    if(archivo == NULL){
        printf("archivo no encontrado\n");
    }else{
        while (letra != EOF)
        {
            letra = getc(archivo);
            if(letra != ' ' && letra != -1 && letra != 9 && letra != 10){
                mapa[contador_fila][contador_columna] = letra - 48;
                contador_columna++;
                if(contador_columna % 9 == 0){
                    contador_columna = 0;
                    contador_fila++;
                }
            }
        }
    }
    mostrar_mapa(mapa);
}

int escoger_numero(int mapa[9][9]){
    int eleccion = 0;
    while (eleccion < 1 || eleccion > 9)
    {
        mostrar_mapa(mapa);
        printf("\n\nEscoja un numero de 1 a 9\n");
        scanf("%d", &eleccion);
        if(eleccion < 1 || eleccion > 9){
            
            printf("clear");
            printf("Eleccion invalida\n");
            reglas();
            system("pause");
        }
    }
    return eleccion;
}

char *cargar_solucion(int valor){
    char *nombre_archivo = malloc(sizeof(char) * 21);
    switch (valor)
    {
    case 1:strcpy(nombre_archivo, "sudoku1.txt");break;
    case 2:strcpy(nombre_archivo, "sudoku2.txt");break;
    case 3:strcpy(nombre_archivo, "sudoku3.txt");break;
    case 4:strcpy(nombre_archivo, "sudoku4.txt");break;
    case 5:strcpy(nombre_archivo, "sudoku5.txt");break;
    case 6:strcpy(nombre_archivo, "sudoku6.txt");break;
    case 7:strcpy(nombre_archivo, "sudoku7.txt");break;
    case 8:strcpy(nombre_archivo, "sudoku8.txt");break;
    case 9:strcpy(nombre_archivo, "sudoku9.txt");break;
    }
    return nombre_archivo;
}

void actualizar_mapa(int mapa[9][9], int fila, int columna, int valor){
    mapa[fila][columna] = valor;
}

bool validar_jugada(int fila, int columna, int mapa_origen[9][9]){
    if(mapa_origen[fila][columna] != 0){
        system("pause");
        return false;
    }else{
        return true;
    }
}

void elegir_porsicion(int numero, int mapa[9][9], int *fila_elegida, int *collumna_elegida, int mapa_origen[9][9]){
    int fila = -1, columna = -1;
    bool validar = false;
    while(fila < 0 || columna > 9 || validar == false){
        printf("Elija la fila donde desea colocar este numero\n");
        scanf("%d", &fila);
        if(fila < 0 || fila > 9){
            printf("Fila invalida\n");
        }else{
            printf("Elija la columna donde desea colocar este numero\n");
            scanf("%d", &columna);
            if(columna < 0 || columna > 9){
                printf("Columna invalida\n");
            }else{
                if(mapa_origen[fila][columna] != 0){
                    printf("No puede sobreescribir este numero\n");
                }else{
                    validar = validar_jugada(fila, columna, mapa_origen);
                    if(validar == false){
                        printf("No puede colocar este numero en esta posicion\n");
                    }
                }
            }
        }
    }
    *fila_elegida = fila;
    *collumna_elegida = columna;
}

bool evaluar_victoria(int mapa[9][9], int solucion[9][9]){
    int fila = 0, columna = 0;
    while (fila < 9)
    {
        while (columna < 9)
        {
            if(mapa[fila][columna] != solucion[fila][columna]){
                return false;
            }
            columna++;
        }
        columna = 0;
        fila++;
    }
    return true;
}

int main(){
    int mapa[9][9], mapa_origen[9][9], solucion[9][9] = {0}, fila = -1, columna = -1, continuar = 1;
    reglas();
    int eleccion = elegir_sudoku();
    cargar_sobre_matriz(cargar_eleccion(eleccion), mapa);
    memcpy(mapa_origen, mapa, sizeof(int) * 81);
    cargar_sobre_matriz("sudoku1.txt", solucion);
    while(continuar == 1){
        int valor = escoger_numero(mapa);
        printf("Valor: %d", valor);
        elegir_porsicion(valor, mapa, &fila, &columna, mapa_origen);
        actualizar_mapa(mapa, fila, columna, valor);
        mostrar_mapa(mapa);
        bool victoria = evaluar_victoria(mapa, solucion);
        if(victoria == true){
            continuar = 0;
            system("clear");
            printf("Felicidades, ha ganado\n");
        }
    }
    return 0;   
}