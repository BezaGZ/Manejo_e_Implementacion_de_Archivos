#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"
#include "persistencia.h"

int main() {
    int opcion = 0;
    int num_emp = 0;
    struct empleado empleados[100];
    num_emp = cargarEmpleados(empleados);
    printf("BIENVENIDOS AL GESTOR DE EMPLEADOS\n");
    mostrarMenu();
    scanf("%d", &opcion);

    while (opcion != 7) {
        switch (opcion) {
            case 1: {
                int creado = alta(empleados, num_emp);
                if (creado == 1) {
                    printf("Empleado creado correctamente\n");
                    num_emp++;
                }
                break;
            }
            case 2: {
                int eliminado = baja(empleados, num_emp);
                if (eliminado == 1) {
                    printf("Empleado eliminado correctamente\n");
                    num_emp--;
                }
                break;
            }
            case 3:
                listarEmpleados(empleados, num_emp);
                break;
            case 4:
                consultarDatosEmpleados(empleados, num_emp);
                break;
            case 5:
                modificarSueldo(empleados, num_emp);
                break;
            case 6:
                modificarHoras(empleados, num_emp);
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
        mostrarMenu();
        scanf("%d", &opcion);
    }
    guardarEmpleados(empleados, num_emp);
    printf("Hasta luego...\n");
    return 0;
}