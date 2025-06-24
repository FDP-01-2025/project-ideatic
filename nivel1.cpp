#include <iostream>
#include <ctime> //para generar valores aleatorios, en este caso, los laberintos xd.
using namespace std;

void showmenu(); // show menu to the user to continue
void homescreen(); //game welcome

void gLabyrinth(int rows, int columns, int density) //base function to adjust the labyrinth values
{
    int **matriz;
    matriz = new int *[rows]; // The matrix requests the number of rows that the maze will have.
    int walls = density * 8; 
    int wallsd = rows * columns * density / 4; // formula to calculate the measurements of the labyrinth.
    for (int i = 0; i < rows; i++) // For each row, the number of columns will be created
    {
        matriz[i] = new int[columns]; // number of columns.
    }
    // definition of the values ​​of the columns and rows of the maze:
    for (int a = 0; a < rows; a++)
    {
        for (int b = 0; b < columns ; b++)
        {
            if (a == 0 || b == 0 || a == rows-1  || b == columns-1)
            {
                matriz[a][b] = 1;
            }
            else
            {
                matriz[a][b] = 0;
            }
        }
    }             