#include <curses.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>  // Necesaria para PlaySound()
#pragma comment(lib, "winmm.lib")  // Enlaza con la librería de sonido

#define MAP_WIDTH 50
#define MAP_HEIGHT 15
#define DENSITY 150

void reproducirFondo() {
    PlaySound("Musicafondo.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void reproducirVictoria() {
    PlaySound(NULL, 0, 0); // Detiene fondo
    PlaySound("Ganaste.wav", NULL, SND_FILENAME | SND_SYNC);
}

void gLabyrinth(WINDOW* win, int rows, int columns, int density, int **&matriz, int &sx, int &sy) {
    matriz = new int*[rows];
    int walls = density * 8;
    for (int i = 0; i < rows; i++)
        matriz[i] = new int[columns];

    for (int a = 0; a < rows; a++)
        for (int b = 0; b < columns; b++)
            matriz[a][b] = (a == 0 || b == 0 || a == rows-1 || b == columns-1) ? 1 : 0;

    srand(time(NULL));
    for (int c = 0; c < density; c++) {
        int cl = rand() % (columns - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (rows - 4) + 2;
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1;
        for (int d = 0; d < walls; d++) {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;
            if (matriz[mr[ran]][mc[ran]] == 0) {
                matriz[mr[ran]][mc[ran]] = 1;
                matriz[mr[ran] + (rw - mr[ran]) / 2][mc[ran] + (cl - mc[ran]) / 2] = 1;
            }
        }
    }

    // Elegir celda de salida
    for (int y = rows - 2; y > 1; y--) {
        for (int x = columns - 2; x > 1; x--) {
            if (matriz[y][x] == 0) {
                sy = y;
                sx = x;
                goto salida;
            }
        }
    }
salida:

    // Dibujar laberinto
    for (int e = 0; e < rows; e++) {
        for (int f = 0; f < columns; f++) {
            if (e == sy && f == sx)
                mvwaddch(win, e+1, f+1, 'X'); // Salida
            else if (matriz[e][f] == 1)
                mvwaddch(win, e+1, f+1, 178); // Pared
            else
                mvwaddch(win, e+1, f+1, ' ');
        }
    }
}

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int rows = MAP_HEIGHT, columns = MAP_WIDTH, density = DENSITY;
    int **laberinto = nullptr;

    int startx = (COLS - columns) / 2;
    int starty = (LINES - rows) / 2;
    WINDOW *lab_win = newwin(rows+2, columns+2, starty, startx);
    keypad(lab_win, TRUE);
    box(lab_win, 0, 0);

    int salidaX = 0, salidaY = 0;
    gLabyrinth(lab_win, rows, columns, density, laberinto, salidaX, salidaY);
    wrefresh(lab_win);

    int px = 1, py = 1;
    for (int y = 1; y < rows-1; y++)
        for (int x = 1; x < columns-1; x++)
            if (laberinto[y][x] == 0) {
                py = y;
                px = x;
                goto encontrado;
            }
encontrado:

    reproducirFondo();

    int ch;
    nodelay(lab_win, TRUE);

    while ((ch = wgetch(lab_win)) != 'q') {
        mvwaddch(lab_win, py+1, px+1, ' ');

        if (ch == KEY_UP    && laberinto[py-1][px] == 0) py--;
        if (ch == KEY_DOWN  && laberinto[py+1][px] == 0) py++;
        if (ch == KEY_LEFT  && laberinto[py][px-1] == 0) px--;
        if (ch == KEY_RIGHT && laberinto[py][px+1] == 0) px++;

        mvwaddch(lab_win, py+1, px+1, '@');
        mvwprintw(lab_win, 0, 2, "Tecla: %d   ", ch);
        wrefresh(lab_win);
        napms(50);

        if (px == salidaX && py == salidaY) {
            mvwprintw(lab_win, 0, 20, "¡Has escapado!");
            wrefresh(lab_win);
            reproducirVictoria();
            break;
        }
    }

    // Libera memoria
    for (int i = 0; i < rows; i++)
        delete[] laberinto[i];
    delete[] laberinto;

    delwin(lab_win);
    endwin();
    return 0;
}