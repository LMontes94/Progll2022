/*
Dado un archivo de registros de alumnos ARCHA sin ningún orden donde cada
registro contiene: a) Apellido y Nombre del alumno (34 caracteres) b) Número de
legajo (6 dígitos) c) División asignada (3 dígitos) Se debe desarrollar el algoritmo y
codificación del programa que imprima el listado de alumnos por división ordenado
por división y número de legajo crecientes, a razón de 55 alumnos por hoja.
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

STR_NODO *insertOrdered(STR_ALUMNO valor, STR_NODO **lista)
{
    STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->siguiente = NULL;

    STR_NODO *listaAux = *lista;
    STR_NODO *nodoAnt = NULL;
    while (listaAux != NULL && listaAux->dato.division < valor.division && listaAux->dato.legajo < valor.legajo)
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
        int key = listaAux->dato.division;
        printf("DIVISION: %d \n", key);
        while (listaAux != NULL && key == listaAux->dato.division)
        {
            printf("%d - %s \n ", listaAux->dato.legajo, listaAux->dato.apNom);
            listaAux = listaAux->siguiente;
        }
        printf("\n");
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
int count(STR_NODO *listaAux) {
    int cant = 0;
    while(listaAux != NULL) {
        listaAux = listaAux->siguiente;
        cant++;
    }
    return cant;
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

    FILE *pAlu = NULL;
    pAlu = fopen("ARCHA.dat", "rb+");

    STR_NODO *lista = NULL;
    create(&lista);

    STR_ALUMNO alumni;
    fread(&alumni, sizeof(STR_ALUMNO), 1, pAlu);

    while (!feof(pAlu))
    {
        insertOrdered(alumni, &lista);
        fread(&alumni, sizeof(STR_ALUMNO), 1, pAlu);
    }

    print(lista);
    clearList(&lista);

    system("pause");
    return 0;
}