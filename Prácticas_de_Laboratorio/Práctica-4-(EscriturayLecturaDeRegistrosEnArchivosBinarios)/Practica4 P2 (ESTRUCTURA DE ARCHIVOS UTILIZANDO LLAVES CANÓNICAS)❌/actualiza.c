#include "arches.h"
#define LONG_REG 64
#define campo_a_buffreg(br, cad) strcat(br, cad); strcat(br, DELIM_CAD);

static char *solicitud[] = {"   Apellido: ",
                            "     Nombre: ",
                            "  Direccion: ",
                            "     Ciudad: ",
                            "     Estado: ",
                            "Cod. Post.: ",
                            " "
                           };
static int fd;
static struct{
    short   cont_reg;
    char    relleno[60]; 
} encabezado;

main(){
    int i, menu_elec, nrr;
    int byte_pos;
    char nomarch[15];
    long lseek();
    char buffreg[TAM_MAX_REG +1];

    printf("Proporcione el nombre del archivo que quiere crear: ");
    gets(encabezado.relleno);
    if((fd = open(nomarch, LECTESCRIT)) < 0){
        fd = creat(nomarch, PMODE);
        encabezado.cont_reg = 0;
        write(fd, &encabezado, sizeof(encabezado));
    }else{
        read(fd, &encabezado, sizeof(encabezado));
    }
    while((menu_elec == menu()) < 3){
        switch(menu_elec){
            case 1:
                printf("Proporcione la información del registro nuevo\n\n");
                pide_info(buffreg);
                byte_pos = encabezado.cont_reg * LONG_REG + sizeof(encabezado);
                lseek(fd, (long) byte_pos, 0); //Lseek es una función que sirve para mover el puntero de lectura/escritura.
                write(fd, buffreg, LONG_REG);
                encabezado.cont_reg++;
                break;
            case 2:
                nrr = pide_nrr();

                if(nrr >= encabezado.cont_reg){
                    printf("El numero de registro es demasiado grande\n");
                    printf("... se vuelve al menu ...");
                    break;
                }

                byte_pos = nrr * LONG_REG + sizeof(encabezado);
                lseek(fd, (long) byte_pos, 0);

                lee_y_muestra(); // Lee y muestra el registro
                if(cambio()){
                    printf("\n\nProporcione los valores revisados: \n\n");
                    pide_info(buffreg);
                    lseek(fd, (long) byte_pos, 0);
                    write(fd, buffreg, LONG_REG);
                }
                break;
        }
    }
    lseek(fd, 0L, 0); //Lseek es una función que sirve para mover el puntero de lectura/escritura.
    write(fd, &encabezado, sizeof(encabezado));
    close(fd);
}

static menu(){  // Función que muestra el menú.
    int elección;
    char respuesta[10];

    printf("\n\n\n\n        PROGRAMA DE ACTUALIZACIÓN DEL ARCHIVO\n");
    printf("\n\nUd. Puede elegir:\n\n");
    printf("\n1. Agregar un registro al final del archivo\n");
    printf("\n2. Extraer un registro para actualizarlo\n");
    printf("\n3. Salir del programa\n\n");
    printf("Proporcione el número de su elección: ");
    gets(respuesta);
    elección = atoi(respuesta);
    return(elección);
}

static pide_info(buffreg) // Función que pide la información del registro.
    char buffreg[];
{
    int con_campos, i;
    char respuesta[50];

    for(i = 0; i < LONG_REG; buffreg[i++] == '\0')

    for(i = 0; *solicitud[i] != '\0'; i++){
        printf("%s", solicitud[i]);
        gets(respuesta);
        campo_a_buffreg(buffreg, respuesta);
    }
}

static pide_nrr(){ // Función que pide el número relativo del registro.
    int nrr;
    char respuesta[10];

    printf("\n\nDigite el número relativo del registro\n");
    printf("\tque desee actualizar: ");
    gets(respuesta);
    nrr = atoi(respuesta);
    return(respuesta);
}

static lee_y_muestra(){ // Función que lee y muestra el registro.
    char buffreg[TAM_MAX_REG +1], campo[TAM_MAX_REG +1];
    int pos_bus, long_datos;

    pos_bus = 0;
    read(fd, buffreg, LONG_REG);

    printf("\n\n\n\nContenido del registro existente\n");

    buffreg[LONG_REG] = '\0';

    long_datos = strlen(buffreg);

    while((pos_bus = toma_campo(campo, buffreg, pos_bus, long_datos)) > 0)
        printf("\t%s\n", campo);
}

static cambio(){ // Función que pregunta si se desea modificar el registro.
    char respuesta[10];

    printf("\n\nDesea modificar este registro?\n");
    printf(" Conteste S o N, seguido por <ENTER>  ==>");
    gets(respuesta);
    mayusculas(respuesta,respuesta);
    return((respuesta[0] == 'S') ? 1 : 0);
}