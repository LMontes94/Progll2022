/*
Una facultad desea establecer ciertas estadísticas de su proceso de inscripciones para lo cual cuenta con los siguientes
archivos:
materias.dat
● El código de materia es alfanumérico y se compone de un prefijo de tres letras que indican la carrera y un número
entero de 1 a 40 luego del -
inscripciones.txt
El archivo materias.dat se encuentra desordenado y tiene la información de las materias de todas las carreras del
establecimiento. El archivo inscripciones.txt se generó a medida que se tomaron las mismas con lo cual el orden es
cronológico
Por política de las autoridades si la materia es anual se tiene un margen extra de 10% sobre la capacidad máxima
Realizar el sistema que permita:
a. Procesar las inscripciones de una especialidad ingresada por el usuario y generar el archivo rechazadas.txt con
aquellas inscripciones que no pudieron ser tomadas por falta de capacidad con el mismo formato que el archivo de
inscripciones.
b. Emitir el listado de inscriptos con las inscripciones aceptadas ordenado por nombre de materia y apellido de los
inscriptos con el siguiente formato:
CARRERA: XXX TOTAL: 999
MATERIA: DESCRIPCION [XXX-99] TOTA MATERIA: 999
ACOSTA JUAN MANUEL 99999999
c. Informar por pantalla el listado de materias con los inscriptos aceptados, ordenado descendentemente por la
cantidad de inscriptos:
MATERIA INSCRIPTOS
XXX-99 150
XXX-99 145.
TOTAL CARRERA: 395
Restricciones:
● No se cuenta con memoria estática para almacenar completo ninguno de los dos archivos recibidos
● No se cuenta con espacio de almacenamiento en disco más que para los archivos que deben generarse como salida
● Ningún archivo recibido puede ser recorrido secuencialmente más de una vez
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;
#define MAX_BUFFER 250
#define CUATRIMESTRAL 100
#define ANUAL 110

struct ST_MATERIA
{
    char codigo[6];
    char descripcion[50];
    short cuatrimestre;
    char modalidad;
    int capacidad;
};

struct ST_INSCRIPCION
{
    char codigo[6];
    int dni;
    char apellido[50];
    char nombre[50];
};

struct ST_NODO
{
    ST_MATERIA dato;
    ST_NODO *ste;
};

struct ST_NODO_INSCRIPCION
{
    ST_INSCRIPCION dato;
    ST_NODO_INSCRIPCION *ste;
};

FILE *abrir(const char *path, const char *mode)
{
    FILE *ptrArchivo = fopen(path, mode);
    if (ptrArchivo == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s", path);
        exit(EXIT_FAILURE);
    }
    return ptrArchivo;
}

ST_NODO *insertOrdered(ST_MATERIA valor, ST_NODO **lista)
{
    ST_NODO *nodo = (ST_NODO *)malloc(sizeof(ST_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    ST_NODO *listaAux = *lista;
    ST_NODO *nodoAnt = NULL;
    while (listaAux != NULL && strcmp(listaAux->dato.codigo, valor.codigo) < 0)
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

ST_NODO *search(ST_NODO *lista, ST_INSCRIPCION valor)
{
    ST_NODO *listaAux = lista;
    while (listaAux != NULL && strcmp(listaAux->dato.codigo, valor.codigo) != 0)
    {
        listaAux = listaAux->ste;
    }
    return listaAux;
}

ST_NODO_INSCRIPCION *insertOrderedInscriptos(ST_INSCRIPCION valor, ST_NODO_INSCRIPCION **lista)
{
    ST_NODO_INSCRIPCION *nodo = (ST_NODO_INSCRIPCION *)malloc(sizeof(ST_NODO_INSCRIPCION));
    nodo->dato = valor;
    nodo->ste = NULL;

    ST_NODO_INSCRIPCION *listaAux = *lista;
    ST_NODO_INSCRIPCION *nodoAnt = NULL;
    while (listaAux != NULL && strcmp(listaAux->dato.codigo, valor.codigo) < 0 && strcmp(listaAux->dato.apellido, valor.apellido) < 0)
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

int count(ST_NODO_INSCRIPCION *listaAux, char codigo[])
{
    int cant = 0;
    while (listaAux != NULL)
    {
        if (strcmp(listaAux->dato.codigo,codigo) == 0)
        {
          cant++;  
        }        
        listaAux = listaAux->ste;
        
    }

    return cant;
}

void menu(int &opcion);
void leer(ST_INSCRIPCION *inscripcion, FILE *file);
void printInscriptos(ST_NODO_INSCRIPCION *lista);
void printInscriptosXMateria(ST_NODO_INSCRIPCION *lista, char codigo[]);
int main()
{

    FILE *materiasBin = abrir("materias.dat", "rb");
    FILE *inscripcionesTxt = abrir("inscripciones.txt", "r");
    FILE *rechazadasTxt = abrir("rechazadas.txt", "w");

    ST_MATERIA materia;
    ST_INSCRIPCION inscripcion;
    ST_NODO *listaMaterias;
    ST_NODO_INSCRIPCION *listaInscriptos;
    fread(&materia, sizeof(ST_MATERIA), 1, materiasBin);
    while (!feof(materiasBin))
    {
        if (materia.modalidad == 'A')
        {
            (materia.capacidad * 10) / 100;
        }
        insertOrdered(materia, &listaMaterias);
        fread(&materia, sizeof(ST_MATERIA), 1, materiasBin);
    }

    leer(&inscripcion, inscripcionesTxt);
    while (!feof(inscripcionesTxt))
    {
        ST_NODO *listaAux = search(listaMaterias, inscripcion);
        if (listaAux->dato.capacidad > 0)
        {
            insertOrderedInscriptos(inscripcion, &listaInscriptos);
            listaAux->dato.capacidad--;
        }
        else
        {
            fprintf(rechazadasTxt, "%s %d %s %s", inscripcion.codigo, inscripcion.dni, inscripcion.apellido, inscripcion.nombre);
        }
        leer(&inscripcion, inscripcionesTxt);
    }

    int opcion = 0;
    while (opcion != 3)
    {
        switch (opcion)
        {
        case 1:
        {
            printInscriptos(listaInscriptos);
            break;
        }
        case 2:
            printInscriptosXMateria(listaInscriptos,listaMaterias->dato.codigo);
            break;
        case 3:
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
    printf("1- Imprimir listado de inscriptos\n");
    printf("2- Imprimir listado de materias con los inscriptos aceptados\n");
    printf("3- Salir\n");
    printf("Seleccione una opcion..\n");
    scanf("%d", &opcion);
    return;
}

void leer(ST_INSCRIPCION *inscripcion, FILE *file)
{
    char buffer[MAX_BUFFER];
    if (fgets(buffer, MAX_BUFFER, file) != NULL)
    {
        strcpy(inscripcion->codigo, (strtok(buffer, " ")));
        inscripcion->dni = atoi(strtok(NULL, " "));
        strcpy(inscripcion->apellido, strtok(NULL, " "));
        strcpy(inscripcion->nombre, strtok(NULL, " \n"));
    }
    return;
}

void printInscriptos(ST_NODO_INSCRIPCION *lista)
{
    ST_NODO_INSCRIPCION *listaAux = lista;

    while (listaAux != NULL)
    {
        char key[6];
        strcpy(key, listaAux->dato.codigo);
        printf("Materia: %s     Total Materia: \n", key);
        while (listaAux != NULL && strcmp(key, listaAux->dato.codigo) == 0)
        {
            printf("%s  %s  %d\n", listaAux->dato.apellido, listaAux->dato.nombre, listaAux->dato.dni);
            listaAux = listaAux->ste;
        }
    }

    return;
}