//
// Created by Bezaleel on 13/11/23.
//
#include <string.h>

void verHabitacionesDisponibles(MYSQL *con) {
    MYSQL_RES *result = NULL;

    if (mysql_query(con, "SELECT IdHabitacion, tipo, precio, estado FROM habitacion WHERE estado = 'Disponible';") != 0) {
        fprintf(stderr, "Error al verificar habitación disponible: %s\n", mysql_error(con));
        return;
    }

    result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_ROW row;

    printf("\n********************** Habitaciones Disponibles **********************\n");
    printf("%-20s%-20s%-20s%-20s\n", "Habitación", "Tipo", "Precio", "Estado");
    printf("**********************************************************************\n");
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%-20s%-20s%-20s%-20s\n", row[0], row[1], row[2], row[3]);

    }
    printf("**********************************************************************\n");
    mysql_free_result(result);
}

void verHabitacionesOcupadas(MYSQL *con) {
    MYSQL_RES *result = NULL;

    if (mysql_query(con, "SELECT IdHabitacion, tipo, precio, estado FROM habitacion WHERE estado = 'Ocupado';") != 0) {
        fprintf(stderr, "Error al verificar habitaciones ocupadas: %s\n", mysql_error(con));
        return;
    }

    result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_ROW row;

    printf("\n************************ Habitaciones Ocupadas ***********************\n");
    printf("%-20s%-20s%-20s%-20s\n", "Habitación", "Tipo", "Precio", "Estado");
    printf("**********************************************************************\n");
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%-20s%-20s%-20s%-20s\n", row[0], row[1], row[2], row[3]);
    }
    printf("**********************************************************************\n");
    mysql_free_result(result);
}

void modificarEstadoHabitacion(MYSQL *con) {
    int idHabitacion;
    char nuevoEstado[50];

    printf("\n********************* Modificar Estado de Habitación **********************\n");
    printf("Ingrese el número de habitación que desea modificar: ");
    scanf("%d", &idHabitacion);

    char queryVerificar[100];
    sprintf(queryVerificar, "SELECT * FROM habitacion WHERE IdHabitacion = %d;", idHabitacion);
    if (mysql_query(con, queryVerificar) != 0) {
        fprintf(stderr, "Error al verificar la modificación de la habitación: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificar = mysql_store_result(con);
    if (mysql_num_rows(resultVerificar) == 0) {
        printf("Error: La habitación con el número %d no existe.\n", idHabitacion);
        printf("***************************************************************************\n");
        return;
    }
    mysql_free_result(resultVerificar);

    printf("Ingrese el nuevo estado de la habitación (Disponible, Ocupado, En mantenimiento): ");
    scanf(" %49[^\n]", nuevoEstado);

    if (strcmp(nuevoEstado, "Disponible") != 0 &&
            strcmp(nuevoEstado, "Ocupado") != 0 &&
            strcmp(nuevoEstado, "En mantenimiento") != 0) {
        printf("Error: Estado no válido. Por favor, ingrese un estado válido.\n");
        printf("***************************************************************************\n");
        return;
    }

    char query[200];
    sprintf(query, "UPDATE habitacion SET estado = '%s' WHERE IdHabitacion = %d;", nuevoEstado, idHabitacion);


    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al actualizar el estado: %s\n", mysql_error(con));
        return;
    }

    printf("Estado de la habitación actualizado con éxito.\n");
    printf("***************************************************************************\n");
}

void verHabitacionesEnMantenimiento(MYSQL *con) {
    MYSQL_RES *result = NULL;

    if (mysql_query(con, "SELECT IdHabitacion, tipo, precio, estado FROM habitacion WHERE estado = 'En mantenimiento';") != 0) {
        fprintf(stderr, "Error al verificar habitaciones en mantenimiento: %s\n", mysql_error(con));
        return;
    }

    result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_ROW row;

    printf("\n********************** Habitaciones en Mantenimiento **********************\n");
    printf("%-20s%-20s%-20s%-20s\n", "Habitación", "Tipo", "Precio", "Estado");
    printf("***************************************************************************\n");
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%-20s%-20s%-20s%-20s\n", row[0], row[1], row[2], row[3]);
    }
    printf("***************************************************************************\n");
    mysql_free_result(result);
}

void manejoHabitaciones(MYSQL *con) {
    int opcionHabitaciones;
    char entrada[50];
    do {
        printf("\n\t** Sub Menú Manejo de Habitaciones **\n");
        printf("\t1. Ver Habitaciones Disponibles\n");
        printf("\t2. Ver Habitaciones Ocupadas\n");
        printf("\t3. Ver Habitaciones En Mantenimiento\n");
        printf("\t4. Modificar Estado de Habitación\n");
        printf("\t5. Volver al Menú Principal\n");
        printf("\tSeleccione una opción: ");

        scanf("%s", entrada);

        if (sscanf(entrada, "%d", &opcionHabitaciones) != 1) {
            opcionHabitaciones = -1;
        }
        switch (opcionHabitaciones) {
            case 1:
                verHabitacionesDisponibles(con);
                break;
            case 2:
                verHabitacionesOcupadas(con);
                break;
            case 3:
                verHabitacionesEnMantenimiento(con);
                break;
            case 4:
                modificarEstadoHabitacion(con);
                break;
            case 5:
                printf("Volviendo al Menú Principal\n");
                break;
            default:
                printf("Opción no válida. Inténtelo de nuevo.\n");
        }
    } while (opcionHabitaciones != 5);
}