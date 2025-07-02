#ifndef BALL_H
#define BALL_H

#include <curses.h>

#define MAX_BALLS 10

// Estructura para las bolas lanzadas por el personaje
struct Ball
{
    int x, y, dx, dy;
    bool active;
    int frame;
};

// Dibuja y mueve todas las bolas activas, sin laberinto
void update_balls(WINDOW *win, Ball balls[], int max_balls, int width, int height)
{
    for (int i = 0; i < max_balls; i++)
    {
        if (balls[i].active)
        {
            // Mueve la bola
            balls[i].x += balls[i].dx;
            balls[i].y += balls[i].dy;

            // Desactiva la bola si sale de los límites de la pantalla
            if (balls[i].x <= 0 || balls[i].x >= width - 1 ||
                balls[i].y <= 0 || balls[i].y >= height - 1)
            {
                balls[i].active = false;
            }
            else
            {
                // Dibuja la bola
                wattron(win, COLOR_PAIR(4));
                mvwaddch(win, balls[i].y, balls[i].x, 'o');
                wattroff(win, COLOR_PAIR(4));
            }
        }
    }
    napms(70); // Pequeña pausa para animación
}

// Lanza una nueva bola en la dirección del personaje
void shoot_ball(Ball balls[], int max_balls, int x, int y, int last_dir)
{
    for (int i = 0; i < max_balls; i++)
    {
        if (!balls[i].active)
        {
            balls[i].x = x;
            balls[i].y = y;
            if (last_dir == KEY_UP)
            {
                balls[i].dx = 0;
                balls[i].dy = -1;
            }
            else if (last_dir == KEY_DOWN)
            {
                balls[i].dx = 0;
                balls[i].dy = 1;
            }
            else if (last_dir == KEY_LEFT)
            {
                balls[i].dx = -1;
                balls[i].dy = 0;
            }
            else /* KEY_RIGHT o por defecto */
            {
                balls[i].dx = 1;
                balls[i].dy = 0;
            }
            balls[i].active = true;
            balls[i].frame = 0;
            break;
        }
    }
}

#endif // BALL_H