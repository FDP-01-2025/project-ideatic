#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime> //para generar valores aleatorios, en este caso, los laberintos xd.
using namespace std;

#define columns 50 // numero de columnas que tendra la matriz para formar el laberinto
#define rows 15    // numero de filas que tendra la matriz para el laberint

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
void generatelab(int matriz[rows][columns], int density)
{
    int walls = density * 8;

    for (int i = 0; i < rows; i++) // para cada fila, se creara el numero de columnas
    {
        for (int a = 0; a < rows; a++)
        {
            if (a == 0 || i == 0 || a == rows - 1 || i == columns - 1)
            {
                matriz[a][i] = 1;
            }
            else
            {
                matriz[a][i] = 0;
            }
        }
    }
    // para generar el laberinto:
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

            if (matriz[mr[ran]][mc[ran]] == 0)
            {
                matriz[mr[ran]][mc[ran]] = 1;
                matriz[mr[ran] + (rw - mr[ran]) / 2][mc[ran] + (cl - mc[ran]) / 2] = 1;
            }
        }
    }
}
int main()
{
    int lab[rows][columns];
    float density = 0.25;

    srand(time(NULL) / 10); // para poder generar el laberinto cada 10 segundos.

    homescreen();
    showmenu();
    int option;
    cout << "Select a option to continue: ";
    cin >> option;
   // switch (showmenu){
    return option;
    generatelab(lab, 5);
    //showlabyrinth(lab);
    return 0;
}
