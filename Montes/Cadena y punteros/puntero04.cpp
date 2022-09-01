/*
4) Declarar un struct que defina una variable del tipo vector de caracteres, llamada nombre, y otra
que sea del tipo entero, llamada edad y ...
    a) En la función main, asigne el valor “Kokumo” y “30” para nombre y edad respectivamente.
    b) Luego, invoque una función que reciba el struct por parámetro y que imprima el valor de
    ambas variables del struct.
    c) Dentro de esa misma función, cambie los valores de las variables en cuestión y muestre
    nuevamente sendos valores.
    d) De regreso en el main, e inmediatamente después de la llamada a la función, imprima los
    valores del struct; analice qué valores se imprimieron en pantalla.
*/
#include <iostream>
#include <string.h>
using namespace std;

struct ST_PERSONA
{
    char nombre[15];
    int edad;
};

void mostrarPersona(ST_PERSONA);
int main()
{
    ST_PERSONA persona;
    strcpy(persona.nombre,"Kokumo");
    persona.edad = 30;
    mostrarPersona(persona);
    printf("Nombre: %s\n",persona.nombre);
    printf("Edad: %d\n",persona.edad);
    
    system("pause");
    return 0;
}

void mostrarPersona(ST_PERSONA persona){
    
    printf("Nombre: %s\n",persona.nombre);
    printf("Edad: %d\n",persona.edad);
    
     strcpy(persona.nombre,"Lucas");
     persona.edad = 28;

     printf("Nombre: %s\n",persona.nombre);
    printf("Edad: %d\n",persona.edad);
    return;
}
