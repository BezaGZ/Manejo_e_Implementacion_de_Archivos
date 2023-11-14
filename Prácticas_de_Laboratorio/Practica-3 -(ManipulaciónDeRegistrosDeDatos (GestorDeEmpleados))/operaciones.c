#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operaciones.h"

void mostrarMenu(){
    printf("\nIntroduce la opción que desea realizar:\n");
    printf("\n1. Alta empleado\n");
    printf("2. Baja empleado\n");
    printf("3. Listar empleado\n");
    printf("4. Consultar datos de un empleado\n");
    printf("5. Modificar el sueldo de un empleado\n");
    printf("6. Modificar horas de un empleado\n");
    printf("7. Salir\n");
}
void listarEmpleados(struct empleado empleados[100], int num_emp){
    printf("Listando los datos de los empleados...\n");
    for(int i = 0; i < num_emp; i++){
        printf("Nombre: %s\n", empleados[i].nombre);
        printf("ID: %d\n", empleados[i].id);
        printf("Sueldo: %f\n", empleados[i].sueldo);
        printf("Horas: %d\n", empleados[i].horas);
        printf("\n");
    }
}

int comprobarId(struct empleado empleados[100], int num_emp, int id){
    for(int i = 0; i < num_emp; i++){
        if(empleados[i].id == id){
            return 1;
        }
    }
    return 0;
}

int alta(struct empleado empleados[100], int num_emp){
    int creado = 0;
    struct empleado emp;

    fflush(stdin);
    printf("Introduce el nombre y apellidos del empleado:\n");
    scanf("%[^\n]s", emp.nombre);

    printf("Introduce el ID del empleado:\n");
    scanf("%d", &emp.id);

    printf("Introduce el sueldo del empleado:\n");
    scanf("%f", &emp.sueldo);

    printf("Introduce las horas del empleado:\n");
    scanf("%d", &emp.horas);

    int existe = comprobarId(empleados, num_emp, emp.id);

    if(num_emp < 100 && existe == 0){
        empleados[num_emp] = emp;
        num_emp++;
        creado = 1;
    }else{
        printf("No se ha podido crear el empleado\n");
    }

    return creado;
}

int baja(struct empleado empleados[100], int num_emp){
    int eliminado = 0;
    int id, indice;

    printf("Introduce el ID del empleado a dar de baja:\n");
    scanf("%d", &id);

    int existe = comprobarId(empleados, num_emp, id);

    if(existe == 1){
        for(int i = 0; i < num_emp; i++){
            if(empleados[i].id == id){
                indice = i;
            }
        }
        for(int i = indice; i < num_emp; i++){
            empleados[i] = empleados[i+1];
            struct empleado aux;
            empleados[i+1] = aux;
            //aux = empleados[i];
        }
        eliminado = 1;
    }else{
        printf("No existe ningún empleado con ese ID\n");
    }
    return eliminado;
}

void consultarDatosEmpleados(struct empleado empleados[100], int num_emp){
    int id;
    printf("Introduce el ID del empleado a consultar:\n");
    scanf("%d", &id);

    int existe = comprobarId(empleados, num_emp, id);
    if(existe == 1){
        for(int i = 0; i < num_emp; i++){
            if(empleados[i].id == id){
                printf("Nombre: %s\n", empleados[i].nombre);
                printf("ID: %d\n", empleados[i].id);
                printf("Sueldo: %f\n", empleados[i].sueldo);
                printf("Horas: %d\n", empleados[i].horas);
                printf("\n");
            }
        }
    }else{
        printf("No existe ningún empleado con ese ID\n");
    }
}

void modificarSueldo(struct empleado empleados[100], int num_emp){
    int id;
    printf("Introduce el ID del empleado a modificar:\n");
    scanf("%d", &id);

    int existe = comprobarId(empleados, num_emp, id);
    if(existe == 1){
        for(int i = 0; i < num_emp; i++){
            if(empleados[i].id == id){
                printf("Introduce el nuevo sueldo:\n");
                scanf("%f", &empleados[i].sueldo);
            }
        }
    }else{
        printf("No existe ningún empleado con ese ID\n");
    }
}

void modificarHoras(struct empleado empleados[100], int num_emp){
    int id;

    printf("Ingrese el ID del empleado: ");
    scanf("%d", &id);

    int existe = comprobarId(empleados, num_emp, id);

    if(existe == 1){
        for(int i = 0; i < num_emp; i++){
            if(empleados[i].id == id){
                printf("Introduce las nuevas horas:\n");
                scanf("%d", &empleados[i].horas);
            }
        }
    }else{
        printf("No existe ningún empleado con ese ID\n");
    }
}