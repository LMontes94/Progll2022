/*
Ej. 12: Dado un archivo binario de productos que contiene 100 registros, y cada registro corresponde a
un producto que está codificado del 1 a 100, ordenado por código de producto
        con el siguiente diseño:
                código de producto (1..100, char)           stock (int)
                y otro archivo binario de pedidos, con el siguiente diseño:
                Número de pedido(int)                       número de cliente (long)
                Código de producto (1..100, char)           cantidad pedida (int)
        Se pide desarrollar un algoritmo que:
                a) grabar un archivo de texto con los pedidos que fueron satisfechos en su totalidad según el
                siguiente listado:
                Pedidos Satisfechos
                Número de pedido  Número de Cliente   Código de Producto   Cantidad pedida
                  9999                   999999                999                9999
                  9999                   999999                999                9999

                b) actualizar el campo stock del archivo de producto, cada vez que acepte un pedido.
                c) grabar un archivo binario con el mismo diseño que el archivo de pedidos, con aquellos pedidos
                que no pueden ser satisfechos en su totalidad.
*/
#include <iostream>
#include "string.h"
using namespace std;

struct ST_PRODUCTO
{
    char codProducto;
    int stock;
};
struct ST_PEDIDO
{
    int nroPedido;
    char codProducto;
    long nroCliente;
    int cantPedida;
};

FILE *abrir(const char *path, const char *mode);
void actualizarStock(FILE *archivo, ST_PEDIDO pedido, ST_PRODUCTO producto);

int main()
{

    FILE *productos = abrir("PRODUCTOS.DAT", "rb+");
    FILE *pedidos = abrir("PEDIDOS.DAT", "rb");
    FILE *pedidosSatisfechos = abrir("PEDIDOS_SATISFECHOS.TXT", "w");
    FILE *pedidosIncompletos = abrir("PEDIDOS_INSATISFECHOS.DAT", "wb");
    ST_PRODUCTO producto;
    ST_PEDIDO pedido;

    fread(&pedido, sizeof(ST_PEDIDO), 1, pedidos);
    while (!feof(pedidos))
    {
        fseek(productos, sizeof(ST_PRODUCTO) * (pedido.codProducto - 1), SEEK_SET);
        fread(&producto, sizeof(ST_PRODUCTO), 1, productos);
        if (pedido.cantPedida < producto.stock)
        {
            actualizarStock(productos,pedido,producto);
            fprintf(pedidosSatisfechos,"%d %d %4s %d\n",pedido.nroPedido,pedido.nroCliente,pedido.codProducto,pedido.cantPedida);
        }else{
          fwrite(&pedido,sizeof(ST_PEDIDO),1,pedidosIncompletos);
        }
        fread(&pedido, sizeof(ST_PEDIDO), 1, pedidos);
    }
    
    fclose(productos);
    fclose(pedidos);
    fclose(pedidosSatisfechos);
    fclose(pedidosIncompletos);
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

void actualizarStock(FILE *archivo, ST_PEDIDO pedido, ST_PRODUCTO producto)
{
    producto.stock =- pedido.cantPedida;
    fseek(archivo, sizeof(ST_PRODUCTO) * (pedido.codProducto - 1), SEEK_SET);
    fwrite(&producto, sizeof(ST_PRODUCTO), 1, archivo);
    return;
}