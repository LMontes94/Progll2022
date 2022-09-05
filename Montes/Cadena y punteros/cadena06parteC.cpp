/*
6) Utilizando la función gets, leer de la entrada estándar una línea de longitud máxima 80
caracteres. Utilizando sólo sintaxis de punteros determinar:
    a) ¿Cuántas palabras conforman la línea leída?
    b) ¿Cuál es la palabra de longitud máxima y cuántos caracteres posee?
    c) Repita el punto a) y b) utilizando la funciones strtok y strlen
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX_CHARS 80
int contarCaracteres(char *palabra);
char *maxChars(char *oracion);
int main()
{
    char oracion[MAX_CHARS + 1];
    int maxPalabra = 0;
    char *palabraMas = NULL;
    palabraMas = (char *)malloc(sizeof(MAX_CHARS + 1));

    printf("Ingresar una oracion: \n");
    gets(oracion);
    palabraMas = maxChars(oracion);
    printf("Palabra con mas longitud es: %s\n", palabraMas);
    maxPalabra = contarCaracteres(palabraMas);
    printf("y contiene %d caracteres\n", maxPalabra);

    free(palabraMas);
    system("pause");
    return 0;
}

int contarCaracteres(char *palabra)
{
    return strlen(palabra);
}

char *maxChars(char *oracion)
{
    char *auxOracion = NULL;
    auxOracion = (char *)malloc(sizeof(MAX_CHARS + 1));
    char *palabra = NULL;
    palabra = (char *)malloc(sizeof(MAX_CHARS + 1));
    char *palabraMas = NULL;
    palabraMas = (char *)malloc(sizeof(MAX_CHARS + 1));
    int i = 0;
    int longPalabra = 0;
    int maxPalabra = 0;
    int ultima = contarCaracteres(oracion);
    strcpy(auxOracion, oracion);
    palabra = strtok(auxOracion, " .");
    while (palabra != NULL)
    {
        longPalabra = contarCaracteres(palabra);
        if (longPalabra > maxPalabra)
        {
            maxPalabra = longPalabra;
            strcpy(palabraMas, palabra);
        }

        palabra = strtok(NULL, " ,.-");
    }

    return palabraMas;
}