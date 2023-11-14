//
// Created by Bezaleel on 10/11/23.
//
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "Conexion.h"

#define TAM_CADENA 100

#define QUERY_INSERTAR "INSERT INTO usuario (nombre, apellido, telefono, email) VALUES (?, ?, ?, ?)"
#define QUERY_ACTUALIZAR "UPDATE usuario SET telefono = ? WHERE id = ?"
#define QUERY_ELIMINAR "DELETE FROM usuario WHERE id = ?"

int conectar(MYSQL **conexion){
    *conexion = mysql_init(NULL);
    if(*conexion == NULL){
        fprintf(stderr, "%s\n", mysql_error(*conexion));
        return 1;
    }

    if(mysql_real_connect(*conexion, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0) == NULL){
        fprintf(stderr, "%s\n", mysql_error(*conexion));
        mysql_close(*conexion);
        return 1;
    }

    printf("Conexion exitosa\n");

    return 0;
}

int menu(){
    int opcion;

    printf("1. Insertar\n");
    printf("2. Actualizar\n");
    printf("3. Eliminar\n");
    printf("4. Salir\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    return opcion;

}

int main(){
    int error_conexion, id, id_res, columnas;
    unsigned long length[4];
    char first_name[TAM_CADENA], last_name[TAM_CADENA], phone_number[TAM_CADENA], email[TAM_CADENA];
    bool is_null[5], error[5];

    MYSQL *conexion;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5];

    MYSQL_RES *res_prt;
    MYSQL_FIELD *campo;

    error_conexion = conectar(&conexion);
    if(!error_conexion){
        stmt = mysql_stmt_init(conexion);

        if(stmt){
            switch(menu()){
                case 1:
                    if(!mysql_stmt_prepare(stmt, QUERY_INSERTAR, strlen(QUERY_INSERTAR))){
                        memset(bind, 0, sizeof(bind));

                        /*
                        bind[0].buffer_type = MYSQL_TYPE_LONG;
                        bind[0].buffer = (char *) &id;
                        bind[0].is_null = 0;
                        bind[0].length = 0;
                        */

                        bind[0].buffer_type = MYSQL_TYPE_STRING;
                        bind[0].buffer = (char *) first_name;
                        bind[0].buffer_length = TAM_CADENA;
                        bind[0].is_null = 0;
                        bind[0].length = &length[2];

                        bind[1].buffer_type = MYSQL_TYPE_STRING;
                        bind[1].buffer = (char *) last_name;
                        bind[1].buffer_length = TAM_CADENA;
                        bind[1].is_null = 0;
                        bind[1].length = &length[2];

                        bind[2].buffer_type = MYSQL_TYPE_STRING;
                        bind[2].buffer = (char *) phone_number;
                        bind[2].buffer_length = TAM_CADENA;
                        bind[2].is_null = 0;
                        bind[2].length = &length[3];

                        bind[3].buffer_type = MYSQL_TYPE_STRING;
                        bind[3].buffer = (char *) email;
                        bind[3].buffer_length = TAM_CADENA;
                        bind[3].is_null = 0;
                        bind[3].length = &length[4];

                        if(!mysql_stmt_bind_param(stmt, bind)){
                            printf("Ingrese nombre: ");
                            scanf("%s", first_name);
                            length[1] = strlen(first_name);
                            printf("Ingrese apellido: ");
                            scanf("%s", last_name);
                            length[2] = strlen(last_name);
                            printf("Ingrese telefono: ");
                            scanf("%s", phone_number);
                            length[3] = strlen(phone_number);
                            printf("Ingrese email: ");
                            scanf("%s", email);
                            length[4] = strlen(email);

                            if(!mysql_stmt_execute(stmt)){
                                if(mysql_stmt_affected_rows(stmt) > 0){
                                    printf("Se inserto correctamente\n");
                                }else{
                                    printf("No se inserto correctamente\n");
                                }
                                mysql_stmt_close(stmt);
                            }
                        }else{
                            printf("Error al asociar los parametros a la sentencia preparada.\n");
                        }
                    }else{
                        printf("Error al preparar la sentencia.\n");
                    }
                    break;

                case 2:
                    if(!mysql_stmt_prepare(stmt, QUERY_ACTUALIZAR, strlen(QUERY_ACTUALIZAR))){
                        memset(bind, 0, sizeof(bind));

                        bind[0].buffer_type = MYSQL_TYPE_STRING;
                        bind[0].buffer = (char *) phone_number;
                        bind[0].buffer_length = TAM_CADENA;
                        bind[0].is_null = 0;
                        bind[0].length = &length[0];

                        bind[1].buffer_type = MYSQL_TYPE_LONG;
                        bind[1].buffer = (char *) &id;
                        bind[1].is_null = 0;
                        bind[1].length = 0;

                        if(!mysql_stmt_bind_param(stmt, bind)){
                            printf("Ingrese id: ");
                            scanf("%d", &id);
                            printf("Ingrese telefono: ");
                            scanf("%s", phone_number);
                            length[0] = strlen(phone_number);

                            if(!mysql_stmt_execute(stmt)){
                                if(mysql_stmt_affected_rows(stmt) > 0){
                                    printf("Se actualizo correctamente\n");
                                }else{
                                    printf("No se actualizo correctamente\n");
                                }
                                mysql_stmt_close(stmt);
                            }
                        }else{
                            printf("Error al asociar los parametros a la sentencia preparada.\n");
                        }
                    }else{
                        printf("Error al preparar la sentencia.\n");
                    }
                    break;

                case 3:
                    if(!mysql_stmt_prepare(stmt, QUERY_ELIMINAR, strlen(QUERY_ELIMINAR))){
                        memset(bind, 0, sizeof(bind));

                        bind[0].buffer_type = MYSQL_TYPE_LONG;
                        bind[0].buffer = (char *) &id;
                        bind[0].is_null = 0;
                        bind[0].length = 0;

                        if(!mysql_stmt_bind_param(stmt, bind)){
                            printf("Ingrese id: ");
                            scanf("%d", &id);

                            if(!mysql_stmt_execute(stmt)){
                                if(mysql_stmt_affected_rows(stmt) > 0){
                                    printf("Se elimino correctamente\n");
                                }else{
                                    printf("No se elimino correctamente\n");
                                }
                                mysql_stmt_close(stmt);
                            }
                        }else{
                            printf("Error al asociar los parametros a la sentencia preparada.\n");
                        }
                    }else{
                        printf("Error al preparar la sentencia.\n");
                    }
                    break;

                default:
                    printf("Opcion no valida\n");
                    break;
            }
        }else{
            printf("Error al inicializar la sentencia preparada.\n");
        }
        mysql_close(conexion);
    }
    return 0;
}
