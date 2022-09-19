/*
Ej. 23: Un negocio de ropa, vende sus artículos en distintos talles. Para realizar la facturación dispone de
los siguientes archivos:
Un archivo “Articulos.dat”, con los precios de cada artículo y talle que vende, con el
siguiente diseño de registro:
    a.1) código de articulo (1..100) a.2) talle (1..5) a.3) precio (real)
También se dispone de dispone de un conjunto de ventas a facturar, que se ingresan por teclado con los
siguientes datos: código de artículo, talle y unidades (1 dígito). Las ventas finalizan con un código de
artículo negativo.
Desarrollar un algortimo que:
    1) informe el precio de la venta, considerando un descuento del 10% si las unidades vendidas son
    superiores a tres más el 21% del IVA.
    2) al final del proceso emita el siguiente listado, ordenado por artículo y talle ascendente:
    Código de Artículo 999

    Talle Unidades Vendidas
      9         99
      9         99
Total unidades vendidas artículo 9999999
...............................................
Total general de unidades vendidas 9999999
*/
#include <iostream>
#include "string.h"
#include <stdlib.h>

#define MAX_ARTICULOS 100
#define MAX_TALLES 5
using namespace std;

struct ST_ARTICULO
{
    int id;
    int talle;
    float precio;
};

struct ST_VENTAS
{
    int id;
    int talle;
    int unidad;
};

FILE *abrir(const char *path, const char *mode);
void menu(int &opcion);
cargarVenta(ST_VENTAS ventas[MAX_ARTICULOS][MAX_TALLES], bool &vendio);
void cargarArticulos(ST_ARTICULO articulo[MAX_ARTICULOS][MAX_TALLES], const char *path, const char *mode);
int contarUnidadesVendidas(ST_VENTAS venta[][MAX_PATH]);
float sumarPrecios(ST_VENTAS venta[][MAX_PATH], ST_ARTICULO articulo[MAX_ARTICULOS][MAX_TALLES]);
float aplicarDescuento(ST_VENTAS venta[][MAX_PATH], ST_ARTICULO articulo[MAX_ARTICULOS][MAX_TALLES]);
float sumoIva(float ventaFinal);
void imprimirListado(ST_VENTAS ventas[][MAX_TALLES]);
int main()
{

    FILE *articulosFile = abrir("Articulos.dat", "rb");
    ST_ARTICULO articulo[MAX_ARTICULOS][MAX_TALLES];
    ST_VENTAS ventas[MAX_ARTICULOS][MAX_TALLES];
    int opcion = 0;
    bool vendio = false;
    float ventaFinal;
    cargarArticulos(articulo, "Articulos.dat", "rb");
    while (opcion != 3)
    {
        menu(opcion);
        switch (opcion)
        {
        case 1:
            cargarVenta(ventas, vendio);
            if (vendio)
            {
                if (contarUnidadesVendidas(ventas) > 3)
                {
                    ventaFinal = aplicarDescuento(ventas, articulo);
                    ventaFinal = sumoIva(ventaFinal);
                }
                else
                {
                    ventaFinal = sumarPrecios(ventas, articulo);
                    ventaFinal = sumoIva(ventaFinal);
                }
                printf("Precio final de la venta: %0.2f$", ventaFinal);
            }else{
                printf("No se realizo la venta!!")
            }
            break;
        case 2:
            break;
        case 3:
            printf("Cerrando app....!!");
            break;
        default:
            printf("Opcion no valida...!!! Vuelva a seleccionar una opcion..");
            break;
        }
    }

    fclose(articulosFile);
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
void menu(int &opcion)
{

    printf("------MENU-------");
    printf(" 1-Informe de la Venta");
    printf(" 2- Mostrar listado");
    printf(" 3-Salir");
    printf("-----------------------");
    scanf("%d", opcion);
    return;
}
void cargarArticulos(ST_ARTICULO articulo[MAX_ARTICULOS][MAX_TALLES], const char *path, const char *mode)
{
    FILE *ptrArchivo = abrir(path, mode);
    ST_ARTICULO articuloAux;
    int i = 0;
    fread(&articuloAux, sizeof(ST_ARTICULO), 1, ptrArchivo);
    while (!feof(ptrArchivo))
    {
        articulo[articuloAux.id][articuloAux.talle].id = articuloAux.id;
        articulo[articuloAux.id][articuloAux.talle].talle = articuloAux.talle;
        articulo[articuloAux.id][articuloAux.talle].precio = articuloAux.precio;
        i++;
        fread(&articuloAux, sizeof(ST_ARTICULO), 1, ptrArchivo);
    }

    return;
}
void cargarVenta(ST_VENTAS ventas[MAX_ARTICULOS][MAX_TALLES], bool &vendio)
{
    ST_VENTAS venta;
    venta.id = 0;
    printf("Ingresar codigo del articulo o un numero negativo para terminar la venta: \n");
    scanf("%d", &venta.id);
    while (venta.id > 0)
    {
        vendio = true;
        printf("Ingresar el talle: \n");
        scanf("%d", &venta.talle);
        printf("Ingresar cantidad a vender: ");
        scanf("%d", &venta.unidad);

        ventas[venta.id][venta.talle].id = venta.id;
        ventas[venta.id][venta.talle].talle = venta.talle;
        ventas[venta.id][venta.talle].unidad = venta.unidad;

        printf("Ingresar codigo del articulo o un numero negativo para terminar la venta: \n");
        scanf("%d", &venta.id);
    }

    return;
}
int contarUnidadesVendidas(ST_VENTAS venta[][MAX_PATH])
{
    int cantVendidas;
    for (int i = 0; i < MAX_ARTICULOS; i++)
    {
        for (int j = 0; j < MAX_TALLES; j++)
        {
            if (venta[i][j].unidad > 0)
            {
                cantVendidas++;
            }
        }
    }
    return cantVendidas;
}
float aplicarDescuento(ST_VENTAS venta[][MAX_PATH], ST_ARTICULO articulo[MAX_ARTICULOS][MAX_TALLES])
{
    float precioVenta = sumarPrecios(venta, articulo);
    return precioVenta - ((precioVenta * 10) / 100);
}
float sumarPrecios(ST_VENTAS venta[][MAX_PATH], ST_ARTICULO articulo[MAX_ARTICULOS][MAX_TALLES])
{
    float precioVenta for (int i = 0; i < MAX_ARTICULOS; i++)
    {
        for (int j = 0; j < MAX_TALLES; j++)
        {
            if (venta[i][j].unidad > 0)
            {
                precioVenta = precioVenta + (venta[i][j].unidad * articulo[venta[i][j].id][venta[i][j].talle].precio);
            }
        }
    }
    return precioVenta;
}
float sumoIva(float ventaFinal)
{
    return precioVenta + ((precioVenta * 21) / 100);
}
void imprimirListado(ST_VENTAS ventas[][MAX_TALLES]){
    
    int i = 0,j;
    int keyId;
    printf("Talle    Unidades Vendidas");
   while(i < MAX_ARTICULOS){
    j=0;
     keyId = ventas[i][j].id;
     while (j < MAX_TALLES && keyId == ventas[i][j].id)
     {
        printf("  %d        %d",ventas[i][j].talle,ventas[i][j].unidad;
        j++;
     }
     i++;
   }
    
    return
}