/*
Realizar un programa que presente un menu al usuario con las siguientes figuras geométricas:
* Cuadrado
* Circulo
* Triángulo (equilatero)
* Pentágono
* Esfera
* Cilindro

Según la opción ingresada solicitar al usuario los datos necesarios para calcular el área, perímetro
y volumen según corresponda

Realizar el programa utilizando funciones y construir los TAD que considere necesarios

* Realizar la lectura y escritura por consola utilizando nuestros nuevos amigos printf y scanf en lugar de cin y cout
*/

#include <iostream>
#include "figurasGeometricas.h"
using namespace std;

void menu(int &opcion);
int main()
{
    int opcion = 0;
    int salida = 7;
    int lado = 0;
    int radio = 0;
    int altura = 0;
    while (opcion != salida)
    {
        menu(opcion);
        switch (opcion)
        {
        case 1:
        {
            printf("Ingrese un lado del cuadrado:");
            scanf("%d", &lado);
            Cuadrado cuadrado = cargarCuadrado(lado);
            printf("El area es: %f y el perimetro es %f\n\n", area(cuadrado), perimetro(cuadrado));
        break;
        }       
        case 2:
        {
            printf("Ingrese el radio del circulo:");
            scanf("%d", &radio);
            Circulo circulo = cargarCirculo(radio);
            printf("El area es: %f y el perimetro es %f\n\n", area(circulo), perimetro(circulo));
        break;
        }       
        case 3:
        {
            printf("Ingrese un lado del Triangulo equilatero:");
            scanf("%d", &lado);
            Triangulo triangulo = cargarTriangulo(lado);
            printf("El area es: %f y el perimetro es %f\n\n", area(triangulo), perimetro(triangulo));
            break;
        }
        case 4:
        {
            printf("Ingrese un lado del Pentagono:");
            scanf("%d", &lado);
            Pentagono pentagono = cargarPentagono(lado);
            printf("El area es: %f y el perimetro es %f\n\n", area(pentagono), perimetro(pentagono));
            break;
        }    
        case 5:
        {
            printf("Ingrese el radio de la esfera:");
            scanf("%d", &radio);
            Esfera esfera = cargarEsfera(radio);
            printf("El area es: %f y el volumen es %f\n\n", area(esfera), volumen(esfera));
            break;
        }    
        case 6:
        {
            printf("Ingrese el radio del clilindro: ");
            scanf("%d", &radio);
            printf("Ingrese la altura del cilindro:");
            scanf("%d", &altura);
            Cilindro cilindro = cargarCilindro(radio, altura);
            printf("El area es: %f y el volumen es %f\n\n", area(cilindro), volumen(cilindro));
            break;
        }    
        default:
            printf("Selecciono una opcion incorrecta");
            break;
        }
    }
    printf("Cerrando aplicacion....");
    return 0;
}

void menu(int &opcion)
{

    printf("          Figuras Geometricas\n");
    printf("  1- *Cuadrado\n");
    printf("  2- *Circulo\n");
    printf("  3- *Triángulo (equilatero)\n");
    printf("  4- *Pentágono\n");
    printf("  5- *Esfera\n");
    printf("  6- *Cilindro\n");
    printf("  7- *Salir\n");
    scanf("%d", opcion);
    return;
}