/*
Ej. 14: Una empresa de cable desea actualizar el archivo de series que emite por sus distintos canales,
con material nuevo. Para ello posee los siguientes archivos:
    a) un archivo maestro de series, Series.dat, con un registro con los datos de cada series, ordenado
        ascendente por Id_Serie, con el siguiente diseño:
            a.1) Id_Serie a.2) Título de la serie a.3) Genero
                ( 9 dígitos ) (20 caracteres) ( 10 caracteres)
            b) otro archivo de novedades de series, NovSeries.dat, con el mismo diseño y orden que el archivo
            anterior, que contiene las novedades a incorporar.
            Se pide desarrollar la metodología necesaria para escribir un algoritmo que Grabe un archivo maestro de
            series actualizado, ActSeries.dat, con el mismo diseño y orden que los anteriores.
*/

#include <iostream>
#include "string.h"
#define MAX_CHARS 25
using namespace std;

struct ST_SERIE
{
    int idSerie;
    char titulo[20];
    char genero[10];
};

FILE *abrir(const char *path, const char *mode);

int main()
{
    FILE *seriesMaster = abrir("Series.dat", "rb");
    FILE *novSeries = abrir("NovSeries.dat", "rb");
    FILE *actSeries = abrir("ActSeries.dat", "wb");
    ST_SERIE serie;
    ST_SERIE nuevaSerie;

    fread(&serie, sizeof(ST_SERIE), 1, seriesMaster);
    fread(&nuevaSerie, sizeof(ST_SERIE), 1, novSeries);
    while (!feof(seriesMaster) && !feof(novSeries))
    {
        if (serie.idSerie < nuevaSerie.idSerie)
        {
            fwrite(&serie, sizeof(ST_SERIE), 1, actSeries);
            fread(&serie, sizeof(ST_SERIE), 1, seriesMaster);
        }
        else
        {
            fwrite(&nuevaSerie, sizeof(ST_SERIE), 1, actSeries);
            fread(&nuevaSerie, sizeof(ST_SERIE), 1, novSeries);
        }
    }

    while (!feof(seriesMaster))
    {
        fwrite(&serie, sizeof(ST_SERIE), 1, actSeries);
        fread(&serie, sizeof(ST_SERIE), 1, seriesMaster);
    }

    while (!feof(novSeries))
    {
        fwrite(&nuevaSerie, sizeof(ST_SERIE), 1, actSeries);
        fread(&nuevaSerie, sizeof(ST_SERIE), 1, novSeries);
    }

    fclose(seriesMaster);
    fclose(novSeries);
    fclose(actSeries);
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
