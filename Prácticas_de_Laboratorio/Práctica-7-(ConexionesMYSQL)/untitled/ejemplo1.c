//
// Created by Bezaleel on 10/11/23.
//
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>


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

    mysql_close(con);

    return 0;
}