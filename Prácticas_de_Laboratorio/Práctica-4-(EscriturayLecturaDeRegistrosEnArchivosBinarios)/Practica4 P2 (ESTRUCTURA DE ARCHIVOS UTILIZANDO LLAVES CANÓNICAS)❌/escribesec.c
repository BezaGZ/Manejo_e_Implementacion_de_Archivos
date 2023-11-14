#include "arches.h"
#define saca_cad(fd, cad)   write((fd), (cad), strlen(cad))

main(){
    char nombre[30], apellido[30], direccion[30], ciudad[30];
    char estado[15], cp[9];
    char nomarch[15];
    int fd;

    printf("Proporcione el nombre del archivo que quiere crear: ");
    gets(nomarch);

    if((fd = creat(nomarch, PMODE)) < 0){
        printf("No se pudo crear el archivo %s\n", nomarch);
        exit(1);
    }
    printf("\n\nDigite un apellido, o <CR> para salir\n>>>");
    gets(apellido);
    while(strlen(apellido) > 0){
        printf("\n Nombre:");
        gets(nombre);
        printf(" Direccion:");
        gets(direccion);
        printf("    Ciudad:");
        gets(ciudad);
        printf("    Estado:");
        gets(estado);
        printf("Cod. Post.:");
        gets(cp);

        saca_cad(fd, apellido);
        saca_cad(fd, nombre);
        saca_cad(fd, direccion);
        saca_cad(fd, ciudad);
        saca_cad(fd, estado);
        saca_cad(fd, cp);

        printf("\n\nDigite un apellido, o <CR> para salir\n>>>");
        gets(apellido);
    }
    close(fd);
}