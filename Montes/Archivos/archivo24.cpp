/*
Ej. 24: Se realiza un censo en las distintas escuelas del país. La información se encuentra en el archivo
binario DATOSESCUELAS.DAT con un registro por cada escuela censada, con el siguiente diseño:
a.1 Nombre de provincia (20 caracteres) a.2 Nombre de la Ciudad (20 caracteres) a.3 Nro. de escuela (3
dígitos) a.4 Cantidad de alumnos (4 dígitos)
El archivo está ordenado por ciudad dentro de provincia. Se pide desarrollar un algoritmo que:
a) emita el siguiente listado:
****************** Listado de Escuelas *********************
Provincia de ......................
Ciudad
de......................
Escuela N° Cantidad de alumnos
........ ................
........ ...............
Total Escuelas Ciudad ......... Total
alumnos...............
Ciudad
de......................
Escuela N° Cantidad de alumnos
........ ................
........ ...............
Total Escuelas Ciudad ......... Total alumnos...............
Total Escuelas Provincia ......... Total alumnos...............
Provincia de
......................
Ciudad de......................
Escuela N°

Cantidad de
alumnos
........ ...............
Total Escuelas Ciudad ......... Total alumnos...............
Total Escuelas Provincia ......... Total alumnos...............
Total Escuelas País ......... Total alumnos...............

b) grabe un archivo binario de totales, ordenado por cantidad de alumnos, con el siguiente diseño:
b.1 Nombre de provincia (20 caracteres)
b.2 Cantidad de alumnos (long)
NOTA: Utilice el siguiente juego de datos para el seguimiento del algoritmo:

Provincia Ciudad N° de escuela Cantidad de Alumnos
BSAS LA PLATA 10 500
BSAS LA PLATA 15 800
BSAS MERCEDES 8 600
SAN LUIS MERCEDES 3 400
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_CHARS 20
using namespace std;

struct ST_REGISTRO
{
    char provincia[MAX_CHARS];
    char ciudad[MAX_CHARS];
    int escuela;
    int alumnos;
};

struct ST_AUX
{
    char provincia[MAX_CHARS];
    long alumnos;
};

FILE *abrir(const char *path, const char *mode);
int main()
{

    FILE *escuelasFile = abrir("DATOSESCUELAS.DAT", "rb");
    FILE *totalAlumnosFile = abrir("TotalAlumnosXprovincia.dat", "wb");
    ST_REGISTRO registro;
    ST_AUX aux;
    char provincia[MAX_CHARS];
    char ciudad[MAX_CHARS];
    int totalEscuelasPais = 0;
    int totalAlumnosPais = 0;
    printf("****************** Listado de Escuelas *********************\n");
    fread(&registro, sizeof(ST_REGISTRO), 1, escuelasFile);
    while (!feof(escuelasFile))
    {
        printf("Provincia de %s\n", registro.provincia);
        strcpy(provincia, registro.provincia);
        int totalEscuelasProvincia = 0;
        aux.alumnos = 0;
        while (!feof(escuelasFile) && strcmp(provincia, registro.provincia) == 0)
        {
            printf("Ciudad\n");
            printf("de %s\n", registro.ciudad);
            printf("Escuela N°     Cantidad de alumnos\n");
            strcpy(ciudad, registro.ciudad);
            int totalEscuelasCiudad = 0;
            int totalAlumnosCiudad = 0;
            while (!feof(escuelasFile) && strcmp(provincia, registro.provincia) == 0 && strcmp(ciudad, registro.ciudad) == 0)
            {
                printf("  %d                  %d\n", registro.escuela, registro.alumnos);
                totalAlumnosCiudad = +registro.alumnos;
                totalEscuelasCiudad++;
                fread(&registro, sizeof(ST_REGISTRO), 1, escuelasFile);
            }
            printf("Total Escuelas Ciudad %d -- Total alumnos %d\n",totalEscuelasCiudad,totalAlumnosCiudad);
            totalEscuelasProvincia =+ totalEscuelasCiudad;
            aux.alumnos =+ totalAlumnosCiudad;
        }
        printf("Total Escuelas Provincia %d -- Total alumnos %d\n",totalEscuelasProvincia,aux.alumnos);
        strcpy(aux.provincia, provincia);
        fwrite(&aux, sizeof(ST_AUX), 1, totalAlumnosFile);
        totalEscuelasPais =+ totalEscuelasProvincia;
        totalAlumnosPais =+ aux.alumnos;
    }
    printf("Total Escuelas País %d -- Total alumnos %d\n",totalEscuelasPais,totalAlumnosPais);

    fclose(escuelasFile);
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