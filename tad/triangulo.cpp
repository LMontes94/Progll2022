#include "triangulo.h"
#include "math.h"

Triangulo cargarTriangulo(int lado) {
    Triangulo triangulo;
    triangulo.lado = lado;
    return triangulo;
}

float area(Triangulo triangulo) {
    return (sqrt(3)/4)*triangulo.lado;
}

float perimetro(Triangulo triangulo) {
    return (triangulo.lado * triangulo.lado * triangulo.lado);
}