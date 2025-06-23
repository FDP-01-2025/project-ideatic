#include <stdio.h>
#include <stdlib.h>

int main()
{

    int total_lineas = 10, nlinea = 0, nast = 0, nesp = 0;

    printf ("Piramide de asteriscos:\n");
    printf ("Indique cuantos pisos desea que tenga la piramide (Maximo 40 pisos): ");
    scanf("%d", &total_lineas);

    while (nlinea <= total_lineas)
    {
            while (nesp < total_lineas - nlinea)
            {
                printf(" ");
                nesp++;
            }
            while (nast < ((nlinea * 2) - 1))
            {
                printf("*");
                nast++;
            }
    nesp = 0;
    nast = 0;
    nlinea++;
    printf("\n");
    }
    return 0;
}