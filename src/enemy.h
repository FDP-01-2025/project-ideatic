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

    generarLaberinto(laberinto);
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

// --- BLOQUE JEFE Y PROYECTILES ---

#define BOSS_WIDTH 7
#define BOSS_HEIGHT 5
#define BOSS_LIVES 10
#define PLAYER_LIVES 5
#define MAX_BALLS 10

// Estructura para bolas (proyectiles)


// Estructura para el jefe
struct Boss
{
    int x, y;
    int dir;
    int lives;
    bool active;
};

// Variables globales para el jefe y proyectiles
extern Boss jefe;
extern Ball balls[MAX_BALLS];
extern int boss_player_x, boss_player_y; // Posición del jugador en el modo jefe
extern int boss_ch, boss_last_dir, boss_player_lives;

// Inicializar jefe y proyectiles
inline void inicializar_jefe_y_bolas(int ancho, int alto)
{
    jefe.x = ancho / 2 - BOSS_WIDTH / 2;
    jefe.y = 3;
    jefe.dir = 1;
    jefe.lives = BOSS_LIVES;
    jefe.active = true;

    boss_player_x = ancho / 2;
    boss_player_y = alto - 5;
    boss_player_lives = PLAYER_LIVES;
    boss_last_dir = KEY_RIGHT;

    for (int i = 0; i < MAX_BALLS; i++)
        balls[i].active = false;
}

// Dibujar el jefe
inline void dibujarJefe(WINDOW* win)
{
    if (!jefe.active)
        return;

    wattron(win, COLOR_PAIR(5));
    mvwaddch(win, jefe.y,     jefe.x + 1, '_');
    mvwaddch(win, jefe.y,     jefe.x + 2, 'O');
    mvwaddch(win, jefe.y,     jefe.x + 3, '_');
    mvwaddch(win, jefe.y,     jefe.x + 4, 'O');
    mvwaddch(win, jefe.y,     jefe.x + 5, '_');
    mvwaddch(win, jefe.y + 1, jefe.x + 2, '[');
    mvwaddch(win, jefe.y + 1, jefe.x + 3, ' ');
    mvwaddch(win, jefe.y + 1, jefe.x + 4, ']');
    mvwprintw(win, jefe.y + 2, jefe.x, "/-----\\");
    mvwprintw(win, jefe.y + 3, jefe.x, "|  |  |");
    mvwprintw(win, jefe.y + 4, jefe.x, "\\-----/");
    wattroff(win, COLOR_PAIR(5));
}

// Mover el jefe
inline void moverJefe(int ancho, int alto)
{
    if (!jefe.active)
        return;

    static int counter = 0;
    if (++counter < 1)
        return;
    counter = 0;

    int nx = jefe.x + jefe.dir * 2;

    if (nx <= 0 || nx >= ancho - BOSS_WIDTH - 1)
    {
        jefe.dir *= -1;
        nx = jefe.x + jefe.dir * 2;
        if (rand() % 3 == 0 && jefe.y < alto - BOSS_HEIGHT - 5)
        {
            jefe.y += 1;
        }
    }
    jefe.x = nx;
}

// Disparar una bola (proyectil)
inline void shoot_ball()
{
    for (int i = 0; i < MAX_BALLS; i++)
    {
        if (!balls[i].active)
        {
            balls[i].x = boss_player_x;
            balls[i].y = boss_player_y;
            balls[i].dir = boss_last_dir;
            balls[i].active = true;
            break;
        }
    }
}

// Actualizar posición de las bolas
inline void update_balls(WINDOW* win, int ancho, int alto)
{
    for (int i = 0; i < MAX_BALLS; i++)
    {
        if (balls[i].active)
        {
            mvwaddch(win, balls[i].y, balls[i].x, ' ');

            switch (balls[i].dir)
            {
            case KEY_UP:
                balls[i].y--;
                break;
            case KEY_DOWN:
                balls[i].y++;
                break;
            case KEY_LEFT:
                balls[i].x--;
                break;
            case KEY_RIGHT:
                balls[i].x++;
                break;
            }

            wattron(win, COLOR_PAIR(6));
            mvwaddch(win, balls[i].y, balls[i].x, 'o');
            wattroff(win, COLOR_PAIR(6));

            if (balls[i].x <= 0 || balls[i].x >= ancho - 1 ||
                balls[i].y <= 0 || balls[i].y >= alto - 1)
            {
                balls[i].active = false;
                continue;
            }

            if (jefe.active &&
                balls[i].x >= jefe.x && balls[i].x <= jefe.x + BOSS_WIDTH - 1 &&
                balls[i].y >= jefe.y && balls[i].y <= jefe.y + BOSS_HEIGHT - 1)
            {
                balls[i].active = false;
                jefe.lives--;

                wattron(win, COLOR_PAIR(3));
                mvwaddch(win, balls[i].y, balls[i].x, '*');
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                napms(50);

                if (jefe.lives <= 0)
                {
                    jefe.active = false;
                }
            }
        }
    }
}

