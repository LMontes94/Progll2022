/*
Ej. 10: Dado el archivo binario generado en el ejercicio 6, desarrolle un programa que genere un archivo
ordenado por número de legajo (cada registro debe tener los campos legajo y apellido y nombre) para
todos los alumnos que se inscribieron una o más veces. Cada legajo debe ocupar una posición única y
predecible en el archivo. El intervalo de los legajos es 80001 a 110000. Pueden no presentarse todos los
legajos
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
FILE *burbujeoMejorado();
int main()
{
    FILE *archivo = abrir("DIAFINALES.DAT", "rb");
    FILE *inscripcionesAnteriores = abrir("FINALES.DAT", "ab");
    Inscripcion *inscripcion;
    inscripcion = (Inscripcion *)malloc(sizeof(Inscripcion));

    fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {
        fwrite(&inscripcion, sizeof(Inscripcion), 1, inscripcionesAnteriores);
        fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    }

    fclose(archivo);
    fclose(inscripcionesAnteriores);

    inscripcionesAnteriores = abrir("FINALES.DAT", "rb");

    fread(&inscripcion, sizeof(Inscripcion), 1, inscripcionesAnteriores);
    printf("Legajo      Nombre y Apellido       Fecha         Código de materia\n");
    while (!feof(inscripcionesAnteriores))
    {
        printf(" %d            %s                %d/%d/%d              %d\n",
               inscripcion->legajo, inscripcion->nombre, inscripcion->dia, inscripcion->mes, inscripcion->anio, inscripcion->codMateria);
        fread(&inscripcion, sizeof(Inscripcion), 1, inscripcionesAnteriores);
    }
    fclose(inscripcionesAnteriores);
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

FILE *burbujeoMejorado(FILE *inscriptos)
{
    FILE *ptrArchivo = abrir("ORDENADO_X_LEGAJO.DAT", "wb");
    Inscripcion *inscripcion;
    inscripcion = (Inscripcion *)malloc(sizeof(Inscripcion));
    int i, j, aux;
    i = 0;
    bool ordenado = false;
    fread(&inscripcion, sizeof(Inscripcion), 1, inscriptos);
    while (!feof(inscriptos) && !ordenado)
    {
        ordenado = true;
        for (j = 0; j < arr.length - i - 1; j++)
        {

            if (arr[j].points < arr[j + 1].points)
            {
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
                ordenado = false;
            }
            if (arr[j].points == arr[j + 1].points)
            {
                if (arr[j].df < arr[j + 1].df)
                {
                    aux = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = aux;
                    ordenado = false;
                }
            }
        }
        i++;
    }
    return ptrArchivo;
}