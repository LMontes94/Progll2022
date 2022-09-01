/*
Declarar una variable que sea puntero a un número entero y luego ...
    a) Imprimir por pantalla la dirección de memoria.
    b) Imprimir su valor.
    c) Asignar dinámicamente espacio en memoria.
    d) Imprimir nuevamente su valor.
    e) Imprimir el valor que se encuentra en el espacio asignado dinámicamente.
*/

#include <iostream>
using namespace std;
int main()
{
  
    int *ptrEntero = NULL;
    printf("Posicion de memoria del puntero %p valor actual %p\n", &ptrEntero, ptrEntero);
    ptrEntero = (int*) malloc(sizeof(int));

    printf("Valor actual del puntero %p\n", ptrEntero);
    *ptrEntero = 20;

    printf("El valor del contenido de la memoria asignada dinamicamente es: %d\n", *ptrEntero);

    free(ptrEntero);
    ptrEntero = NULL;
    
    system("pause");
    return 0;
}