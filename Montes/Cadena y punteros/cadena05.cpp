/*
5) Dada una cadena, cuya longitud máxima es de 80 caracteres, y utilizando sólo sintaxis de
punteros, devolver la cadena inversa.
    a) ¿De qué forma se modifica el ejercicio si se desea modificar la cadena recibida?
*/
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_CHARS 80
int longitudPalabra(const char *palabra);
void darVueltaPalabra(char *palabra, char *inversa);
int main()
{
    char palabra[MAX_CHARS + 1];
    char inversa[MAX_CHARS + 1];

    printf("Ingresar una palabra: \n");
    scanf("%s", &palabra);
    darVueltaPalabra(palabra, inversa);
    printf("La palabra dada vuelta: %s", inversa);
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

void darVueltaPalabra(char *palabra, char *inversa)
{

    int ultimo = longitudPalabra(palabra) - 1;
    int i = 0;
    while (i <= ultimo)
    {
        *(inversa + i) = *(palabra + (ultimo - i));
        i++;
    }
    *(inversa + (ultimo + 1)) = '\0';
    return;
}