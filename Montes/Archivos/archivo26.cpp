/*
Ej. 26: Dado el archivo “ALUMNOS.dat” con los datos personales de alumnos ordenado por legajo, con
el siguiente diseño:
a.1 Legajo (8 dígitos) a.2 Apellido y nombre ( 30 caracteres)
a.3 Domicilio (20 caracteres) a.4 Código postal (4 dígitos)
a.5 Teléfono (10 caracteres) a.6 Año de ingreso (4 dígitos)
Y otro archivo sin orden que el mencionado llamado “NOVEDADES.dat”, con cantidad máxima de
registros es 100. Posee las actualizaciones (altas, bajas, y modificaciones) a ser aplicadas, donde cada
registro contiene además de todos los campos de Alumnos.dat un código de operación (‘A’= Alta, ‘B’=
Baja, ‘M’= Modificación).
Se pide desarrollar todos los pasos necesarios para realizar un programa que genere un archivo
actualizado “ALUMACTU.dat” con el mismo diseño.
Restricciones:
1) memoria para arrays 7200 bytes 2) memoria para arrays 900 bytes
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_CHARS 30
#define MAX_REGISTROS 100
using namespace std;

struct ST_ALUMNO
{
    long int legajo;
    char apellidoNombre[MAX_CHARS];
    char domicilio[20];
    short int codPostal;
    char telefono[10];
    short int anioIngreso;
}; 

struct ST_ALUMNO_ACTUALIZACION
{
    ST_ALUMNO alumno;
    char actualizacion;
};

FILE *abrir(const char *path, const char *mode);
ST_ALUMNO actualizarAlumno(ST_ALUMNO alumno);
void cargarNovedades(ST_ALUMNO_ACTUALIZACION registros[], int maxRegistros, FILE *archivo);
void ordenarResgistrosXLegajo(ST_ALUMNO_ACTUALIZACION registros[],int maxRegistros);
int main()
{

    FILE *alumnosFile = abrir("ALUMNOS.dat", "rb");
    FILE *novedadesFile = abrir("NOVEDADES.dat", "rb");
    FILE *alumnosActualizadosFile = abrir("ALUMACTU.dat","wb");
    ST_ALUMNO alumno;
    ST_ALUMNO alumnoAux;
    ST_ALUMNO_ACTUALIZACION registros[MAX_REGISTROS];
    int i = 0;
    
    cargarNovedades(registros,MAX_REGISTROS,novedadesFile);
    fclose(novedadesFile);
    ordenarResgistrosXLegajo(registros,MAX_REGISTROS);

    fread(&alumno,sizeof(ST_ALUMNO),1,alumnosFile);
    while (!feof(alumnosFile) && i < MAX_REGISTROS)
    {
        if (alumno.legajo == registros[i].alumno.legajo)
        {
            if (registros[i].actualizacion == 'M')
            {
                alumnoAux = actualizarAlumno(registros[i].alumno);
            }
            fwrite(&alumnoAux, sizeof(ST_ALUMNO), 1, alumnosActualizadosFile);
            fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
            i++;
        }
        else if (alumno.legajo < registros[i].alumno.legajo)
        {
            fwrite(&alumno, sizeof(ST_ALUMNO), 1, alumnosActualizadosFile);
            fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
        }
        if (alumno.legajo > registros[i].alumno.legajo)
        {
            if (registros[i].actualizacion == 'A')
            {
                alumnoAux = actualizarAlumno(registros[i].alumno);
            }
            fwrite(&alumnoAux, sizeof(ST_ALUMNO), 1, alumnosActualizadosFile);
            i++;
        }
    }
    
     while (!feof(alumnosFile))
    {
        fwrite(&alumno, sizeof(ST_ALUMNO), 1, alumnosActualizadosFile);
        fread(&alumno, sizeof(ST_ALUMNO), 1, alumnosFile);
    }

    while (i < MAX_REGISTROS)
    {
        if (registros[i].actualizacion == 'A')
        {
            alumnoAux = actualizarAlumno(registros[i].alumno);
        }
        fwrite(&alumnoAux, sizeof(ST_ALUMNO), 1, alumnosActualizadosFile);
        i++;
    }
    
    fclose(alumnosActualizadosFile);
    fclose(alumnosFile);
    system("pause");
    return 0;
}

FILE *abrir(const char *path, const char *mode){
    FILE *ptrArchivo = fopen(path, mode);
    if (ptrArchivo == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo %s", path);
        exit(EXIT_FAILURE);
    }
    return ptrArchivo;
}

ST_ALUMNO actualizarAlumno(ST_ALUMNO alumno)
{
    ST_ALUMNO aux;
    aux.legajo = alumno.legajo;
    strcpy(aux.apellidoNombre, alumno.apellidoNombre);
    strcpy(aux.domicilio, alumno.domicilio);
    aux.codPostal = alumno.codPostal;
    strcpy(aux.telefono, alumno.telefono);
    aux.anioIngreso = alumno.anioIngreso;
    return aux;
}
