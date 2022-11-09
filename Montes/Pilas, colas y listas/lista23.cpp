/*
23. Dado un archivo de registros de alumnos ARCHA sin ningún orden, donde cada
registro contiene: a) Apellido y Nombre del alumno (34 caracteres) b) Número de
legajo (6 dígitos) c) División asignada (1 a 100) Se debe desarrollar el algoritmo y
codificación del programa que genere un archivo ARCHL igual al anterior pero
ordenado por número de legajo. Nota: Memoria estática 64 Kb; dinámica suficiente si
ningún nodo ocupa más de 12 bytes.
*/
#include <iostream>
#include "string.h"
using namespace std;

#define MAX_BUFFER 250

typedef struct Alumno {
    char nombre[35];
    int legajo;
    char division;
} Alumno;

typedef struct Indice {
    int legajo;
    int posicionArchivo;
} STR_DATO;

typedef struct Nodo {
    STR_DATO dato;
    Nodo *siguiente;
} STR_NODO;

// Funciones de lista
void create(STR_NODO **lista);
bool isEmpty(STR_NODO *lista);
STR_NODO* insertInFront(STR_DATO valor, STR_NODO **lista);
STR_NODO* insertAtEnd(STR_DATO valor, STR_NODO **lista);
STR_NODO* insertOrdered(STR_DATO valor, STR_NODO **lista);
STR_NODO* insertWithoutDuplicate(STR_DATO valor, STR_NODO **lista);
void print(STR_NODO *lista);
void clearList(STR_NODO **lista);
STR_NODO *search(STR_NODO *lista, STR_DATO valor);
STR_DATO deleteFirst(STR_NODO **lista);
void sort(STR_NODO **lista);
int count(STR_NODO *listaAux);

FILE *abrir(const char *fileName, const char *modo);
void cerrar(FILE * file);
int leer(Alumno *registro, FILE * file);
int leer(int pos, Alumno *registro, FILE * file);
int escribir(Alumno registro, FILE * file);


int main() {
    STR_NODO *lista;
    create(&lista);

    FILE * alumnos = abrir("ARCHA.dat", "rb");
    FILE *ordenado = abrir("ARCHL.dat", "wb");

    int i = 0;
    Alumno alumno;
    leer(&alumno, alumnos);
    while(!feof(alumnos)) {
        STR_DATO elemento;
        elemento.legajo = alumno.legajo;
        elemento.posicionArchivo = i;
        insertOrdered(elemento, &lista);
        i++;
        leer(&alumno, alumnos);
    }

    while(!isEmpty(lista)) {
        STR_DATO elemento = deleteFirst(&lista);
        Alumno alumno;
        leer(elemento.posicionArchivo, &alumno, alumnos);
        escribir(alumno, ordenado);
    }


    cerrar(alumnos);
    cerrar(ordenado);
    system("pause");
    return 0;
}


// Funciones de Listas
void create(STR_NODO **lista) {
    *lista = NULL;
    return;
}

bool isEmpty(STR_NODO *lista) {
    return lista == NULL;
}

STR_NODO* insertInFront(STR_DATO valor, STR_NODO **lista) {
    STR_NODO* nodo = (STR_NODO *) malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->siguiente = *lista;

    *lista = nodo;
    return nodo;
}

STR_NODO* insertAtEnd(STR_DATO valor, STR_NODO **lista) {
    STR_NODO* nodo = (STR_NODO *) malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->siguiente = NULL;

    if(isEmpty(*lista)) {
        *lista = nodo;
    } else {
        STR_NODO *listaAux = *lista;
        while(listaAux->siguiente != NULL) {
            listaAux = listaAux->siguiente;
        }
        listaAux->siguiente = nodo;
    }

    return nodo;
}

STR_NODO* insertOrdered(STR_DATO valor, STR_NODO **lista) {
    STR_NODO* nodo = (STR_NODO *) malloc(sizeof(STR_NODO));
    nodo->dato = valor;
    nodo->siguiente = NULL;

    STR_NODO *listaAux = *lista;
    STR_NODO *nodoAnt = NULL;
    while(listaAux != NULL && listaAux->dato.legajo < valor.legajo) {
        nodoAnt = listaAux;
        listaAux = listaAux->siguiente;
    }

    if(nodoAnt == NULL) {
        *lista = nodo;
    } else {
        nodoAnt->siguiente = nodo;
    }

    nodo->siguiente = listaAux;
    return nodo;
}

STR_NODO* insertWithoutDuplicate(STR_DATO valor, STR_NODO **lista) {
    STR_NODO *nodo = search(*lista, valor);
    if(nodo == NULL) {
        nodo = insertOrdered(valor, lista);
    }

    return nodo;
}

void clearList(STR_NODO **lista) {
    STR_NODO *aux = NULL;
    while(*lista != NULL) {
        aux = *lista;
        *lista = (*lista)->siguiente;
        free(aux);
    }
}

STR_NODO *search(STR_NODO *lista, STR_DATO valor) {
    STR_NODO *listaAux = lista;
    while(listaAux != NULL && listaAux->dato.legajo != valor.legajo) {
        listaAux = listaAux->siguiente;
    }
    return listaAux;
}

STR_DATO deleteFirst(STR_NODO **lista) {
    STR_NODO *nodoAux = *lista;
    *lista = (*lista)->siguiente;
    STR_DATO dato = nodoAux->dato;
    free(nodoAux);
    return dato;
}

void sort(STR_NODO **lista) {
    STR_NODO *listaAux;
    create(&listaAux);
    STR_DATO dato;
    while(*lista != NULL) {
        dato = deleteFirst(lista);
        insertOrdered(dato, &listaAux);
    }

    *lista = listaAux;
}

int count(STR_NODO *listaAux) {
    int cant = 0;
    while(listaAux != NULL) {
        listaAux = listaAux->siguiente;
        cant++;
    }

    return cant;
}

void print(STR_NODO *listaAux) {
    while(listaAux != NULL) {
        printf("Legajo: %d - Posicion: %d\n", listaAux->dato.legajo, listaAux->dato.posicionArchivo);
        listaAux = listaAux->siguiente;
    }
}

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

void cerrar(FILE * file) {
    fclose(file);
    file = NULL;
}

/**
 * Lee el registro en la posicion especificada
 */
int leer(int pos, Alumno *registro, FILE * file) {
    fseek(file, sizeof(Alumno) * pos, SEEK_SET);
    return leer(registro, file);
}

int leer(Alumno *registro, FILE * file) {
    return fread(registro, sizeof(Alumno), 1, file);
}

int escribir(Alumno registro, FILE * file) {
    return fwrite(&registro, sizeof(Alumno), 1, file);
}