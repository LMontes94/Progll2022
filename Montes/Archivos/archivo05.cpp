/*
Ej. 5: Realice diagrama y codificación para el desarrollo del siguiente enunciado.
Enunciado: Dado un conjunto de Nombres y Fechas de nacimientos (AAAAMMDD), que finaliza con
un Nombre = “FIN”, informar el nombre de la persona de mayor edad.

Nombre del registroREG  Nombre Fecha (AAAAMMDD)
20 caracteres           8 dígitos enteros
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#define MAX_CHARS 20
using namespace std;

struct ST_PERSONA
{
    char nombre[MAX_CHARS + 1];
    int fecha;
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
    ST_PERSONA persona;
    ST_PERSONA mayorPersona;
    mayorPersona.fecha = 00000101;
    FILE *archivo = abrir("ALUMNOS.TXT", "r");
   
    while (strcmp(persona.nombre,"fin") != 0 &&
    fscanf(archivo, "%s %d\n",persona.nombre,persona.fecha ) != EOF)
    {
       if (persona.fecha < mayorPersona.fecha || mayorPersona.fecha == 00000101)
       {
         strcpy(mayorPersona.nombre,persona.nombre);
         mayorPersona.fecha = persona.fecha;
       }
       
    }
    printf("La persona mayor es: %s y nacio el %d",persona.nombre,persona.fecha);
    fclose(archivo);

    system("pause");
    return 0;
}