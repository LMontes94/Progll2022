#include <iostream>
using namespace std;

struct ST_NODO
{
    int dato;
    ST_NODO *siguiente;
};

struct ST_COLA
{
    ST_NODO *frente;
    ST_NODO *fin;
};

void add(ST_COLA *cola, int dato)
{

    // creacion del nodo
    ST_NODO *nodo = (ST_NODO *)(malloc(sizeof(ST_NODO)));
    nodo->dato = dato;
    nodo->siguiente = NULL;

    // Insertamos el nuevo nodo en la cola
    if (cola->frente == NULL)
    {
        cola->frente = nodo;
    }
    else
    {
        cola->fin->siguiente = nodo;
    }
    cola->fin = nodo;
    return;
}

int remove(ST_COLA *cola)
{

    ST_NODO *aux = cola->frente;
    int valor = aux->dato;
    cola->frente = aux->siguiente;

    if (cola->frente == NULL)
    {
        cola->fin = NULL;
    }
    free(aux);
    return valor;
}

bool isEmpty(ST_COLA *cola){
   return cola->frente == NULL && cola->fin == NULL;
}

int main()
{

    ST_COLA cola;
    cola.frente = NULL;
    cola.fin = NULL;

    system("pause");
    return 0;
}