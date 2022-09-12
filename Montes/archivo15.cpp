/*
Ej. 15: El dueño de un local de venta de libros desea relevar el stock que posee en el local y en el
depósito, para realizar las compras del mes.
Para ello cuenta con dos archivos:
        a) StockEnLocal.dat, ordenado por código del libro, con un registro por cada libro que se
        encuentra en el local, con el siguiente diseño:
        a.1) Código de libro ( 4 dígitos )
        a.3) Autor (20 caracteres)
        a.6) Stock en el local (char)
        a.2) Título del libro (30 caracteres)
        a.4) Editorial (20 caracteres)
        a.7) Genero ( 10 caracteres)
        b) StockEnDeposito.dat, ordenado por código del libro, con un registro por cada libro que se
        encuentra en el depósito, con el siguiente diseño:
        b.1) Código de libro ( 4 dígitos ) b.2) Stock en depósito (unsigned char)
        Se pide desarrollar la metodología necesaria para escribir un algoritmo que emita un listado ordenado por
        código de libro, con un renglón por cada libro que tenga faltante en stock sea en depósito, local o en
        ambos lugares, con el siguiente formato:
                Libros faltantes
                Código Observación
                9999 Falta en depósito
                9999 Falta en local
                9999 Falta en local y en depósito
                Total de libros en falta: 9999999
*/
#include <iostream>
#include "string.h"
#define MAX_CHARS 25
using namespace std;

struct ST_LOCAL
{
    int idLibro;
    char autor[20];
    char stock;
    char titulo[30];
    char editorial[20];
    char genero[10];
};

struct ST_DEPOSITO
{
    int idLibro;
    char stock;
};

FILE *abrir(const char *path, const char *mode);

int main()
{
    FILE *stockLocal = abrir("StockEnLocal.dat", "rb");
    FILE *stockDeposito = abrir("StockEnDeposito.dat", "rb");
    ST_LOCAL local;
    ST_DEPOSITO deposito;
    int librosFaltantes = 0;
    fread(&local, sizeof(ST_LOCAL), 1, stockLocal);
    fread(&deposito, sizeof(ST_DEPOSITO), 1, stockDeposito);

    while (!feof(stockLocal))
    {

        int key = local.idLibro;
        while (!feof(stockDeposito) && key == local.idLibro)
        {
            if (local.stock == '0' && deposito.stock == '0')
            {
                printf("%d  Falta en local y en depósito\n", local.idLibro);
                librosFaltantes++;
            }
            else if (local.stock == '0')
            {
                printf("%d  Falta en local\n", local.idLibro);
                librosFaltantes++;
            }
            else if (deposito.stock == '0')
            {
                printf("%d  Falta en depósito\n", deposito.idLibro);
                librosFaltantes++;
            }
            fread(&deposito, sizeof(ST_DEPOSITO), 1, stockDeposito);
        }

        fread(&local, sizeof(ST_LOCAL), 1, stockLocal);
    }
    printf("Total de libros en falta: %d",librosFaltantes);
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
