#include <iostream>
#include <curses.h>
#ifndef MOVER_H
#define MOVER_H

// Definición de la función para mover al personaje
// Recibe referencias a x e y, la tecla presionada y los límites del área de juego
void mover_personaje(int &x, int &y, int ch, int ancho, int alto)
{

    // Mueve hacia arriba si no sale del borde superior
    if (ch == KEY_UP && y > 1)
        y--;
    // Mueve hacia abajo si no sale del borde inferior
    else if (ch == KEY_DOWN && y < alto - 2)
        y++;
    // Mueve hacia la izquierda si no sale del borde izquierdo
    else if (ch == KEY_LEFT && x > 1)
        x--;
    // Mueve hacia la derecha si no sale del borde derecho
    else if (ch == KEY_RIGHT && x < ancho - 2)
        x++;
}
