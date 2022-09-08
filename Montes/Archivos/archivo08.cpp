/*
Dado el archivo binario generado en el ejercicio 7, desarrollar la codificación en C o C++ que
graba un archivo de texto, LISTADO.TXT, de los alumnos inscriptos de acuerdo al siguiente diseño.
        Legajo      Nombre y Apellido       Fecha         Código de materia
        99999999    xxxxxxxxxxxxxxxxxxxx   dd/mm/aa         999999
        99999999    xxxxxxxxxxxxxxxxxxxx   dd/mm/aa         999999
Realice la estrategia de resolución, la representación gráfica del algoritmo, y dibuje el diseño del registro
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
    FILE *lista = abrir("LISTADO.TXT", "w");
    Inscripcion *inscripcion;
    inscripcion = (Inscripcion *)malloc(sizeof(Inscripcion));

    fprintf(lista, "Legajo      Nombre y Apellido       Fecha         Código de materia\n");
    fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {

        fprintf(lista, " %d            %s                %d/%d/%d              %d\n",
                inscripcion->legajo, inscripcion->nombre, inscripcion->dia, inscripcion->mes, inscripcion->anio, inscripcion->codMateria);
        fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    }

    fclose(archivo);
    fclose(lista);
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