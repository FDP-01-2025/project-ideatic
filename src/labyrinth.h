#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h" // Incluye las constantes ROWS y COLUMNS

// Generar el laberinto
void generarLaberinto(int laberinto[ROWS][COLUMNS]) {
    srand(time(NULL));

    // Inicializar el laberinto con muros exteriores
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) {
                laberinto[i][j] = 1; // Muros exteriores
            } else {
                laberinto[i][j] = rand() % 2; // Generar muros internos aleatorios
            }
        }
    }

    // Crear un camino para el personaje
    laberinto[1][1] = 0; // Punto de inicio
    laberinto[ROWS - 2][COLUMNS - 2] = 0; // Punto de salida
}

// Dibujar el laberinto
void dibujarLaberinto(int laberinto[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (laberinto[i][j] == 1) {
                mvaddch(i, j, '#'); // Muros del laberinto
            } else {
                mvaddch(i, j, ' '); // Espacios libres
            }
        }
    }
}

#endif // LABYRINTH_H