/*
Crear un algoritmo que solicite por pantalla, hasta que ingrese un valor de corte, nombre
y edad, considerando que...
    a) Modelar lo que ingresa el usuario en structs y almacenarlos en un vector
    (considerar 10 posiciones).
    b) Imprimir por pantalla los datos del vector.
    c) Ordenar el vector en base a la edad, de mayor a menor.
    d) Imprimir por pantalla los datos del vector ordenado.
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct ST_PERSONA
{
    string nombre = "";
    int edad;
};

int main()
{
    ST_PERSONA personas[10];
    ST_PERSONA persona;
    string key = "fin";
    int i = 0;
    printf("Ingrese nombre o fin si desea salir: \n");
    scanf("%s", &persona.nombre);
    
    if (persona.nombre == key)
    {
        printf("Cerrando programa....");
    }else{
      printf("Ingrese edad: \n");
        scanf("%d", &persona.edad);
        while (persona.nombre != key || i < 11)
        {
            personas[i].nombre = persona.nombre;
            personas[i].edad = persona.edad;
            i++;
            printf("Ingrese nombre o un 'fin' si desea salir: \n");
            scanf("%s", &persona.nombre);
        }  
    }

    return 0;
}