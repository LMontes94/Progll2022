/*
Dada una pila y un valor I, desarrollar un procedimiento que elimine los 2 primeros
nodos de la pila y deje el valor I como primero. (Definir parámetros y codificar).
*/

#include <iostream>
using namespace std;

struct STR_NODO
{
    int dato;
    STR_NODO *ste;
};

void create(STR_NODO **pila)
{
    *pila = NULL;
}

bool isEmpty(STR_NODO *pila)
{
    return pila == NULL;
}

void push(STR_NODO **pila, int valor)
{
    STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    nodo->ste = *pila;
    *pila = nodo;
    return;
}

int pop(STR_NODO **pila)
{
    int dato = (*pila)->dato;
    STR_NODO *aux = *pila;
    *pila = (*pila)->ste;

    free(aux);
    return dato;
}

void clear(STR_NODO **pila)
{
    while (!isEmpty(*pila))
    {
        printf("%d->", pop(pila));
    }
    printf("NULL");
}

int main()
{

    STR_NODO *pila = NULL;

    create(&pila);
    
    push(&pila, 1);
    push(&pila, 2);
    
    int valor;
    printf("Ingresar el valor a agregar a la pila: \n");
    scanf("%d",&valor);
    
    pop(&pila);
    pop(&pila);
    push(&pila,valor);
    clear(&pila);
    system("pause");
    return 0;
}