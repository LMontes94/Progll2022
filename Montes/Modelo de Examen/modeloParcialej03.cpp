/*
Ejercicio 3
Se dispone del archivo de texto binarios.txt el cual posee en cada línea números codificados
en sistema binario (sólo ceros y unos). Cada número tendrá una longitud máxima de 31
caracteres y están todos los caracteres.
Se solicita generar el archivo binario decimales.dat el cual contendrá el número decimal
equivalente.
Ejemplo:
10101 -> genera 21
10001 -> genera 17
*/
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

int obtenerDecimal(const char *bin)
{
    int dec = 0;
    for (int i = 0; i < 31; i++)
    {
        dec += (bin[i - 30] - '0') * pow(2, 30 - i);
    }
    return dec;
}

int main()
{

    FILE *pTxt = NULL;
    pTxt = fopen("binarios.txt", "r");
    FILE *pBin = NULL;
    pBin = fopen("decimales.dat", "wb");

    char cadena[31];
    while (fgets(cadena, 32, pBin))
    {
        int decimal = obtenerDecimal(cadena);
        fwrite(&decimal, sizeof(decimal), 1, pBin);
    }

    system("pause");
    return 0;
}