#include <curses.h> // Incluye la biblioteca para manejo de pantalla y teclado en consola
#include "archivo.h"
#include <stdlib.h>
#include <time.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 15
#define MAX_BOLAS 10 // Máximo de bolas en pantalla

int main()
{
    int x = MAP_WIDTH / 2, y = MAP_HEIGHT - 2; // Posición inicial del jugador (@)
    int ch, game_over = 0;                     // Variable para almacenar la tecla presionada
    int last_dir = KEY_RIGHT;                  // direccion del personaje por defecto la derecha

    // Arreglo de bolas
    Bola bolas[MAX_BOLAS];
    for (int i = 0; i < MAX_BOLAS; i++)
        bolas[i].activa = false;

    initscr();            // Inicializa la pantalla para usar funciones de curses
    keypad(stdscr, TRUE); // Habilita la lectura de teclas especiales (flechas)
    noecho();             // No muestra las teclas presionadas en pantalla
    curs_set(0);          // Oculta el cursor

    // Calcula la posición para centrar la ventana de juego
    int startx = (COLS - MAP_WIDTH) / 2;
    int starty = (LINES - MAP_HEIGHT) / 2;
    WINDOW *gamewin = newwin(MAP_HEIGHT, MAP_WIDTH, starty, startx);
    keypad(gamewin, TRUE);  // Habilita teclas especiales en la ventana de juego
    nodelay(gamewin, TRUE); // Hace que wgetch no bloquee

    // Inicializa colores (asegúrate de tener esto antes de usarlos)
    start_color();
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Color del personaje
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // Color de la bola

    while (!game_over)
    {
        werase(gamewin);    // Limpia la ventana de juego
        box(gamewin, 0, 0); // Dibuja el borde
        clear();            // Limpia la pantalla antes de dibujar

        mvwaddch(gamewin, y, x, '@' | COLOR_PAIR(2));

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

        ch = wgetch(gamewin); // Lee la tecla (no bloquea por nodelay)

        // Movimiento del jugador y guarda la última dirección
        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
        {
            mover_personaje(x, y, ch, MAP_WIDTH, MAP_HEIGHT);
            last_dir = ch; // Guarda la última dirección
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
                    } // Derecha por defecto
                    bolas[i].activa = true;
                    bolas[i].frame = 0; // <-- Agrega esto
                    break;
                }
            }
        }

        if (ch == 'q' || ch == 'Q')
            break;

        // Mueve todas las bolas activas según su dirección
        for (int i = 0; i < MAX_BOLAS; i++)
        {
            if (bolas[i].activa)
            {
                // Si la bola va vertical, solo se mueve cada 2 frames
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

        napms(70); // Pequeña pausa para que la animación sea visible
    }

    // Pantalla de Game Over
    werase(gamewin);
    box(gamewin, 0, 0);
    mvwprintw(gamewin, MAP_HEIGHT / 2, 2, "¡Game Over! Presiona una tecla...");
    wrefresh(gamewin);
    wgetch(gamewin);

    // Libera recursos y termina curses
    delwin(gamewin);
    endwin(); // Finaliza el modo curses y restaura la terminal
    return 0; // Fin del programa
}
