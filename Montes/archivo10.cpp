/*
Ej. 10: Dado el archivo binario generado en el ejercicio 6, desarrolle un programa que genere un archivo
ordenado por número de legajo (cada registro debe tener los campos legajo y apellido y nombre) para
todos los alumnos que se inscribieron una o más veces. Cada legajo debe ocupar una posición única y
predecible en el archivo. El intervalo de los legajos es 80001 a 110000. Pueden no presentarse todos los
legajos
*/
#include <iostream>
#include "string.h"
#define LEGAJO_INICIAL 80001
#define LEGAJO_FINAL 110000
using namespace std;

struct Inscripcion
{
    int legajo;
    int codMateria;
    int dia;
    int mes;
    int anio;
    char nombre[26];
    char apellido[26];
};

struct Registro
{
    int legajo;
    char nombre[26];
    char apellido[26];
};

FILE *abrir(const char *path, const char *mode);
void cargarArchivo(FILE *archivo, int maxRegistros, const char *path, const char *mode);
void imprimirArchivoBin(const char *path, const char *mode);
int main()
{

    FILE *archivo = abrir("DIASFINALES.DAT", "rb");
    FILE *archivoOrdenado;
    Inscripcion inscripcion;
    Registro reg;
    int maxRegistros = LEGAJO_FINAL - LEGAJO_INICIAL;
    cargarArchivo(archivoOrdenado, maxRegistros, "FINALES_ORDENADOS.DAT", "wb");
    archivoOrdenado = abrir("FINALES_ORDENADOS.DAT", "wb+");

    fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {
        reg.legajo = inscripcion.legajo;
        strcpy(reg.nombre, inscripcion.nombre);
        strcpy(reg.apellido, inscripcion.apellido);
        fseek(archivoOrdenado,sizeof(Registro)* (inscripcion.legajo-LEGAJO_INICIAL), SEEK_SET);
        fwrite(&reg, sizeof(Registro), 1, archivoOrdenado);
        fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    }
    
    fclose(archivo);
    fclose(archivoOrdenado);
    imprimirArchivoBin("FINALES_ORDENADOS.DAT", "rb");
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
void cargarArchivo(FILE *archivo, int maxRegistros, const char *path, const char *mode)
{
    archivo = abrir(path, mode);
    Registro inscriptos;
    fseek(archivo,sizeof(Registro)*(LEGAJO_FINAL-LEGAJO_INICIAL), SEEK_END);
    fwrite(0, sizeof(Registro), 1, archivo);
  
    fclose(archivo);
    return;
}
void imprimirArchivoBin(const char *path, const char *mode)
{
    FILE *archivo = abrir(path, mode);
    Registro reg;
    fread(&reg, sizeof(Registro), 1, archivo);
    while (!feof(archivo))
    {
        printf("%d %s %s\n",reg.legajo,reg.nombre,reg.apellido);
        fread(&reg, sizeof(Registro), 1, archivo);
    }
    fclose(archivo);
    return;
}