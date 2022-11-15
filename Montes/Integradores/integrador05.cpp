/*
Una facultad requiere de una pieza de software que le permita gestionar a los alumnos
inscriptos.
La universidad cuenta actualmente con 1000 alumnos, de cada uno posee los siguientes
datos:
● Legajo, 7 caracteres
● Carrera: 1 caracter
● Nombre, 30 caracteres
● Apellido, 30 caracteres
● Email, 30 caracteres
● Teléfono, 10 caracteres
El legajo es un número entero entre 1000 y 2000.

Las carreras están nomencladas según el siguiente listado
● K, ingeniería en sistemas
● C, ingeniería civil
● P ingeniería electrónica
● D ingeniería mecánica
Los datos antes mencionados se encuentran almacenados en el archivo alumnes.dat
Los datos de las carreras se encuentran almacenados en el archivo carreras.txt, donde
además del código se encuentra el nombre y descripción de la carrera.
Por otra parte, la facultad posee las notas de cada materia de los alumnos en distintos
archivos, uno por cada materia. El nombre de cada archivo indica la materia.
Estos archivos poseen el número, fecha de cada parcial y el legajo de cada alumno. Tener en
cuenta que estos archivos se encuentran desordenados y que sólo hay 2 parciales por cada
alumno.
Se pide:
1. Imprimir el archivo de notas de forma ordenada, utilizando el legajo como criterio.
Restricción: sólo puede ser recorrido secuencialmente 1 vez.
2. Calcular y guardar el promedio de las notas de los alumnos, ordenado por legajo de
forma ascendente. Restricción: sólo posee 8000 bytes de espacio en disco.
*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;
#define MAX_ALUMNOS 1000

struct ST_ALUMNO
{
  char legajo[7]; // 7 caracteres
  char carrera; // 1 caracter
  char nombre[30]; // 30 caracteres
  char apellido[30];// 30 caracteres
  char email[30];// 30 caracteres
  char telefono[10];// 10 caracteres
};

struct ST_CARRERA
{
    char codigo;
    char nombre[30];
    char descripcion[250];
};

struct ST_MATERIA
{
    
};

FILE *abrir(const char *fileName, const char *modo)
{
    FILE *file = fopen(fileName, modo);
    if (file == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo: %s", fileName);
        exit(EXIT_FAILURE);
    }

    return file;
}

int main(){

    FILE *alumnosBin = abrir("alumnes.dat","rb");
    FILE *carrerasTxt = abrir("carreras.txt","r");
    

    system("pause");
    return 0;
}