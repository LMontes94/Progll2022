/*
22. Dadas dos listas LISTA y LISTB (nodo = registro + puntero), desarrollar y codificar
un procedimiento que genere otra lista LISTC por apareo del campo LEGAJO del
registro (define orden creciente en ambas). Nota: LISTA y LISTB dejan de ser útiles
después del apareo).
*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;

typedef struct Alumno
{
    char apNom[35 + 1];
    int legajo;
    int division;

} STR_DATO, STR_ALUMNO;

typedef struct Nodo
{
    STR_DATO dato;
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

STR_NODO *insertOrdered(STR_DATO valor, STR_NODO **lista)
{
    STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->siguiente = NULL;

    STR_NODO *listaAux = *lista;
    STR_NODO *nodoAnt = NULL;
    while (listaAux != NULL && listaAux->dato.legajo < valor.legajo)
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

STR_NODO *apareo(STR_NODO *listaA, STR_NODO *listaB)
{
    STR_NODO *listaC;
    create(&listaC);
    while (listaB != NULL)
    {
        insertOrdered(listaB->dato, &listaA);
        listaB = listaB->siguiente;
    }

    listaC = listaA;
    listaA = NULL;
    listaB = NULL;

    return listaC;
}

void print(STR_NODO *lista)
{
    STR_NODO *listaAux;
    listaAux = lista;
    while (listaAux != NULL)
    {
        printf("LISTA C \n");
        while (listaAux != NULL)
        {
            printf("-%d -%d -%s \n", listaAux->dato.legajo, listaAux->dato.division, listaAux->dato.apNom);
            listaAux = listaAux->siguiente;
        }
    }
}

/*
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
*/

int main()
{

    STR_NODO *lista = NULL;
    create(&lista);
    STR_NODO *listaB = NULL;
    create(&listaB);
    STR_NODO *listaC = NULL;
    create(&listaC);

    STR_ALUMNO alum;

    printf("Complete la Lista A \n");
    printf("Ingrese un Apellido (Fin para terminar):");
    scanf("%s", &alum.apNom);
    while (strcmp(alum.apNom, "Fin") != 0)
    {
        printf("Ingrese una division:");
        scanf("%d", &alum.division);

        printf("Ingrese una legajo:");
        scanf("%d", &alum.legajo);

        insertOrdered(alum, &lista);

        printf("Ingrese un Apellido (Fin para terminar):");
        scanf("%s", &alum.apNom);
    }

    printf("Complete la Lista B \n");
    printf("Ingrese un Apellido (Fin para terminar):");
    scanf("%s", &alum.apNom);
    while (strcmp(alum.apNom, "Fin") != 0)
    {
        printf("Ingrese una division:");
        scanf("%d", &alum.division);

        printf("Ingrese una legajo:");
        scanf("%d", &alum.legajo);

        insertOrdered(alum, &listaB);

        printf("Ingrese un Apellido (Fin para terminar):");
        scanf("%s", &alum.apNom);
    }

    listaC = apareo(lista, listaB);
    print(listaC);
    clearList(&lista);

    system("pause");
    return 0;
}