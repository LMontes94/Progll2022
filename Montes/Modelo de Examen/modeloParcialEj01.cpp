/*
Ejercicio 1
Una pequeña importadora de libros y revistas científicas desea avisar a sus clientes cuando
deben retirar los pedidos realizados. Para ello dispone de los datos de los pedidos
almacenados en el archivo de texto Pedidos.txt, donde cada línea posee los datos de un
pedido.
Código de pedido Código de cliente Recibido
char[10] int (1-100) char (S | N)
También dispone de los datos de sus clientes, almacenados en el archivo binario
Agenda.dat, ordenado por código de cliente, donde cada línea posee:
Código Nombre Apellido Email
int (1-100) char[20] char[20] char[20]
La distribuidora requiere la construcción de un programa que le permita grabar un archivo
binario con los pedidos recibidos (campo Recibido = ‘S’).
La estructura del registro será la siguiente:

Email Mensaje
char[20] char[256]

El campo <Mensaje> se compone de la siguiente manera:
Estimado/a <Nombre>, su pedido <Código de Pedido> se encuentra disponible para ser
retirado.
*/
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAX_CLIE 100

struct ST_PED
{
    char codPed[10 + 1];
    int codCliente;
    char Recibido;
};

struct ST_AGE
{
    int codigo;
    char Nombre[20 + 1];
    char Apellido[20 + 1];
    char Email[20 + 1];
};

struct ST_REC
{
    char Email[20 + 1];
    char Mensaje[256];
};

void leerTxt(ST_PED pd, FILE *pedidos)
{
    char buffer[255];

    if (fgets(buffer, 255, pedidos) != NULL)
    {
        strcpy(pd.codPed, strtok(buffer, ";"));
        pd.codCliente = atoi(strtok(NULL, ";"));
        pd.Recibido = strtok(NULL, ";\n")[0];
    }
    return;
}

void cargarAgenda(ST_AGE agenda[MAX_CLIE], FILE *file)
{
    ST_AGE aux;
    int i = 0;
    while (i < MAX_CLIE)
    {
        fread(&aux, sizeof(ST_AGE), 1, file);
        agenda[i].codigo = aux.codigo;
        strcpy(agenda[i].Nombre, aux.Nombre);
        strcpy(agenda[i].Apellido, aux.Apellido);
        strcpy(agenda[i].Email, aux.Email);
        i++;
    }

    return;
}

int main()
{

    FILE *pPed = NULL;
    pPed = fopen("Pedidos.txt", "r+");

    FILE *pAgenda = NULL;
    pAgenda = fopen("Agenda.dat", "rb+");

    FILE *pPedRecibidos = NULL;
    pPedRecibidos = fopen("Recibidos.dat", "wb+");

    ST_PED pedidos;
    ST_AGE agenda[MAX_CLIE];
    ST_REC recibido;

    leerTxt(pedidos, pPed);
    cargarAgenda(agenda, pAgenda);

    while (!feof(pPed))
    {
        if (pedidos.Recibido == 'S')
        {

            // HACERLO CON FSEEK PARA NO OCUPAR TANTO.
            strcpy(recibido.Email, agenda[pedidos.codCliente - 1].Email);
            char nombre[20 + 1];
            char codP[10 + 1];
            strcpy(nombre, agenda[pedidos.codCliente - 1].Nombre);
            strcpy(codP, pedidos.codPed);
            char mensaje[256];
            strcpy(recibido.Mensaje, "Estimado/a ");
            strcat(recibido.Mensaje, nombre);
            strcat(recibido.Mensaje, ", su pedido ");
            strcat(recibido.Mensaje, codP);
            strcat(recibido.Mensaje, " se encuentra disponible para ser retirado.");
            fwrite(&recibido, sizeof(ST_REC), 1, pPedRecibidos);
        }
        leerTxt(pedidos, pPed);
    }
    fclose(pAgenda);
    fclose(pPed);
    fclose(pPedRecibidos);

    system("pause");
    return 0;
}