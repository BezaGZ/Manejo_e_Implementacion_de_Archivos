#include "arches.h"
#include <string.h>
#define LONG_REG 64
typedef char NODOLLAVE[30];
typedef char REGDATOS [LONG_REG +1];
static struct{
    short cont_reg;
    char relleno[30];
} encabezado;

main(){
    int fd_ent, fd_sal, i, cont_reg;
    char *calloc();
    REGDATOS *registros;
    NODOLLAVE *nodosllave;
    short *indice;

    fd_ent = toma_archent();
    fd_sal = toma_archsal();

    if(fd_ent < 0 || fd_sal < 0){
        printf("Programa terminado\n");
        exit(1);
    }

    cont_reg = encabezado.cont_reg;

    registros = (REGDATOS *) calloc(cont_reg, sizeof(REGDATOS));
    nodosllave = (NODOLLAVE *) calloc(cont_reg, sizeof(NODOLLAVE));
    indice = (short *) calloc(cont_reg, sizeof(short));
    
    if(registros == 0L || nodosllave == 0L || indice == 0L){
        printf("No se pudo asignar el espacio requerido\n");
        printf("El archivo es demasiado grande para\n");
        printf("clasificarse en memoria\n");
        exit(1);
    }

    for(i = 0; i < cont_reg; i++){
        read(fd_ent, registros[i], LONG_REG);
        extrae_llave(nodosllave[i], registros[i]);
        indice[i] = i;
    }

    clasif_shell(indice, nodosllave, cont_reg);

    for(i = 0; i < cont_reg; i++)
        write(fd_sal, registros[indice[i]], LONG_REG);

    close(fd_ent);
    close(fd_sal);
}

static toma_archent(){
    char nomarch[30];
    int fd;

    printf("Proporcione el nombre del archivo de entrada: ");
    gets(nomarch);
    if((fd = open(nomarch, LECTESCRIT)) < 0){
        printf("El archivo %s no puede abrirse\n", nomarch);
    }else{
        read(fd, &encabezado, sizeof(encabezado));
    }
    return(fd);
}

static toma_archsal(){
    char nomarch[30];
    int fd;

    printf("Proporcione el nombre del archivo de salida: ");
    gets(nomarch);
    if((fd = creat(nomarch, 0644/*MODOP*/)) < 0){
        printf("El archivo %s no puede crearse\n", nomarch);
    }else{
        write(fd, &encabezado, sizeof(encabezado));
    }
    return(fd);
}

static extrae_llave(llave, registro)
    REGDATOS registro;
    char llave[];
{
    int pos_bus;
    char nombre[30], apellido[30];

    pos_bus = 0;
    pos_bus = toma_campo(apellido, registro, pos_bus, LONG_REG);
    pos_bus = toma_campo(nombre, registro, pos_bus, LONG_REG);
    hazllave(apellido, nombre, llave);
}

#define CAMPO_LLAVE(i) nodosllave [indice[(i)]]
typedef char NODOLLAVE[30];

clasif_shell(indice, nodosllave, n)
    short indice[];
    NODOLLAVE nodosllave[];
    int n;
{
    int espacio, i, j;
    char *llave_ins;
    short subindice_ins;

    for(espacio = n >> 1; espacio > 0; espacio >>= 1){
        for(j = espacio; j < n; j++){
            llave_ins = CAMPO_LLAVE(j);
            subindice_ins = indice[j];
            for(i = j - espacio; i >= 0; i -= espacio){
                if(strcmp(CAMPO_LLAVE(i), llave_ins) <= 0)
                    break;
                indice[i + espacio] = indice[i];
            }
            indice[i + espacio] = subindice_ins;
        }
    }
}