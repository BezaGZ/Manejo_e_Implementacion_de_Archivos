#include "arches.h"
#define campo_a_buffreg(br, cad) strcat(br, cad); strcat(br, DELIM_CAD);

char buffreg[TAM_MAX_REG +1];
char *solicitud[] = {
    "Digite un apellido, o <CR> para salir: ",
    "                               Nombre: ",
    "                            Direccion: ",
    "                               Ciudad: ",
    "                               Estado: ",
    "                           Cod. Post.: ",
    "\0"
};

main(){
    char respuesta[50];
    char nomarch[15];
    int fd, i;
    int long_reg;

    printf("Proporcione el nombre del archivo que quiere crear: ");
    gets(nomarch);

    if((fd = creat(nomarch, PMODE)) < 0){
        printf("No se pudo crear el archivo %s\n", nomarch);
        exit(1);
    }
    printf("\n\n%s", solicitud[0]);
    gets(respuesta);
    while(strlen(respuesta) > 0){
        buffreg[0] = '\0';
        campo_a_buffreg(buffreg, respuesta);
        for( i = 1; *solicitud[i] != '\0'; i++){
            printf("%s", solicitud[i]);
            gets(respuesta);
            campo_a_buffreg(buffreg, respuesta);
        }
        long_reg = strlen(buffreg);
        write(fd, &long_reg, 2);
        write(fd, buffreg, long_reg);
        printf("\n\n%s", solicitud[0]);
        gets(respuesta);
    }
    close(fd);
}