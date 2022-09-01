/*
1) Declarar una variable entera, un vector de caracteres de diez posiciones y una variable con
soporte de decimales y ...
    a) Asignarle valores.
    b) Imprimir el valor de cada una.
    c) Imprimir la dirección de memoria de cada una.
*/

#include <iostream>
using namespace std;
int main()
{
    int i = 0;
    int entero;
    char caracteres[11] = "hola mundo";
    float decimales;

    entero = 10;
    decimales = 0.123;

    printf("El valor de la variable entera es: %d\n", entero);
    printf("El valor de la variable decimal es: %f\n", decimales);
    //printf("%10s\n", caracteres);

    while (*(caracteres + i) != '\0')
    {
        printf("%c", *(caracteres + i));
        i++;
    }
    printf("\n");
    printf("La posicion de memoria de la variable entera es: %p\n", &entero);
    printf("La posicion de memoria de la variable decimal es: %p\n", &decimales);
    printf("La posicion de la cadena de caracteres es: %p\n",&caracteres);
    system("pause");
    return 0;
}