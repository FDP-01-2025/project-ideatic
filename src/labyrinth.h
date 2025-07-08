#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h" // Incluye las constantes ROWS y COLUMNS

// Puedes ajustar la densidad del laberinto (más alto = más muros)
#define LAB_DENSITY 150

// Genera un laberinto en la matriz recibida (1 = muro, 0 = camino)
inline void generarLaberinto(int matriz[ROWS][COLUMNS]) {
    int walls = LAB_DENSITY * 6;

    // Inicializa los bordes como muros y el interior como caminos
    for (int i = 0; i < ROWS; i++) {
        for (int a = 0; a < COLUMNS; a++) {
            if (a == 0 || i == 0 || a == COLUMNS - 1 || i == ROWS - 1) {
                matriz[i][a] = 1; // Borde: muro
            } else {
                matriz[i][a] = 0; // Interior: camino
            }
        }
    }

    // Generación de paredes internas aleatorias
    for (int c = 0; c < LAB_DENSITY; c++) {
        // Selecciona una celda par aleatoria dentro del laberinto
        int cl = rand() % (COLUMNS - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (ROWS - 4) + 2;
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1; // Coloca un muro

        // Intenta expandir el muro en varias direcciones
        for (int d = 0; d < walls; d++) {
            int mc[4] = {cl, cl, cl + 2, cl - 2}; // Posibles columnas destino
            int mr[4] = {rw + 2, rw - 2, rw, rw}; // Posibles filas destino
            int ran = rand() % 4; // Elige dirección aleatoria

            // Verifica que la celda destino esté dentro de los límites
            if (mr[ran] >= 0 && mr[ran] < ROWS && mc[ran] >= 0 && mc[ran] < COLUMNS) {
                // Si la celda destino es un camino, la convierte en muro
                if (matriz[mr[ran]][mc[ran]] == 0) {
                    matriz[mr[ran]][mc[ran]] = 1;
                    // También coloca un muro en la celda intermedia para conectar
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

// Dibuja el laberinto en la ventana de curses
inline void dibujarLaberinto(WINDOW* win, int matriz[ROWS][COLUMNS], int offset_y = 0, int offset_x = 0) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (matriz[i][j] == 1) {
                mvwaddch(win, offset_y + i, offset_x + j, '#'); // Dibuja muro
            } else {
                mvwaddch(win, offset_y + i, offset_x + j, ' '); // Dibuja camino
            }
        }
    }
    wrefresh(win); // Refresca la ventana para mostrar los cambios
}

#endif // LABYRINTH_H