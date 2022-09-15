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
#define MAX_CAMIONES 200
#define MAX_CHOFERES 150
using namespace std;

struct ST_DESTINO
{
    int idDestino;
    float distancia;
};
struct ST_VIAJE
{
    char patente[MAX_CHARS];
    int idDestino;
    int idChofer;
};

FILE *abrir(const char *path, const char *mode);

int main()
{
    
    FILE *destinosFile = abrir("Destinos.dat","rb");
    FILE *viajesFile = abrir("Viajes.dat","rb");
    ST_DESTINO destino;
    ST_VIAJE viaje;
    
    fread(&destino,sizeof(ST_DESTINO),1,destinosFile);
    fread(&viaje,sizeof(ST_VIAJE),1,viajesFile);
    while (!feof(destinosFile) && !feof(viajesFile))
    {
        if (destino.idDestino == viaje.idDestino)
        {
            
        }
        
    }
    
    fclose(destinosFile);
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
