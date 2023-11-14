//
// Created by Bezaleel on 10/11/23.
//
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

void consultarPorId(MYSQL *con) {
    // Solicitar al usuario que ingrese el ID del usuario
    printf("Ingresa el ID del usuario: ");
    char id[50];
    fgets(id, sizeof(id), stdin);

    // Eliminar el salto de línea del final del ID
    size_t len = strlen(id);
    if (len > 0 && id[len - 1] == '\n') {
        id[len - 1] = '\0';
    }

    // Construir la consulta de búsqueda por ID
    char consulta[200];
    snprintf(consulta, sizeof(consulta), "SELECT * FROM usuario WHERE id = '%s'", id);

    // Ejecutar la consulta
    if (mysql_query(con, consulta)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(con));
        return;
    }

    // Obtener el resultado de la consulta
    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(con));
        return;
    }

    // Imprimir los nombres de las columnas
    MYSQL_FIELD *field;
    while ((field = mysql_fetch_field(result))) {
        printf("%s ", field->name);
    }
    printf("\n");

    // Imprimir el registro
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < mysql_num_fields(result); i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    // Liberar el resultado
    mysql_free_result(result);
}

void consultarPorNombre(MYSQL *con) {
    // Solicitar al usuario que ingrese el nombre del usuario
    printf("Ingresa el nombre del usuario: ");
    char nombre[50];
    fgets(nombre, sizeof(nombre), stdin);

    // Eliminar el salto de línea del final del nombre
    size_t len = strlen(nombre);
    if (len > 0 && nombre[len - 1] == '\n') {
        nombre[len - 1] = '\0';
    }

    // Construir la consulta de búsqueda por nombre
    char consulta[200];
    snprintf(consulta, sizeof(consulta), "SELECT * FROM usuario WHERE nombre LIKE '%%%s%%'", nombre);

    // Ejecutar la consulta
    if (mysql_query(con, consulta)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(con));
        return;
    }

    // Obtener el resultado de la consulta
    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(con));
        return;
    }

    // Imprimir los nombres de las columnas
    MYSQL_FIELD *field;
    while ((field = mysql_fetch_field(result))) {
        printf("%s ", field->name);
    }
    printf("\n");

    // Imprimir el registro
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < mysql_num_fields(result); i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    // Liberar el resultado
    mysql_free_result(result);
}

int main() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    const char *host = "127.0.0.1";
    const char *user = "root";
    const char *password = "20191717";
    const char *database = "dbusuario";

    if (mysql_real_connect(con, host, user, password, database, 33060, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(con));
        mysql_close(con);
        return 1;
    }

    printf("Conexión exitosa a la base de datos MySQL\n");

    int opcion;
    do {
        printf("\nMenú:\n");
        printf("1. Consultar por ID\n");
        printf("2. Consultar por nombre\n");
        printf("0. Salir\n");
        printf("Ingresa tu opción: ");
        scanf("%d", &opcion);

        // Limpiar el búfer de entrada
        while(getchar() != '\n');

        switch (opcion) {
            case 1:
                consultarPorId(con);
                break;
            case 2:
                consultarPorNombre(con);
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Inténtalo de nuevo.\n");
        }

    } while (opcion != 0);

    mysql_close(con);

    return 0;
}
