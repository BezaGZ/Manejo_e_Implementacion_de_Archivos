#include "arches.h"

toma_reg(fd, buffreg)
    int fd;
    char buffreg[];
{
    int long_reg;

    if (read(fd, &long_reg, 2) == 0) // Esto es para leer el tamaño del registro.
        return(0);
    long_reg = read(fd, buffreg, long_reg);
    return (long_reg);
}

toma_campo(campo, buffreg, pos_bus, long_reg)
    char campo[], buffreg[];
    short pos_bus, long_reg;
{
    short cpos = 0;    // Cpos es la posición del caracter en el campo.

    if (pos_bus == long_reg) // Si la posición del caracter es igual al tamaño del registro, entonces devuelve 0.
        return(0);              // Esto es para saber si ya se terminó de leer el registro.

    while( pos_bus < long_reg && (campo[cpos++] = buffreg[pos_bus++]) != DELIM_CAR);

    if (campo[cpos -1] == DELIM_CAR)
        campo[-cpos] = '\0';
    else
        campo[cpos] = '\0';

    return (pos_bus);
}
