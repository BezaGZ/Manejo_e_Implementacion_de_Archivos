hazllave(apellido, nombre, cad)
    char apellido[], nombre[], cad[];
{
    int longap, longnom;

    longap = cadespac(apellido); // longap es una funcion que devuelve la longitud de la cadena.
    strcpy(cad, apellido);
    cad[longap++] = ' '; // cad hace referencia a la cadena que se le pasa como parametro.
    cad[longap] = '\0';
    longnom = cadespac(nombre); // longnom es una funcion que devuelve la longitud de la cadena.
    strcat(cad, nombre); // strcat es una funcion que concatena dos cadenas.
    mayusculas(cad);
    return(longap + longnom); // devuelve la longitud de la cadena.
}