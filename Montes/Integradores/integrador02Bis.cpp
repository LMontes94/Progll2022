#include <iostream>
#include "string.h"
#define MAX_NODOS_ATENCION 10
#define MAX_PEDIDOS_X_NODO 100
using namespace std;

typedef struct Proceso {
    int id;
    int ciclos;
    char tipo[4];
} STR_PROCESO, STR_DATO;

typedef struct Nodo {
    STR_PROCESO dato;
    Nodo *siguiente;
} STR_NODO;

typedef struct Queue {
    STR_NODO *head;
    STR_NODO *tail;
} STR_QUEUE;

typedef struct NodoAtencion {
    char disponibles = MAX_PEDIDOS_X_NODO;
    STR_QUEUE pedidos;
    bool activo = false;
    int cantCPU;
    int cantES;
    int cantCPUProcesados;
} STR_NODO_ATENCION;

bool recibir(STR_PROCESO proceso, STR_NODO_ATENCION nodos[]);
int activarNodo(STR_NODO_ATENCION nodos[]);
bool agregarPedido(STR_PROCESO pedido, STR_NODO_ATENCION nodos[]);

int main () {

    STR_NODO_ATENCION nodos[MAX_NODOS_ATENCION];
    int cantNodosActivos = 0;

    STR_PROCESO proceso;
    leerProceso(&proceso);  //Tomamos un proceso e algun lado
    agregarPedido(proceso);
    procesar(30);

    system("pause");
    return 0;
}

bool agregarPedido(STR_PROCESO pedido, STR_NODO_ATENCION nodos[]) {
    int posNodo = getNodoAtencion(nodos); //BUsco nodo que va a atender (el que menos ocupado este) o devuelve -1 si ya no hay capacidad.

    if(posNodo == -1) {
        return false;
    }

    add(pedido, &(nodos[posNodo].pedidos));  //Encolo el pedido
    nodos[posNodo].disponibles--;  // Decremento la capacidad disponible
    if(strcmp(pedido.tipo, "CPU") == 0) {
        nodos[posNodo].cantCPU++;
    }else {
        nodos[posNodo].cantES++;
    }
    return true;  //Devuelve true porque pudo agregar el pedido a la estructura
}

// Busca el nodo mas libre, si no hay intenta crear uno, si no puede devuelve -1
int getNodoAtencion(STR_NODO_ATENCION nodos[]) {
    int pos = -1;
    int max = 0;
    for(int i = 0; i < MAX_NODOS_ATENCION; i++) {
        if(nodos[i].activo && nodos[i].disponibles > 0 && nodos[i].disponibles > max) {
            max = nodos[i].disponibles;
            pos = i;
        }
    }

    if(pos == -1) {
        return activarNodo(nodos);  // Intenta activar un nuevo nodo, devuelve la posicion del nodo activado
    }

    return pos;
}

// Busca el primer nodo inactivo para activarlo retorna la posicion del nuevo nodo activo,
// si no habia ninguno inactivo (no hay mas nodos disponibles) retorna -1
int activarNodo(STR_NODO_ATENCION nodos[]) {
    for(int i = 0; i < MAX_NODOS_ATENCION; i++) {
        if(!nodos[i].activo) {
            nodos[i].disponibles = MAX_PEDIDOS_X_NODO;
            nodos[i].pedidos = createQueue();
            nodos[i].activo = true;
            return i;
        }
    }
    return -1;
}

STR_QUEUE createQueue() {
    STR_QUEUE queue;
    queue.head = NULL;
    queue.tail = NULL;
    return queue;
}

void add(STR_DATO valor, STR_QUEUE *queue) {
    STR_NODO* ptrNodo = (STR_NODO*) malloc(sizeof(STR_NODO));
    ptrNodo->dato = valor;
    ptrNodo->siguiente = NULL;

    if(queue->head == NULL) {
        queue->head = ptrNodo;
    } else {
        queue->tail->siguiente = ptrNodo;
    }

    queue->tail = ptrNodo;
}