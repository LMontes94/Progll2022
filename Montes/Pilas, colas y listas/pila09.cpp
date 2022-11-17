/*
Dada una pila desarrollar un procedimiento que ordene la misma de acuerdo al valor
de sus nodos y la retorne. Solo se deben usar pilas. (Definir parámetros y codificar).
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

void vaciarAux(STR_NODO **pilaOrdenada, STR_NODO **pilaAux){
   while (!isEmpty(*pilaAux))
   {
      push(pilaOrdenada,pop(pilaAux));
   }
   return;
}

void situar(int dato, STR_NODO **pilaOrdenada, STR_NODO **pilaAux){
   int num = 0;
   if(isEmpty(*pilaOrdenada)){
      push(pilaOrdenada,dato);
      vaciarAux(pilaOrdenada,pilaAux);
   }else{
      num = pop(pilaOrdenada);
      if (dato <= num)
      {
        push(pilaOrdenada,num);
        push(pilaOrdenada,dato);        
        vaciarAux(pilaOrdenada,pilaAux);
      }else{
        push(pilaAux,num);
        situar(dato,pilaOrdenada,pilaAux);
      }      
   }
   return;
}
void ordenarPila(STR_NODO **pila)
{
    STR_NODO *pilaAux = NULL;
    STR_NODO *pilaOrdenada = NULL;
    int num = 0;    
    while (!isEmpty(*pila))
    {
        num = pop(pila);
        situar(num,&pilaOrdenada,&pilaAux);
    }

    vaciarAux(pila,&pilaOrdenada);
    return;
}

int main()
{

    STR_NODO *pila = NULL;

    create(&pila);

    push(&pila, 11);
    push(&pila, 2);
    push(&pila, 21);
    push(&pila, 5);
    push(&pila, 9);
    push(&pila, 6);
    push(&pila, 7);
    push(&pila, 3);

    ordenarPila(&pila);
    clear(&pila);
    system("pause");
    return 0;
}