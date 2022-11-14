/*
Ejercicio 1
Una empresa desea realizar el resumen mensual de las horas trabajadas y horas de ausencia de sus
empleados. Para realizar el cálculo cuenta con un archivo binario “HORAS_DIARIAS.dat” donde cada
registro se compone de los siguientes datos:
● Legajo del empleado: 10 caracteres
● Día del mes: número de 1 a 31
● Horas: número entero de 1 a 24
● Ausencia: 1 o 0 (si es 1: las Horas son horas de ausencia, si es 0: las Horas son horas
trabajadas)
El archivo se encuentra desordenado y por haber distintos turnos puede haber más de un registro
por día de un mismo empleado. Se solicita:

a. Definir la estrategia y estructuras necesarias para la lectura del archivo y realización
de los puntos b. y c.
b. Imprimir por pantalla el listado de las horas imputadas por cada empleado para el
mes, ordenado por legajo en forma creciente. imprimiendo:

      Legajo  Hs. Trabajadas Hs. Ausencia   % Ausentismo (HA / HT + HA)

c. Indicar el día del mes con mayor cantidad de Horas de Ausencia
d. Indicar el legajo con mayor Ausentismo
*/

#include <iostream>
#include "string.h"

using namespace std;

struct ST_EMPLEADO
{
    char legajo[10];
    short dia;
    short hora;
    bool ausencia;
};

struct ST_DATO
{
    char legajo[10];
    int hsT = 0;
    int hsA = 0;
    float porcentajeA;
};

struct ST_NODO
{
    ST_DATO dato;
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
bool isEmpty(ST_NODO *lista) {
    return lista == NULL;
}
ST_NODO* insertOrdered(ST_DATO valor, ST_NODO **lista) {
    ST_NODO* nodo = (ST_NODO *)malloc(sizeof(ST_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    ST_NODO *listaAux = *lista;
    ST_NODO *nodoAnt = NULL;
    while(listaAux != NULL && strcmp(listaAux->dato.legajo,valor.legajo) < 0) {
        nodoAnt = listaAux;
        listaAux = listaAux->ste;
    }

    if(nodoAnt == NULL) {
        *lista = nodo;
    } else {
        nodoAnt->ste = nodo;
    }

    nodo->ste = listaAux;
    return nodo;
}
ST_NODO* insertWithoutDuplicate(ST_DATO valor, ST_NODO **lista) {
    ST_NODO *nodo = search(*lista, valor);
    if(nodo == NULL) {
        nodo = insertOrdered(valor, lista);
    }else{
        nodo->dato.hsA =+ valor.hsA;
        nodo->dato.hsT =+ valor.hsT;
        nodo->dato.porcentajeA = nodo->dato.hsA /(nodo->dato.hsT+nodo->dato.hsA);
    }

    return nodo;
}
ST_NODO *search(ST_NODO *lista, ST_DATO valor) {
    ST_NODO *listaAux = lista;
    while(listaAux != NULL && strcmp(listaAux->dato.legajo,valor.legajo) != 0) {
        listaAux = listaAux->ste;
    }
    return listaAux;
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
void clearList(ST_NODO **lista) {
    ST_NODO *aux = NULL;
    while(*lista != NULL) {
        aux = *lista;
        *lista = (*lista)->ste;
        free(aux);
    }
}

ST_DATO deleteFirst(ST_NODO **lista) {
    ST_NODO *nodoAux = *lista;
    *lista = (*lista)->ste;
    ST_DATO dato = nodoAux->dato;
    free(nodoAux);
    return dato;
}
void print(ST_NODO *listaAux) {
    while(listaAux != NULL) {
        printf("Legajo: %d - Posicion: %d\n", listaAux->dato.legajo, listaAux->dato.hsA);
        listaAux = listaAux->ste;
    }
}
int main(){
    
    FILE *horasDiariasFile = abrir("HORAS_DIARIAS.dat","rb");
    ST_EMPLEADO empleado;
    ST_NODO *lista = NULL;

    fread(&empleado,sizeof(ST_EMPLEADO),1,horasDiariasFile);
    while (!feof(horasDiariasFile))
    {
        ST_DATO dato;
        strcpy(dato.legajo,empleado.legajo);
        if (empleado.ausencia)
        {
            dato.hsA =+ empleado.hora;   
        }else{
            dato.hsT =+ empleado.hora;
        }
        insertWithoutDuplicate(dato,&lista);   
        fread(&empleado,sizeof(ST_EMPLEADO),1,horasDiariasFile);
    }
    

    system("pause");
    return 0;
}