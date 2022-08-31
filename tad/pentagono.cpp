#include "pentagono.h"
#include <cmath>

Pentagono cargarCirculo(int lado) {
    Pentagono pentagono;
    pentagono.lado = lado;
    return pentagono;
}

float anguloCentral(Pentagono pentagono){
   return(360/pentagono.lado);
}

float apotema(Pentagono pentagono){
   return pentagono.lado/(2*tan(anguloCentral(pentagono)/2));
}

float perimetro(Pentagono pentagono) {
    return 5*pentagono.lado;
}

float area(Pentagono pentagono) {
    return (perimetro(pentagono)*apotema(pentagono))/2;
}





