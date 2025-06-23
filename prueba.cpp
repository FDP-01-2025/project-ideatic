#include <curses.h>
<<<<<<< HEAD
#include "src/archivo.h"
#include "src/torre.h"
#include <stdlib.h>
#include <time.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 15
#define MAX_BOLAS 10

int main()
{
    // Inicialización de variables principales
    int x = MAP_WIDTH / 2, y = MAP_HEIGHT - 2; // Posición inicial del jugador
    int ch, game_over = 0;
    int last_dir = KEY_RIGHT; // Dirección inicial
    int vidas = 3;            // Vidas del jugador

    // Inicializa el arreglo de bolas
    Bola bolas[MAX_BOLAS];
    for (int i = 0; i < MAX_BOLAS; i++)
        bolas[i].activa = false;

    // Inicializa la pantalla y colores
    initscr();
    start_color();
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Color del personaje
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // Color de la bola
    init_pair(5, COLOR_RED, COLOR_BLACK);    // Color rojo para corazones
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    // Calcula la posición para centrar la ventana de juego
    int startx = (COLS - MAP_WIDTH) / 2;
    int starty = (LINES - MAP_HEIGHT) / 2;
    WINDOW *gamewin = newwin(MAP_HEIGHT, MAP_WIDTH, starty, startx);
    keypad(gamewin, TRUE);
    nodelay(gamewin, TRUE);

    // Bucle principal del juego
    while (!game_over)
    {
        // Limpia y dibuja el área de juego
        werase(gamewin);
        if (ch == 'q')
            break; // Sale si se presiona 'q'
        box(gamewin, 0, 0);
        clear();

        // Dibuja el personaje
        mvwaddch(gamewin, y, x, '@' | COLOR_PAIR(2));

        // Muestra los corazones (vidas)
        mostrar_corazones(gamewin, vidas);

        // Dibuja todas las bolas activas
        for (int i = 0; i < MAX_BOLAS; i++)
        {
            if (bolas[i].activa)
            {
                wattron(gamewin, COLOR_PAIR(4));
                mvwaddch(gamewin, bolas[i].y, bolas[i].x, 'o');
                wattroff(gamewin, COLOR_PAIR(4));
            }
        }

        wrefresh(gamewin);
        // Lee la tecla presionada (no bloquea)
        ch = wgetch(gamewin);

        // Movimiento del jugador y guarda la última dirección
        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
        {
            mover_personaje(x, y, ch, MAP_WIDTH, MAP_HEIGHT);
            last_dir = ch;
        }

        // Espadazo si se presiona 'x'
        if (ch == 'x' || ch == 'X')
        {
            espadaso(gamewin, x, y, last_dir);
            wrefresh(gamewin);
            napms(120);
        }

        // Lanza una nueva bola en la dirección del último movimiento
        if (ch == ' ')
        {
            for (int i = 0; i < MAX_BOLAS; i++)
            {
                if (!bolas[i].activa)
                {
                    bolas[i].x = x;
                    bolas[i].y = y;
                    // Dirección según la última flecha presionada
                    if (last_dir == KEY_UP)
                    {
                        bolas[i].dx = 0;
                        bolas[i].dy = -1;
                    }
                    else if (last_dir == KEY_DOWN)
                    {
                        bolas[i].dx = 0;
                        bolas[i].dy = 1;
                    }
                    else if (last_dir == KEY_LEFT)
                    {
                        bolas[i].dx = -1;
                        bolas[i].dy = 0;
                    }
                    else
                    {
                        bolas[i].dx = 1;
                        bolas[i].dy = 0;
                    }
                    bolas[i].activa = true;
                    bolas[i].frame = 0;
                    break;
                }
            }
        }

        // Mueve todas las bolas activas según su dirección
        for (int i = 0; i < MAX_BOLAS; i++)
        {
            if (bolas[i].activa)
            {
                // Si la bola va vertical, se mueve más lento
                if ((bolas[i].dx == 0) && (bolas[i].dy != 0))
                {
                    bolas[i].frame++;
                    if (bolas[i].frame % 2 == 0)
                    {
                        bolas[i].y += bolas[i].dy;
                    }
                }
                else
                {
                    bolas[i].x += bolas[i].dx;
                    bolas[i].y += bolas[i].dy;
                }
                // Desactiva si sale del área
                if (bolas[i].x <= 0 || bolas[i].x >= MAP_WIDTH - 1 ||
                    bolas[i].y <= 0 || bolas[i].y >= MAP_HEIGHT - 1)
                {
                    bolas[i].activa = false;
                }
            }
        }

        // Si el personaje entra a la torre, muestra recuadro pequeño
        if (x >= MAP_WIDTH - 8)
        {
            mostrar_entrada_torre(starty, startx, MAP_HEIGHT, MAP_WIDTH);
            // No pongas break si quieres que el juego continúe
        }

        napms(70); // Pequeña pausa para animación
    }
    nodelay(gamewin, FALSE);
    // Pantalla de Game Over
    werase(gamewin);
    box(gamewin, 0, 0);
    mvwprintw(gamewin, MAP_HEIGHT / 2, 2, "¡Game Over! Presiona una tecla...");
    wrefresh(gamewin);
    wgetch(gamewin);

    // Libera recursos y termina curses
    delwin(gamewin);
    endwin();
    return 0;
}
=======

int main() {
    initscr();
    printw("¡Hola desde PDCurses!");
    refresh();
    getch();
    endwin();
    return 0;
}
>>>>>>> d25b61f (Cambios nivel 2)
