/*
Ej. 18: Dado el archivo “ALUMNOS.dat” con los datos personales de alumnos ordenado por legajo, con
el siguiente diseño:
a.1 Legajo (8 dígitos) a.2 Apellido y nombre ( 30 caracteres)
a.3 Domicilio (20 caracteres) a.4 Código postal (4 dígitos)
a.5 Teléfono (10 caracteres) a.6 Año de ingreso (4 dígitos)
Y otro archivo con el mismo orden que el mencionado llamado “NOVEDADES.dat”, con las
actualizaciones (altas, bajas, y modificaciones) a ser aplicadas, donde cada registro contiene además de
todos los campos de Alumnos.dat un código de operación (“A”= Alta, “B”= Baja, “M”= Modificación).
a- Desarrollar todos los pasos necesarios para realizar un programa que genere un archivo actualizado
“ALUMACTU.dat” con el mismo diseño.
b- Rehacer el ejercicio considerando que el archivo NOVEDADES es de texto separado por tabs en
lugar de binario.
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>
#define MAX_CHARS 25
using namespace std;

struct ST_ALUMNO
{
    int legajo;
    char apellidoNombre[30];
    char domicilio[20];
    int codPostal;
    char telefono[10];
    int anioIngreso;
};

struct ST_ALUMNO_ACTUALIZACION
{
    ST_ALUMNO alumno;
    char actualizacion;
};

FILE *abrir(const char *path, const char *mode);
ST_ALUMNO actualizarAlumno(ST_ALUMNO alumno);
int main()
{
    FILE *alumnosFile = abrir("ALUMNOS.dat", "rb");
    FILE *novedadesFile = abrir("NOVEDADES.dat", "rb");
    FILE *alumnosActFile = abrir("ALUMACTU.dat", "wb");

    ST_ALUMNO alumno;
    ST_ALUMNO_ACTUALIZACION novedadAlumno;
    ST_ALUMNO alumnoAux;
    fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
    fread(&novedadAlumno, sizeof(ST_ALUMNO_ACTUALIZACION), 1, novedadesFile);
    while (!feof(alumnosFile) && !feof(novedadesFile))
    {
        if (alumno.legajo == novedadAlumno.alumno.legajo)
        {
            if (novedadAlumno.actualizacion == 'M')
            {
                alumnoAux = actualizarAlumno(novedadAlumno.alumno);
            }
            fwrite(&alumnoAux, sizeof(ST_ALUMNO), 1, alumnosActFile);
            fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
            fread(&novedadAlumno, sizeof(ST_ALUMNO_ACTUALIZACION), 1, novedadesFile);
        }
        else if (alumno.legajo < novedadAlumno.alumno.legajo)
        {
            fwrite(&alumno, sizeof(ST_ALUMNO), 1, alumnosActFile);
            fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
        }
        if (alumno.legajo > novedadAlumno.alumno.legajo)
        {
            if (novedadAlumno.actualizacion == 'A')
            {
                alumnoAux = actualizarAlumno(novedadAlumno.alumno);
            }
            fwrite(&alumnoAux, sizeof(ST_ALUMNO), 1, alumnosActFile);
            fread(&novedadAlumno, sizeof(ST_ALUMNO_ACTUALIZACION), 1, novedadesFile);
        }
    }

    while (!feof(alumnosFile))
    {
        fwrite(&alumno, sizeof(ST_ALUMNO), 1, alumnosActFile);
        fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
    }

    while (!feof(novedadesFile))
    {
        if (novedadAlumno.actualizacion == 'A')
        {
            alumnoAux = actualizarAlumno(novedadAlumno.alumno);
        }
        fwrite(&alumnoAux, sizeof(ST_ALUMNO), 1, alumnosActFile);
        fread(&novedadAlumno, sizeof(ST_ALUMNO_ACTUALIZACION), 1, novedadesFile);
    }
    fclose(alumnosFile);
    fclose(novedadesFile);
    fclose(alumnosActFile);
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

ST_ALUMNO actualizarAlumno(ST_ALUMNO alumno)
{
    ST_ALUMNO aux;
    aux.legajo = alumno.legajo;
    strcpy(aux.apellidoNombre, alumno.apellidoNombre);
    strcpy(aux.domicilio, alumno.domicilio);
    aux.codPostal = alumno.codPostal;
    strcpy(aux.telefono, alumno.telefono);
    aux.anioIngreso = alumno.anioIngreso;
    return aux;
}
