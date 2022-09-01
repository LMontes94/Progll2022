#include <iostream>
using namespace std;

int main()
{

        char palabra[10] = "Hola";
        char *miPuntero = NULL;
        int i = 0;

        miPuntero == (char *)malloc(sizeof(char));

        miPuntero = palabra;
        float real = 100;
        printf("Variable real, valor: %.2f pos: %p\n", real, &real);

        printf("Pantalla puntero (a): %s \n", miPuntero);
        printf("Direccion de memoria (b): %p \n", &miPuntero);
        printf("valor del puntero (c): ");
        while (*(miPuntero + i) != '\0')
        {
                printf("%c", *(miPuntero + i));
                i++;
        }
        printf("\n");
        printf("Direccion de memoria (b) miPuntero[0]: %p \n", &miPuntero[0]);
        printf("valor del puntero (c) miPuntero[0]: %c \n", miPuntero[0]);
        miPuntero++;
        printf("Direccion de memoria (b) miPuntero[0]: %p \n", &miPuntero[0]);
        printf("valor del puntero (c): %c \n", miPuntero[0]);
        printf("----------------------------------\n");

        free(miPuntero);

        system("pause");
        return 0;
}