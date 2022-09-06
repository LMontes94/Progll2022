/*
Ej. 4 Dados los siguientes dibujos que corresponden a distintos tipos de registros realice su declaración
en C++, y especifique la nomenclatura para acceder al registro y cada uno de sus campos.

a)

Nombre           FechaNacimiento
(20 caracteres)  Dia      Mes      Anio
                 (1..31) (1..12) (4 dígitos)
char[20]          char     char     short

b)

Legajo       ApellidoNombre          Calificaciones
(8 dígitos)  Apellido    Nombre      Nota1 Nota2 Nota3
            (20 carac) (20 carac)

*/
#include <iostream>
#define MAX_CHARS 20
using namespace std;

struct ST_FECHA
{
    char dia;
    char mes;
    int anio;
};

struct ST_PERSONA
{
    char nombre[MAX_CHARS+1];
    ST_FECHA fecha;
};

struct ST_ALUMNO
{
    int legajo;
    ST_PERSONA persona;
    int calificaciones[3];
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
    ST_ALUMNO alumno;
    FILE *archivo = abrir("ALUMNOS.TXT", "r");
    printf("Número de legajo    Nombre     Notas\n");
    while (fscanf(archivo, "%d %s %d %d %d %d\n", &alumno.legajo, alumno.persona.nombre, alumno.calificaciones[0], alumno.calificaciones[1],alumno.calificaciones[2]) != EOF)
    {
        printf("    %d               %s        %d %d %d\n",
        alumno.legajo,alumno.persona.nombre, alumno.calificaciones[0], alumno.calificaciones[1],alumno.calificaciones[2]);
    }
    fclose(archivo);

    system("pause");
    return 0;
}