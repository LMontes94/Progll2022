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
FILE *burbujeoMejorado();
void leerArchivo(FILE, const char *path, const char *mode);
int main()
{
    FILE *archivo = abrir("DIASFINALES.DAT", "rb");
    FILE *archivoOrdenadoXLegajo = abrir("Ordenado_X_Legajo.dat","wb");
    Inscripcion inscripcion;
    Inscripcion inscripcionAux;
   /* printf("Lectura del archivo antes de ordenar\n");
    leerArchivo(archivo, "DIASFINALES.TXT", "r");
    printf("------------------------------------------------");*/

    int i;
    i = 0;
    bool ordenado = false;
    fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo) && !ordenado)
    {
        ordenado = true;
        fread(&inscripcionAux, sizeof(Inscripcion), 1, archivo);
        if (inscripcion.legajo > inscripcionAux.legajo)
        {
            fseek(archivo, (i) * sizeof(Inscripcion), SEEK_SET);
            fwrite(&inscripcionAux,sizeof(Inscripcion),1,archivo);
            fwrite(&inscripcion,sizeof(Inscripcion),1,archivo);
            ordenado = false;
        }
       i++; 
       fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
       printf("%d %s %s",inscripcion.legajo,inscripcion.nombre,inscripcion.apellido);
    }
    
    fclose(archivo);
    fclose(archivoOrdenadoXLegajo);

    archivoOrdenadoXLegajo = abrir("Ordenado_X_Legajo.dat","wb");
    fread(&inscripcion, sizeof(Inscripcion), 1, archivoOrdenadoXLegajo);
    while (!feof(archivo))
    {
        printf("%d %s %s\n",inscripcion.legajo,inscripcion.nombre,inscripcion.apellido);
        fread(&inscripcion, sizeof(Inscripcion), 1, archivoOrdenadoXLegajo);
    }

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