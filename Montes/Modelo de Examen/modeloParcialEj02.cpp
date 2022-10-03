/*
Ejercicio 2
Desarrolle la función validaEmail que reciba una cadena de caracteres y devuelve true o
false si la cadena recibida es o no una dirección de email válida.
Una dirección de email válida posee: <nombre> @ <dominio> . <extensión>
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

bool validacaract(char buf[256])
{
    int i = 0;
    while (buf[i] != '\0')
    {
        if (!isalpha(buf[i]))
        {
            return false;
        }
        i++;
    }
    return true;
}

bool validaEmail(const char *cad)
{
    char buffer[256];
    strcpy(buffer, cad);
    char nombre[256];
    int i = 0;
    bool nomb = true;
    char dom[256];
    bool domi = true;
    char ext[256];
    bool exten = true;

    if (strchr(buffer, '@') != NULL)
    {

        if (strchr(buffer, '.') != NULL && strchr(buffer, '.') > strchr(buffer, '@'))
        {
            strcpy(nombre, strtok(buffer, "@"));
            strcpy(dom, strtok(NULL, "."));
            strcpy(ext, strtok(NULL, "\n"));
            if (nombre != NULL)
            {
                nomb = validacaract(nombre);
                if (nomb == true)
                {
                    if (dom != NULL)
                    {
                        domi = validacaract(dom);
                        if (domi == true)
                        {
                            if (ext != NULL)
                            {
                                exten = validacaract(ext);
                                if (exten == true)
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

int main()
{
    char cadCaracteres[256] = {"arieltoma@gmail.com"};

    if (validaEmail(cadCaracteres))
    {
        printf("Es una direccion de email valida \n");
    }
    else
    {
        printf("No es una direccion de email valida \n");
    }

    system("pause");
    return 0;
}