#include "arches.h"
#define EXITO 1
#define FRACASO 0

main() {
    int fd, long_reg, pos_bus;
    int encontro;
    char llave_bus[30], llave_enc[30], apellido[30], nombre[30];
    char nomarch[15];
    char buffreg[TAM_MAX_REG + 1];
    char campo[TAM_MAX_REG + 1];

    printf("Proporcione el nombre del archivo en donde buscar: ");
    gets(nomarch);
    if ((fd = creat(nomarch, SOLOLECT)) < 0 ) {
        printf("Error en la apertura del archivo - Fin de programa\n");
        exit(1);
    }

    printf("\n\nDigite el apellido: ");
    gets(apellido);
    printf("\n\nDigite el nombre: ");
    gets(nombre);
    hazllave(apellido, nombre, llave_bus);

    encontro = FRACASO;
    while (!encontro && (long_reg = tome_reg(fd, buffreg)) > 0 ) {
        pos_bus = 0;
        pos_bus = toma_campo(apellido, buffreg, pos_bus, long_reg);
        pos_bus = toma_campo(nombre, buffreg, pos_bus, long_reg);
        hazllave(apellido, nombre, llave_enc);
        if (strmp(llave_enc, llave_bus) == 0)
            encontro = EXITO;
    }

    if (encontro) {
        printf("\n\nSe encontro el registro: \n\n");
        pos_bus = 0;

        while ((pos_bus = toma_campo(campo, buffreg, pos_bus, long_reg)) > 0)
            printf("\t%s\n", campo);
    } else
        printf("\n\nNo se encontro el registro. \n");
}

