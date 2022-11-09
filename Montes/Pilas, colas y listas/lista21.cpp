/*
Dada una LISTA (nodo = registro + puntero), imprimirla en orden natural si tiene más
de 100 nodos, caso contrario imprimiría en orden inverso.
*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;

typedef struct Nodo
{
    int dato;
    Nodo *siguiente;

} STR_NODO;

typedef struct Nodo2
{
    int dato;
    Nodo2 *siguiente;

} STR_NODO2;

void create(STR_NODO **lista)
{
    *lista = NULL;
    return;
}

bool isEmpty(STR_NODO *lista)
{
    return lista == NULL;
}

STR_NODO *insertOrdered(int valor, STR_NODO **lista)
{
    STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->siguiente = NULL;

    STR_NODO *listaAux = *lista;
    STR_NODO *nodoAnt = NULL;
    while (listaAux != NULL && listaAux->dato < valor)
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

void print(STR_NODO *lista)
{
    STR_NODO *listaAux;
    listaAux = lista;
    while (listaAux != NULL)
    {

        printf("%d  \n ", listaAux->dato);
        listaAux = listaAux->siguiente;
    }
}

void clearList(STR_NODO **lista)
{
    STR_NODO *aux = NULL;
    while (*lista != NULL)
    {
        aux = *lista;
        *lista = (*lista)->siguiente;
        free(aux);
    }
}

int deleteFist(STR_NODO **lista)
{
    int dato = (*lista)->dato;
    STR_NODO *aux = *lista;
    *lista = (*lista)->siguiente;
    free(aux);
    return dato;
}

int count(STR_NODO *listaAux)
{
    int cant = 0;
    while (listaAux != NULL)
    {
        listaAux = listaAux->siguiente;
        cant++;
    }

    return cant;
}

void push(STR_NODO2 **pila, int valor)
{
    STR_NODO2 *nodo = (STR_NODO2 *)malloc(sizeof(STR_NODO2));
    nodo->dato = valor;
    nodo->siguiente = NULL;

    nodo->siguiente = *pila;
    *pila = nodo;
    return;
}

int pop(STR_NODO2 **pila)
{
    int dato = (*pila)->dato;
    STR_NODO2 *aux = *pila;
    *pila = (*pila)->siguiente;

    free(aux);
    return dato;
}

bool isEmptyP(STR_NODO2 *pila)
{
    return pila == NULL;
}

void clearP(STR_NODO2 **pila)
{

    while (!isEmptyP(*pila))
    {
        pop(pila);
    }
    *pila = NULL;
}

/*STR_NODO* insertAtEnd(int valor, STR_NODO **lista) {
    STR_NODO* nodo = (STR_NODO *) malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->siguiente = NULL;
    if(isEmpty(*lista)) {
        *lista = nodo;
    } else {
        STR_NODO *listaAux = *lista;
        while(listaAux->siguiente != NULL) {
            listaAux = listaAux->siguiente;
        }
        listaAux->siguiente = nodo;
    }
    return nodo;
}
STR_NODO* insertInFront(int valor, STR_NODO **lista) {
    STR_NODO* nodo = (STR_NODO *) malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->siguiente = *lista;
    *lista = nodo;
    return nodo;
}
STR_NODO *search(STR_NODO *lista, int valor) {
    STR_NODO *listaAux = lista;
    while(listaAux != NULL && listaAux->dato != valor) {
        listaAux = listaAux->siguiente;
    }
    return listaAux;
}
void sort(STR_NODO **lista) {
    STR_NODO *listaAux;
    create(&listaAux);
    int dato;
    while(*lista != NULL) {
        dato = deleteFist(lista);
        insertOrdered(dato, &listaAux);
    }
    *lista = listaAux;
}
STR_NODO* apareo(STR_NODO *listaA, STR_NODO *listaB) {
    STR_NODO * listaC;
    create(&listaC);
    while(listaA != NULL) {
        insertAtEnd(listaA->dato, &listaC);
        listaA = listaA->siguiente;
    }
    while(listaB != NULL) {
        insertAtEnd(listaB->dato, &listaC);
        listaB = listaB->siguiente;
    }
    return listaC;
}
*/

int main()
{
    STR_NODO *lista = NULL;
    STR_NODO2 *pila = NULL;
    create(&lista);
    for (int i = 0; i < 90; i++)
    {
        insertOrdered((i + 1), &lista);
    }

    int contador = 0;
    contador = count(lista);

    if (contador > 100)
    {
        print(lista);
    }
    else
    {
        while (!isEmpty(lista))
        {
            push(&pila, deleteFist(&lista));
        }
        while (!isEmptyP(pila))
        {
            printf("- %d \n", pop(&pila));
        }
    }

    clearList(&lista);
    clearP(&pila);

    system("pause");
    return 0;
}