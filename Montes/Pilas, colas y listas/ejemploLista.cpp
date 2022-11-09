#include <iostream>
#include "string.h"
using namespace std;

#define MAX_BUFFER 250

typedef struct Alumno
{
    char apellidoNombre[36];
    int legajo;
    char division;
} ST_DATO, ST_ALUMNO;

typedef struct Nodo
{
    ST_DATO dato;
    Nodo *siguiente;
} ST_NODO;



// Funciones de Listas
void create(ST_NODO **lista)
{
    *lista = NULL;
    return;
}

bool isEmpty(ST_NODO *lista)
{
    return lista == NULL;
}

ST_NODO *insertInFront(ST_DATO valor, ST_NODO **lista)
{
    ST_NODO *nodo = (ST_NODO *)malloc(sizeof(ST_NODO));
    nodo->dato = valor;
    nodo->siguiente = *lista;

    *lista = nodo;
    return nodo;
}

ST_NODO *insertAtEnd(ST_DATO valor, ST_NODO **lista)
{
    ST_NODO *nodo = (ST_NODO *)malloc(sizeof(ST_NODO));
    nodo->dato = valor;
    nodo->siguiente = NULL;

    if (isEmpty(*lista))
    {
        *lista = nodo;
    }
    else
    {
        ST_NODO *listaAux = *lista;
        while (listaAux->siguiente != NULL)
        {
            listaAux = listaAux->siguiente;
        }
        listaAux->siguiente = nodo;
    }

    return nodo;
}

ST_NODO *insertOrdered(ST_DATO valor, ST_NODO **lista)
{
    ST_NODO *nodo = (ST_NODO *)malloc(sizeof(ST_NODO));
    nodo->dato = valor;
    nodo->siguiente = NULL;

    ST_NODO *listaAux = *lista;
    ST_NODO *nodoAnt = NULL;
    while (listaAux != NULL && listaAux->dato.division < valor.division)
    {
        nodoAnt = listaAux;
        listaAux = listaAux->siguiente;
    }

    if (nodoAnt == NULL)
    {
        *lista = nodo;
    }
    else
    {
        nodoAnt->siguiente = nodo;
    }

    nodo->siguiente = listaAux;
    return nodo;
}

ST_NODO *insertWithoutDuplicate(ST_DATO valor, ST_NODO **lista)
{
    ST_NODO *nodo = search(*lista, valor);
    if (nodo == NULL)
    {
        nodo = insertOrdered(valor, lista);
    }

    return nodo;
}

void clearList(ST_NODO **lista)
{
    ST_NODO *aux = NULL;
    while (*lista != NULL)
    {
        aux = *lista;
        *lista = (*lista)->siguiente;
        free(aux);
    }
}

ST_NODO *search(ST_NODO *lista, ST_DATO valor)
{
    ST_NODO *listaAux = lista;
    while (listaAux != NULL && listaAux->dato.legajo != valor.legajo)
    {
        listaAux = listaAux->siguiente;
    }
    return listaAux;
}

ST_DATO deleteFirst(ST_NODO **lista)
{
    ST_NODO *nodoAux = *lista;
    *lista = (*lista)->siguiente;
    ST_DATO dato = nodoAux->dato;
    free(nodoAux);
    return dato;
}

void sort(ST_NODO **lista)
{
    ST_NODO *listaAux;
    create(&listaAux);
    ST_DATO dato;
    while (*lista != NULL)
    {
        dato = deleteFirst(lista);
        insertOrdered(dato, &listaAux);
    }

    *lista = listaAux;
}

int count(ST_NODO *listaAux)
{
    int cant = 0;
    while (listaAux != NULL)
    {
        listaAux = listaAux->siguiente;
        cant++;
    }

    return cant;
}

void print(ST_NODO *listaAux)
{
    while (listaAux != NULL)
    {
        int key = listaAux->dato.division;
        printf("DIVISION: %d\n", key);
        while (listaAux != NULL && key == listaAux->dato.division)
        {
            printf("%d - %s\n", listaAux->dato.legajo, listaAux->dato.apellidoNombre);
            listaAux = listaAux->siguiente;
        }
        printf("\n");
    }
}

