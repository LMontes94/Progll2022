/*
Una aplicación para descargas de Series posee la información en un archivo binario,
Episodios.dat, con un registro por cada episodio, ordenado ascendente por Id_Serie y Número de
temporada, con el siguiente diseño:
1) Id_Serie ( 9 dígitos )
3) Número de temporada (1..12)
5) Cantidad de descargas (long)
2) Título del episodio (20 caracteres)
4) Número de episodio (unsigned char)
6) Fecha de última descarga (aaaammdd)
Se pide desarrollar la metodología necesaria para escribir un algoritmo emita el siguiente listado:
Listado de Descargas de Series

Serie: 999999999
Temporada: 99
    N. de Episodio     Título del Episodio       Cant. descargas    Fecha de última descarga
            999            xxxxxxxxxxxxxx            9999999           dd/mm/aaaa
            999            xxxxxxxxxxxxxx            9999999           dd/mm/aaaa
.....................................................................................
Cant. Total de Episodios de la Serie: 99999
Total descargas de la temporada:999999999
Serie: 999999999
Temporada: 99
    N. de Episodio   Título del Episodio      Cant. descargas    Fecha de última descarga
        999           xxxxxxxxxxxxxx              9999999             dd/mm/aaaa
        999           xxxxxxxxxxxxxx              9999999             dd/mm/aaaa
.....................................................................................
*Cant. Total de Episodios de la temporada: 99999
*Total descargas de la temporada: 999999999
**Cant. Total de Episodios de la Serie: 99999
**Total descargas de la Serie: 999999999
.......................................................................
***Total General de series: 9999
*/
#include <iostream>
#include "string.h"
#define MAX_CHARS 25
using namespace std;

struct ST_SERIE
{
    int idSerie;
    int temporada;
    long descargas;
    char titulo[30];
    char nroEpisodio;
    int fechaUltimaDescarga;
};

FILE *abrir(const char *path, const char *mode);

int main()
{
    FILE *episodiosFile = abrir("Episodios.dat", "rb");
    ST_SERIE serie;

    int totalSeries = 0;
    fread(&serie, sizeof(ST_SERIE), 1, episodiosFile);
    while (!feof(episodiosFile))
    {
        int cantCapSerie = 0;
        int descargasSerie = 0;
        printf("Serie: %d\n", serie.idSerie);
        int idserie = serie.idSerie;
        while (!feof(episodiosFile) && idserie == serie.idSerie)
        {
            printf("Temporada: %d\n", serie.temporada);
            int temporada = serie.temporada;
            int cantEpisodios = 0;
            int descargasTemporada = 0;
            printf("N. de Episodio     Título del Episodio       Cant. descargas    Fecha de última descarga\n");
            while (!feof(episodiosFile) && temporada == serie.temporada)
            {
                printf(" %s           %s              %d             %d\n", serie.nroEpisodio, serie.titulo, serie.descargas, serie.fechaUltimaDescarga);
                descargasTemporada = +serie.descargas;
                cantEpisodios++;
                fread(&serie, sizeof(ST_SERIE), 1, episodiosFile);
            }
            printf(".....................................................................................\n");
            printf("Cant. Total de Episodios de la Serie: %d\n", cantEpisodios);
            printf("Total descargas de la temporada: %d\n", descargasTemporada);
            cantCapSerie = +cantEpisodios;
            descargasSerie = +descargasTemporada;
        }
        printf("Cant. Total de Episodios de la Serie: %d\n",cantCapSerie);
        printf("Total descargas de la Serie: %d\n",descargasSerie);
        totalSeries++;
    }
    printf(".....................................................................................\n");
    printf("Total General de series: %d\n",totalSeries);
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
