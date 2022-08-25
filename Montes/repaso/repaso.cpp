/*
1) Desarrollar un algoritmo que defina un vector de 10 posiciones y...
    a) Asigne a cada una de las posiciones el valor que resulta de: posición_actual x
       posición_anterior.
    b) Imprimir en pantalla la posición y su valor.
    c) Invertir el orden del vector e imprimir por pantalla la posición y su valor.
*/

#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int vector[10];
    for (int i = 0; i < 10; i++)
    {
       vector[i] = i+1;
        
      cout << i << vector[i] << endl;  

    }
    
    for (int i = 0; i < 10; i++)
    {
        if (i != 0)
        {
            vector[i] = vector[i] * vector[i-1];
        }
        cout << i << vector[i] << endl;  
    }
    
    for (int i = 9; i >= 0; i--)
    {
        cout << i << vector[i] << endl;
    }
    
    return 0;
}