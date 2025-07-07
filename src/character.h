#include <iostream>
#include <curses.h>
#include <ctime>
#include "ball.h"
#include "save_game.h"
#include "music.h"
#include "labyrinth.h" // Incluye las funciones del laberinto
#include "constants.h" // Incluye las constantes ROWS y COLUMNS

#define MOVER_H
int x = 10, y = 5;
int coin_x, coin_y;
int ch = 0, score = 0;
Ball balls[MAX_BALLS] = {}; // Arreglo de bolas

void espadaso(WINDOW *win, int x, int y, int last_dir);

void inicial()
{
    // Inicializa la pantalla y colores
    initscr();
    noecho();
    curs_set(0);
    start_color();
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Color del personaje
    init_pair(3, COLOR_CYAN, COLOR_BLACK);   // Color de la espada
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL));

    // Posición inicial de la moneda
    coin_x = rand() % (COLS - 2) + 1;
    coin_y = rand() % (LINES - 2) + 1;
    // reproducirFondo();
}

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

void puntos()
{
    int last_dir = KEY_RIGHT; // Inicializa la dirección
    // Ball balls[MAX_BALLS] = {}; // Arreglo de bolas
    int laberinto[ROWS][COLUMNS]; // Matriz del laberinto
    
    generarLaberinto(laberinto); // Generar el laberinto

    while (1)
    {
        clear();
        dibujarLaberinto(laberinto); // Dibujar el laberinto
        box(stdscr, 0, 0);
        mvprintw(0, 2, "Collect coins ($) with '@'. Score: %d | 'q' to quit", score);
        mvaddch(coin_y, coin_x, '$');
        wattron(stdscr, COLOR_PAIR(2));  // Activa el color (por ejemplo, amarillo)
        mvaddch(y, x, '@');              // Dibuja el personaje with color
        wattroff(stdscr, COLOR_PAIR(2)); // Desactiva el color

        update_balls(stdscr, balls, MAX_BALLS, COLS, LINES);

        refresh();

        ch = getch();
        if (ch == 'q' || ch == 'Q')
            break;
        if (ch == ' ')
        {
            shoot_ball(balls, MAX_BALLS, x, y, last_dir);
        }
        // Guarda la última dirección si se mueve
        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
            last_dir = ch;

          // Ataca con la espada si se presiona 'x' o 'X
        if (ch == 'x' || ch == 'X')
        {
            espadaso(stdscr, x, y, last_dir);
            // refresh();
            // napms(120); // Pausa para mostrar la espada
        }

        mover_personaje(x, y, ch, COLS, LINES);

        if (x == coin_x && y == coin_y) {
            reproducirMoneda(); // Reproduce el sonido de la moneda
            napms(500);         // Pausa breve para permitir que el sonido de la moneda se reproduzca
            reproducirFondo();  // Reanuda el sonido de fondo
            score++;
            coin_x = rand() % (COLS - 2) + 1;
            coin_y = rand() % (LINES - 2) + 1;
        }
    }

    // Menú de confirmación para guardar partida al salir
    nodelay(stdscr, FALSE); // Asegura que getch espere la entrada
    clear();
    printw("Do you want to save the game? (y/n): ");
    refresh();
    int save_opt = getch();
    if (save_opt == 'y' || save_opt == 'Y')
    {
        save_game("save.txt", x, y, score, balls, MAX_BALLS);
        printw("\nGame saved!\n");
        refresh();
        napms(1000);
    }

    endwin();
}
// Dibuja una espada al lado del personaje según la dirección
void espadaso(WINDOW *win, int x, int y, int last_dir)
{
    wattron(win, COLOR_PAIR(3)); // Activa color cian
    // last_dir es la última dirección (KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT)
    if (last_dir == KEY_UP)
        mvwaddch(win, y - 1, x, '|'); // Dibuja la espada arriba del personaje
    else if (last_dir == KEY_DOWN)
        mvwaddch(win, y + 1, x, '|'); // Dibuja la espada abajo del personaje
    else if (last_dir == KEY_LEFT)
        mvwprintw(win, y, x - 2, "--"); // Dibuja la espada a la izquierda del personaje
    else                                // Derecha por defecto
        mvwprintw(win, y, x + 1, "--"); // Dibuja la espada a la derecha del personaje
    wattroff(win, COLOR_PAIR(3));       // Desactiva color cian

    refresh();
    napms(120); // Pausa para mostrar la espada
}