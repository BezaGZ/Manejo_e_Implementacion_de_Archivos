//
// Created by Bezaleel on 13/11/23.
//
#include <string.h>
#include <time.h>

void imprimirResultado(MYSQL_RES *result) {
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("\n*******************************\n");
        printf("Reservación: %s\n", row[0]);
        printf("Habitación: %s\n", row[1]);
        printf("Cliente: %s\n", row[2]);
        printf("Fecha Ingreso: %s\n", row[3]);
        printf("Fecha Salida: %s\n", row[4]);
        printf("Estado: %s\n", row[5]);
        printf("*******************************\n");
    }

    printf("\n*******************************************************\n");
}
void verReservacionesFechaEspecifica(MYSQL *con) {
    char fecha[20];
    struct tm tm_fecha;
    printf("\n*********** Reservasciones Fecha de Ingreso ***********\n");
    printf("Ingrese la fecha de ingreso (YYYY-MM-DD): ");
    scanf("%s", fecha);

    if (strptime(fecha, "%Y-%m-%d", &tm_fecha) == NULL) {
        printf("Error: El formato de fecha ingresado no es válido. Use el formato YYYY-MM-DD.\n");
        printf("*******************************************************\n");
        return;
    }

    char query[200];
    sprintf(query, "SELECT Reservacion, Habitacion, Cliente, FechaIngreso, FechaSalida, Estado FROM verReservas WHERE DATE(FechaIngreso) = '%s';", fecha);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        printf("*******************************************************\n");
        return;
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        printf("*******************************************************\n");
        return;
    }

    if (mysql_num_rows(result) == 0) {
        printf("No hay reservaciones para la fecha ingresada.\n");
        printf("*******************************************************\n");
    } else {
        imprimirResultado(result);
    }

    mysql_free_result(result);
}
void consultarReservasHabitacion(MYSQL *con) {
    int idHabitacion;
    printf("\n******* Historial de Reservación por Habitación *******\n");
    printf("Ingrese el número de la habitación: ");
    scanf("%d", &idHabitacion);

    char queryVerificar[100];
    sprintf(queryVerificar, "SELECT * FROM habitacion WHERE IdHabitacion = %d;", idHabitacion);
    if (mysql_query(con, queryVerificar) != 0) {
        fprintf(stderr, "Error al verificar la habitación: %s\n", mysql_error(con));
        printf("*******************************************************\n");
        return;
    }

    MYSQL_RES *resultVerificar = mysql_store_result(con);
    if (mysql_num_rows(resultVerificar) == 0) {
        printf("Error: La habitación con el número %d no existe.\n", idHabitacion);
        printf("*******************************************************\n");
        mysql_free_result(resultVerificar);
        return;
    }
    mysql_free_result(resultVerificar);

    char query[200];
    sprintf(query, "SELECT Reservacion, Habitacion, Cliente, FechaIngreso, FechaSalida, Estado FROM verReservas WHERE Habitacion = %d;", idHabitacion);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        printf("*******************************************************\n");
        return;
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        printf("*******************************************************\n");
        return;
    }

    if (mysql_num_rows(result) == 0) {
        printf("No hay reservaciones para la habitación ingresada.\n");
        printf("*******************************************************\n");
    } else {
        imprimirResultado(result);
    }

    mysql_free_result(result);
}
void verReservasConfirmadasFecha(MYSQL *con) {
    char fecha[20];
    struct tm tm_fecha;

    printf("\n*********** Reservaciones Confirmadas *****************\n");
    printf("Ingrese la fecha de ingreso (YYYY-MM-DD): ");
    scanf("%s", fecha);

    if (strptime(fecha, "%Y-%m-%d", &tm_fecha) == NULL) {
        printf("Error: El formato de fecha ingresado no es válido. Use el formato YYYY-MM-DD.\n");
        printf("*******************************************************\n");
        return;
    }

    char query[200];
    sprintf(query, "SELECT Reservacion, Habitacion, Cliente, FechaIngreso, FechaSalida, Estado FROM verReservas WHERE FechaIngreso = '%s' AND Estado = 'Confirmada';", fecha);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        printf("*******************************************************\n");
        return;
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        printf("*******************************************************\n");
        return;
    }

    if (mysql_num_rows(result) == 0) {
        printf("No hay reservaciones confirmadas para la fecha ingresada.\n");
        printf("*******************************************************\n");
    } else {
        imprimirResultado(result);
    }

    mysql_free_result(result);
}
void reservacionesClientePorId(MYSQL *con) {
    char idCliente[20];
    printf("\n*************** Reservaciones de Cliente *************\n");

    int validoVerificar = 1;
    do {
        printf("Ingrese el DPI del cliente: ");
        scanf("%s", idCliente);

        validoVerificar = 1;
        for (int i = 0; i < strlen(idCliente); i++) {
            if (!isdigit(idCliente[i])) {
                validoVerificar = 0;
                break;
            }
        }

        if (strlen(idCliente) != 13 || !validoVerificar) {
            printf("Error: El DPI debe tener exactamente 13 dígitos y contener solo números.\n");
        }

    } while (strlen(idCliente) != 13 || !validoVerificar);

    char query[200];
    sprintf(query, "SELECT * FROM verCliente WHERE Dpi = %s;", idCliente);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        return;
    }

    if (mysql_num_rows(result) == 0) {
        printf("No hay reservaciones para el cliente con el DPI proporcionado o el DPI no existe.\n");
        printf("*******************************************************\n");
    } else {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            printf("\n*******************************\n");
            printf("Reservacion: %s\nHabitacion: %s\nDPI: %s\nCliente: %s\nFecha Ingreso: %s\nFecha Salida: %s\nEstado: %s\n",
                   row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
            printf("*******************************\n");
        }
        printf("\n*******************************************************\n");
    }

    mysql_free_result(result);
}
void agregarReservacion(MYSQL *con) {
    int idHabitacion;
    char fechaIngreso[20], idCliente[20], fechaSalida[20], estado[] = "Confirmada";

    printf("\n***************** Agregar Reservación *****************\n");
    printf("Ingrese el número de habitación: ");
    scanf("%d", &idHabitacion);

    char queryVerificarHabitacion[100];
    sprintf(queryVerificarHabitacion, "SELECT * FROM habitacion WHERE IdHabitacion = %d;", idHabitacion);
    if (mysql_query(con, queryVerificarHabitacion) != 0) {
        fprintf(stderr, "Error al verificar la habitación: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificarHabitacion = mysql_store_result(con);
    if (mysql_num_rows(resultVerificarHabitacion) == 0) {
        printf("Error: La habitación con el número %d no existe.\n", idHabitacion);
        printf("*******************************************************\n");
        mysql_free_result(resultVerificarHabitacion);
        return;
    }
    mysql_free_result(resultVerificarHabitacion);

    int validoAgregar = 1;
    do {
        printf("Ingrese el DPI del cliente: ");
        scanf("%s", idCliente);

        validoAgregar = 1;
        for (int i = 0; i < strlen(idCliente); i++) {
            if (!isdigit(idCliente[i])) {
                validoAgregar = 0;
                break;
            }
        }

        if (strlen(idCliente) != 13 || !validoAgregar) {
            printf("Error: El DPI debe tener exactamente 13 dígitos y contener solo números.\n");
        } else {
            char queryVerificarCliente[100];
            sprintf(queryVerificarCliente, "SELECT * FROM cliente WHERE IdCliente = %s;", idCliente);

            if (mysql_query(con, queryVerificarCliente) != 0) {
                fprintf(stderr, "Error al verificar la existencia del cliente: %s\n", mysql_error(con));
                return;
            }

            MYSQL_RES *resultVerificarCliente = mysql_store_result(con);
            if (mysql_num_rows(resultVerificarCliente) == 0) {
                printf("Error: El cliente con el DPI %s no existe.\n", idCliente);
                printf("*******************************************************\n");
                mysql_free_result(resultVerificarCliente);
                return;
            }
            mysql_free_result(resultVerificarCliente);
        }

    } while (strlen(idCliente) != 13 || !validoAgregar);


    printf("Ingrese fecha de ingreso (YYYY-MM-DD): ");
    scanf("%s", fechaIngreso);

    struct tm tm_fecha;
    if (strptime(fechaIngreso, "%Y-%m-%d", &tm_fecha) == NULL) {
        printf("Error: El formato de la fecha de ingreso no es válido.\n");
        printf("*******************************************************\n");
        return;
    }

    char queryVerificarReservacionExistente[200];
    sprintf(queryVerificarReservacionExistente, "SELECT * FROM reservacion WHERE IdHabitacion = %d AND fecha_ingreso = '%s' AND estado != 'Cancelada';", idHabitacion, fechaIngreso);

    if (mysql_query(con, queryVerificarReservacionExistente) != 0) {
        fprintf(stderr, "Error al verificar la existencia de reservaciones: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificarReservacionExistente = mysql_store_result(con);
    if (!resultVerificarReservacionExistente) {
        fprintf(stderr, "Error al obtener el resultado de la consulta de reservación existente: %s\n", mysql_error(con));
        return;
    }

    if (mysql_num_rows(resultVerificarReservacionExistente) > 0) {
        MYSQL_ROW rowReservacionExistente = mysql_fetch_row(resultVerificarReservacionExistente);
        if (strcmp(rowReservacionExistente[4], "Cancelada") == 0) {
            printf("Puede registrar la nueva reserva ya que la reserva anterior está cancelada.\n");
        } else {
            printf("Error: Ya hay una reserva confirmada para la habitación %d en la fecha de ingreso %s.\n", idHabitacion, fechaIngreso);
            printf("*******************************************************\n");
            mysql_free_result(resultVerificarReservacionExistente);
            return;
        }
    }

    mysql_free_result(resultVerificarReservacionExistente);






    printf("Ingrese fecha de salida (YYYY-MM-DD): ");
    scanf("%s", fechaSalida);

    struct tm tm_fecha_1;
    if (strptime(fechaSalida, "%Y-%m-%d", &tm_fecha_1) == NULL) {
        printf("Error: El formato de la fecha de ingreso no es válido.\n");
        printf("*******************************************************\n");
        return;
    }

    char query[300];
    sprintf(query, "INSERT INTO reservacion (IdHabitacion, IdCliente, fecha_ingreso, fecha_salida, estado) VALUES (%d, %s, '%s', '%s', '%s');",
            idHabitacion, idCliente, fechaIngreso, fechaSalida, estado);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        return;
    }

    if (mysql_query(con, "SELECT LAST_INSERT_ID();") != 0) {
        fprintf(stderr, "Error al obtener el ID de la última fila insertada: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultId = mysql_store_result(con);
    if (!resultId) {
        fprintf(stderr, "Error al obtener el resultado de la consulta para el ID: %s\n", mysql_error(con));
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(resultId);
    if (!row) {
        fprintf(stderr, "Error: No se pudo obtener el ID de la última fila insertada.\n");
        mysql_free_result(resultId);
        return;
    }

    int idReservacion = atoi(row[0]);
    mysql_free_result(resultId);

    printf("\n*******************************************************\n");
    printf("Reservación agregada exitosamente.\n");
    printf("Número de Reservación: %d\n", idReservacion);
    printf("Habitación: %d\n", idHabitacion);
    printf("DPI del Cliente: %s\n", idCliente);
    printf("Fecha de Ingreso: %s\n", fechaIngreso);
    printf("Fecha de Salida: %s\n", fechaSalida);
    printf("Estado: %s\n", estado);
    printf("*******************************************************\n");
    return;
}
void actualizarReservacion(MYSQL *con) {
    int idReservacion;
    char nuevaFechaIngreso[20], nuevaFechaSalida[20];


    printf("\n**************** Modificar Reservación ****************\n");
    printf("Ingrese el número de reservación a actualizar: ");
    scanf("%d", &idReservacion);

    char queryVerificar[100];
    sprintf(queryVerificar, "SELECT * FROM reservacion WHERE IdReservacion = %d;", idReservacion);
    if (mysql_query(con, queryVerificar) != 0) {
        fprintf(stderr, "Error al verificar la reservación: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificar = mysql_store_result(con);
    if (mysql_num_rows(resultVerificar) == 0) {
        printf("Error: La reservación con el número %d no existe.\n", idReservacion);
        printf("*******************************************************\n");
        mysql_free_result(resultVerificar);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(resultVerificar);
    char *estadoReservacion = row[5];
    mysql_free_result(resultVerificar);

    if (strcmp(estadoReservacion, "Cancelada") == 0) {
        printf("Error: No se puede actualizar la reservación porque está cancelada.\n");
        printf("*******************************************************\n");
        return;
    }



    printf("Ingrese la nueva fecha de ingreso (YYYY-MM-DD): ");
    scanf("%s", nuevaFechaIngreso);

    struct tm tm_fecha;
    if (strptime(nuevaFechaIngreso, "%Y-%m-%d", &tm_fecha) == NULL) {
        printf("Error: El formato de la fecha de ingreso no es válido.\n");
        printf("*******************************************************\n");
        return;
    }


    char queryConflictos[300];
    sprintf(queryConflictos, "SELECT * FROM reservacion WHERE IdReservacion != %d AND IdHabitacion = (SELECT IdHabitacion FROM reservacion WHERE IdReservacion = %d) AND estado = 'Confirmada' AND (('%s' BETWEEN fecha_ingreso AND fecha_salida) OR ('%s' BETWEEN fecha_ingreso AND fecha_salida));", idReservacion, idReservacion, nuevaFechaIngreso, nuevaFechaIngreso);
    if (mysql_query(con, queryConflictos) != 0) {
        fprintf(stderr, "Error al verificar conflictos de fechas: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultConflictos = mysql_store_result(con);
    if (mysql_num_rows(resultConflictos) > 0) {
        printf("Error: La nueva fecha de ingreso coincide con otra reservación confirmada en la misma habitación.\n");
        printf("*******************************************************\n");
        mysql_free_result(resultConflictos);
        return;
    }

    char queryExistencia[300];
    sprintf(queryExistencia, "SELECT * FROM reservacion WHERE IdHabitacion = (SELECT IdHabitacion FROM reservacion WHERE IdReservacion = %d) AND fecha_ingreso = '%s' AND estado = 'Confirmada';", idReservacion, nuevaFechaIngreso);
    if (mysql_query(con, queryExistencia) != 0) {
        fprintf(stderr, "Error al verificar la existencia de reservaciones confirmadas: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultExistencia = mysql_store_result(con);
    if (mysql_num_rows(resultExistencia) > 0) {
        printf("Error: Ya hay una reservación confirmada para la misma habitación en la nueva fecha de ingreso.\n");
        printf("*******************************************************\n");
        mysql_free_result(resultExistencia);
        return;
    }

    mysql_free_result(resultConflictos);
    mysql_free_result(resultExistencia);



    printf("Ingrese la nueva fecha de salida (YYYY-MM-DD): ");
    scanf("%s", nuevaFechaSalida);

    struct tm tm_fecha_1;
    if (strptime(nuevaFechaSalida, "%Y-%m-%d", &tm_fecha_1) == NULL) {
        printf("Error: El formato de la fecha de ingreso no es válido.\n");
        printf("*******************************************************\n");
        return;
    }

    char query[200];
    sprintf(query, "UPDATE reservacion SET fecha_ingreso = '%s', fecha_salida = '%s' WHERE IdReservacion = %d;", nuevaFechaIngreso, nuevaFechaSalida, idReservacion);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        return;
    }

    printf("\nFechas de la Reservación actualizadas exitosamente.\n");
    printf("*******************************************************\n");
}
void cancelarReservacion(MYSQL *con) {
    int idReservacion;
    printf("\n***************** Cancelar Reservación ****************\n");
    printf("Ingrese el número único de reservación: ");
    scanf("%d", &idReservacion);

    char queryVerificar[100];
    sprintf(queryVerificar, "SELECT * FROM reservacion WHERE IdReservacion = %d;", idReservacion);
    if (mysql_query(con, queryVerificar) != 0) {
        fprintf(stderr, "Error al verificar la reservación: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificar = mysql_store_result(con);
    if (mysql_num_rows(resultVerificar) == 0) {
        printf("Error: La reservación con el número %d no existe.\n", idReservacion);
        printf("*******************************************************\n");
        mysql_free_result(resultVerificar);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(resultVerificar);
    mysql_free_result(resultVerificar);

    if (strcmp(row[5], "Cancelada") == 0) {
        printf("Error: La reservación con el número %d ya está cancelada.\n", idReservacion);
        printf("*******************************************************\n");
        return;
    }

    char query[200];
    sprintf(query, "UPDATE reservacion SET estado = 'Cancelada' WHERE IdReservacion = %d;", idReservacion);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        return;
    }

    printf("\nReservación cancelada exitosamente.\n");
    printf("*******************************************************\n");
}
void generarFactura(MYSQL *con) {
    int idReservacion;
    printf("\n******************** Generar Factura ******************\n");
    printf("Ingrese el número de reservación para generar factura: ");
    scanf("%d", &idReservacion);

    char queryVerificar[100];
    sprintf(queryVerificar, "SELECT * FROM reservacion WHERE IdReservacion = %d;", idReservacion);
    if (mysql_query(con, queryVerificar) != 0) {
        fprintf(stderr, "Error al verificar la reservación: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificar = mysql_store_result(con);
    if (mysql_num_rows(resultVerificar) == 0) {
        printf("Error: La reservación con el número %d no existe.\n", idReservacion);
        printf("*******************************************************\n");
        mysql_free_result(resultVerificar);
        return;
    }
    mysql_free_result(resultVerificar);

    char query[300];
    sprintf(query, "SELECT * FROM verFactura WHERE Reservacion = %d;", idReservacion);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == NULL) {
        printf("La reservación seleccionada está 'Cancelada'. No se puede generar la factura.\n");
    } else {

        printf("\n*********FACTURA*********\n");
        printf("Reservación: %s\n", row[0]);
        printf("Nombre: %s %s\n", row[1], row[2]);
        printf("Tipo de Habitación: %s\n", row[3]);
        printf("Precio de Habitación: %s", row[4]);

        printf("\n¡Gracias por su reserva!\n");
        printf("*************************\n\n");
    }

    printf("*******************************************************\n");
    mysql_free_result(result);
}
void manejoReservaciones(MYSQL *con) {
    int opcion;
    char entrada[100];

    do {
        printf("\n\t** Sub Menú Manejo de Reservaciones **\n");
        printf("\t1. Historial de reservaciones por habitación\n");
        printf("\t2. Reservaciones para fecha específica\n");
        printf("\t3. Reservaciones confirmadas para fecha específica\n");
        printf("\t4. Reservaciones para cliente especifico (DPI)\n");
        printf("\t5. Agregar una reservación\n");
        printf("\t6. Actualizar datos de una reservación\n");
        printf("\t7. Cancelar una reservación\n");
        printf("\t8. Generar factura por número de reservación\n");
        printf("\t9. Volver al Menú Princial\n");
        printf("\tSeleccione una opción: ");

        scanf("%s", entrada);

        if (sscanf(entrada, "%d", &opcion) != 1) {
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                consultarReservasHabitacion(con);
                break;
            case 2:
                verReservacionesFechaEspecifica(con);
                break;
            case 3:
                verReservasConfirmadasFecha(con);
                break;
            case 4:
                reservacionesClientePorId(con);
                break;
            case 5:
                agregarReservacion(con);
                break;
            case 6:
                actualizarReservacion(con);
                break;
            case 7:
                cancelarReservacion(con);
                break;
            case 8:
                generarFactura(con);
                break;
            case 9:
                printf("Saliendo del Menú de Manejo de Reservaciones\n");
                break;
            default:
                printf("Opción no válida. Inténtelo de nuevo.\n");
        }
    } while (opcion != 9);
}