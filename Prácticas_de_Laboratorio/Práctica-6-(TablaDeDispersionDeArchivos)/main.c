#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>  // Incluye la librería ctype para las funciones de validación de caracteres

// Tamaño de la tabla hash
#define TABLE_SIZE 29

struct Registro {
    char codigo[7];  // 3 letras + 3 números + '\0'
    char nombre[23]; // Longitud fija de 22 caracteres + '\0'
    double precio;
};

// Funcion hashcode Calcula el valor de hash de una clave.
// Utiliza la suma de los valores ASCII de los caracteres en la clave
// y lo mapea a un indice en la tabla hash( con un tamaño de 29) usando el operado modulo '%'.
int hashCode(const char *clave) {
    int suma = 0;
    int longitud = strlen(clave);

    for (int i = 0; i < longitud; i++) {
        suma += clave[i];
    }

    return suma % TABLE_SIZE;
}

// Verifica si el código tiene 3 letras y 3 números (sin importar el orden)
// Si el codigo no es valido, no se inserta en la tabla.
int esCodigoValido(const char *codigo) {

    if (strlen(codigo) != 6)
        return 0;  // La longitud no es la correcta
    int letras = 0;
    int numeros = 0;
    for (int i = 0; i < 6; i++) {
        if (isalpha(codigo[i])) {
            letras++;
        } else if (isdigit(codigo[i])) {
            numeros++;
        }
    }
    return (letras == 3 && numeros == 3);
}

// Permite insertar un registro en la tabla. Comprueba si el codigo es valido y,
// si lo es, busca un indice disponible en la tabla y lo inserta (Utilizando el manejo de colisiones por saturacion progresiva)
// y guarda el registro en ese indice.
void insertarRegistro(struct Registro tabla[], const char *codigo, const char *nombre, double precio) {
    if (!esCodigoValido(codigo)) {
        printf("Código no válido. Debe tener el formato 'XXX999' (3 letras + 3 números NO IMPORTA EL ORDEN).\n");
        return;
    }

    // Se calcula el índice del registro
    int indice = hashCode(codigo);
    // Si el índice está ocupado, se busca el siguiente índice disponible
    while (tabla[indice].codigo[0] != '\0') {
        indice = (indice + 1) % TABLE_SIZE;
    }

    strncpy(tabla[indice].codigo, codigo, sizeof(tabla[indice].codigo));
    strncpy(tabla[indice].nombre, nombre, sizeof(tabla[indice].nombre));
    tabla[indice].precio = precio;
    printf("Registro insertado: %s (hashCode: %d)\n", codigo, indice);
}

// Busca un registro por su codigo en la tabla. Comienza en el indice calculado
// por la funcion hasgcode, y si ese indice esta ocupado, avanza linealmente hasta en contrar
// el registro o encontrar un indice vacio.
void buscarRegistro(struct Registro tabla[], const char *codigo) {
    int indice = hashCode(codigo);
    int intentos = 0;

    while (tabla[indice].codigo[0] != '\0' && intentos < TABLE_SIZE) {
        if (strcmp(tabla[indice].codigo, codigo) == 0) { // Si el código es igual al buscado
            printf("Registro encontrado: Código: %s - Nombre: %s - Precio: %.2f (hashCode: %d)\n", tabla[indice].codigo, tabla[indice].nombre, tabla[indice].precio, indice);
            return;
        }
        // Si el índice está ocupado, se busca el siguiente índice disponible
        indice = (indice + 1) % TABLE_SIZE;
        intentos++;
    }

    printf("Registro no encontrado: %s (hashCode: %d)\n", codigo, indice);
}

// Muestra todos los registros almacenados en la tabla
void mostrarRegistros(struct Registro tabla[]) {
    printf("Registros almacenados:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabla[i].codigo[0] != '\0') {
            printf("Código: %s - Nombre: %s - Precio: %.2f (hashCode: %d)\n", tabla[i].codigo, tabla[i].nombre, tabla[i].precio, i);
        }
    }
}

int main() {
    struct Registro tabla[TABLE_SIZE];

    for (int i = 0; i < TABLE_SIZE; i++) {
        strcpy(tabla[i].codigo, "");
    }

    int opcion;
    char codigo[7];
    char nombre[23];
    double precio;

    do {
        printf("Menú:\n");
        printf("1. Insertar registro\n");
        printf("2. Buscar registro\n");
        printf("3. Mostrar todos los registros\n");
        printf("4. Inserta registros con colisiones\n");
        printf("5. Salir\n");
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el código (6 caracteres): ");
                scanf("%s", codigo);
                printf("Ingrese el nombre (hasta 22 caracteres): ");
                scanf("%s", nombre);
                printf("Ingrese el precio: ");
                scanf("%lf", &precio);
                insertarRegistro(tabla, codigo, nombre, precio);
                break;
            case 2:
                printf("Ingrese el código a buscar: ");
                scanf("%s", codigo);
                buscarRegistro(tabla, codigo);
                break;
            case 3:
                mostrarRegistros(tabla);
                break;
            case 4:
                insertarRegistro(tabla, "ABC123", "Producto 1", 10.99);
                insertarRegistro(tabla, "BAC132", "Producto 2", 20.49);
                insertarRegistro(tabla, "ACB213", "Producto 3", 5.99);
                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}

