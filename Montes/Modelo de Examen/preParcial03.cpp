/*
Se dispone de un vector de 10 posiciones donde cada posición contiene una lista. Cada nodo de cada lista
posee una letra (a - z).
Nodo 1      Nodo 2         Nodo 3
a Nodo 2      l Nodo 3      a NULL

Desarrolle el programa que utilizando una pila indique cuántas de estas forman un palíndromo
*/

#include <iostream>

using namespace std;
#define MAX_POSICIONES 10

typedef struct nodo
{
    char letra;
    struct nodo *ste;
} STR_NODO;

void create(STR_NODO **head)
{
    *head = NULL;
}

bool isEmpty(STR_NODO *head)
{
    return head == NULL;
}

void push(STR_NODO **head, char dato)
{
    STR_NODO *nodo = (STR_NODO *)(malloc(sizeof(STR_NODO)));
    nodo->letra = dato;
    nodo->ste = NULL;

    nodo->ste = *head;
    *head = nodo;

    return;
}

char pop(STR_NODO **head)
{
    char valor;
    (*head)->letra, valor;
    STR_NODO *aux = *head;
    *head = (*head)->ste;
    free(aux);
    return valor;
}

char deleteFirst(STR_NODO **list)
{
    STR_NODO *nodoAux = *list;
    *list = (*list)->ste;
    char dato = nodoAux->letra;
    free(nodoAux);
    return dato;
}

bool esPalindromo(STR_NODO *pila, STR_NODO *lista)
{
    while (!isEmpty(pila) && !isEmpty(lista))
    {
        char letra = pop(&pila);
        if (letra != lista->letra)
        {
            return false;
        }
        lista = lista->ste;
    }
    return true;
}

int main()
{

    STR_NODO listas[10];
    STR_NODO *pila;

    int palindromo = 0;

    for (int i = 0; i < MAX_POSICIONES; i++)
    {
        STR_NODO *listaAux = &listas[i];
        while (!isEmpty(listaAux))
        {
            char letra = deleteFirst(&listaAux);
            push(&pila, letra);
        }
        if (esPalindromo(pila, &listas[i]))
        {
            palindromo++;
        }
    }

    if (palindromo > 0)
    {
        printf("En el vector hay %d palabras palidromas\n",palindromo);
    }else{
       printf("No hay palabras palindromas en el vector\n"); 
    }
    
    
    system("pause");
    return 0;
}