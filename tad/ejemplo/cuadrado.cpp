#include "cuadrado.h"

Cuadrado cargarCuadrado(int lado) {
    Cuadrado cuadrado;
    cuadrado.lado = lado;
    return cuadrado;
}

float area(Cuadrado cuadrado) {
    return cuadrado.lado * cuadrado.lado;
}

float perimetro(Cuadrado cuadrado) {
    return cuadrado.lado * 4;
}
