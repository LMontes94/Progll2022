/*
Ej. 13: Se dispone un archivo binario de inscripción de alumnos a exámenes finales
MAESTROFINALES.DAT y otro con las inscripciones del día de hoy DIAFINALES.DAT, ambos
ordenados ascendente por código de materia y con el siguiente diseño:
    a.1Nro de legajo (8 dígitos)   a.2 Código de materia (6 dígitos)     a.3 ApellidoNombre(25caract)
Se pide desarrollar un programa que genere un nuevo archivo de inscripciones a finales
FINALESACT.DAT resultante del apareo de los dos archivos anteriores, con el mismo orden y diseño.
    Estrategia:
         Asignar y abrir archivos
         Leer registro archivo maestro con control de EOF
         Leer registro archivo finales del día con control de EOF
         Mientras no sea fin de archivo de ninguno de los dos archivos
            o Si el código de materia del registro del maestro es menor al código de materia del registro
            del archivo del día
         Grabar registro archivo maestro en archivo de finales actualizado
         Leer registro archivo maestro con control de EOF
            o De lo contrario
         Grabar registro archivo finales del día en archivo de finales actualizado
         Leer registro archivo finales del día con control de EOF
         Por fin de archivo del maestro mientras no sea fin de archivo de finales del día
            o Grabar registro archivo finales del día en archivo de finales actualizado
            o Leer registro archivo finales del día con control de EOF
         Por fin de archivo finales del día mientras no sea fin de archivo maestro
            o Grabar registro archivo maestro en archivo de finales actualizado
            o Leer registro archivo maestro con control de EOF
         Cerrar archivos
*/
#include <iostream>
#include "string.h"
#define MAX_CHARS 25
using namespace std;

struct ST_INSCRIPCION
{
    int legajo;
    int idMateria;
    char apellidoNombre[MAX_CHARS + 1];
};

FILE *abrir(const char *path, const char *mode);

int main()
{
    FILE *maestroFinales = abrir("MAESTROFINALES.DAT", "rb");
    FILE *diaFinales = abrir("DIAFINALES.DAT", "rb");
    FILE *finalesAct = abrir("FINALESACT.DAT", "wb");
    ST_INSCRIPCION maestro;
    ST_INSCRIPCION alumno;

    fread(&maestro, sizeof(ST_INSCRIPCION), 1, maestroFinales);
    fread(&alumno, sizeof(ST_INSCRIPCION), 1, diaFinales);
    while (!feof(maestroFinales) && !feof(diaFinales))
    {
        if (maestro.idMateria < alumno.idMateria)
        {
            fwrite(&maestro, sizeof(ST_INSCRIPCION), 1, finalesAct);
            fread(&maestro, sizeof(ST_INSCRIPCION), 1, maestroFinales);
        }
        else
        {
            fwrite(&alumno, sizeof(ST_INSCRIPCION), 1, finalesAct);
            fread(&alumno, sizeof(ST_INSCRIPCION), 1, diaFinales);
        }
    }

    while (!feof(maestroFinales))
    {
        fwrite(&maestro, sizeof(ST_INSCRIPCION), 1, finalesAct);
        fread(&maestro, sizeof(ST_INSCRIPCION), 1, maestroFinales);
    }

    while (!feof(diaFinales))
    {
        fwrite(&alumno, sizeof(ST_INSCRIPCION), 1, finalesAct);
        fread(&alumno, sizeof(ST_INSCRIPCION), 1, diaFinales);
    }

    fclose(maestroFinales);
    fclose(diaFinales);
    fclose(finalesAct);
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
