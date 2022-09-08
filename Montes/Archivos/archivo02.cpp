/*
Ej. 2: Dado el archivo del EJ. 1 grabe otro archivo APROB.TXT que contenga una primer línea con el
siguiente título “Listado de alumnos aprobados”, y a continuación una por cada alumno con el legajo y
promedio de aquellos alumnos cuyo promedio sea >= 6.
Archivos de entrada y de salida

Archivo de Entrada
CURSO.TXT

Archivo de Salida
APROB.TXT
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
    FILE *aprobados = abrir("APROB.TEXT","w");
    float promedio;
    printf("Legajo:");
    scanf("%d", &legajo);
    while (legajo >= 0)
    {
        printf("Nota 1:");
        scanf("%d", &nota1);
        printf("Nota 2:");
        scanf("%d", &nota2);
        
        promedio = (nota1 + nota2) / 2.0;
        fprintf(archivo, "%d %.2f\n", legajo, promedio);
        
        if (promedio > 6.9)
        {
            fprintf(aprobados, "%d %.2f\n", legajo, promedio);
        }
        
        printf("Legajo:");
        scanf("%d", &legajo);
    }



    fclose(archivo);
    fclose(aprobados);
    system("pause");
    return 0;
}