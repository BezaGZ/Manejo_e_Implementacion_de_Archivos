#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // La conexión ha tenido éxito, puedes realizar consultas y otras operaciones aquí.

    printf("Conexión exitosa a la base de datos MySQL\n");

    // Solicitar al usuario que ingrese el nombre o el ID del usuario
    printf("Ingresa el nombre o el ID del usuario: ");
    char input[50];
    fgets(input, sizeof(input), stdin);

    // Eliminar el salto de línea del final del input
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Construir la consulta de búsqueda
    char consulta[200];  // Aumenté el tamaño para permitir consultas más largas
    snprintf(consulta, sizeof(consulta), "SELECT * FROM usuario WHERE nombre LIKE '%%%s%%' OR id = '%s'", input, input);

    // Ejecutar la consulta
    if (mysql_query(con, consulta)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(con));
        mysql_close(con);
        return 1;
    }

    // Obtener el resultado de la consulta
    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(con));
        mysql_close(con);
        return 1;
    }

    // Imprimir los nombres de las columnas
    MYSQL_FIELD *field;
    while ((field = mysql_fetch_field(result))) {
        printf("%s ", field->name);
    }
    printf("\n");

    // Imprimir los registros
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < mysql_num_fields(result); i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    // Liberar el resultado
    mysql_free_result(result);

    // Cerrar la conexión
    mysql_close(con);

    return 0;
}
