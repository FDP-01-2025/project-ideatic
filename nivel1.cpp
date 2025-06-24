#include <curses.h>
#include <cstdlib>
#include <ctime> //para generar valores aleatorios, en este caso, los laberintos xd.
using namespace std;

#define MAP_WIDTH 50
#define MAP_HEIGHT 15 
#define DENSITY 150


void showmenu(); // show menu to the user to continue
void homescreen(); //game welcome

void gLabyrinth(WINDOW* win, int rows, int columns, int density, int **&matriz)
{
    matriz = new int*[rows];
    int walls = density * 8;
    for (int i = 0; i < rows; i++)
        matriz[i] = new int[columns];

    // definition of the values ​​of the columns and rows of the maze:
   for (int a = 0; a < rows; a++)
        for (int b = 0; b < columns; b++)
            matriz[a][b] = (a == 0 || b == 0 || a == rows-1 || b == columns-1) ? 1 : 0;

    srand(time(NULL)); // It will be used to generate new values ​​for the rows or variables each time the program is run.
    for (int c = 0; c < density; c++)
    {
        int cl = rand() % (columns - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (rows - 4) + 2;
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1;
        for (int d = 0; d < walls; d++)
        {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;
            if (matriz[mr[ran]][mc[ran]] == 0)
            {
                matriz[mr[ran]][mc[ran]] = 1;
                matriz[mr[ran] + (rw - mr[ran]) / 2][mc[ran] + (cl - mc[ran]) / 2] = 1;
            }
        }
    }
// Draw the maze in the curses window (+1 to leave the border)
    for (int e = 0; e < rows; e++)
        for (int f = 0; f < columns; f++)
            if (matriz[e][f] == 1)
                mvwaddch(win, e+1, f+1, 178); // Pared
            else
                mvwaddch(win, e+1, f+1, ' '); // Espacio
}
int main()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); // enables arrows in the main window

    int rows = MAP_HEIGHT, columns = MAP_WIDTH, density = DENSITY;
    int **laberinto = nullptr;

    // create labyrinth window
    int startx = (COLS - columns) / 2;
    int starty = (LINES - rows) / 2;
    WINDOW *lab_win = newwin(rows+2, columns+2, starty, startx);
    keypad(lab_win, TRUE); // enables arrows inlab_win
    box(lab_win, 0, 0);

    


