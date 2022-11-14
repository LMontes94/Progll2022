/*
Un corralón recibe en horario de oficina material de construcción que entrega durante los fines de semana.
Diariamente un empleado da de alta los artículos en el sistema respetando el orden de llegada, para lo cual
imputa el código de la ubicación temporal en la playa, código de barra y precio de ventas; la carga queda en
memoria.
En una etapa posterior, fuera de horario de oficina, los empleados trasladan a la ubicación definitiva cada uno
de estos artículos recibidos; para asistirse, imprimen la nómina de bultos en el orden inverso al que fueron
recibidos, con los tres datos relevados oportunamente.
Los sábados por la mañana un empleado recibe los pedidos que los clientes realizan telefónicamente; ingresa
al sistema el nombre, dirección, código postal, código del artículo (únicamente puede comprar un sólo tipo) y
la cantidad.
Todo queda en memoria hasta que por la tarde, cuando dejan de recibirse llamados, se imprime el listado de
clientes en el mismo orden que fueron recibidos, para realizar el delivery.
a. Desarrollar la estrategia y estructuras para el problema enunciado y para los puntos siguientes:
b. Realizar la carga de un artículo recibido.
c. Realizar la impresión de los artículos.
d. Realizar el alta de un pedido.
e. Realizar la impresión del listado para el delivery
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;

struct ST_ARTICULO
{
    int codUbi;
    int codBarra;
    float precio;
};

struct ST_PEDIDO
{
    char nombre[30];
    char direccion[20];
    int codPostal;
    int codArticulo;
    int cantidad;
};

struct STR_NODO
{
    ST_ARTICULO dato;
    STR_NODO *ste;
};
struct ST_NODO
{
    ST_PEDIDO dato;
    ST_NODO *ste;
};

struct STR_QUEUE
{
    ST_NODO *frente;
    ST_NODO *fin;
};

FILE *abrir(const char *fileName, const char *modo)
{
    FILE *file = fopen(fileName, modo);
    if (file == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo: %s", fileName);
        exit(EXIT_FAILURE);
    }

    return file;
}
void create(STR_NODO **pila)
{
    *pila = NULL;
}

bool isEmpty(STR_NODO *pila)
{
    return pila == NULL;
}

void push(STR_NODO **pila, ST_ARTICULO valor)
{
    STR_NODO *nodo = (STR_NODO *)malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    nodo->ste = *pila;
    *pila = nodo;
    return;
}

ST_ARTICULO pop(STR_NODO **pila)
{
   ST_ARTICULO dato = (*pila)->dato;
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

void create(STR_QUEUE *queue)
{
    queue->fin = NULL;
    queue->frente = NULL;
}

bool isEmpty(STR_QUEUE &queue)
{
    return queue.fin == NULL && queue.frente == NULL;
}

void add(STR_QUEUE *queue, ST_PEDIDO valor)
{
    ST_NODO *nodo = (ST_NODO *)malloc(sizeof(ST_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    if (queue->frente == NULL)
    {
        queue->frente = nodo;
    }
    else
    {
        queue->fin->ste = nodo;
    }

    queue->fin = nodo;
    return;
}

ST_PEDIDO remove(STR_QUEUE *queue)
{
    ST_NODO *aux = queue->frente;
    ST_PEDIDO dato = aux->dato;
    queue->frente = aux->ste;

    if (queue->frente == NULL)
    {
        queue->fin = NULL;
    }

    free(aux);
    return dato;
}

void menu(int &opcion);
ST_ARTICULO cargarArticulo();
void printArticulos(STR_NODO *pila);
ST_PEDIDO cargarPedido();
void printPedidos(STR_QUEUE *queue);

int main()
{
    STR_NODO *pila = NULL;
    STR_QUEUE pedidos;
    create(&pedidos);

    ST_ARTICULO articulo;
    ST_PEDIDO pedido;
    int opcion = 0;

    while (opcion != 5)
    {
        menu(opcion);
        switch (opcion)
        {
        case 1:
            articulo = cargarArticulo();
            push(&pila, articulo);
            break;
        case 2:
            printArticulos(pila);
            break;
        case 3:
            pedido = cargarPedido();
            add(&pedidos, pedido);
            break;
        case 4:
            printPedidos(&pedidos);
            break;
        case 5:
            printf("Cerrando app..... NV!!\n");
            break;
        default:
            printf("Opcion no valida!!!, vuelva a seleccion una opcion\n");
            break;
        }
    }

    system("pause");
    return 0;
}

void menu(int &opcion)
{

    printf("------Menu---------\n");
    printf("1- Cargar articulos\n");
    printf("2- Imprimir listado de articulos\n");
    printf("3- Cargar pedido\n");
    printf("4- Imprimir listado de pedidos\n");
    printf("5- Salir\n");
    printf("Seleccione una opcion..\n");
    scanf("%d", &opcion);
    return;
}

ST_ARTICULO cargarArticulo()
{

    ST_ARTICULO articulo;
    printf("Ubicacion temporal: \n");
    scanf("%d", articulo.codUbi);
    printf("Codigo de articulo: \n");
    scanf("%d", articulo.codBarra);
    printf("Precio: \n");
    scanf("%0.2f", articulo.precio);
    return articulo;
}

void printArticulos(STR_NODO *pila)
{

    STR_NODO *pilaAux = pila;
    ST_ARTICULO dato;
    printf("Ubicacion temporal      Codigo de barra     precio\n");
    while (!isEmpty(pilaAux))
    {
        dato = pop(&pilaAux);
        printf("%d                           %d              %0.2f\n", dato.codUbi, dato.codBarra, dato.precio);
    }
    free(pilaAux);
    return;
}

ST_PEDIDO cargarPedido()
{
    ST_PEDIDO pedido;

    printf("--------Cargar de datos-------\n");
    printf("Nombre del cliente: \n");
    scanf("%s", pedido.nombre);
    printf("Direccion: \n");
    scanf("%s", pedido.direccion);
    printf("Codigo postal\n");
    scanf("%d", pedido.codPostal);
    printf("Codigo del articulo\n");
    scanf("%d", pedido.codArticulo);
    printf("Cantidad\n");
    scanf("%d", pedido.cantidad);
    return pedido;
}

void printPedidos(STR_QUEUE *queue)
{

    printf("Nombre  Direccion   Cod Postal  Cod Articulo    Cantidad");
    while (!isEmpty(*queue))
    {
        ST_PEDIDO valor = remove(queue);
        printf("%s, %s, %d, %d, %d\n", valor.nombre, valor.direccion, valor.codPostal,
               valor.codArticulo, valor.cantidad);
    }
    return;
}