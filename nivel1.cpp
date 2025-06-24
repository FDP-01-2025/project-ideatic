#include <iostream>
#include <studio.h>
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