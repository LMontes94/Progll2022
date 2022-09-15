/*
Ej. 17: El dueño de un local de venta de juegos para distintas consolas necesita desarrollar un algoritmo
que grabe un archivo, JuegosPorConsola.dat, ordenado por consola, con un solo registro por consola
según el siguiente diseño:
a) Consola (10 caracteres) b) Cantidad de juegos ( 4 dígitos )
Para obtener la información solicitada se cuenta con el archivo Juegos.dat, ordenado por consola, con un
registro por cada juego que se encuentra en el local, con el siguiente diseño:
1) Código del juego ( 6 dígitos )
3) Stock en el local (char)
2) Titulo del Juego (30 caracteres)
4) Consola (10 caracteres)
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>
#define MAX_CHARS 25
using namespace std;

struct ST_CONSOLA
{
    char nombre[20];
    int cantJuegos;
};

struct ST_JUEGO
{
    int idJuego;
    char *stock;
    char titulo[30];
    char consola[10];
};

FILE *abrir(const char *path, const char *mode);

int main()
{
    FILE *consolaFile = abrir("JuegosPorConsola.dat", "wb");
    FILE *juegosFile = abrir("Juegos.dat", "rb");
    ST_CONSOLA consola;
    ST_JUEGO juego;

    fread(&juego, sizeof(ST_JUEGO), 1, juegosFile);
    while (!feof(juegosFile))
    {
        strcpy(consola.nombre, juego.consola);
        while (!feof(juegosFile) && strcmp(consola.nombre, juego.consola) == 0)
        {
            int stock = atoi(juego.stock);
            consola.cantJuegos = +stock;

            fread(&juego, sizeof(ST_JUEGO), 1, juegosFile);
        }
        fwrite(&consola, sizeof(ST_CONSOLA), 1, consolaFile);
    }

    fclose(consolaFile);
    fclose(juegosFile);
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
