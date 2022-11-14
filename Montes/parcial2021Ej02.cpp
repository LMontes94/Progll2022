/*
Dado una estructura del tipo:
● Valor
● PosicionSiguiente
Siguiendo los mismos lineamientos de los vistos para listas, pero utilizando un vector de MAX_ELEMENTOS posiciones,
realice el diagrama e implemente las operaciones:
a. insertarOrdenado,
b. insertarAlFrente
c. borrarPrimero
*/

#include <iostream>

using namespace std;
#define MAX_ELEMENTOS 10

struct STR_NODO
{
    int valor;
    STR_NODO *ste;
};

STR_NODO* insertOrdered(int valor, STR_NODO **lista) {
    STR_NODO* nodo = (STR_NODO *) malloc(sizeof(STR_NODO));
    nodo->valor = valor;
    nodo->ste = NULL;

    STR_NODO *listaAux = *lista;
    STR_NODO *nodoAnt = NULL;
    while(listaAux != NULL && listaAux->valor < valor) {
        nodoAnt = listaAux;
        listaAux = listaAux->ste;
    }

    if(nodoAnt == NULL) {
        *lista = nodo;
    } else {
        nodoAnt->ste = nodo;
    }

    nodo->ste = listaAux;
    return nodo;
}