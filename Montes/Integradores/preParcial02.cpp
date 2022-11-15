/*
Dado el archivo binario libros.dat, que posee datos desordenados sobre libros valiosos con la siguiente
estructura:
ISBN                Nombre      Año edición        Valor
Entero (10 dígitos) Char(40) Entero (1600 - 1700) Float (2 decimales)
Se desea obtener un listado agrupado por ISBN ordenado por año indicando: ISBN, Nombre y Valor Promedio.
Restricciones:
● No posee memoria estática suficiente para almacenar el archivo en memoria.
● No dispone de espacio suficiente en disco para duplicar el archivo.
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;

struct ST_LIBRO
{
    int isbn;
    char nombre[40];
    int anio;
    float valor;
};

struct ST_NODO
{
    ST_LIBRO dato;
    ST_NODO *ste;
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

ST_NODO *insertOrdered(ST_LIBRO valor, ST_NODO **lista)
{
    ST_NODO *nodo = (ST_NODO *)malloc(sizeof(ST_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    ST_NODO *listaAux = *lista;
    ST_NODO *nodoAnt = NULL;
    while (listaAux != NULL && listaAux->dato.isbn < valor.isbn && listaAux->dato.anio < valor.anio)
    {
        nodoAnt = listaAux;
        listaAux = listaAux->ste;
    }

    if (nodoAnt == NULL)
    {
        *lista = nodo;
    }
    else
    {
        nodoAnt->ste = nodo;
    }

    nodo->ste = listaAux;
    return nodo;
}

void print(ST_NODO *listaAux)
{

    while (listaAux != NULL)
    {
        int key = listaAux->dato.isbn;
        printf("ISBN %d\n", key);
        while (listaAux != NULL && key == listaAux->dato.isbn)
        {
            int anio = listaAux->dato.anio;
            printf("AÑO: %d\n", anio);
            while (listaAux != NULL && key == listaAux->dato.isbn && anio == listaAux->dato.anio)
            {
                printf("Nombre: %s  %0.2f\n", listaAux->dato.nombre, listaAux->dato.valor);
                listaAux = listaAux->ste;
            }
        }
    }
}
int main()
{

    FILE *librosDat = abrir("libros.dat", "rb");
    ST_LIBRO libro;
    ST_NODO *lista = NULL;

    fread(&libro, sizeof(ST_LIBRO), 1, librosDat);
    while (!feof(librosDat))
    {
        insertOrdered(libro, &lista);
        fread(&libro, sizeof(ST_LIBRO), 1, librosDat);
    }
    
    print(lista);
    system("pause");
    return 0;
}