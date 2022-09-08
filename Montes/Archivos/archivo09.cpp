/*
Ej. 9: Dado el archivo binario generado en el ejercicio 6, que contiene todas las inscripciones del día, y
otro con el mismo diseño que contiene las inscripciones anteriores (FINALES.DAT), desarrolle un
programa que agregue al archivo de inscripciones anteriores el contenido del archivo del día. Al final del
proceso emita un listado del archivo de los registros agregados al archivo.
    Estrategia:
                 Asignar archivos
                 Abrir archivos para leer y actualizar
                 Ubicarse al final del archivo de inscripciones anteriores
                 Recorrer secuencialmente el archivo de inscripciones del día
                    o Leer registro archivo de inscripciones del día
                    o Grabar registro en archivo de inscripciones anteriores
                 Ubicarse en el primer registro de los agregados
                 Recorrer secuencialmente el archivo de inscripciones anteriores desde donde fue ubicado
                    o Leer registro archivo de inscripciones anteriores
                    o Listar datos del registro
                 Cerrar archivos
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

FILE *abrir(const char *path, const char *mode);

int main()
{
    FILE *archivo = abrir("DIAFINALES.DAT", "rb");
    FILE *inscripcionesAnteriores = abrir("FINALES.DAT", "ab");
    Inscripcion *inscripcion;
    inscripcion = (Inscripcion *)malloc(sizeof(Inscripcion));

    fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    while (!feof(archivo))
    {
        fwrite(&inscripcion, sizeof(Inscripcion), 1, inscripcionesAnteriores);
        fread(&inscripcion, sizeof(Inscripcion), 1, archivo);
    }

    fclose(archivo);
    fclose(inscripcionesAnteriores);

    inscripcionesAnteriores = abrir("FINALES.DAT", "rb");

    fread(&inscripcion, sizeof(Inscripcion), 1, inscripcionesAnteriores);
    printf("Legajo      Nombre y Apellido       Fecha         Código de materia\n");
    while (!feof(inscripcionesAnteriores))
    {
        printf(" %d            %s                %d/%d/%d              %d\n",
                inscripcion->legajo, inscripcion->nombre, inscripcion->dia, inscripcion->mes, inscripcion->anio, inscripcion->codMateria);
        fread(&inscripcion, sizeof(Inscripcion), 1, inscripcionesAnteriores);
    }
    fclose(inscripcionesAnteriores);
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