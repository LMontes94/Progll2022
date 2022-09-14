/*
Ej. 21: Una empresa de aviación realiza 500 vuelos semanales a distintos puntos del país y requiere
desarrollar un programa para la venta de pasajes.
Para ello dispone de un archivo “Vuelos.dat”, con un registro por cada uno de los 500 vuelos que
realiza, sin ningún orden, con el siguiente diseño de registro:
a.1) código de vuelo (6 caracteres) a.2) cantidad de pasajes disponibles (3 dígitos) También se dispone
de otro archivo “Compradores.dat”, con los potenciales compradores y con el siguiente diseño de registro:
b.1) código de vuelo b.2) cantidad de pasajes solicitados (3 dígitos)
b.3) DNI del solicitante (8 dígitos) b.4) apellido y nombre del solicitante (25 caracteres)
Se pide:
1) Para los solicitantes a los cuales se les venden pasajes, emitir el siguiente listado:
DNI       Apellido y Nombre        Cantidad de pasajes  Código de Vuelo
99999999  xxxxxxxxxxxxxxxxxxxxxxxx      999                  999
99999999  xxxxxxxxxxxxxxxxxxxxxxxx      999                  999

2) Al final del proceso emitir el siguiente listado ordenado por código de vuelo
Código de Vuelo Pasajes disponibles Pasajes no vendidos
BUE999                 999              999
XXX999                 999              999

Nota: Se le vende al solicitante si la cantidad de pasajes que solicita está disponible, en caso contrario se
computa como pasajes no vendidos. Desarrolle el ejercicio utilizando la siguiente estructura de datos:
Array de registro: VECTOR : array [1..500] of treg. Bytes que ocupa = (7 + 2 + 2) *500 = 5500 bytes

        CODIGOV           PASAJESDISP     PASAJESNOV
        char[7] (7 bytes) short (2 bytes) short (2 bytes)
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_VUELOS 500
using namespace std;

struct ST_VUELO
{
    char idVuelo[7];
    short int pasajes;
};

struct ST_COMPRADOR
{
    char idVuelo[7];
    short int pasajes;
    int dni;
    char apellidoNombre[26];
};

FILE *abrir(const char *path, const char *mode);
void cargarVuelosSemanales(ST_VUELO vuelo[MAX_VUELOS],const char *path, const char *mode);
void ordenarXIdVuelo(ST_VUELO vuelo[], int cantVuelos);
int main()
{
    
    FILE *vuelosFile = abrir("Vuelos.dat","rb");
    FILE *compradoresFile = abrir("Compradores.dat","rb");
    ST_VUELO vuelo[MAX_VUELOS];
    ST_COMPRADOR comprador;
    int pasajesDisponibles[MAX_VUELOS];
    int pasajesNoVendidos[MAX_VUELOS];
    cargarVuelosSemanales(vuelo,"Vuelos.dat","rb");
    ordenarXIdVuelo(vuelo,MAX_VUELOS);
    fread(&comprador,sizeof(ST_COMPRADOR),1,compradoresFile);
    while (!feof(compradoresFile))
    {
        for (int i = 0; i < MAX_VUELOS; i++)
        {
            if (strcmp(vuelo[i].idVuelo,comprador.idVuelo) == 0)
            {
                if (comprador.pasajes < vuelo[i].pasajes)
                {
                    vuelo[i].pasajes =- comprador.pasajes;
                }
                
            }
            
        }
        
        
    }
    
    system("pause");
    return 0;
}

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

void cargarVuelosSemanales(ST_VUELO vuelo[MAX_VUELOS],const char *path, const char *mode){
    FILE *ptrArchivo = fopen(path, mode);
    int i = 0;
    fread(&vuelo[i],sizeof(ST_VUELO),1,ptrArchivo);
    while (!feof(ptrArchivo))
    {
        i++;
        fread(&vuelo[i],sizeof(ST_VUELO),1,ptrArchivo);
    }
    
}
void ordenarXIdVuelo(ST_VUELO vuelo[], int cantVuelos)
{
    int i, j;
    ST_VUELO aux;
    i = 0;
    bool ordenado = false;
    while (i < cantVuelos && !ordenado)
    {
        ordenado = true;
        for (j = 0; j < cantVuelos - i - 1; j++)
        {

            if (strcmp(vuelo[j].idVuelo, vuelo[j + 1].idVuelo) < 0)
            {
                aux = vuelo[j];
                vuelo[j] = vuelo[j + 1];
                vuelo[j + 1] = aux;
                ordenado = false;
            }
        }
        i++;
    }
    return;
}

