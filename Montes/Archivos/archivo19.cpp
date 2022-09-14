/*
Ej. 19: Dado un archivo de productos codificados de 1 a 100, sin ningún orden, con el siguiente diseño:
código de producto (1..100) precio unitario (single)
y un conjunto de pedidos, y de cada uno se conoce: código de producto, y cantidad de unidades pedidas
(long). Los pedidos finalizan con un código de producto igual a 0.
Se pide:
 informar de cada pedido código de producto, unidades, precio unitario e importe
 al final del proceso:
    o informar los códigos de productos que no fueron vendidos
    o grabar un archivo de texto con el siguiente listado

                Listado de Facturación por producto
                Código de Producto   Total facturado
                      999               99999.99
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>
#define MAX_PRODUCTOS 100
using namespace std;

struct ST_PRODUCTO
{
    int idProducto;
    float precio;
};

struct ST_PEDIDO
{
    int idProducto;
    int cantPedida;
};

FILE *abrir(const char *path, const char *mode);
void cargarProductos(ST_PRODUCTO producto[], int cantProductos, const char *path, const char *mode);
void ordernadoXIdProducto(ST_PRODUCTO arr[], int maxProductos);
void inicializarProducto(ST_PRODUCTO arr[], int maxProductos);
void imprimirPedido(ST_PEDIDO pedido, ST_PRODUCTO producto[MAX_PRODUCTOS]);
void guardarFacturacion(ST_PRODUCTO productos[MAX_PRODUCTOS],FILE *archivo);
void imprimirProductosNoVedidos(ST_PRODUCTO[],int maxProductos);
int main()
{
    FILE *productosFile = abrir("Productos.dat", "rb");
    FILE *pedidosFile = abrir("Pedidos.dat", "rb");
    FILE *facturacionXProducto = abrir("Facturacion_x_Producto.txt", "w");

    ST_PRODUCTO producto[MAX_PRODUCTOS];
    ST_PRODUCTO facturacionProductos[MAX_PRODUCTOS];
    ST_PEDIDO pedido;    
    
    inicializarProducto(facturacionProductos,MAX_PRODUCTOS);
    cargarProductos(producto, MAX_PRODUCTOS, "Productos.dat", "rb");
    ordernadoXIdProducto(producto, MAX_PRODUCTOS);

    fread(&pedido, sizeof(ST_PEDIDO), 1, pedidosFile);
    while (!feof(pedidosFile) && pedido.idProducto != 0)
    {
        imprimirPedido(pedido,producto);
        facturacionProductos[pedido.idProducto - 1].idProducto = pedido.idProducto;
        facturacionProductos[pedido.idProducto - 1].precio =+ (producto[pedido.idProducto-1].precio*pedido.cantPedida);
    }
    
    imprimirProductosNoVedidos(facturacionProductos,MAX_PRODUCTOS);
    guardarFacturacion(facturacionProductos,facturacionXProducto);
    
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

void cargarProductos(ST_PRODUCTO producto[], int cantProductos, const char *path, const char *mode)
{
    FILE *ptrArchivo = fopen(path, mode);
    int i = 0;
    fread(&producto[i], sizeof(ST_PRODUCTO), 1, ptrArchivo);
    while (!feof(ptrArchivo))
    {
        i++;
        fread(&producto[i], sizeof(ST_PRODUCTO), 1, ptrArchivo);
    }
    return;
}

void ordernadoXIdProducto(ST_PRODUCTO arr[], int maxProductos)
{
    int i, j;
    ST_PRODUCTO aux;
    i = 0;
    bool ordenado = false;
    while (i < maxProductos && !ordenado)
    {
        ordenado = true;
        for (j = 0; j < maxProductos - i - 1; j++)
        {

            if (arr[j].idProducto < arr[j + 1].idProducto)
            {
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
                ordenado = false;
            }
        }
        i++;
    }
    return;
}

void inicializarProducto(ST_PRODUCTO arr[], int maxProductos){
    for (int i = 0; i < maxProductos; i++)
    {
        arr[i].idProducto = i + 1;
        arr[i].precio = 0.0;
    }
    return;
}

void imprimirPedido(ST_PEDIDO pedido, ST_PRODUCTO producto[MAX_PRODUCTOS])
{
    printf("COD PRODUCTO: %d\n", pedido.idProducto);
    printf("Unidades: %d\n", pedido.cantPedida);
    printf("Precio Unitario: %.2f$\n", producto[pedido.idProducto - 1].precio);
    printf("Importe total: %.2f\n", (pedido.cantPedida * producto[pedido.idProducto - 1].precio));
    printf(".........................................................................");
    return;
}

void guardarFacturacion(ST_PRODUCTO productos[MAX_PRODUCTOS],FILE *archivo){
     archivo = abrir("Facturacion_x_Producto.txt", "w");
     fprintf(archivo,"      Listado de Facturación por producto\n");
     fprintf(archivo,"          Código de Producto   Total facturado\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++)
    {
        if(productos[i].precio != 0.0){
            fprintf(archivo,"                %d                      %.2f\n",productos[i].idProducto,productos[i].precio);
        }
    }
    return;
}

void imprimirProductosNoVedidos(ST_PRODUCTO productos[],int maxProductos){
    printf("Los códigos de productos que no fueron vendidos\n");
    for (int i = 0; i < maxProductos; i++)
    {
        if(productos[i].precio == 0.0){
            printf(" %d\n",productos[i].idProducto);
        }
    }
    return;
}