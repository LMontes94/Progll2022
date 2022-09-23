/*
Ej. 22: Una empresa que distribuye mercadería hacia distintas localidades del interior dispone de los
siguientes archivos:
Un archivo “Destinos.dat”, con información de la distancia a cada uno de los destinos y con
el siguiente diseño de registro:
    a.1) número de destino (3 dígitos) a.2) distancia en kilómetros (float)
También se dispone de otro archivo “Viajes.dat”, con los viajes realizados por cada camión y con el
siguiente diseño de registro:
    b.1) patente del camión (6 caracteres, no son más de 200 camiones) b.2) número de destino b.3) número
        de chofer (1..150)
Se pide desarrollar la metodología necesaria para realizar un programa que informe:
1. Cantidad de viajes realizados a cada destino
2. Número de chofer con menor cantidad de km recorridos
3. Patente de los camiones que viajaron al destino 116 sin repeticiones de las mismas.
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_CHARS 7
#define MAX_DESTINOS 999
#define MAX_CAMIONES 200
#define MAX_CHOFERES 150
using namespace std;

struct ST_DESTINO
{
    int idDestino;
    float distancia;
};
struct ST_CHOFER
{
    int idChofer;
    float kmRecorridos;
};

struct ST_VIAJE
{
    char patente[MAX_CHARS];
    int idDestino;
    int idChofer;
};

FILE *abrir(const char *path, const char *mode);
void cargarDestinos(ST_DESTINO destino[], int maxDestinos, FILE *archivo);
int contarRegistros(FILE *file);
int buscarChofer(int codChofer, FILE *file);
ST_VIAJE obtenerViaje(int pos, FILE *file);
bool revisarPatenteRepetida(char patente[][MAX_CHARS], char *patenteViaje);
int buscarMenor(ST_CHOFER kmsC[], int cant);
int main()
{

    FILE *destinosFile = abrir("Destinos.dat", "rb");
    FILE *viajesFile = abrir("Viajes.dat", "rb");
    ST_DESTINO destino[MAX_DESTINOS];
    ST_VIAJE viaje;
    int viajeXDestino[MAX_DESTINOS];
    ST_CHOFER choferConMenosKm[MAX_CHOFERES];
    char patenteDestino116[MAX_CAMIONES][MAX_CHARS];
    int cantPatentes = 0;

    cargarDestinos(destino, MAX_DESTINOS, destinosFile);
    fclose(destinosFile);

    fread(&viaje, sizeof(ST_VIAJE), 1, viajesFile);
    while (!feof(viajesFile))
    {
        viajeXDestino[viaje.idDestino - 1]++;
        int posChofer = buscarChofer(viaje.idChofer, viajesFile);
        viaje = obtenerViaje(posChofer, viajesFile);
        if (viaje.idDestino == destino[viaje.idDestino - 1].idDestino)
        {
            choferConMenosKm[viaje.idChofer - 1].idChofer = viaje.idChofer;
            choferConMenosKm[viaje.idChofer - 1].kmRecorridos = +destino[viaje.idDestino - 1].distancia;
        }
        if (viaje.idDestino == 116)
        {
            if (!revisarPatenteRepetida(patenteDestino116, viaje.patente))
            {
                strcpy(patenteDestino116[cantPatentes], viaje.patente);
                cantPatentes++;
            }
        }
        fread(&viaje, sizeof(ST_VIAJE), 1, viajesFile);
    }
    printf("Punto 1: \n");
    for (int i = 0; i < MAX_DESTINOS; i++)
    {
        printf("Destino: %d \t CantViajes: %d", destino[i].idDestino, viajeXDestino[i]);
    }
    printf("Punto 2: \n");
    printf("El chofer que menos recorrio fue: %d \n", buscarMenor(choferConMenosKm, MAX_CHOFERES) + 1);

    printf("Punto 3: \n");
    printf("patentes que fueron al destino 116 son: \n");
    for (int i = 0; i < cantPatentes; i++)
    {
        printf("- %s \n", patenteDestino116[i]);
    }
    fclose(viajesFile);
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
void cargarDestinos(ST_DESTINO destino[], int maxDestinos, FILE *archivo)
{
    ST_DESTINO destinoAux;
    fread(&destinoAux, sizeof(ST_DESTINO), 1, archivo);
    while (!feof(archivo))
    {
        destino[destinoAux.idDestino - 1].idDestino = destinoAux.idDestino;
        destino[destinoAux.idDestino - 1].distancia = destinoAux.distancia;
        fread(&destinoAux, sizeof(ST_DESTINO), 1, archivo);
    }

    return;
}
ST_VIAJE obtenerViaje(int pos, FILE *file)
{
    ST_VIAJE viaje;
    fseek(file, pos * sizeof(ST_VIAJE), SEEK_SET);
    fread(&viaje, sizeof(ST_VIAJE), 1, file);
    return viaje;
}
int contarRegistros(FILE *file)
{
    int posActual = ftell(file);

    fseek(file, 0, SEEK_END);
    int cant = ftell(file) / sizeof(ST_VIAJE);

    fseek(file, posActual, SEEK_SET);
    return cant;
}
int buscarChofer(int codChofer, FILE *file)
{
    int inicio = 0;
    int fin = contarRegistros(file) - 1;
    while (fin >= inicio)
    {
        int mitad = inicio + (fin - inicio) / 2;
        // Si el elemento es el del medio, devolvemos la posicion
        ST_VIAJE viaje = obtenerViaje(mitad, file);
        if (viaje.idChofer == codChofer)
        {
            return mitad;
        }
        // Si el elemento es menor entonces solo puede estar en la primer mitad
        if (viaje.idChofer < codChofer)
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
bool revisarPatenteRepetida(char patente[][MAX_CHARS], char *patenteViaje)
{
    int i = 0;

    while (i < MAX_CAMIONES)
    {
        if (strcmp(patente[i], patenteViaje) == 0)
        {
            return true;
        }
        i++;
    }
    return false;
}
int buscarMenor(ST_CHOFER kmsC[], int cant)
{
    int min = kmsC[0].idChofer;
    int posMin = 0;

    for (int i = 1; i < cant; i++)
    {
        if (kmsC[i].idChofer < min)
        {
            min = kmsC[i].idChofer;
            posMin = min;
        }
    }
    return posMin;
}