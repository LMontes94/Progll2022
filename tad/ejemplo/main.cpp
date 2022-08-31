#include <iostream>
#include "cuadrado.h"

using namespace std;

int main()
{

    char tipoFigura;
    printf("Ingrese el tipo de figura (c, t, i,):\n");
    scanf("%c", &tipoFigura);

    switch (tipoFigura)
    {
    case 'c':
    {
        int lado = 0;
        printf("Ingrese un lado del cuadrado:");
        scanf("%d", &lado);
        Cuadrado cuadrado = cargarCuadrado(lado);
        printf("El area es: %f y el perimetro es %f\n\n", area(cuadrado), perimetro(cuadrado));
        break;
    }

    default:
        break;
    }

    system("pause");
    return 0;
}