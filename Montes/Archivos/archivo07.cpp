/*
Ej. 7: Dado el archivo binario generado en el ejercicio 6, desarrolle un programa que solicitando por
teclado un código de materia permita seleccionar todos los registros que se anotaron para rendirla y los
grabe en otro archivo (MATFINALES.DAT), con el mismo diseño.
*/

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
};

FILE *abrir(const char *path, const char *mode);

int main()
{
    FILE *archivo = abrir("DIAFINALES.DAT", "rb");
    FILE *finales = abrir("MATFINALES.DAT", "wb");
    Inscripcion *inscripcion;
    inscripcion = (Inscripcion *)malloc(sizeof(Inscripcion));
    int codMateria;
    printf("Legajo");
    scanf("%d", &codMateria);

    while (codMateria > 0)
    {
        fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
        printf("Todos los inscriptos a %d son:\n",codMateria);
        while (!feof(archivo))
        {
           if (codMateria == inscripcion->codMateria)
           {
              printf("Nombre: %s\n",inscripcion->nombre);
              fwrite(&inscripcion, sizeof(Inscripcion), 1, finales);
           }
           
           fread(&inscripcion, sizeof(Inscripcion), 1, archivo); 
        }
        printf("---------------------------------------------\n");
        printf("Legajo");
        scanf("%d", &codMateria);
    }

    fclose(archivo);
    fclose(finales);
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