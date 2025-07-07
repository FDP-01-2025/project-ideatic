#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime> //para generar valores aleatorios, en este caso, los laberintos xd.
using namespace std;

void homescreen()
{
    cout << "Welcome to Lost city :D" << endl;
    cout << "press enter to continue" << endl;
}
void showmenu()
{
    cout << "|-----------------------------|" << endl;
    cout << "|            MENU             |" << endl;
    cout << "| Select a option to continue |" << endl;
    cout << "|          1. Play            |" << endl;
    cout << "|       2. Show levels        |" << endl;
    cout << "|          3. Exit            |" << endl;
    cout << "|        4. Save game         |" << endl;
    cout << "|-----------------------------|" << endl;
}
void level1()
{
    cout << "                LEVEL 1           " << endl;
    cout << "Use the rows to move and to attack" << endl;
}

#define rows 15    // numero de filas que tendra la matriz para el laberint
#define columns 60 // numero de columnas que tendra la matriz para formar el laberinto
#define density 150

void generatelab(int matriz[rows][columns])
{
    int walls = density * 6;

    for (int i = 0; i < rows; i++) // para cada fila, se creara el numero de columnas
    {
        for (int a = 0; a < columns; a++)
        {
            if (a == 0 || i == 0 || a == columns - 1 || i == rows - 1)
            {
                matriz[i][a] = 1;
            }
            else
            {
                matriz[i][a] = 0;
            }
        }
    }

    // para generar el laberinto:

    srand(time(NULL)); // para poder generar el laberinto cada cierto tiempo.

    for (int c = 0; c < density; c++)
    {
        int cl = rand() % (columns - 4) + 2; // se coloca despues del rand esa operacion porque debe de estar dentro del laberinto, se le resta 4, para que tome valores dentro del numero de columnas.
        cl = (cl / 2) * 2;
        int rw = rand() % (rows - 4) + 2; // lo mismo para las filas.
        rw = (rw / 2) * 2;

        matriz[rw][cl] = 1;

        for (int d = 0; d < walls; d++)
        {
            int mc[4] = {cl, cl, cl + 2, cl - 2}; // longitud para las columnas, los ultimos dos valores corresponden a cuando las filas se mantengan en 0 y viceversa para las columnas.
            int mr[4] = {rw + 2, rw - 2, rw, rw}; // longitud para las filas
            int ran = rand() % 4;                 // ran=numeros random xd

            if (mr[ran] >= 0 && mc[ran] < rows && mc[ran] >= 0 && mc[ran] < columns)
            {
                if (matriz[mr[ran]][mc[ran]] == 0)
                {
                    matriz[mr[ran]][mc[ran]] = 1;
                    int midrow = mr[ran] + (rw - mr[ran]) / 2;
                    int midcolumn = mc[ran] + (cl - mc[ran]) / 2;
                    if (midrow >= 0 && midrow < rows && midcolumn >= 0 && midcolumn < columns)
                    {
                        matriz[midrow][midcolumn] = 1;
                    }
                }
            }
        }
    }
}
void showlabyrinth(int matriz[rows][columns])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matriz[i][j] == 1)
            {
                cout << "##";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

int main()
{
    srand(time(NULL));

    int lab[rows][columns];

    //homescreen();
    //showmenu();
    generatelab(lab);
    showlabyrinth(lab);

    return 0;
}