// Ataque con espada
inline void espadaso(WINDOW* win)
{
    wattron(win, COLOR_PAIR(3));

    if (boss_last_dir == KEY_UP)
        mvwaddch(win, boss_player_y - 1, boss_player_x, '|');
    else if (boss_last_dir == KEY_DOWN)
        mvwaddch(win, boss_player_y + 1, boss_player_x, '|');
    else if (boss_last_dir == KEY_LEFT)
        mvwprintw(win, boss_player_y, boss_player_x - 2, "--");
    else
        mvwprintw(win, boss_player_y, boss_player_x + 1, "--");

    wattroff(win, COLOR_PAIR(3));

    // Verificar golpe al jefe
    if (jefe.active)
    {
        bool hit = false;

        if (boss_last_dir == KEY_UP &&
            boss_player_x >= jefe.x && boss_player_x <= jefe.x + BOSS_WIDTH - 1 &&
            boss_player_y - 1 >= jefe.y && boss_player_y - 1 <= jefe.y + BOSS_HEIGHT - 1)
        {
            hit = true;
        }
        else if (boss_last_dir == KEY_DOWN &&
                 boss_player_x >= jefe.x && boss_player_x <= jefe.x + BOSS_WIDTH - 1 &&
                 boss_player_y + 1 >= jefe.y && boss_player_y + 1 <= jefe.y + BOSS_HEIGHT - 1)
        {
            hit = true;
        }
        else if (boss_last_dir == KEY_LEFT &&
                 boss_player_x - 2 >= jefe.x && boss_player_x - 2 <= jefe.x + BOSS_WIDTH - 1 &&
                 boss_player_y >= jefe.y && boss_player_y <= jefe.y + BOSS_HEIGHT - 1)
        {
            hit = true;
        }
        else if (boss_last_dir == KEY_RIGHT &&
                 boss_player_x + 1 >= jefe.x && boss_player_x + 1 <= jefe.x + BOSS_WIDTH - 1 &&
                 boss_player_y >= jefe.y && boss_player_y <= jefe.y + BOSS_HEIGHT - 1)
        {
            hit = true;
        }

        if (hit)
        {
            jefe.lives -= 2; // Espada hace más daño
            if (jefe.lives <= 0)
            {
                jefe.active = false;
            }
        }
    }

    wrefresh(win);
    napms(120);
}

// Dibujar al jugador (modo jefe)
inline void dibujarJugadorBoss(WINDOW* win)
{
    wattron(win, COLOR_PAIR(2));
    mvwaddch(win, boss_player_y, boss_player_x, '@');
    wattroff(win, COLOR_PAIR(2));
}

// Mover al jugador (modo jefe)
inline void moverJugadorBoss(int ancho, int alto, int ch)
{
    int nx = boss_player_x, ny = boss_player_y;

    if (ch == KEY_UP && ny > 1)
        ny--;
    else if (ch == KEY_DOWN && ny < alto - 2)
        ny++;
    else if (ch == KEY_LEFT && nx > 1)
        nx--;
    else if (ch == KEY_RIGHT && nx < ancho - 2)
        nx++;

    boss_player_x = nx;
    boss_player_y = ny;

    if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
    {
        boss_last_dir = ch;
    }
}

// Mostrar información del jefe
inline void mostrarInfoBoss(WINDOW* win)
{
    mvwprintw(win, 0, 2, "VIDAS JUGADOR: %d | VIDA JEFE: %d/%d | CONTROLES: Flechas, Espacio: Disparo, X: Espada, Q: Salir",
             boss_player_lives, jefe.lives, BOSS_LIVES);
}

// --- FIN BLOQUE JEFE Y PROYECTILES ---

// #include "enemy.h"
#include <curses.h>
#include <unistd.h> // Para usleep

void jugar_jefe()
{
    // Inicializa el jefe y proyectiles
    inicializar_jefe_y_bolas(COLUMNS, ROWS);

    int ch = 0;
    bool juegoActivo = true;

    while (juegoActivo)
    {
        werase(stdscr);

        // Dibuja el jefe y el jugador
        dibujarJefe(stdscr);
        dibujarJugadorBoss(stdscr);
        update_balls(stdscr, COLUMNS, ROWS);
        moverJefe(COLUMNS, ROWS);
        mostrarInfoBoss(stdscr);

        // Verifica victoria
        if (!jefe.active)
        {
            mvprintw(ROWS / 2, (COLUMNS - 20) / 2, "¡HAS DERROTADO AL JEFE!");
            refresh();
            napms(2000);
            return; // Mejor usar return para salir de la función
        }

        // Verifica derrota
        if (boss_player_lives <= 0)
        {
            mvprintw(ROWS / 2, (COLUMNS - 10) / 2, "¡HAS PERDIDO!");
            refresh();
            napms(2000);
            return; // Mejor usar return para salir de la función
        }

        // Entrada del usuario
        ch = getch();
        if (ch == 'q' || ch == 'Q')
        {
            juegoActivo = false;
            break;
        }
        else if (ch == ' ')
        {
            shoot_ball();
        }
        else if (ch == 'x' || ch == 'X')
        {
            espadaso(stdscr);
        }

        moverJugadorBoss(COLUMNS, ROWS, ch);

        refresh();
        napms(50); // En vez de usleep(50000);
    }
}
#endif // ENEMY_H
