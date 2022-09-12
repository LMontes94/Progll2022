/*
Ej. 11: Dado el archivo binario generado en el ejercicio 10, desarrolle un programa que elimine, si los
hubiese, los registros que no contengan datos válidos de la siguiente manera:
        a) Genere un nuevo archivo, elimine el archivo original y renombre al archivo actual
        b) Compacte en el mismo archivo
*/
#include <iostream>
#include "string.h"
#define LEGAJO_INICIAL 80001
#define LEGAJO_FINAL 110000
using namespace std;

struct Inscripcion
{
    int legajo;
    int codMateria;
    int dia;
    int mes;
    int anio;
    char nombre[26];
    char apellido[26];
};

struct Registro
{
    int legajo;
    char nombre[26];
    char apellido[26];
};

FILE *abrir(const char *path, const char *mode);
void cargarArchivo(FILE *archivo, int maxRegistros, const char *path, const char *mode);
void imprimirArchivoBin(const char *path, const char *mode);
int main()
{

    FILE *archivo = abrir("FINALES_ORDENADOS.DAT", "rb");
    FILE *archivoLimpio = abrir("FINALES_ARCHIVOFINAL.DAT", "wb");
    Registro reg;

    fread(&reg, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {
        if (reg.legajo == 0)
        {
            fwrite(&reg, sizeof(Registro), 1, archivoLimpio);
        }
        fread(&reg, sizeof(Inscripcion), 1, archivo);
    }
    
    remove("FINALES_ORDENADOS.DAT");
    rename("FINALES_ARCHIVOFINAL.DAT","FINALES_ORDENADOS.DAT");

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