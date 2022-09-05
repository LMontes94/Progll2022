/*
7) Utilizando la función gets, leer de la entrada estándar una línea de longitud máxima 80
caracteres. Se pide generar y devolver la cadena que surge como producto de la
concatenación de aquellas palabras que terminan en una consonante y la siguiente

comienza con una vocal. Ejemplo:
Canción Elefante Lavarropas Avión → CanciónElefante LavarropasAvión
Pájaro Auto Flor Ventana → Pájaro Auto Flor Ventana
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
using namespace std;
#define MAX_CHARS 80
int contarCaracteres(char *palabra);
char *concaterPalabra(char *oracion);
int main()
{
    char oracion[MAX_CHARS + 1];
    int maxPalabra = 0;
    char *oracionConcatenada = NULL;
    oracionConcatenada = (char *)malloc(sizeof(MAX_CHARS + 1));

    printf("Ingresar una oracion: \n");
    gets(oracion);

    concaterPalabra(oracion);
    system("pause");
    return 0;
}

int contarCaracteres(char *palabra)
{
    return strlen(palabra);
}

bool esVocal(char letra)
{
    char letraMinuscula = tolower(letra);
    char vocales[] = "aeiou";
    int ultimo = contarCaracteres(vocales);
    int i;
    for (i = 0; i < ultimo; i++)
    {
        if (letraMinuscula == vocales[i])
        {
            return true;
        }
    }
    return false;
}

char *concaterPalabra(char *oracion)
{
    char *auxOracion = NULL;
    auxOracion = (char *)malloc(sizeof(MAX_CHARS + 1));
    char *palabra = NULL;
    palabra = (char *)malloc(sizeof(MAX_CHARS + 1));
    char *aux = NULL;
    aux = (char *)malloc(sizeof(MAX_CHARS + 1));
    char *oracionResul = NULL;
    oracionResul = (char *)malloc(sizeof(MAX_CHARS + 1));
    int longPalabra = 0;
    bool flag = true;
    bool primerPalabra = true;
    strcpy(auxOracion, oracion);
    palabra = strtok(auxOracion, " .");
    while (palabra != NULL)
    {
        longPalabra = contarCaracteres(palabra);
        printf("%c",*palabra+longPalabra);
        if (flag && !esVocal(*(palabra)))
        {
            strcpy(aux, palabra);
            flag = false;
        }

        longPalabra = contarCaracteres(aux);
        printf("%c",*(aux + longPalabra));
        if (!esVocal(*(aux + longPalabra)) && esVocal(*palabra))
        {
            if (primerPalabra && aux != NULL)
            {
                strcpy(oracionResul, aux);
                primerPalabra = false;
            }
            else
            {
                strcat(oracionResul, aux);
            }
            strcat(oracionResul, palabra);
            strcat(oracionResul, " ");
            flag = true;
            printf("%s\n", oracionResul);
        }

        palabra = strtok(NULL, " ,.-");
    }

    return oracionResul;
}