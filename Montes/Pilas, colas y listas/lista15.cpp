/*
15. Dado un archivo de registros de alumnos, donde cada registro contiene: a) Apellido y
Nombre del alumno (35 caracteres) b) Número de legajo (7 dígitos) c) División
asignada (1 a 100) ordenado por número de legajo, desarrollar el algoritmo y
codificación del programa que imprima el listado de alumnos por división, ordenado
por división y número de legajo crecientes, a razón de 55 alumnos por hoja.
*/

#include <iostream>
#include "string.h"
using namespace std;

struct ST_DATO
{
    char apellidoNombre[35];
    int legajo;
    int division;
};

struct ST_NODO
{
    ST_DATO alumno;
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

void cerrar(FILE *file)
{
    fclose(file);
    file = NULL;
}

void leer(ST_DATO *alumno, FILE *file)
{
    char buffer[250];
    if (fgets(buffer, 250, file) != NULL)
    {
        alumno->division = atoi(strtok(buffer, ";"));
        strcpy(alumno->apellidoNombre, strtok(NULL, ";"));
        alumno->legajo = atoi(strtok(NULL, ";\n"));
    }
    return;
}

ST_NODO *insertOrdered(ST_DATO valor, ST_NODO **lista)
{
    ST_NODO *nodo = (ST_NODO *)malloc(sizeof(ST_NODO));
    nodo->alumno = valor;
    nodo->ste = NULL;

    ST_NODO *listaAux = *lista;
    ST_NODO *nodoAnt = NULL;
    while (listaAux != NULL && listaAux->alumno.division < valor.division)
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
        int key = listaAux->alumno.division;
        printf("DIVISION: %d\n", key);
        while (listaAux != NULL && key == listaAux->alumno.division)
        {
            printf("%d - %s\n", listaAux->alumno.legajo, listaAux->alumno.apellidoNombre);
            listaAux = listaAux->ste;
        }
        printf("\n");
    }
}

void clearList(ST_NODO **lista)
{
    ST_NODO *aux = NULL;
    while (*lista != NULL)
    {
        aux = *lista;
        *lista = (*lista)->ste;
        free(aux);
    }
}

int main()
{ 
    FILE *alumnosFile = abrir("alumnos.txt","r");
    ST_NODO *lista = NULL;
    ST_DATO alumno;
    
    leer(&alumno,alumnosFile);
    while (!feof(alumnosFile))
    {
        insertOrdered(alumno,&lista);
        leer(&alumno,alumnosFile);
    }

    print(lista);
    
    
    system("pause");
    return 0;
}