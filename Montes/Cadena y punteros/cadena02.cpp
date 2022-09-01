/*
Dado una cadena, cuya longitud máxima es de 80 caracteres, y utilizando sólo sintaxis de
punteros, determinar si la cadena es o no un palíndromo. Ejemplo:
NEUQUEN → verdadero
CHUBUT → falso
2) Repita el ejercicio 1 utilizando funciones de la biblioteca <string.h>
*/

#include <iostream>
#include <string.h>
using namespace std;

#define MAX_CHARS 80

void leer(char palabra[MAX_CHARS + 1]);
bool esPolindromo(char letra[MAX_CHARS + 1]);
int contarCaracteres(char palabra[MAX_CHARS + 1]);
int main()
{

    char palabra[MAX_CHARS + 1] = " ";

    printf("Ingrese la palabra a analizar: \n");
    leer(palabra);

    if (esPolindromo(palabra))
    {
        printf("La palabra %s es palindromo.\n", palabra);
    }
    else
    {
        printf("La palabra %s no es palindromo.\n", palabra);
    }
    system("pause");
    return 0;
}

void leer(char palabra[MAX_CHARS + 1])
{
    scanf("%s", palabra);
}

int contarCaracteres(char palabra[MAX_CHARS + 1])
{
    return strlen(palabra);
}

void darVueltaPalabra(char palabra[MAX_CHARS + 1], char inversa[MAX_CHARS + 1])
{

    int ultimo = contarCaracteres(palabra) - 1;
    int i = 0;
    while (i <= ultimo)
    {
        inversa[i]= palabra[ultimo - i] ;
        i++;
    }
    inversa[ultimo + 1] = '\0';
    return;
}

bool esPolindromo(char palabra[MAX_CHARS + 1])
{
    bool polindromo;
    char inversa[MAX_CHARS + 1];
    darVueltaPalabra(palabra, inversa);
    if (strcmp(palabra, inversa) == 0)
    {
        polindromo = true;
    }
    else
    {
        return polindromo = false;
    }
    return polindromo;
}