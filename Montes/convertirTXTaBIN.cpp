#include <iostream>
#include "string.h"

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
int main()
{
    FILE *archivo = abrir("DIASFINALES.TXT", "r");
    FILE *archivoBin = abrir("DIASFINALES.DAT", "wb");
    Inscripcion inscripcion;

    while (fscanf(archivo, "%d %s %s %d %d %d %d\n", &inscripcion.legajo, inscripcion.nombre, inscripcion.apellido, &inscripcion.anio, &inscripcion.mes,
                  &inscripcion.dia, &inscripcion.codMateria) != EOF)
    {
        printf("%d %s %s %d %d %d %d\n", inscripcion.legajo, inscripcion.nombre, inscripcion.apellido, inscripcion.anio, inscripcion.mes,
                  inscripcion.dia, inscripcion.codMateria);
        printf("-------------------------------------------------\n");         
        fwrite(&inscripcion, sizeof(Inscripcion), 1, archivoBin);
    }
    fclose(archivo);
    fclose(archivoBin);
    archivoBin = abrir("DIASFINALES.DAT", "rb");
    fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {
        printf("%d %s %s\n", inscripcion.legajo, inscripcion.nombre, inscripcion.apellido);
        fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    }
    fclose(archivo);
    system("pause");
    return 0;
}