#include <iostream>
#include <curses.h>
#include <ctime>
#include "ball.h"
#include "save_game.h"
#include "music.h"
#include "labyrinth.h" // Incluye las funciones del laberinto
#include "constants.h" // Incluye las constantes ROWS y COLUMNS
#include "enemy.h"

#define MOVER_H
int x = 10, y = 5;
int coin_x, coin_y;
int ch = 0, score = 0;
Ball balls[MAX_BALLS] = {}; // Arreglo de bolas
int laberinto[ROWS][COLUMNS];
Enemy enemigos[NUM_ENEMIGOS];

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
    init_pair(5, COLOR_RED, COLOR_BLACK);    // O el color que prefieras
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL));

    // Generar enemigos en posiciones libres del laberinto
    generar_enemigos(enemigos, NUM_ENEMIGOS, laberinto);
    for (int i = 0; i < NUM_ENEMIGOS; i++)
    {
        enemigos[i].dir = (rand() % 2 == 0) ? 1 : -1; // Dirección inicial aleatoria
        enemigos[i].active = true;
    }

    // Posición inicial de la moneda: SOLO en un espacio libre
    do
    {
        coin_x = rand() % COLUMNS;
        coin_y = rand() % ROWS;
    } while (laberinto[coin_y][coin_x] != 0);
    // reproducirFondo();
    generarLaberinto(laberinto); // PRIMERO genera el laberinto

    // Luego busca una posición libre para la moneda
    do
    {
        coin_x = rand() % COLUMNS;
        coin_y = rand() % ROWS;
    } while (laberinto[coin_y][coin_x] != 0);

    // ...resto del código...
}

// Definición de la función para mover al personaje
// Recibe referencias a x e y, la tecla presionada y los límites del área de juego
void mover_personaje(int &x, int &y, int ch, int ancho, int alto)
{
    int nx = x, ny = y;
    if (ch == KEY_UP && y > 1)
        ny--;
    else if (ch == KEY_DOWN && y < alto - 2)
        ny++;
    else if (ch == KEY_LEFT && x > 1)
        nx--;
    else if (ch == KEY_RIGHT && x < ancho - 2)
        nx++;
    // Solo mueve si no hay muro
    if (laberinto[ny][nx] == 0)
    {
        x = nx;
        y = ny;
    }
}

void puntos()
{
    int last_dir = KEY_RIGHT;
    int offset_y = 1, offset_x = 1;
    int enemy_tick = 0;        // Contador para el movimiento de enemigos
    const int ENEMY_SPEED = 3; // Mueven cada 3 ciclos
    while (1)
    {
        clear();
        // Dibuja el marco
        for (int i = 0; i < ROWS + 2; i++)
        {
            mvaddch(i, 0, '|');
            mvaddch(i, COLUMNS + 1, '|');
        }
        for (int j = 0; j < COLUMNS + 2; j++)
        {
            mvaddch(0, j, '-');
            mvaddch(ROWS + 1, j, '-');
        }

        // Dibuja el laberinto
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                if (laberinto[i][j] == 1)
                    mvaddch(offset_y + i, offset_x + j, '#');
            }
        }

        mvprintw(0, COLUMNS + 4, "Collect coins ($) with '@'. Score: %d | 'q' to quit", score);
        mvaddch(offset_y + coin_y, offset_x + coin_x, '$');
        wattron(stdscr, COLOR_PAIR(2));
        mvaddch(offset_y + y, offset_x + x, '@');
        wattroff(stdscr, COLOR_PAIR(2));

        update_balls(stdscr, balls, MAX_BALLS, offset_x, offset_y);
        // Mueve los enemigos antes de dibujarlos
        if (enemy_tick % ENEMY_SPEED == 0)
        {
            mover_enemigos(enemigos, NUM_ENEMIGOS, laberinto);
        }
        dibujar_enemigos(stdscr, enemigos, NUM_ENEMIGOS, offset_x, offset_y);

        // Verifica colisión con enemigos
        for (int i = 0; i < NUM_ENEMIGOS; i++)
        {
            if (enemigos[i].active && enemigos[i].x == x && enemigos[i].y == y)
            {
                // Mensaje de derrota y reinicio
                clear();
                mvprintw(ROWS / 2, (COLUMNS - 10) / 2, "¡Has perdido! Presiona una tecla para reiniciar...");
                refresh();
                nodelay(stdscr, FALSE);
                getch();
                nodelay(stdscr, TRUE);
                // Reinicia variables principales
                score = 0;
                x = 10;
                y = 5;
                generarLaberinto(laberinto);
                generar_enemigos(enemigos, NUM_ENEMIGOS, laberinto);
                for (int j = 0; j < NUM_ENEMIGOS; j++)
                {
                    enemigos[j].dir = (rand() % 2 == 0) ? 1 : -1;
                    enemigos[j].active = true;
                }
                do
                {
                    coin_x = rand() % COLUMNS;
                    coin_y = rand() % ROWS;
                } while (laberinto[coin_y][coin_x] != 0);
                continue; // Reinicia el ciclo principal
            }
        }

        // Verifica si el jugador ha ganado
        if (score >= 5)
        {
            clear();
            mvprintw(ROWS / 2, (COLUMNS - 10) / 2, "¡Felicidades! ¡Ganaste el nivel!");
            refresh();
            nodelay(stdscr, FALSE);
            getch();
            break; // Sale del bucle y termina el juego
        }

        refresh();

        ch = getch();
        if (ch == 'q' || ch == 'Q') {
            // Menú de confirmación para guardar partida al salir
            bool salir = menu_guardar_partida(x, y, score, balls, MAX_BALLS);
            if (salir) {
                break; // Sale del bucle y termina el juego
            }
            // Si NO quiere salir (presionó 'r'), simplemente sigue el bucle y el juego continúa
        }
        if (ch == ' ')
        {
            shoot_ball(balls, MAX_BALLS, x, y, last_dir);
        }
        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
            last_dir = ch;
        if (ch == 'x' || ch == 'X')
        {
            espadaso(stdscr, offset_x + x, offset_y + y, last_dir);
        }

        if (x == coin_x && y == coin_y)
        {
            reproducirMoneda();
            napms(500);
            reproducirFondo();
            score++;
            // Nueva moneda en un espacio libre
            do
            {
                coin_x = rand() % COLUMNS;
                coin_y = rand() % ROWS;
            } while (laberinto[coin_y][coin_x] != 0);
        }
        mover_personaje(x, y, ch, COLUMNS, ROWS);
        enemy_tick++; // Incrementa el contador de ciclos
    }


  
    // Si retorna true, continúa y termina el juego normalmente
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