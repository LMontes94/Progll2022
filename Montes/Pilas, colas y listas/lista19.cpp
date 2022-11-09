/*
19. Dada una lista (nodo = registro + puntero), desarrollar y codificar una función que
devuelva la cantidad de nodos que tiene.
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
int deleteFist(STR_NODO **lista) {
    int dato = (*lista)->dato;
    STR_NODO *aux = *lista;
    *lista = (*lista)->siguiente;
    free(aux);
    return dato;
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
    create(&lista);

    int valor = 0;
    printf("Ingrese el valor (0 para terminar)\n");
    scanf("%d", &valor);

    while (valor != 0)
    {
        insertOrdered(valor, &lista);
        printf("Ingrese el valor (0 para terminar)\n");
        scanf("%d", &valor);
    }

    int contador = 0;
    contador = count(lista);
    printf("La lista tiene %d de nodos \n", contador);

    clearList(&lista);

    system("pause");
    return 0;
}
