//
// Created by Bezaleel on 13/11/23.
//
#include <string.h>

void verClientes(MYSQL *con) {
    MYSQL_RES *result = NULL;

    if (mysql_query(con, "SELECT IdCliente, nombre, apellido, email, telefono FROM cliente;") != 0) {
        fprintf(stderr, "Error al verificar los clientes: %s\n", mysql_error(con));
        return;
    }
    result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(con));
        return;
    }

    MYSQL_ROW row;

    printf("\n************************************** Clientes Registrados **************************************\n");
    printf("%-15s%-20s%-20s%-30s%-15s\n", "DPI", "Nombre", "Apellido", "Email", "Teléfono");
    printf("**************************************************************************************************\n");

    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%-15s%-20s%-20s%-30s%-15s\n", row[0], row[1], row[2], row[3], row[4]);
    }
    printf("**************************************************************************************************\n");
    mysql_free_result(result);
}
void agregarCliente(MYSQL *con) {
    int idCliente;
    char nombre[50], apellido[50], email[100], telefono[20];

    printf("\n************************************** Agregar Cliente **************************************\n");

    printf("Ingrese el DPI del nuevo cliente: ");
    scanf("%d", &idCliente);

    char queryVerificar[100];
    sprintf(queryVerificar, "SELECT * FROM cliente WHERE IdCliente = %d;", idCliente);
    if (mysql_query(con, queryVerificar) != 0) {
        fprintf(stderr, "Error al verificar el DPI del cliente: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificar = mysql_store_result(con);
    if (mysql_num_rows(resultVerificar) > 0) {
        printf("Error: El DPI del cliente ya existe.\n");
        printf("*********************************************************************************************\n");
        mysql_free_result(resultVerificar);
        return;
    }
    mysql_free_result(resultVerificar);


    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nombre);

    if (strlen(nombre) > 49) {
        printf("Error: Longitud del nombre excede el límite permitido.\n");
        printf("*********************************************************************************************\n");
        return;
    }

    printf("Ingrese el apellido del cliente: ");
    scanf("%s", apellido);

    if (strlen(apellido) > 49) {
        printf("Error: Longitud del apellido excede el límite permitido.\n");
        printf("*********************************************************************************************\n");
        return;
    }

    printf("Ingrese el email del cliente: ");
    scanf("%s", email);

    printf("Ingrese el teléfono del cliente, Formato: (XXXX-XXXX): ");
    scanf("%s", telefono);

    char query[200];
    sprintf(query, "INSERT INTO cliente (IdCliente, nombre, apellido, email, telefono) VALUES (%d, '%s', '%s', '%s', '%s');", idCliente, nombre, apellido, email, telefono);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        return;
    }

    printf("Cliente agregado con éxito.\n");
    printf("*********************************************************************************************\n");
}
void eliminarCliente(MYSQL *con) {
    int idCliente;

    printf("\n************************************** Eliminar Cliente **************************************\n");
    printf("Ingrese el DPI del cliente que desea eliminar: ");
    scanf("%d", &idCliente);

    char queryVerificar[100];
    sprintf(queryVerificar, "SELECT * FROM cliente WHERE IdCliente = %d;", idCliente);
    if (mysql_query(con, queryVerificar) != 0) {
        fprintf(stderr, "Error al verificar la existencia del cliente: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificar = mysql_store_result(con);
    if (mysql_num_rows(resultVerificar) == 0) {
        printf("Error: El cliente con el DPI %d no existe.\n", idCliente);
        printf("**********************************************************************************************\n");
        mysql_free_result(resultVerificar);
        return;
    }
    mysql_free_result(resultVerificar);

    char query[100];
    sprintf(query, "DELETE FROM cliente WHERE IdCliente = %d;", idCliente);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        return;
    }

    printf("Cliente eliminado con éxito.\n");
    printf("**********************************************************************************************\n");
}
void actualizarCliente(MYSQL *con) {
    int idCliente;
    char nuevoNombre[50], nuevoApellido[50], nuevoEmail[100], nuevoTelefono[20];

    printf("\n************************************** Actualizar Cliente **************************************\n");
    printf("Ingrese el DPI del cliente que desea actualizar: ");
    scanf("%d", &idCliente);

    char queryVerificar[100];
    sprintf(queryVerificar, "SELECT * FROM cliente WHERE IdCliente = %d;", idCliente);
    if (mysql_query(con, queryVerificar) != 0) {
        fprintf(stderr, "Error al verificar la existencia del cliente: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *resultVerificar = mysql_store_result(con);
    if (mysql_num_rows(resultVerificar) == 0) {
        printf("Error: El cliente con el DPI %d no existe.\n", idCliente);
        printf("************************************************************************************************\n");
        mysql_free_result(resultVerificar);
        return;
    }
    mysql_free_result(resultVerificar);

    printf("Ingrese el nuevo nombre del cliente: ");
    scanf("%s", nuevoNombre);

    printf("Ingrese el nuevo apellido del cliente: ");
    scanf("%s", nuevoApellido);

    printf("Ingrese el nuevo email del cliente: ");
    scanf("%s", nuevoEmail);

    printf("Ingrese el nuevo teléfono del cliente: ");
    scanf("%s", nuevoTelefono);

    char query[200];
    sprintf(query, "UPDATE cliente SET nombre = '%s', apellido = '%s', email = '%s', telefono = '%s' WHERE IdCliente = %d;", nuevoNombre, nuevoApellido, nuevoEmail, nuevoTelefono, idCliente);

    if (mysql_query(con, query) != 0) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", mysql_error(con));
        return;
    }

    printf("Datos del cliente actualizados con éxito.\n");
    printf("************************************************************************************************\n");
}

void manejoClientes(MYSQL *con) {
    int opcion;
    char entrada[100];

    do {
        printf("\n\t** Sub Menú Manejo de Clientes **\n");
        printf("\t1. Ver Clientes\n");
        printf("\t2. Agregar Cliente\n");
        printf("\t3. Eliminar Cliente\n");
        printf("\t4. Actualizar Cliente\n");
        printf("\t5. Volver al Menú Principal\n");
        printf("\tSeleccione una opción: ");

        scanf("%s", entrada);

        if (sscanf(entrada, "%d", &opcion) != 1) {
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                verClientes(con);
                break;

            case 2:
                agregarCliente(con);
                break;

            case 3:
                eliminarCliente(con);
                break;

            case 4:
                actualizarCliente(con);
                break;

            case 5:
                printf("Saliendo del Menú de Manejo de Clientes\n");
                break;

            default:
                printf("Opción no válida. Inténtelo de nuevo.\n");
        }
    } while (opcion != 5);
}
