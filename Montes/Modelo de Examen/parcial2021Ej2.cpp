/*
 Desarrolle una funcion validaTelefono que reciba una cadena de caracteres y devuelve treu o false
 si la cadena recibida es o no un nro de telefono con el formato esperado.
 un nro de telefono valido posee + <cod_pais> - <cod_area>- <nro_telefono>
   .cod_pais, cod_area, nro_telefono deben ser digitos.
   .Como maximo entre cod_area y nro_telefono deben sumar 8 digitos.
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
        if (!isdigit(buf[i]))
        {
            return false;
        }
        i++;
    }
    return true;
}

int charsMaxima(const char *codArea,const char *nroTelefono){
   char *telefono;
   strcpy(telefono,codArea);
   strcat(telefono,nroTelefono);
   int i = 0;
   while (*(telefono + i) != '\0')
   {
      i++;
   }   
  return i;
}
bool validaTelefono(const char *cad)
{
    char buffer[20];
    strcpy(buffer, cad);
    char codPais[4];
    int i = 0;
    char codArea[4];
    char nroTelefono[9];
    char *chars = strchr(buffer, '+');
    printf("%d",chars-buffer+1);
    if ( chars != NULL && (chars-buffer) == 0)
    {

        if (strchr(buffer, '-') != NULL && strchr(buffer, '-') > strchr(buffer, '+'))
        {
            strtok(buffer, "+");
            strcpy(codPais, strtok(buffer, "-"));
            strcpy(codArea, strtok(NULL, "-"));
            strcpy(nroTelefono, strtok(NULL, "\n"));
            if (codPais != NULL)
            {
                if (validacaract(codPais))
                {
                    if (codArea != NULL)
                    {
                        if (validacaract(codArea))
                        {
                            if (nroTelefono != NULL)
                            {
                                if (validacaract(nroTelefono))
                                {
                                    if (charsMaxima(codArea,nroTelefono) < 12)
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
    }

    return false;
}

int main()
{
    char telefono[18] = {"+54-911-25480810"};

    if (validaTelefono(telefono))
    {
        printf("Es un numero de telefono valido \n");
    }
    else
    {
        printf("No es un numero de telefono valido \n");
    }

    system("pause");
    return 0;
}