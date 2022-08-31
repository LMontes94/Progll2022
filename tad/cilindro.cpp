#include "cilindro.h"
#define PI 3.14

Cilindro cargarCirculo(int radio, int altura) {
    Cilindro cilindro;
    cilindro.radio = radio;
    cilindro.altura = altura;
    return cilindro;
}

float area(Cilindro cilindro) {
    return 2*PI*(cilindro.radio * cilindro.altura) + 2*PI*(cilindro.radio*cilindro.radio);
}

float volumen(Cilindro cilindro) {
    return (PI*(cilindro.radio*cilindro.radio)*cilindro.altura);
}