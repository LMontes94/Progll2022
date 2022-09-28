/*
Ej. 27 Dado el archivo “PRODUCTOS.dat” con los datos de los productos que vende un mayorista,
ordenado por código de producto y con el siguiente diseño:
a.1 Código de producto (8 caracteres) a.2 Descripción del producto ( 30 caracteres)
a.3 Cantidad en Stock (4 dígitos) a.4 Precio de venta (real)
a.5 Estado del registro (‘A’=activo / ‘I’= inactivo )
Y otro archivo sin ningún orden llamado “NOVEDADES.dat”, con las actualizaciones (altas, bajas, y
modificaciones) a ser aplicadas, donde cada registro contiene además de todos los campos de
Productos.dat un código de operación (‘A’= Alta, ‘B’= Baja, ‘M’= Modificación).
Se pide desarrollar todos los pasos necesarios para realizar un programa que actualice el archivo
“Productos.dat” sobre sí mismo.
NOTA: Los códigos de los productos a dar de alta siempre tendrán un valor superior a los que se
encuentren ya grabados en Productos.dat, y no son más de 20.
Restricciones memoria para arrays 100 bytes
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_CHARS 30
#define MAX_NUEVOS 20
using namespace std;

struct ST_PRODUCTO
{
    char idProducto[8];
    char descripcion[MAX_CHARS];
    int stock;
    float precio;
    char estado;
};

struct ST_NOVEDAD
{
    ST_PRODUCTO producto;
    char actualizacion;
};

FILE *abrir(const char *path, const char *mode);
void actualizarProducto(ST_PRODUCTO producto, int pos, FILE *archivo);
int contarRegistros(FILE *file);
int buscarProducto(char *idProducto, FILE *archivo);
ST_PRODUCTO obtenerProducto(int pos, FILE *archivo);
void ordenarXId(ST_PRODUCTO producto[], int maxNuevos);

int main()
{
    FILE *productosFile = abrir("PRODUCTOS.dat", "rb+");
    FILE *novedadesFile = abrir("NOVEDADES.dat", "rb");
    FILE *auxFile = abrir("ProductosAux.dat","wb");
    ST_NOVEDAD novedad;
    ST_PRODUCTO produtosAlta[MAX_NUEVOS];
    int i = 0;
    fread(&novedad, sizeof(ST_NOVEDAD), 1, novedadesFile);
    while (!feof(novedadesFile))
    {
        if (novedad.actualizacion == 'M' || novedad.actualizacion == 'm')
        {
            int posProducto = buscarProducto(novedad.producto.idProducto, productosFile);
            ST_PRODUCTO producto = obtenerProducto(posProducto, productosFile);
            actualizarProducto(producto, posProducto, auxFile);
        }
        else if (novedad.actualizacion == 'A' || novedad.actualizacion == 'a')
        {
            strcpy(produtosAlta[i].idProducto, novedad.producto.idProducto);
            strcpy(produtosAlta[i].descripcion, novedad.producto.descripcion);
            produtosAlta[i].estado = novedad.producto.estado;
            produtosAlta[i].precio = novedad.producto.precio;
            produtosAlta[i].stock = novedad.producto.stock;
            i++;
        }
    }
    
    ordenarXId(produtosAlta,MAX_NUEVOS);
    fseek(auxFile,sizeof(ST_PRODUCTO),SEEK_END);
    for (int j = 0; j < i; j++)
    {
        fwrite(&produtosAlta[j],sizeof(ST_PRODUCTO),1,auxFile);
    }
    
    fclose(productosFile);
    fclose(novedadesFile);
    fclose(auxFile);

    remove("PRODUCTOS.dat");
    rename("ProductosAux.dat","PRODUCTOS.dat");
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
ST_PRODUCTO obtenerProducto(int pos, FILE *archivo)
{
    ST_PRODUCTO producto;
    fseek(archivo, pos * sizeof(ST_PRODUCTO), SEEK_SET);
    fread(&producto, sizeof(ST_PRODUCTO), 1, archivo);
    return producto;
}

void actualizarProducto(ST_PRODUCTO producto, int pos, FILE *archivo)
{
    fseek(archivo, pos * sizeof(ST_PRODUCTO), SEEK_SET);
    fwrite(&producto, sizeof(ST_PRODUCTO), 1, archivo);
    return;
}

int contarRegistros(FILE *file)
{
    int posActual = ftell(file);

    fseek(file, 0, SEEK_END);
    int cant = ftell(file) / sizeof(ST_PRODUCTO);

    fseek(file, posActual, SEEK_SET);
    return cant;
}

int buscarProducto(char *idProducto, FILE *archivo)
{
    int inicio = 0;
    int fin = contarRegistros(archivo) - 1;
    while (fin >= inicio)
    {
        int mitad = inicio + (fin - inicio) / 2;
        // Si el elemento es el del medio, devolvemos la posicion
        ST_PRODUCTO producto = obtenerProducto(mitad, archivo);
        if (strcmp(producto.idProducto, idProducto) == 0)
        {
            return mitad;
        }
        // Si el elemento es menor entonces solo puede estar en la primer mitad
        if (strcmp(producto.idProducto, idProducto) < 0)
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