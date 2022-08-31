#include "circulo.h"
#define PI 3.14

Circulo cargarCirculo(int radio) {
    Circulo circulo;
    circulo.radio = radio;
    return circulo;
}

float area(Circulo circulo) {
    return PI*(circulo.radio * circulo.radio);
}

float perimetro(Circulo circulo) {
    return 2*PI*circulo.radio;
}