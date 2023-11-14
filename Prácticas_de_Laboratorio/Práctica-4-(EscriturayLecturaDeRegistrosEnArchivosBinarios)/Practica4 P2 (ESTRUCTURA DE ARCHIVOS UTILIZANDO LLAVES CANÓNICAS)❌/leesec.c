#include "arches.h"

main(){
    int fd, n;
    char cad[30];
    char nomarch[15];
    int cont_campos;

    printf("Proporcione el nombre del archivo que quiere leer: ");
    gets(nomarch);
    if((fd = creat(nomarch, SOLOLECT)) < 0){
        printf("No se pudo crear el archivo %s\n", nomarch);
        exit(1);
    }

    cont_campos = 0;
    while((n = leecampo(fd, cad)) > 0)
        printf("\tCampo # %3d: %s\n", ++cont_campos, cad);

    close(fd);
}

leecampo(fd, cad)
    int fd;
    char cad[];
{
    int i;
    char c;

    i = 0;
    while((read(fd, &c, 1)) > 0 && c != DELIM_CAR)
        cad[i++] = c;
    cad[i] = '\0'; // Cad funciona como un buffer el cual se llena con los caracteres leidos del archivo
    return(i);
}