#ifndef MOVER_H
#define MOVER_H

// Declaración de la función para mover al personaje dentro de los límites del área de juego
void mover_personaje(int &x, int &y, int ch, int ancho, int alto);

#endif

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

// Matrices para las posturas del personaje según la dirección (3x3)
// Cada matriz representa una postura diferente
char personaje_up[3][3] = {
    {' ', 'O', ' '},   // Cabeza
    {'/', '|', '\\'},  // Brazos y torso
    {' ', '^', ' '}    // Piernas levantadas
};
char personaje_down[3][3] = {
    {' ', 'O', ' '},
    {'/', '|', '\\'},
    {'/', ' ', '\\'}
};
char personaje_left[3][3] = {
    {' ', 'O', ' '},
    {'/', '|', '-'},
    {'/', ' ', ' '}
};
char personaje_right[3][3] = {
    {' ', 'O', ' '},
    {'-', '|', '\\'},
    {' ', ' ', '\\'}
};

// Arte ASCII de un caballero (5x5)
// Cada string representa una fila del caballero
char caballero[5][6] = {
    "  O  ",  // Cabeza
    " /|\\ ", // Brazos y torso
    " /|\\ ", // Armadura/escudo
    "  |  ",  // Cintura
    " / \\ "  // Piernas
};

struct Bola
{
    int x, y;
    int dx, dy; // Dirección de la bola
    bool activa;
    int frame;  // Contador para controlar la velocidad

};