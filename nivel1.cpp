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
    creation of the labyrinth
    srand(time(NULL)); // It will be used to generate new values ​​for the rows or variables each time the program is run.
    for (int c = 0; c < density; c++)
    {
        int cl = rand() % (columns - 4) + 2;
        cl = (cl /2) * 2;
        int rw = rand() % (rows - 4) + 2;
        rw = (rw /2) * 2;
        matriz[rw][cl] = 1;
        for (int d = 0; d < walls; d++)
        {
            int mc[4] = {cl, cl, cl + 2, cl - 2}; // length for the columns, the last two values ​​correspond to when the rows remain at 0 and vice versa for the columns.
            int mr[4] = {rw + 2, rw - 2, rw, rw}; // lenght for the rows.
            int ran = rand() % 4; //ran=random numbers

            if (matriz[mr[ran]][mc[ran]] == 0)
            {
                matriz[mr[ran]][mc[ran]] = 1;
                matriz[mr[ran] + (rw - mr[ran]) / 2][mc[ran] + (cl - mc[ran]) / 2] = 1;
            }
        }
    }
    // add density to the walls
    for (int e = 0; e < rows; e++)
    {
        for (int f = 0; f < columns; f++)
        {
            if (matriz[e][f] == 1)
            {
                char x = 178;
                cout << x <<x;
                //cout << "1 "; // 1 will be displayed if the matrix is ​​equal to 1, this will be what will represent the walls of the maze.
            }
            if (matriz[e][f] == 0)
            {
            cout << "  "; }
        }
        cout << "\n";
    }
}
    int main()
    {
        gLabyrinth(15, 50, 150); //labyrinth values.
        return 0;
    }        