#include <iostream>
#include "string.h"
#include <stdio.h>
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

FILE *abrir(const char *path, const char *mode);
int main()
{
    FILE *archivo = abrir("DIASFINALES.DAT", "rb+");
    FILE *archivoOrdenadoXLegajo = abrir("Ordenado_X_Legajo.dat", "wb");
    Inscripcion inscripcion;

    long actualPos = ftell(archivo);
    fseek(archivo, 0, SEEK_END);
    long ultimo = ftell(archivo);
    fseek(archivo, actualPos, SEEK_SET);
    int cantRegistros = (int)(ultimo / sizeof(Inscripcion));
    Inscripcion inscriptosOrdenados[cantRegistros];
    int i = 0;
    fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {
        inscriptosOrdenados[i].legajo = inscripcion.legajo;
        strcpy(inscriptosOrdenados[i].nombre, inscripcion.nombre);
        strcpy(inscriptosOrdenados[i].apellido, inscripcion.apellido);
        inscriptosOrdenados[i].codMateria = inscripcion.codMateria;
        inscriptosOrdenados[i].anio = inscripcion.anio;
        inscriptosOrdenados[i].mes = inscripcion.mes;
        inscriptosOrdenados[i].dia = inscripcion.dia;
        i++;
        fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    }
    Inscripcion aux;
    int j;
    i = 0;
    bool ordenado = false;
    while (i < cantRegistros && !ordenado)
    {
        ordenado = true;
        for (j = 0; j < cantRegistros - j - 1; j++)
        {

            if (inscriptosOrdenados[j].legajo > inscriptosOrdenados[j + 1].legajo)
            {
                aux = inscriptosOrdenados[j];
                inscriptosOrdenados[j] = inscriptosOrdenados[j + 1];
                inscriptosOrdenados[j + 1] = aux;
            ordenado = false;
        }
        }
       i++; 
       fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
       printf("%d %s %s\n",inscripcion.legajo,inscripcion.nombre,inscripcion.apellido);
    }
    
    for (int k = 0; k < cantRegistros; k++)
    {
        fwrite(&inscriptosOrdenados[k], sizeof(Inscripcion), 1, archivoOrdenadoXLegajo);
    }
    fseek(archivo, 0, SEEK_SET);
    fread(&inscripcion, sizeof(Inscripcion), 1, archivoOrdenadoXLegajo);
    while (!feof(archivo))
    {
        printf("%d %s %s\n", inscripcion.legajo, inscripcion.nombre, inscripcion.apellido);
        fread(&inscripcion, sizeof(Inscripcion), 1, archivoOrdenadoXLegajo);
    }
    fclose(archivo);
    fclose(archivoOrdenadoXLegajo);
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

void leerArchivo(FILE *archivo, const char *path, const char *mode)
{
    archivo = abrir(path, mode);
    Inscripcion inscripcion;

    while (fscanf(archivo, "%d %s %s %d %d %d %d\n", &inscripcion.legajo, inscripcion.nombre, inscripcion.apellido, &inscripcion.anio, &inscripcion.mes,
                  &inscripcion.dia, &inscripcion.codMateria) != EOF)
    {
        printf("    %d               %s %s\n", inscripcion.legajo, inscripcion.nombre, inscripcion.apellido);
    }
    fclose(archivo);
    return;
}
