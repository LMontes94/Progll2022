/*
Ej. 25: Dado un archivo binario “ACTASFINALES.dat” que contiene las actas de los exámenes finales
de las distintas materias, ordenado por libro y folio y con el siguiente diseño
a.1Libro (6 dígitos) a.2 Folio ( 1..999) a.3 Fecha (aaaammdd)
a.4Código materia (6 dígitos) a.5 Legajo (10 dígitos)
a.6Apellido y nombre (20 caracteres) a.7 Nota (1..10, 0 indica ausente)
Se pide desarrollar todos los pasos necesarios para realizar un algoritmo que grabe un archivo
“TOTALES.dat” ordenado por libro y folio con el siguiente diseño:
b.1 Libro (6 dígitos) b.2 Folio ( 1..999)
b.3 Total alumnos inscriptos (1..20) b.4 Total alumnos ausentes (1..20)
b.5 Total alumnos aprobados (1..20) b.6 Total alumnos desaprobados (1..20)
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_CHARS 20
#define MAX_FOLIOS 999
using namespace std;

struct ST_ACTA
{
    int idLibro;
    int folio;
    int fecha;
    int idMateria;
    int legajo;
    char apellidoNombre[MAX_CHARS];
    int nota;
};

struct ST_AUX
{
    int idLibro;
    int folio;
    int totalAlumnosInscriptos = 0;
    int totalAlumnosAprobados = 0;
    int totalAlumnosAusentes = 0;
    int totalAlumnosDesaprobados = 0;
};

FILE *abrir(const char *path, const char *mode);
int main()
{

    FILE *actasFinalesFile = abrir("ACTASFINALES.dat", "rb");
    FILE *totalesFile = abrir("TOTALES.dat", "wb");
    ST_ACTA acta;
    ST_AUX aux;
   
    fread(&acta,sizeof(ST_ACTA),1,actasFinalesFile);
    while (!feof(actasFinalesFile))
    {
        aux.totalAlumnosAprobados = 0;
        aux.totalAlumnosAusentes = 0;
        aux.totalAlumnosDesaprobados = 0;
        aux.totalAlumnosInscriptos = 0;
        aux.idLibro = acta.idLibro;
        while (!feof(actasFinalesFile) && aux.idLibro == acta.idLibro)
        {
            aux.folio = acta.folio;
            while (!feof(actasFinalesFile) && aux.idLibro == acta.idLibro && aux.folio == acta.folio)
            {
                aux.totalAlumnosInscriptos++;
                if (acta.nota == 0)
                {
                    aux.totalAlumnosAusentes++;
                }else if(acta.nota > 6){
                   aux.totalAlumnosAprobados++;
                }else{
                    aux.totalAlumnosDesaprobados++;
                }                
                fread(&acta,sizeof(ST_ACTA),1,actasFinalesFile);
            }
            
        }
        fwrite(&aux,sizeof(ST_AUX),1,totalesFile);
    }
    
    fclose(actasFinalesFile);
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