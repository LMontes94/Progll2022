/*
Dada una pila y dos valores X e I, desarrollar un procedimiento que inserte el valor X
en la posición I de la pila si es posible. (Definir parámetros y codificar).
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

void cambiarValores(STR_NODO **pila,int valor,int valor2){
  
  STR_NODO *aux = NULL;
  
  return;
}
int main()
{

    STR_NODO *pila = NULL;
    STR_NODO *pilaAux = NULL;
    create(&pila);
    create(&pilaAux);

    push(&pila, 1);
    push(&pila, 2);
    push(&pila, 3);
    push(&pila, 4);
    push(&pila, 5);
    push(&pila, 6);

    int valor;
    int valor2;
    printf("Ingresar el valor a agregar a la pila: \n");
    scanf("%d", &valor);
    printf("Ingresar el valor a agregar a la pila: \n");
    scanf("%d", &valor2);
   
    cambiarValores(&pila,valor,valor2);
    clear(&pila);
    system("pause");
    return 0;
}