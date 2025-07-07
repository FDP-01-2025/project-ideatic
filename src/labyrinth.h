#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h" // Incluye las constantes ROWS y COLUMNS

// Puedes ajustar la densidad si lo deseas
#define LAB_DENSITY 150

// Genera un laberinto en la matriz recibida (1 = muro, 0 = camino)
inline void generarLaberinto(int matriz[ROWS][COLUMNS]) {
    int walls = LAB_DENSITY * 6;

    // Bordes y caminos iniciales
    for (int i = 0; i < ROWS; i++) {
        for (int a = 0; a < COLUMNS; a++) {
            if (a == 0 || i == 0 || a == COLUMNS - 1 || i == ROWS - 1) {
                matriz[i][a] = 1;
            } else {
                matriz[i][a] = 0;
            }
        }
    }

    // Generación de paredes internas
    for (int c = 0; c < LAB_DENSITY; c++) {
        int cl = rand() % (COLUMNS - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (ROWS - 4) + 2;
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1;

        for (int d = 0; d < walls; d++) {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;

            if (mr[ran] >= 0 && mr[ran] < ROWS && mc[ran] >= 0 && mc[ran] < COLUMNS) {
                if (matriz[mr[ran]][mc[ran]] == 0) {
                    matriz[mr[ran]][mc[ran]] = 1;
                    int midrow = mr[ran] + (rw - mr[ran]) / 2;
                    int midcolumn = mc[ran] + (cl - mc[ran]) / 2;
                    if (midrow >= 0 && midrow < ROWS && midcolumn >= 0 && midcolumn < COLUMNS) {
                        matriz[midrow][midcolumn] = 1;
                    }
                }
            }
        }
    }
}

// Si quieres dibujar el laberinto con PDCurses:
inline void dibujarLaberinto(WINDOW* win, int matriz[ROWS][COLUMNS], int offset_y = 0, int offset_x = 0) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (matriz[i][j] == 1) {
                mvwaddch(win, offset_y + i, offset_x + j, '#');
            } else {
                mvwaddch(win, offset_y + i, offset_x + j, ' ');
            }
        }
    }
    wrefresh(win);
}

#endif // LABYRINTH_H