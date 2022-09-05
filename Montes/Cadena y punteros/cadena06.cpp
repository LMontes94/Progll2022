/*
6) Utilizando la función gets, leer de la entrada estándar una línea de longitud máxima 80
caracteres. Utilizando sólo sintaxis de punteros determinar:
    a) ¿Cuántas palabras conforman la línea leída?
    b) ¿Cuál es la palabra de longitud máxima y cuántos caracteres posee?
    c) Repita el punto a) y b) utilizando la funciones strtok y strlen
*/

#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_CHARS 80
int longitudPalabra(const char *palabra);
char *separador(char *oracion,int &i);
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
    printf("Palabra con mas longitud es: %s\n",palabraMas);
    maxPalabra = longitudPalabra(palabraMas);
    printf("y contiene %d caracteres\n",maxPalabra);
    system("pause");
    return 0;
}

int longitudPalabra(const char *palabra)
{
    int longitud = 0;
    while (*(palabra++))
    {
        longitud++;
    }
    return longitud;
}
char *separador(char *oracion, int &i)
{
    char *palabra = NULL;
    palabra = (char *)malloc(sizeof(MAX_CHARS + 1));
    int ultima = longitudPalabra(oracion);
    int j = 0;
    while (*(oracion + i) != '\0')
    {
        if (*(oracion + i) == ' ')
        {
            *(palabra + j) = '\0';
            return palabra;
        }
        *(palabra + j) = *(oracion + i);
        i++;
        j++;
    }
    *(palabra + i) = '\0';
    return palabra;
}

char *maxChars(char *oracion)
{
    char *palabra = NULL;
    palabra = (char *)malloc(sizeof(MAX_CHARS + 1));
    char *palabraMas = NULL;
    palabraMas = (char *)malloc(sizeof(MAX_CHARS + 1));
    int i = 0;
    int longPalabra = 0;
    int maxPalabra = 0;
    int ultima = longitudPalabra(oracion);
    while (i < ultima)
    {
        palabra = separador(oracion,i);
        longPalabra = longitudPalabra(palabra);
        if (longPalabra > maxPalabra)
        {
            maxPalabra = longPalabra;
            palabraMas = palabra;
        }

        i++;
    }

    return palabraMas;
}