/*
Ej. 6: Se dispone de un conjunto de boletas de inscripción de alumnos a examen en el mes de mayo.
Cada boleta tiene los siguientes datos: nombre y apellido, número de legajo, código de materia,
día, mes y año del examen. Los datos finalizan con un nombre y apellido nulo.
Desarrollar un programa que a partir del ingreso de las boletas mencionadas, por teclado, genere
un archivo binario de inscripción de alumnos a exámenes finales DIAFINALES.DAT, según el siguiente
diseño:
        a.1Nro. de legajo (8 dígitos) a.2 Código de materia (6 dígitos)
        a.3Día del examen (1..31) a.4 Mes del examen (1..12)
        a.5Año del examen (4 dígitos) a.6 Nombre-Apellido (25caract)
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
    FILE *archivo = abrir("DIAFINALES.DAT", "wb");
    Inscripcion inscripcion;

    printf("Apellido y Nombre:");
    gets(inscripcion.nombre);
    while (strcmp(inscripcion.nombre, "fin") != 0)
    {
        printf("Legajo:");
        scanf("%d", &inscripcion.legajo);
        printf("Materia:");
        scanf("%d", &inscripcion.codMateria);
        printf("Fecha (dd mm aaaa):");
        scanf("%d", &inscripcion.dia);
        scanf("%d", &inscripcion.mes);
        scanf("%d", &inscripcion.anio);

        fwrite(&inscripcion, sizeof(Inscripcion), 1, archivo);

        printf("Apellido y Nombre:");
        gets(inscripcion.nombre);
    }

    fclose(archivo);
    archivo = abrir("DIAFINALES.DAT", "rb");
    FILE *archivoTxt = abrir("DIAFINALESTXT.TXT", "wt");
    fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {
        fprintf(archivoTxt, "%s %d %d %d/%d/%d\n", inscripcion.nombre, inscripcion.codMateria, inscripcion.legajo, inscripcion.dia, inscripcion.mes, inscripcion.anio);
        fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    }

    fclose(archivo);
    fclose(archivoTxt);
    system("pause");
    return 0;
}