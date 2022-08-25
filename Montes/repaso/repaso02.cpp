/*
2) Implementar un sistema que solicite indefinidamente números por pantalla hasta que se
    ingrese un valor de corte e...
    a) Imprimir el número más alto.
    b) Imprimir el número más bajo.
    c) Imprimir el promedio.
*/

#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    float promedio;
    int dato;
    int max = 0, min = 0, sumatoria = 0, i = 0;
    printf("Ingrese numeros, si desea salir seleccione el 0\n");
    scanf("%d", &dato);
    while (dato != 0)
    {
        if (dato > max)
        {
            max = dato;
        }

        if (dato < min || min == 0)
        {
            min = dato;
        }

        sumatoria = sumatoria + dato;
        i++;
        printf("Ingrese numeros, si desea salir seleccione el 0\n");
        scanf("%d", &dato);
    }
     
     promedio = sumatoria/i;
     printf("El numero mayor ingresado fue: %d",max);
     printf("El numero menor ingresado fue: %d",min);
     printf("El promedio fue de: %f",promedio);
    return 0;
}