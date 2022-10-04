/*
Desarrolle la funcion cuentaVocales que reciba una cadena de caracteres  y devuelve la
cantidad de vocales que posee la misma.
Restriccion: solo puede utilizar notacion de punteros. No puede utilizar funciones de las bibliotecas C/C++
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

int cuentaVocales(const char *palabra){
   int cantVocales = 0;
   int i = 0;
   while (*(palabra + i) != '\0')
   {
      if (*(palabra + i) == 'a' || *(palabra + i) == 'e' || *(palabra + i) == 'i' || *(palabra + i) == 'o' || 
      *(palabra + i) == 'u')
      {
        cantVocales++;
      }
   }
   return cantVocales;
}

int main()
{
    
    system("pause");
    return 0;
}