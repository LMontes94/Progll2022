/*
Considerando básico de una estructura del tipo Pila, emule el comportamiento del
historial de un navegador web de modo tal de poder ir almacenando secuencialmente las
páginas que el usuario visita, permitiéndole regresar al sitio anterior.
Implemente una solución que, ingresando por pantalla la url a visitar, almacene las
direcciones de los distintos sitios; finalizada la carga, imprima el contenido del mismo
modo en el que un browser permitiría la navegación hacia atrás.
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
    char *dato = (char*)malloc(250*sizeof(char));
    strcpy(dato,(*pila)->dato);
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

void printHistorial(STR_NODO *pila){
    
    char *url = (char*)malloc(250*sizeof(char));
    printf("Historial");
    while (!isEmpty(pila))
    {
        url = pop(&pila);
        printf("%s",url);
    }
    
    return;
}
int main()
{
    STR_NODO *pila = NULL;
    char url[250];
  
    while (strcmp(url, "cerrar") != 0)
    {
        printf("Ingresar url:\n");
        scanf("%s",url);
        push(&pila,url);
    }
    
    printHistorial(pila);
    system("pause");
    return 0;
}