#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int valida_int(int min, int max, const char *cadena);
char *my_gets(char *cadena, int tamano);
int getInt();

int valida_int(int min, int max, const char *cadena)
{
    int num;
    do
    {
        printf("%s", cadena);
        num = getInt();
    } while (num < min || num > max);
    return num;
}

char *my_gets(char *cadena, int tamano)
{
    size_t longitud;
    fflush(stdin);
    if (!fgets(cadena, tamano, stdin))
        return NULL;
    longitud = strlen(cadena);
    if (longitud > 0 && cadena[longitud - 1] == '\n')
        cadena[longitud - 1] = '\0';
    return cadena;
}

int getInt()
{
    char cadena[30];
    int i = 0, valor = 0;
    fflush(stdin);
    if (!fgets(cadena, sizeof(cadena), stdin))
        return 0;
    while (cadena[i] != '\0' && cadena[i] != '\n')
    {
        if (cadena[i] >= '0' && cadena[i] <= '9')
            valor = valor * 10 + (cadena[i] - '0');
        i++;
    }
    return valor;
}