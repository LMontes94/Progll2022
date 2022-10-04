/*
Un centro de vacunacion pediatrico desea avisar a los padres de sus pacientes cuando debe vacunar a
sus hijos. Para esto se dispone  de los datos  de sus pacientes, almacenados en el archivo
Agenda.txt(sin orden) donde cada linea posee los datos de un niño.
nombre  apellido   email    Nombre_hijo     Fecha_Vacunacion
char[20] char[20]  char[20]  char[20]       char[10]
cada espacio esta delimitado por un espacio en blanco.

El centro requiere  la construccion de un programa que le permite ingresar la fecha actual (10 caracteres) y
grabe un archivo binario con los registros cuya Fecha_vacunacion coincida ingresada.

La estructura del registro sera la siguente:
email   mensaje
char[20] char[256]

El campo <mensaje> se compone de la siguiente manera:
Estimado/a <Nombre>, el dia <Fecha_Vacunacion> debera vacunar a <Nombre_Hijo> para cumplir con el calendario
de la vacunacion.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;
#define MAX_CHARS 20
#define MAX_BUFFER 256

struct ST_DATO
{
    char nombre[MAX_CHARS];
    char apellido[MAX_CHARS];
    char email[MAX_CHARS];
    char nombreHijo[MAX_CHARS];
    char fechaVacunacion[MAX_CHARS / 2];
};

struct ST_REGISTRO
{
    char email[MAX_CHARS];
    char mensaje[MAX_BUFFER];
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
void leer(ST_DATO *dato, FILE *file)
{
    char buffer[MAX_BUFFER];
    if (fgets(buffer, MAX_BUFFER, file) != NULL)
    {
        strcpy(dato->nombre, strtok(buffer, " "));
        strcpy(dato->apellido, strtok(NULL, " "));
        strcpy(dato->email, strtok(NULL, " "));
        strcpy(dato->nombreHijo, strtok(NULL, " "));
        strcpy(dato->fechaVacunacion, strtok(NULL, " \n"));
    }
    return;
}
void armarMensaje(ST_REGISTRO registro, ST_DATO dato){
   
   strcpy(registro.mensaje,"Estimado/a ");
   strcat(registro.mensaje,dato.nombre);
   strcat(registro.mensaje," , el dia ");
   strcat(registro.mensaje,dato.fechaVacunacion);
   strcat(registro.mensaje," debera vacunar a ");
   strcat(registro.mensaje,dato.nombreHijo);
   strcat(registro.mensaje," para cumplir con el calendario de la vacunacion.");
   return;
}
int main()
{
    FILE *agendaFile = abrir("Agenda.txt", "r");
    FILE *fechaActualFile = abrir("FechaActual.dat", "wb");
    ST_DATO dato;
    ST_REGISTRO registro;
    char fecha[MAX_CHARS / 2];

    printf("Ingresar la fecha actual: \n");
    scanf("%s", &fecha);

    leer(&dato, agendaFile);
    while (!feof(agendaFile))
    {
        if (strcmp(fecha, dato.fechaVacunacion) == 0)
        {
            strcpy(registro.email,dato.email);
            armarMensaje(registro,dato);
            fwrite(&registro,sizeof(ST_REGISTRO),1,fechaActualFile);
        }

        leer(&dato, agendaFile);
    }
    fclose(agendaFile);
    fclose(fechaActualFile);
    system("pause");
    return 0;
}