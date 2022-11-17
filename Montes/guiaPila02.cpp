/*
Varias veces al día la asistente de un empresario deja en la recepción un conjunto
indeterminado de cartas que se van apilando en una bandeja; como todas deben ser
enviadas en el día, no hay necesidad de ordenarlas o de asignarle prioridad.
Cada una hora la recepcionista se encarga de tomar 5 cartas y las despachas; sin
embargo, como pueden acumularse muchas, ajusta la cantidad de cartas a enviar según
la hora:
- 14 hs: envía hasta 10 cartas.
- 15 hs: si hay al menos 20 cartas, envía la mitad de lo que haya en la bandeja; si el
número es impar, considera una carta más.
- 16 hs: saca las necesarias hasta que queden 5 cartas a lo sumo.
- 17 hs: despacha todas las que quedan.
Modelar el proceso utilizando estructura de Pila y considerar, para facilitar el
entendimiento del ejercicio, que antes de que la recepcionista envíe las cartas, siempre
se adelanta la asistente y deja cartas en la bandeja (es posible implementar este
comportamiento leyendo un archivo o recuperando valores de algún arreglo).
*/

#include <iostream>
#include <string.h>
using namespace std;

struct STR_NODO
{
    char dato[250];
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

void push(STR_NODO **pila, char valor[])
{
    STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
    strcpy(nodo->dato, valor);
    nodo->ste = NULL;

    nodo->ste = *pila;
    *pila = nodo;
    return;
}

char *pop(STR_NODO **pila)
{
    char *dato = (char *)malloc(250 * sizeof(char));
    strcpy(dato, (*pila)->dato);
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

void printHistorial(STR_NODO *pila)
{

    char *url = (char *)malloc(250 * sizeof(char));
    printf("Historial");
    while (!isEmpty(pila))
    {
        url = pop(&pila);
        printf("%s", url);
    }

    return;
}

void cargarPila(STR_NODO *pila);
int main()
{
    STR_NODO *pila = NULL;
    char carta[250];
    
    cargarPila(pila);
    while (!isEmpty(pila))
    {
        
    }
    

    system("pause");
    return 0;
}

void cargarPila(STR_NODO *pila){
    
    int i = 100;
    char carta[250] = {"carta"};
    while (i < 100)
    {
      carta[250] = i + '0';
      push(&pila, carta); 
    }
    return;
}