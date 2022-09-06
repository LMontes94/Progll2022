/*
Ej. 1: Se conoce de cada alumno de un curso los siguientes datos: legajo (8dígitos) y las notas de 2
parciales (0..10), que finaliza con un legajo negativo.
Se pide desarrollar un programa que ingrese los datos de los alumnos por teclado y grabe un
archivo de texto CURSO.TXT con una línea por cada alumno, con el número de legajo y su promedio
(real).
        De Entrada                      De Salida
    D                                    CURSO.TXT :Archivo de texto con una línea por cada
    A   Legajo                                    alumno con los siguientes datos
    T   Nota1 por cada alumno             Legajo
    O   Nota2 del curso                   Promedio un alumno por línea
*/

#include <iostream>
using namespace std;

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
    int legajo;
    int nota1;
    int nota2;

    FILE *archivo = abrir("CURSOS.TXT", "w");

    printf("Legajo:");
    scanf("%d", &legajo);
    while (legajo >= 0)
    {
        printf("Nota 1:");
        scanf("%d", &nota1);
        printf("Nota 2:");
        scanf("%d", &nota2);

        fprintf(archivo, "%d %.2f\n", legajo, (nota1 + nota2) / 2.0);

        printf("Legajo:");
        scanf("%d", &legajo);
    }

    fclose(archivo);

    system("pause");
    return 0;
}