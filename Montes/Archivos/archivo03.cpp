/*
Ej. 3: Dado el siguiente dibujo de un registro, especifique la nomenclatura para acceder al registro y cada
uno de sus campos, y las operaciones que se pueden realizar a nivel registro y a nivel campos. Defina otro
registro del mismo tipo de datos.

        Legajo         ApellidoNombre          Nota
        8 dígitos       25 caracteres           0..10
*/
#include <iostream>
#define MAX_CHARS 25
using namespace std;

struct ST_ALUMNO
{
    int legajo;
    char *nombre[MAX_CHARS + 1];
    int nota1;
    int nota2;
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
    FILE *archivo = abrir("CURSOS.TXT", "r");
    printf("Número de legajo    Nombre     Notas\n");
    while (fscanf(archivo, "%d %s %d %d\n", &alumno.legajo, alumno.nombre, &alumno.nota1, &alumno.nota2) != EOF)
    {
        printf("    %d               %s        %d %d\n", alumno.legajo, alumno.nombre, alumno.nota1, alumno.nota2);
    }
    fclose(archivo);

    system("pause");
    return 0;
}