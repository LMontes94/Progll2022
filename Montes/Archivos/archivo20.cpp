/*
Dado un conjunto de N cursos ( <=20) de una materia, se tiene un archivo “CURSOS.DAT” con
la información de cada uno de ellos: código de curso ( 4 caracteres) y cantidad de alumnos. Además se
tiene en otro archivo “ALUMNOS.DAT” con el curso, legajo y nota (1 a 10) de cada alumno.
Se pide:
 informar de la cantidad de alumnos que tuvieron como nota 0, 1, ...,9, 10
 informar al final del proceso el código de curso, el % de aprobados y el de insuficientes de cada
curso.
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_CURSOS 20
#define MAX_NOTAS 10

using namespace std;

struct ST_CURSO
{
    char idCurso[4];
    int cantAlumnos;
};

struct ST_ALUMNO
{
    int legajo;
    int nota;
    char idCurso[4];
};

FILE *abrir(const char *path, const char *mode);
void cargarCursos(ST_CURSO cursos[], int cantCursos, const char *path, const char *mode);
void ordenarXIdCurso(ST_CURSO cursos[], int cantCursos);
void imprimirCantidadXNota(int notas[], int cantNotas);
void imprimirAprobadosXCurso(ST_CURSO cursos[], int cantCursos, int aprobadosXCurso[]);
void imprimirDesaprobadosXCurso(ST_CURSO cursos[], int cantCursos, int desaprobadosXCurso[]);
int main()
{
    FILE *cursosFile = abrir("CURSOS.DAT", "rb");
    FILE *alumnosFile = abrir("ALUMNOS.DAT", "rb");
    ST_ALUMNO alumno;
    ST_CURSO cursos[MAX_CURSOS];
    int notas[MAX_NOTAS] = {0};
    int aprobados[MAX_CURSOS];
    int desaprobados[MAX_CURSOS];

    cargarCursos(cursos, MAX_CURSOS, "CURSOS.DAT", "rb");
    ordenarXIdCurso(cursos, MAX_CURSOS);
    fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
    while (!feof(alumnosFile))
    {
        notas[alumno.nota - 1]++;
        for (int i = 0; i < MAX_CURSOS; i++)
        {
            if (strcmp(alumno.idCurso, cursos[i].idCurso) == 0)
            {
                if (alumno.nota < 7)
                {
                    desaprobados[i]++;
                }
                else
                {
                    aprobados[i]++;
                }
            }
        }

        fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
    }

    imprimirCantidadXNota(notas, MAX_NOTAS);

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

void cargarCursos(ST_CURSO cursos[], int cantCursos, const char *path, const char *mode)
{
    FILE *archivo = abrir(path, mode);
    int i = 0;
    fread(&cursos[i], sizeof(ST_CURSO), 1, archivo);
    while (!feof(archivo))
    {
        i++;
        fread(&cursos[i], sizeof(ST_CURSO), 1, archivo);
    }
    fclose(archivo);
    return;
}
void ordenarXIdCurso(ST_CURSO cursos[], int cantCursos)
{
    int i, j;
    ST_CURSO aux;
    i = 0;
    bool ordenado = false;
    while (i < cantCursos && !ordenado)
    {
        ordenado = true;
        for (j = 0; j < cantCursos - i - 1; j++)
        {

            if (strcmp(cursos[j].idCurso, cursos[j + 1].idCurso) < 0)
            {
                aux = cursos[j];
                cursos[j] = cursos[j + 1];
                cursos[j + 1] = aux;
                ordenado = false;
            }
        }
        i++;
    }
    return;
}
void imprimirCantidadXNota(int notas[], int cantNotas)
{
    for (int i = 0; i < cantNotas; i++)
    {
        printf("La cantidad de alumnos que tuvieron como nota %d: %d\n", (i + 1), notas[i]);
    }

    return;
}
void imprimirAprobadosXCurso(ST_CURSO cursos[], int cantCursos, int aprobadosXCurso[])
{

    float porcentajeAprobados = 0.0;
    for (int i = 0; i < cantCursos; i++)
    {
        porcentajeAprobados = (aprobadosXCurso[i] * 100) / cursos[i].cantAlumnos;
        printf("Codigo del Curso: %s,'%'%0.2f de aprobados\n", cursos[i].idCurso, porcentajeAprobados);
    }

    return;
}

void imprimirDesaprobadosXCurso(ST_CURSO cursos[], int cantCursos, int desaprobadosXCurso[])
{
    float porcentajeDesaprobados = 0.0;
    for (int i = 0; i < cantCursos; i++)
    {
        porcentajeDesaprobados = (desaprobadosXCurso[i] * 100) / cursos[i].cantAlumnos;
        printf("Codigo del Curso: %s,'%'%0.2f de aprobados\n", cursos[i].idCurso, porcentajeDesaprobados);
    }

    return;
}