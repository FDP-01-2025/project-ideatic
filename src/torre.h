#ifndef TORRE_H
#define TORRE_H

#include <curses.h>

// Dibuja la torre en la posición indicada
inline void dibujar_torre(WINDOW *win, int torre_y, int torre_x)
{
    const char *torre[] = {
        "  ||||  ",
        " [____] ",
        " |    | ",
        " |    | ",
        " |    | ",
        " |____| "};
    for (int i = 0; i < 6; i++)
    {
        mvwprintw(win, torre_y + i, torre_x, "%s", torre[i]);
    }
}

// Función para mostrar el recuadro de entrada a la torre
inline void mostrar_entrada_torre(int starty, int startx, int map_height, int map_width)
{
    int win_h = 8, win_w = 24;
    int win_y = (map_height - win_h) / 2;
    int win_x = (map_width - win_w) / 2;
    WINDOW *torre_win = newwin(win_h, win_w, starty + win_y, startx + win_x);
    box(torre_win, 0, 0);
    mvwprintw(torre_win, 2, 4, "¡Has entrado a la torre!");
    mvwprintw(torre_win, 4, 3, "Presiona una tecla...");
    wrefresh(torre_win);
    wgetch(torre_win); // Espera a que el usuario presione una tecla
    delwin(torre_win);
}

#endif