/*
Dada una cadena que representa un número, cuya longitud máxima es de 80 caracteres,
desarrollar la función formatearNumero que reciba dos cadenas. La primera será la
cadena que representa el número mientras que la segunda será la que indique la
preferencia para el separador de miles y decimales (locale). Ejemplo:
    Entrada: “1.050.214,56”, “AR” → “1.050.214, 56”
    Entrada: “1,050,214.56”, “AR” → “1.050.214, 56”
    Entrada: “1.050.214, 56”, “EN” → “1,050,214. 56”
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#define MAX_CHARS 80
using namespace std;

void menu(int &opcion);
int contarCaracteres(char *num);
char *formatearNumero(char num[MAX_CHARS], char separador[2]);
int main()
{
    char num[MAX_CHARS];
    char separador[2];
    char *numFinal;
    numFinal = (char *)malloc(sizeof(MAX_CHARS + 1));
    int opcion;
    menu(opcion);
    while (opcion != 2)
    {
        switch (opcion)
        {
        case 1:
            printf("Ingrese el numero: \n");
            scanf("%s", num);
            printf("indique la preferencia para el separador de miles y decimales:\n");
            printf("AR miles separado por '.' y decimales por ',' \n");
            printf("EN miles separado por ',' y decimales por '.'\n");
            scanf("%s", &separador);
            numFinal = formatearNumero(num, separador);
            break;
        case 2:
            printf("Cerrrando aplicacion.....Nos vemos luego\n");
            break;
        default:
            printf("Opcion incorrecta...Vuelva a elegir.\n");
            break;
        }
    }
    free(numFinal);
    system("pause");
    return 0;
}

void menu(int &opcion)
{
    cout << "    Menu" << endl;
    cout << "-------------------------" << endl;
    cout << "Seleccione una opcion, ingresando el nro." << endl;
    cout << "1-Formatear numero" << endl;
    cout << "2-Salir" << endl;
    cin >> opcion;
    cout << "-------------------------" << endl;
    return;
}
int contarCaracteres(char *num)
{
    return strlen(num);
}
char *formatearNumero(char num[MAX_CHARS], char separador[2])
{
    char *numFinal;
    numFinal = (char *)malloc(sizeof(MAX_CHARS + 1));
    char *aux;
    aux = (char *)malloc(sizeof(MAX_CHARS + 1));
    char *auxNum;
    auxNum = (char *)malloc(sizeof(MAX_CHARS + 1));
    strcpy(aux, num);
    numFinal = (char *)malloc(sizeof(MAX_CHARS + 1));
    int cantChar = contarCaracteres(num);
    auxNum = strtok(aux, ".,");
    while (auxNum != NULL)
    {
        printf("%s",auxNum);
        auxNum = strtok(NULL, " ,.-");
    }
    free(aux);
    free(auxNum);
    return numFinal;
}