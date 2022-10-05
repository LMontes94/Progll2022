/*
Ejercicio 1:


Dado un conjunto de N materias ( <=20) de una carrera, se tiene un archivo “MATERIAS.DAT”
con la información de cada uno de ellas:

Código de materia ( 4 caracteres).
Cantidad de alumnos ( número entero).

Además se tiene en otro archivo “ALUMNOS.DAT” con los siguientes datos:

Código de materia (4 caracteres).
Número de legajo del alumno (6 caracteres).
Nota (1 a 10) de cada alumno.

Se pide:
Informar de la cantidad de alumnos que tuvieron como nota 0, 1, ...,9, 10.
informar al final del proceso el código de materia, el % de aprobados y el de insuficientes de cada materia.

    Materia: AA11 - Aprobados 78% - Reprobados 22%
    Materia: BJD5 - Aprobados 95% - Reprobados 5%
    (...)


*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

struct ST_MATERIA
{
    char id[4];
    int alumnos;
};

struct ST_ALUMNO
{
    char idMateria[4];
    int legajo;
    int nota;
};

struct ST_AUX
{
    char idMateria[4];
    int aprobados;
    int desaprobados;
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
void imprimirNotaAlumnos(int cantidadDeAlumnosXNota[], int cantDeNotas)
{

    for (int i = 0; i < cantDeNotas; i++)
    {
        printf("Alumnos con no %d: %d\n", i, cantidadDeAlumnosXNota[i]);
    }
    return;
}
void cargarCursos(ST_MATERIA cursos[], int cantCursos, const char *path, const char *mode)
{
    FILE *archivo = abrir(path, mode);
    int i = 0;
    fread(&cursos[i], sizeof(ST_MATERIA), 1, archivo);
    while (!feof(archivo))
    {
        i++;
        fread(&cursos[i], sizeof(ST_MATERIA), 1, archivo);
    }
    fclose(archivo);
    return;
}
void ordenarXIdCurso(ST_MATERIA cursos[], int cantCursos)
{
    int i, j;
    ST_MATERIA aux;
    i = 0;
    bool ordenado = false;
    while (i < cantCursos && !ordenado)
    {
        ordenado = true;
        for (j = 0; j < cantCursos - i - 1; j++)
        {

            if (strcmp(cursos[j].id, cursos[j + 1].id) < 0)
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
void imprimirPorcentajeAproYDesaproXMateria(FILE *materiasFile, FILE *alumnosFile)
{

    FILE *materiasFile = abrir("MATERIAS.DAT", "rb");
    FILE *alumnosFile = abrir("ALUMNOS.DAT", "rb");

    ST_MATERIA materia;
    ST_ALUMNO alumno;
    int aprobados = 0, desaprobados = 0;
    float promAprobados = 0.0, promDesaprobados = 0.0;
    fread(&alumno, sizeof(alumno), 1, alumnosFile);

    fclose(materiasFile);
    fclose(alumnosFile);
    return;
}
void imprimirAprobadosXCurso(ST_MATERIA cursos[], int cantCursos, int aprobadosXCurso[])
{

    float porcentajeAprobados = 0.0;
    for (int i = 0; i < cantCursos; i++)
    {
        porcentajeAprobados = (aprobadosXCurso[i] * 100) / cursos[i].alumnos;
        printf("Codigo del Curso: %s,'%'%0.2f de aprobados\n", cursos[i].id, porcentajeAprobados);
    }

    return;
}
void imprimirDesaprobadosXCurso(ST_MATERIA cursos[], int cantCursos, int desaprobadosXCurso[])
{
    float porcentajeDesaprobados = 0.0;
    for (int i = 0; i < cantCursos; i++)
    {
        porcentajeDesaprobados = (desaprobadosXCurso[i] * 100) / cursos[i].alumnos;
        printf("Codigo del Curso: %s,'%'%0.2f de aprobados\n", cursos[i].id, porcentajeDesaprobados);
    }

    return;
}
int main()
{

    FILE *materiaFile = abrir("MATERIAS.DAT", "rb");
    FILE *alumnosFile = abrir("ALUMNOS.DAT", "rb");

    ST_MATERIA materias[20];
    ST_ALUMNO alumno;
    ST_AUX aux;
    int alumnosXNota[11] = {0};
    int aprobados[20];
    int desaprobados[20];
    cargarCursos(materias, 20, "MATERIAS.DAT", "rb");
    ordenarXIdCurso(materias, 20);

    fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
    while (!feof(materiaFile) && !feof(alumnosFile))
    {
        alumnosXNota[alumno.nota]++;
        for (int i = 0; i < 20; i++)
        {
            if (strcmp(alumno.idMateria,materias[i].id))
            {
                if (alumno.nota >= 6)
                {
                    aprobados[i]++;
                }else{
                    desaprobados[i]++;
                }                
            }
            
        }

        fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
    }

    imprimirNotaAlumnos(alumnosXNota, 11);
    imprimirAprobadosXCurso(materias,20,aprobados);
    imprimirDesaprobadosXCurso(materias,20,desaprobados);

    system("pause");
    return 0;
}