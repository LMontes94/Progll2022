/*
8) Utilizando la función gets, leer de la entrada estándar dos líneas de longitud máxima 80
caracteres cada una. Se pide generar y devolver la cadena que surge como producto de
la intersección de las palabras de ambas líneas. Ejemplo:
        línea 1: El fútbol es un deporte que se juega con una pelota redonda.
        línea 2: El rugby es un deporte que se juega con una pelota ovalada.
        salida: El es un deporte que se juega con una pelota.
*/
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define MAX_CHARS 80

int longitudPalabra(const char *palabra){

return strlen(palabra);
}



int main(){

char cadena1[MAX_CHARS+1];
char cadena2[MAX_CHARS+1];
char cadenafin[MAX_CHARS+1];

printf("Ingrese la oracion: ");
gets(cadena1);
printf("Ingrese la oracion 2: ");
gets(cadena2);


bool flag= false;
bool flag2= false;

char *palabra1=NULL;
palabra1=(char*)malloc(sizeof(MAX_CHARS+1));
char *palabra2=NULL;
palabra2=(char*)malloc(sizeof(MAX_CHARS+1));

palabra1=strtok(cadena1," ");
palabra2=strtok(cadena2," ");

while (palabra1!=NULL && palabra2!=NULL)
{
    if (strcmp(palabra1,palabra2)==0 && flag==0)
    {
        strcpy(cadenafin,palabra1);
        flag=true;
        flag2=true;
    }
    else if (strcmp(palabra1,palabra2)==0 && flag==1)
    {
        strcat(cadenafin,palabra1);        
    } 

    palabra1 = strtok(NULL, " ,.-");
    palabra2 = strtok(NULL, " ,.-");
}
if(flag2==0)
{
    strcpy(cadenafin,"Las cadenas no coincidian.");
}


printf("Cadena Final: %s \n",cadenafin);


    system("pause");
    return 0;
}