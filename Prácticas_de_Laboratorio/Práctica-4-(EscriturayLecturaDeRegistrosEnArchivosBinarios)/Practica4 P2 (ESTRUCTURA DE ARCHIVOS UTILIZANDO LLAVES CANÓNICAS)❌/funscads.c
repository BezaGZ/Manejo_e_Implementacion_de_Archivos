cadespace(cad) // cadespace es una funcion que devuelve la longitud de la cadena.
    char cad[];
{
    int i;

    for (i = strlen(cad) - 1; i >= 0 && cad[i] == ' '; i--)
        ;

    cad[++i] = '\0';
    return(i);
}

mayusculas(cadent, cadsal) // mayusculas es una funcion que convierte una cadena a mayusculas.
    char cadent[], cadsal[];
{
    while (*cadsal++ = (*cadent >= 'a' && *cadent <= 'z') ? *cadent & 0x5F : *cadent)
        cadent++;
}
