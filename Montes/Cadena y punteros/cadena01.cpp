/*
1) Dado una cadena, cuya longitud máxima es de 80 caracteres, y utilizando sólo sintaxis de
punteros, determinar si la cadena es o no un palíndromo. Ejemplo:
NEUQUEN → verdadero
CHUBUT → falso
*/

#include <iostream>
using namespace std;

#define MAX_CHARS 80

void leer(char palabra[MAX_CHARS + 1]);
bool esPolindromo(char letra[MAX_CHARS + 1]);
int contarCaracteres(char palabra[MAX_CHARS + 1]);
int main()
{

    char palabra[MAX_CHARS + 1] = " ";

    printf("Ingrese la palabra a analizar: \n");
    leer(palabra);
    
    if (esPolindromo(palabra))
    {
        printf("La palabra %s es palindromo.\n",palabra);
    }
    else
    {
        printf("La palabra %s no es palindromo.\n",palabra);
    }
    system("pause");
    return 0;
}

void leer(char palabra[MAX_CHARS + 1]) {
    scanf("%s", palabra);
}

int contarCaracteres(char palabra[MAX_CHARS + 1]){
    int cantLetras = 0;
    int i = 0;
    while (palabra[i] != '\0'){
       i++;
       cantLetras++;
    }
    
    return cantLetras;
}

bool esPolindromo(char palabra[MAX_CHARS + 1])
{
    int ultimo = contarCaracteres(palabra) - 1;
    int i = 0;
    bool polindromo;
    
    while (palabra[i] != '\0' || i < ultimo)
    {
       if (palabra[i] == palabra[ultimo - i])
        {
            polindromo = true;
        }
        else
        {
           return polindromo = false;
        }
        i++;
    }
    return polindromo;
}