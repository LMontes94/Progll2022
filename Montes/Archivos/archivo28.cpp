/*
Ej. 28: Una biblioteca maneja la siguiente información:
a) un archivo de Libros, ordenado por código de libro y con el siguiente diseño:
a.1 Código del libro (6dígitos) a.2 título del libro (30 caract)
a.3 cantidad de ejemplares (2
dígitos)
a.4 ubicación (3 caract)
a.5 código de la editorial (1..200) a.6 autor (25 caract)
b) un archivo de editoriales ordenado alfabéticamente por nombre de la editorial, con el siguiente diseño.
 nombre de la editorial (25 caracteres)
 código de la editorial (1..200)
c) un archivo de consultas realizadas durante el primer semestre del año. Los diferentes libros consultados
no superan los 1000, y el diseño del registro es el siguiente:
 código del libro
 fecha de consulta (aaaammdd)
Se pide realizar la metodología necesaria para obtener un programa que:
1) Emitir un listado con los libros que tuvieron como mínimo 20 consultas en cada mes del semestre, con
el siguiente diseño, ordenado por código:
Código del Libro    Título     Autor         Editorial        Consultas en el Semestre
                                                                1 2 3 4 5 6
999999            xxxxxxxxx  xxxxxxxxx       xxxxxxxxx         999 999 999 999 999 999
999999            xxxxxxxxx  xxxxxxxxx       xxxxxxxxx         999 999 999 999 999 999


2) Grabar un archivo ordenado alfabéticamente por editorial con el siguiente diseño:
2.1 nombre de la editorial (25 caracteres)
2.2 porcentaje de libros que fueron consultados en el semestre (float)
Restricciones: memoria para arrays 32000 bytes
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_CHARS 30
#define MAX_EDITORIALES 200
#define MAX_CONSULTAS 1000
#define SEMESTRE 6
using namespace std;

struct ST_LIBRO
{
    int id;
    char titulo[MAX_CHARS];
    short int ejemplares;
    char ubicacion[3];
    int idEditorial;
    char autor[MAX_CHARS];
};

struct ST_EDITORIAL
{
    char nombre[MAX_CHARS];
    int id;
};

struct ST_CONSULTA
{
    int id;
    int fecha;
};

struct ST_EDITORIAL_AUX
{
    char nombre[MAX_CHARS];
    float porcentaje;
};

FILE *abrir(const char *path, const char *mode);
void cargarConsultas(ST_CONSULTA consulta[], int cantCosultas, FILE *archivo);
void cargarEditoriales(ST_EDITORIAL editorial[], int cantEditoriales, FILE *archivo);
void contarConsultasXMes(int consultaXMes[][SEMESTRE], int cantConsultas, ST_CONSULTA consulta[]);
bool consultasMayoresA20(int consultaXMes[][SEMESTRE], int idLibro);
ST_EDITORIAL obtenerEditorial(int pos, FILE *archivo);
int contarRegistros(FILE *file);
int buscarEditorial(int idEditorial, FILE *archivo);

int main()
{

    FILE *librosFile = abrir("Libros.dat", "rb");
    FILE *editorialesFile = abrir("Editoriales.dat", "rb");
    FILE *consultasFile = abrir("Consultas.dat", "rb");
    FILE *porcentajeXEditorial = abrir("Porcentaje_X_Editorial","wb");

    ST_EDITORIAL editorial[MAX_EDITORIALES];
    ST_LIBRO libro;
    ST_CONSULTA consulta[MAX_CONSULTAS];
    int consultaXmes[MAX_CONSULTAS][SEMESTRE];
    ST_EDITORIAL_AUX editorialAux[MAX_EDITORIALES];

    cargarConsultas(consulta, MAX_CONSULTAS, consultasFile);
    fclose(consultasFile);

    /*cargarEditoriales(editorial, MAX_EDITORIALES, editorialesFile);
    fclose(editorialesFile);*/

    contarConsultasXMes(consultaXmes, MAX_CONSULTAS, consulta);
    printf("Código del Libro    Título     Autor         Editorial        Consultas en el Semestre\n");
    printf("                                                                1  2  3  4  5  6\n");
    for (int i = 0; i < MAX_CONSULTAS; i++)
    {
        if (consultasMayoresA20(consultaXmes, i))
        {
            fseek(librosFile, (consulta[i].id - 1) * sizeof(ST_LIBRO), SEEK_SET);
            fread(&libro, sizeof(ST_LIBRO), 1, librosFile);
            int posEditorial = buscarEditorial(libro.idEditorial, editorialesFile);
            ST_EDITORIAL editorialAux = obtenerEditorial(posEditorial,editorialesFile);
            printf("%d    %s      %s      %s      ", libro.id, libro.titulo, libro.autor,editorialAux.nombre);
            for (int j = 0; j < SEMESTRE; j++)
            {
                printf(" %d ",consultaXmes[i][j]);
            }
            printf("\n");
        }
    }

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
ST_EDITORIAL obtenerEditorial(int pos, FILE *archivo)
{
    ST_EDITORIAL editorial;
    fseek(archivo, pos * sizeof(ST_EDITORIAL), SEEK_SET);
    fread(&editorial, sizeof(ST_EDITORIAL), 1, archivo);
    return editorial;
}
int contarRegistros(FILE *file)
{
    int posActual = ftell(file);

    fseek(file, 0, SEEK_END);
    int cant = ftell(file) / sizeof(ST_EDITORIAL);

    fseek(file, posActual, SEEK_SET);
    return cant;
}

int buscarEditorial(int idEditorial, FILE *archivo)
{
    int inicio = 0;
    int fin = contarRegistros(archivo) - 1;
    while (fin >= inicio)
    {
        int mitad = inicio + (fin - inicio) / 2;
        // Si el elemento es el del medio, devolvemos la posicion
        ST_EDITORIAL editorial = obtenerEditorial(mitad, archivo);
        if (editorial.id == idEditorial)
        {
            return mitad;
        }
        // Si el elemento es menor entonces solo puede estar en la primer mitad
        if (editorial.id < idEditorial)
        {
            fin = mitad - 1; // Cambio el limite superior
        }
        else
        {
            inicio = mitad + 1; // Cambio el limite inferior
        }
    }
    // Si llegamos hasta aca es que el elemento no estaba
    return -1;
}
