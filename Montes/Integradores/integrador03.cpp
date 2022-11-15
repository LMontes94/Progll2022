/*
Una empresa ferroviaria desea procesar los archivos históricos de venta de pasajes de 2
estaciones que producto de una remodelación fueron unificadas.
Para esto cuenta con 2 archivos binarios, uno por cada estación, donde cada registro
describe una venta de un pasaje. Cada registro contiene
    ● Número de boleto (long int)
    ● Fecha en formato "DD-MM-YYYY HH:MM:SS"
    ● Id de estación (short int)
    ● Precio (float)
Los archivos se encuentran ordenados por fecha.
    Se pide:
    1. Generar un nuevo archivo de texto, que contenga los registros de los 2 archivos
    binarios, ordenado por fecha. La particularidad es que del campo fecha solo se
    requiere la fecha DD-MM-YYYY
    2. A partir del archivo de texto generado en el punto 1, emitir un listado con la siguiente
    forma:
            Estación: xxx
            Año: 9999. Mes:99

            Total mensual: 999.99
            Año: 9999. Mes: 99
            Total mensual: 999.99
            Estación: yyy
            Año: 9999. Mes:99
            Total mensual: 999.99
            Año: 9999. Mes: 99
            Total mensual: 999.99
*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;
#define MAX_BUFFER 250

struct ST_PASAJE
{
    long int boleto;
    char fecha[20]; // "DD-MM-YYYY HH:MM:SS"
    short idEstacion;
    float precio;
};

struct ST_PASAJEAUX
{
    long int boleto;
    char fecha[10]; // "DD-MM-YYYY HH:MM:SS"
    short idEstacion;
    float precio;
};

struct ST_NODO
{
    ST_PASAJEAUX dato;
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

ST_NODO* insertOrdered(ST_PASAJEAUX valor, ST_NODO **lista) {
    ST_NODO* nodo = (ST_NODO *) malloc(sizeof(ST_NODO));
    nodo->dato = valor;
    nodo->ste = NULL;

    ST_NODO *listaAux = *lista;
    ST_NODO *nodoAnt = NULL;
    while(listaAux != NULL && strcmp(listaAux->dato.fecha,valor.fecha)) {
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

void leer(ST_PASAJEAUX *pasaje, FILE *file)
{
    char buffer[MAX_BUFFER];
    if (fgets(buffer, MAX_BUFFER, file) != NULL)
    {
        pasaje->boleto = atoi(strtok(buffer, ";"));
        strcpy(pasaje->fecha, strtok(NULL, ";"));
        pasaje->idEstacion = atoi(strtok(NULL, ";"));
        pasaje->precio = atof(strtok(NULL,";\n"));
    }
    return;
}
int main()
{

    FILE *ventaEstacion1File = abrir("venta_estacion1.dat", "rb");
    FILE *ventaEstacion2File = abrir("venta_estacion2.dat", "rb");
    FILE *apareoDeEstaciones = abrir("archivo_final.txt", "w");

    ST_PASAJE pasaje1;
    ST_PASAJE pasaje2;
    ST_PASAJEAUX pasajeAux;

    fread(&pasaje1, sizeof(ST_PASAJE), 1, ventaEstacion1File);
    fread(&pasaje2, sizeof(ST_PASAJE), 1, ventaEstacion2File);
    while (!feof(ventaEstacion1File) && !feof(ventaEstacion2File))
    {

        if (strcmp(pasaje1.fecha,pasaje2.fecha) <= 0)
        {
            pasajeAux.boleto = pasaje1.boleto;
            strcpy(pasajeAux.fecha,strtok(pasaje1.fecha," "));
            pasajeAux.idEstacion = pasaje1.idEstacion;
            pasajeAux.precio = pasaje1.precio;
            fread(&pasaje1, sizeof(ST_PASAJE), 1, ventaEstacion1File);
        }else{
            pasajeAux.boleto = pasaje2.boleto;
            strcpy(pasajeAux.fecha,strtok(pasaje2.fecha," "));
            pasajeAux.idEstacion = pasaje2.idEstacion;
            pasajeAux.precio = pasaje2.precio;
            fread(&pasaje2, sizeof(ST_PASAJE), 1, ventaEstacion2File);
        }
        
        fprintf(apareoDeEstaciones,"%d;%s;%d;%0.2f\n",pasajeAux.boleto,pasajeAux.fecha,pasajeAux.idEstacion,pasajeAux.precio);
        
    }
    
    leer(&pasajeAux,apareoDeEstaciones);
    while (!feof(apareoDeEstaciones))
    {
       
       leer(&pasajeAux,apareoDeEstaciones); 
    }
    
    system("pause");
    return 0;
}