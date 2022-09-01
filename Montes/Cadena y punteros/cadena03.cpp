/*
Dada una cadena, cuya longitud máxima es de 15 caracteres, y utilizando sólo sintaxis de
punteros, determinar si la cadena forma una dirección de ip válida.
Ejemplo:
192.168.1.23 → verdadero
192.168.1.z → falso
10.250.244.255 → verdadero
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

#define MAX_CHARS 15
void leer(char *ip);
int contarCaracteres(char *ip);
bool sonTodosNros(char *ip);
bool esIp(char *ip);
int main()
{
    char *ip;
    ip = (char*) malloc(sizeof(MAX_CHARS+1));
    printf("Ingrese la ip: \n");
    leer(ip);

    if (esIp(ip))
    {
        printf("La IP %s es VALIDA.\n", ip);
    }
    else
    {
        printf("La palabra %s NO ES VALIDA.\n", ip);
    }
    system("pause");
    return 0;
}

void leer(char *ip)
{
    scanf("%s", ip);
    return;
}
int contarCaracteres(char *ip)
{
    return strlen(ip);
}
bool longuitudValida(char *ip)
{
    int ultimo = contarCaracteres(ip);
    if (ultimo > MAX_CHARS)
    {
        return false;
    }

    return true;
}
bool sonTodosNros(char *ip)
{

    int ultimo = contarCaracteres(ip);
    if (ultimo < 4)
    {
        for (int i = 0; i < ultimo; i++)
        {
            if (!isdigit(*(ip + i)))
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}
bool esIp(char *ip)
{
    char *auxIp;
    char *aux;
    int numIp;

    strcpy(aux, ip);

    if (longuitudValida(aux))
    {
        auxIp = strtok(aux, ".");
        while (auxIp != NULL)
        {
            if (sonTodosNros(auxIp))
            {
                numIp = atoi(auxIp);
                if (numIp < 0 || numIp > 255)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }

            auxIp = strtok(NULL, " ,.-");
        }
    }else{
        return false;
    }

    return true;
}