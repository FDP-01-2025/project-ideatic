#ifndef ENEMY_H
#define ENEMY_H

#include "constants.h"
#include <curses.h>

// Estructura para un enemigo con dirección y tipo de movimiento
struct Enemy
{
    int x, y;
    int dir;       // 1 o -1
    bool vertical; // true = movimiento vertical, false = horizontal
    bool active;
};

#define NUM_ENEMIGOS 5
// Declaración global del arreglo de enemigos
extern Enemy enemigos[NUM_ENEMIGOS];

// Función para generar enemigos en posiciones libres
inline void generar_enemigos(Enemy enemigos[], int cantidad, int laberinto[ROWS][COLUMNS])
{
    int generados = 0;
    while (generados < cantidad)
    {
        int ex = rand() % COLUMNS;
        int ey = rand() % ROWS;
        if (laberinto[ey][ex] == 0)
        {
            enemigos[generados].x = ex;
            enemigos[generados].y = ey;
            enemigos[generados].dir = (rand() % 2 == 0) ? 1 : -1;
            enemigos[generados].vertical = (rand() % 2 == 0); // Aleatorio: vertical u horizontal
            enemigos[generados].active = true;
            generados++;
        }
    }
}

inline void dibujar_enemigos(WINDOW *win, Enemy enemigos[], int cantidad, int offset_x, int offset_y)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (enemigos[i].active)
        {
            wattron(win, COLOR_PAIR(5)); // Usa un color diferente si quieres
            mvwaddch(win, offset_y + enemigos[i].y, offset_x + enemigos[i].x, 'E');
            wattroff(win, COLOR_PAIR(5));
        }
    }
}

// Mueve los enemigos de un lado a otro dentro del laberinto
inline void mover_enemigos(Enemy enemigos[], int cantidad, int laberinto[ROWS][COLUMNS])
{
    for (int i = 0; i < cantidad; i++)
    {
        if (!enemigos[i].active)
            continue;
        int nx = enemigos[i].x;
        int ny = enemigos[i].y;
        if (enemigos[i].vertical)
        {
            ny += enemigos[i].dir;
            // Si hay muro o borde, cambia de dirección
            if (ny < 0 || ny >= ROWS || laberinto[ny][nx] == 1)
            {
                enemigos[i].dir *= -1;
            }
            else
            {
                enemigos[i].y = ny;
            }
        }
        else
        {
            nx += enemigos[i].dir;
            if (nx < 0 || nx >= COLUMNS || laberinto[ny][nx] == 1)
            {
                enemigos[i].dir *= -1;
            }
            else
            {
                enemigos[i].x = nx;
            }
        }
    }
}

void avanzar_nivel(int &score, int &x, int &y, int &nivel, int &enemigos_en_nivel, int laberinto[ROWS][COLUMNS], Enemy enemigos[], int &coin_x, int &coin_y)
{
    nivel++;
    score = 0;
    enemigos_en_nivel += 2; // Aumenta la cantidad de enemigos por nivel
    if (enemigos_en_nivel > 30)
        enemigos_en_nivel = 30; // Límite máximo

    generateLabyrinth(laberinto);
    generar_enemigos(enemigos, enemigos_en_nivel, laberinto);
    for (int j = 0; j < enemigos_en_nivel; j++)
    {
        enemigos[j].dir = (rand() % 2 == 0) ? 1 : -1;
        enemigos[j].active = true;
    }
    do
    {
        coin_x = rand() % COLUMNS;
        coin_y = rand() % ROWS;
    } while (laberinto[coin_y][coin_x] != 0);

    x = 10;
    y = 5;
}
#endif
