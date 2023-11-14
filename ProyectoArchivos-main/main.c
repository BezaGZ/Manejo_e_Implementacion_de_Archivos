#include <mysql/mysql.h>
#include <stdio.h>
#include "conexion.h"
#include "menuHabitaciones.c"
#include "menuClientes.c"
#include "menuReservaciones.c"

MYSQL* establecerConexion() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }

    if (mysql_real_connect(con, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(con));
        mysql_close(con);
        return NULL;
    }

    printf("Conexión exitosa a la base de datos MySQL\n");
    return con;
}

int main() {
    MYSQL *con = establecerConexion();
    if (con == NULL) {
        return 1;
    }

    int opcionMenu;
    char entrada[50];

    do {
        printf("\n* MENU PRINCIPAL RESERVACIONES *\n");
        printf("1. Manejo de Habitaciones\n");
        printf("2. Manejo de Clientes\n");
        printf("3. Manejo de Reservaciones\n");
        printf("4. Salir\n");
        printf("Ingrese su opción: ");

        scanf("%s", entrada);

        if (sscanf(entrada, "%d", &opcionMenu) != 1) {
            opcionMenu = -1;
            printf("Error: Ingrese un número válido.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcionMenu) {
            case 1:
                manejoHabitaciones(con);
                break;
            case 2:
                manejoClientes(con);
                break;
            case 3:
                manejoReservaciones(con);
                break;
            case 4:
                printf("Saliendo del Programa\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (opcionMenu != 4);

    mysql_close(con);
    return 0;
}