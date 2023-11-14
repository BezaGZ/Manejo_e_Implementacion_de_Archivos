//
// Created by Bezaleel on 12/09/23.
//
#include "arches.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LONG_REG 64
typedef char NODOLLAVE[30];
typedef char REGDATOS [LONG_REG +1];
static struct{
    short cont_reg;
    char relleno[30];
} encabezado;

static int toma_archent();
static int toma_archsal();

static int cadespac();
static int hazllave();
static void clasif_shell();
static int toma_campo();
static void mayusculas();
static void extrae_llave();

int main(){
    int fd_ent, fd_sal, i, cont_reg;
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

    if(registros == 0L || nodosllave == 0L || indice == 0L){ //Sirve para verificar si se asigno el espacio requerido.
        printf("No se pudo asignar el espacio requerido\n");
        printf("El archivo es demasiado grande para\n");
        printf("clasificarse en memoria\n");
        exit(1);
    }

    for(i = 0; i < cont_reg; i++){ //Se lee el archivo de entrada.
        read(fd_ent, registros[i], LONG_REG);
        extrae_llave(nodosllave[i], registros[i]);
        indice[i] = i;
    }

    clasif_shell(indice, nodosllave, cont_reg);

    for(i = 0; i < cont_reg; i++) //Se escribe el archivo de salida.
        write(fd_sal, registros[indice[i]], LONG_REG);

    close(fd_ent);
    close(fd_sal);
    return(0);
}

static int toma_archent(){ //Esta funcion lee el archivo de entrada.
    char nomarch[30];
    int fd;

    printf("Proporcione el nombre del archivo de entrada: ");
    fgets(nomarch, 30, stdin);
    if((fd = open(nomarch, LECTESCRIT)) < 0){
        printf("El archivo %s no puede abrirse\n", nomarch);
        exit(1);
    }else{
        read(fd, &encabezado, sizeof(encabezado));
    }
    return(fd);
}

static int toma_archsal(){ //Esta funcion lee el archivo de salida.
    char nomarch[30];
    int fd;

    printf("Proporcione el nombre del archivo de salida: ");
    fgets(nomarch, 30, stdin);
    if((fd = creat(nomarch, PMODE/*0644MODOP*/)) < 0){
        printf("El archivo %s no puede crearse\n", nomarch);
    }else{
        write(fd, &encabezado, sizeof(encabezado));
    }
    return(fd);
}

#define CAMPO_LLAVE(i) nodosllave [indice[(i)]]
typedef char NODOLLAVE[30];

void clasif_shell(indice, nodosllave, n) //Esta funcion clasifica los subindices del arreglo indices[].
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

int toma_campo(campo, buffreg, pos_bus, long_reg) //Esta funcion toma un campo del registro.
        char campo[], buffreg[];
        short pos_bus, long_reg;
{
    short cpos = 0;     /*posicion en el arreglo "campo" */

    if (pos_bus == long_reg) /* si no hay mas campos que leer */
        return(0);              /*devuelve pos_bus de 0 */

    while( pos_bus < long_reg && (campo[cpos++] = buffreg[pos_bus++]) != DELIM_CAR);

    if (campo[cpos -1] == DELIM_CAR)
        campo[-cpos] = '\0';
    else
        campo[cpos] = '\0';

    return (pos_bus);

}

int cadespac(cad) //Esta funcion elimina los espacios en blanco de una cadena.
        char cad[];
{
    int i;

    for (i = strlen(cad) - 1; i >= 0 && cad[i] == ' '; i--)
        ;

    cad[++i] = '\0';
    return(i);
}

void mayusculas(cadent, cadsal) //Esta funcion convierte una cadena a mayusculas.
        char cadent[], cadsal[];
{
    while (*cadsal++ = (*cadent >= 'a' && *cadent <= 'z') ? *cadent & 0x5F : *cadent)
        cadent++;
}

int hazllave(apellido, nombre, cad) //Esta funcion crea una llave.
        char apellido[], nombre[], cad[];
{
    int longap, longnom;

    longap = cadespac(apellido);
    strcpy(cad, apellido);
    cad[longap++] = ' ';
    cad[longap] = '\0';
    longnom = cadespac(nombre);
    strcat(cad, nombre);
    mayusculas(cad, cad);
    return(longap + longnom);
}

static void extrae_llave(llave, registro) //Esta funcion extrae la llave de un registro.
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