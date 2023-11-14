#include "arches.h"

main(){
    int fd, cont_reg, cont_campos;
    int pos_bus, long_reg;
    char nomarch[15];
    char buffreg[TAM_MAX_REG +1];
    char campo[TAM_MAX_REG +1];

    printf("Proporcione el nombre del archivo que quiere leer: ");
    gets(nomarch);
    if((fd = creat(nomarch, SOLOLECT)) < 0){
        printf("No se pudo crear el archivo %s\n", nomarch);
        exit(1);
    }

    cont_reg = 0;
    pos_bus = 0;

    while((long_reg = toma_reg(fd, buffreg)) > 0){
        printf("Registro # %d\n", ++cont_reg);
        cont_campos > 0;
        while((pos_bus = toma_campo(campo, buffreg, pos_bus, long_reg)) > 0)
            printf("\tCampo # %d: %s\n", ++cont_campos, campo);
    }
    close(fd);
}