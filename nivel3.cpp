#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime> //para generar valores aleatorios, en este caso, los laberintos xd.
using namespace std;
void cleanscreen()
{
    system("cls");
}

// para esperar cierto tiempo entre cada texto que se mostrara
void waitscreen(int milliseconds)
{
    Sleep(milliseconds);
}
void level1message()
{
    waitscreen(1100);
    cleanscreen();
    string message1 = "Congratulations! You've made it to level 3 :D";
    string message2 = "Now you must defeat the enemy of this level to move on to the last one.";
    string message3 ="Good luck!, see you at the next level";
    string message4 = "Good luck!, see you at the next level";

    string message[] = {message1, message2, message3, message4};
    for (int i = 0; i < 4; i++)
    {
        cout << endl;
        for (char a : message[i])
        {
            cout << a;
            waitscreen(50);
        }
        waitscreen(800);
    }
    cleanscreen();
    waitscreen(175);
}
void loading()
{
    waitscreen(1000);
    cleanscreen();
    string message = "loading";
    string message1 = "...";
    string message2[] = {message, message1};

    for (int j = 0; j < 2; j++)
    {
        for (char c : message2[j])
        {
            cout << c;
            waitscreen(50);
        }
    }
    waitscreen(300);
    cleanscreen();
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
                cout << "██";
            }
            else
            {
                cout << "░░";
            }
        }
        cout << endl;
    }
}
int main()
{
    srand(time(NULL));

    int lab[rows][columns];

    // homescreen();
    // showmenu();
    generatelab(lab);
    showlabyrinth(lab);

    return 0;
}
