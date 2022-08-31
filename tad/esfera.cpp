#include "esfera.h"
#define PI 3.14

Esfera cargarCirculo(int radio) {
    Esfera esfera;
    esfera.radio = radio;
    return esfera;
}

float area(Esfera esfera) {
    return 4*PI*(esfera.radio * esfera.radio);
}

float volumen(Esfera esfera) {
    return (4*PI*(esfera.radio*esfera.radio*esfera.radio))/3;
}