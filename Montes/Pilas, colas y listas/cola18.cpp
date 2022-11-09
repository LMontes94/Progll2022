/*
Dado un arreglo de N (< 30) colas (nodo = registro + puntero), desarrollar y codificar
un procedimiento que aparee las colas del arreglo en las mismas condiciones que
las definidas en el Ejercicio 14. Nota: Retornar la cola resultante y no mantener las
anteriores.
*/
#include <iostream>
#include "string.h"
using namespace std;

struct STR_DATO
{
    char apellido[21];
    char nombre[21];
};

struct STR_NODO
{
    STR_DATO dato;
    STR_NODO *ste;
};

struct STR_QUEUE {
    STR_NODO *frente;
    STR_NODO *fin;
};

void create(STR_QUEUE *queue)
{  
    queue->fin = NULL;
    queue->frente = NULL;
   
}

bool isEmpty(STR_QUEUE &queue)
{
    return queue.fin == NULL && queue.frente == NULL;
}

void add(STR_QUEUE *queue, STR_DATO valor)
{
    STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    if(queue->frente == NULL) {
        queue->frente = nodo;
    } else {
        queue->fin->ste = nodo;
    }
    
    queue->fin = nodo;
    return;
}

STR_DATO remove(STR_QUEUE *queue) {
    STR_NODO *aux = queue->frente;
    STR_DATO dato = aux->dato;
    queue->frente = aux->ste;

    if(queue->frente == NULL) {
        queue->fin = NULL;
    }

    free(aux);
    return dato;
}


void print(STR_QUEUE *queue)
{
    while (!isEmpty(*queue))
    {
        STR_DATO valor = remove(queue);
        printf("%s, %s\n", valor.apellido, valor.nombre);
    }
}

void anexar(STR_QUEUE queue[5], STR_QUEUE *queueAB) {
    
int i=0;
    while (i<5)
    {
     
    while(!isEmpty(queue[i])) {
        add(queueAB, remove(&queue[i]));
    }
     i++;  
    }
    
return;  
}

int main()
{

    STR_QUEUE queue[5];
    STR_QUEUE queueAB;

    for (int i = 0; i < 5; i++)
    {
        create(&queue[i]);
        
    }
    create(&queueAB);
    
    STR_DATO alumno;
    int i=0;


    while(i<5)
    {
            
            printf("Complete la COLA %d\n",i+1);
            printf("Ingrese un Apellido (Fin para terminar):");
            scanf("%s", &alumno.apellido);
            while (strcmp(alumno.apellido, "Fin") != 0)
            {
                printf("Ingrese un Nombre:");
                scanf("%s", &alumno.nombre);

                add(&queue[i], alumno);

                printf("Ingrese un nombre (Fin para terminar):");
                scanf("%s", &alumno.apellido);
            }

        i++;

    }   
   
  
    anexar(queue,&queueAB);
    print(&queueAB);
    
   

    system("pause");
    return 0;
}