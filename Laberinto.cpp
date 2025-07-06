#include <curses.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define MAP_WIDTH 50
#define MAP_HEIGHT 15
#define DENSITY 150
#define NUM_ENEMIGOS 4

struct Enemigo {
    int x, y;
    int dx, dy;
    bool vivo;
};

void reproducirFondo() {
    PlaySound("Musicafondo.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void reproducirVictoria() {
    PlaySound(NULL, 0, 0); // Detiene fondo
    PlaySound("Ganaste.wav", NULL, SND_FILENAME | SND_SYNC);
}

void inicializarEnemigos(Enemigo enemigos[], int num, int **matriz) {
    for (int i = 0; i < num; i++) {
        do {
            enemigos[i].x = rand() % (MAP_WIDTH - 2) + 1;
            enemigos[i].y = rand() % (MAP_HEIGHT - 2) + 1;
        } while (matriz[enemigos[i].y][enemigos[i].x] != 0);
        enemigos[i].dx = (rand() % 2) ? 1 : -1;
        enemigos[i].dy = (rand() % 2) ? 1 : -1;
        enemigos[i].vivo = true;
    }
}

// Mueve los enemigos por el laberinto, rebotando en paredes
void moverEnemigos(Enemigo enemigos[], int num, int **matriz, int ciclo) {
    if (ciclo % 3 != 0) return; // Solo mueve cada 3 ciclos (~240ms si napms(80))
    for (int i = 0; i < num; i++) {
        if (!enemigos[i].vivo) continue;
        int nx = enemigos[i].x + enemigos[i].dx;
        int ny = enemigos[i].y + enemigos[i].dy;
        // Rebote en paredes del laberinto
        if (matriz[ny][nx] == 1) {
            enemigos[i].dx *= -1;
            enemigos[i].dy *= -1;
        } else {
            enemigos[i].x = nx;
            enemigos[i].y = ny;
        }
    }
}

void dibujarEnemigos(WINDOW* win, Enemigo enemigos[], int num) {
    for (int i = 0; i < num; i++) {
        if (enemigos[i].vivo)
            mvwaddch(win, enemigos[i].y + 1, enemigos[i].x + 1, 'E');
    }
}

void gLabyrinth(WINDOW* win, int rows, int columns, int density, int **&matriz, int &sx, int &sy) {
    if (matriz) {
        for (int i = 0; i < rows; i++)
            delete[] matriz[i];
        delete[] matriz;
    }
    matriz = new int*[rows];
    int walls = density * 8;
    for (int i = 0; i < rows; i++)
        matriz[i] = new int[columns];

    for (int a = 0; a < rows; a++)
        for (int b = 0; b < columns; b++)
            matriz[a][b] = (a == 0 || b == 0 || a == rows-1 || b == columns-1) ? 1 : 0;

    srand(time(NULL));
    for (int c = 0; c < density; c++) {
        int cl = rand() % (columns - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (rows - 4) + 2;
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1;
        for (int d = 0; d < walls; d++) {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;
            if (matriz[mr[ran]][mc[ran]] == 0) {
                matriz[mr[ran]][mc[ran]] = 1;
                matriz[mr[ran] + (rw - mr[ran]) / 2][mc[ran] + (cl - mc[ran]) / 2] = 1;
            }
        }
    }

    // Elegir celda de salida
    for (int y = rows - 2; y > 1; y--) {
        for (int x = columns - 2; x > 1; x--) {
            if (matriz[y][x] == 0) {
                sy = y;
                sx = x;
                goto salida;
            }
        }
    }
salida:

    // Dibujar laberinto
    for (int e = 0; e < rows; e++) {
        for (int f = 0; f < columns; f++) {
            if (e == sy && f == sx)
                mvwaddch(win, e+1, f+1, 'X'); // Salida
            else if (matriz[e][f] == 1)
                mvwaddch(win, e+1, f+1, 178); // Pared
            else
                mvwaddch(win, e+1, f+1, ' ');
        }
    }
}

// Dibuja la espada cuando el usuario ataca
void atacarEspada(int px, int py, int dir, Enemigo enemigos[], int num, WINDOW* win) {
    int tx = px, ty = py;
    char espada = '|';
    if (dir == 0) { ty--; espada = '|'; }
    if (dir == 1) { ty++; espada = '|'; }
    if (dir == 2) { tx--; espada = '-'; }
    if (dir == 3) { tx++; espada = '-'; }
    // Dibuja la espada
    mvwaddch(win, ty+1, tx+1, espada);
    wrefresh(win);
    napms(120); // Espada visible un instante
    // Elimina enemigos si están en la casilla de ataque
    for (int i = 0; i < num; i++) {
        if (enemigos[i].vivo && enemigos[i].x == tx && enemigos[i].y == ty) {
            enemigos[i].vivo = false;
        }
    }
}

void disparar(int px, int py, int dir, Enemigo enemigos[], int num, int **matriz, WINDOW* win) {
    int tx = px, ty = py;
    char bullet = '*';
    while (true) {
        if (dir == 0) ty--;
        if (dir == 1) ty++;
        if (dir == 2) tx--;
        if (dir == 3) tx++;
        if (matriz[ty][tx] == 1) break;
        bool hit = false;
        for (int i = 0; i < num; i++) {
            if (enemigos[i].vivo && enemigos[i].x == tx && enemigos[i].y == ty) {
                enemigos[i].vivo = false;
                hit = true;
            }
        }
        mvwaddch(win, ty+1, tx+1, bullet);
        wrefresh(win);
        napms(40);
        if (hit) break;
    }
}
 
// Nueva función: dibuja el laberinto en pantalla según la matriz actual
void dibujarLaberinto(WINDOW* win, int **matriz, int rows, int columns, int sx, int sy) {
    for (int e = 0; e < rows; e++) {
        for (int f = 0; f < columns; f++) {
            if (e == sy && f == sx)
                mvwaddch(win, e+1, f+1, 'X'); // Salida
            else if (matriz[e][f] == 1)
                mvwaddch(win, e+1, f+1, 178); // Pared
            else
                mvwaddch(win, e+1, f+1, ' ');
        }
    }
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    int rows = MAP_HEIGHT, columns = MAP_WIDTH, density = DENSITY;
    int **laberinto = nullptr;

    int startx = (COLS - columns) / 2;
    int starty = (LINES - rows) / 2;
    WINDOW *lab_win = newwin(rows+2, columns+2, starty, startx);
    keypad(lab_win, TRUE);
    box(lab_win, 0, 0);

    int salidaX = 0, salidaY = 0;
    gLabyrinth(lab_win, rows, columns, density, laberinto, salidaX, salidaY);
    wrefresh(lab_win);

    int px = 1, py = 1;
    for (int y = 1; y < rows-1; y++)
        for (int x = 1; x < columns-1; x++)
            if (laberinto[y][x] == 0) {
                py = y;
                px = x;
                goto encontrado;
            }
encontrado:

    reproducirFondo();

    Enemigo enemigos[NUM_ENEMIGOS];
    inicializarEnemigos(enemigos, NUM_ENEMIGOS, laberinto);

    int ch;
    nodelay(lab_win, TRUE);
    int dir = 3; // 0=arriba, 1=abajo, 2=izq, 3=der

    unsigned long lastLabTime = clock();
    int ciclo = 0;

    

    while ((ch = wgetch(lab_win)) != 'q') {
        // Cambia el laberinto cada 10 segundos (pero NO reubica al jugador)
        if ((clock() - lastLabTime) > 10 * CLOCKS_PER_SEC) {
            // Solo genera la matriz y enemigos, NO dibuja aquí
            gLabyrinth(nullptr, rows, columns, density, laberinto, salidaX, salidaY);
            inicializarEnemigos(enemigos, NUM_ENEMIGOS, laberinto);
            lastLabTime = clock();
        }

        // Dibuja el laberinto y entidades en cada ciclo
        werase(lab_win);
        box(lab_win, 0, 0);
        dibujarLaberinto(lab_win, laberinto, rows, columns, salidaX, salidaY);

        // Movimiento jugador
        mvwaddch(lab_win, py+1, px+1, ' ');
        if (ch == KEY_UP    && laberinto[py-1][px] == 0) { py--; dir = 0; }
        if (ch == KEY_DOWN  && laberinto[py+1][px] == 0) { py++; dir = 1; }
        if (ch == KEY_LEFT  && laberinto[py][px-1] == 0) { px--; dir = 2; }
        if (ch == KEY_RIGHT && laberinto[py][px+1] == 0) { px++; dir = 3; }

        // Ataque espada (tecla 'a')
        if (ch == 'a') {
            atacarEspada(px, py, dir, enemigos, NUM_ENEMIGOS, lab_win);
        }
        // Disparo (tecla 's')
        if (ch == 's') {
            disparar(px, py, dir, enemigos, NUM_ENEMIGOS, laberinto, lab_win);
        }

        dibujarEnemigos(lab_win, enemigos, NUM_ENEMIGOS);
        mvwaddch(lab_win, py+1, px+1, '@');
        mvwprintw(lab_win, 0, 2, "a=espada s=disparo q=salir");
        wrefresh(lab_win);

        moverEnemigos(enemigos, NUM_ENEMIGOS, laberinto, ciclo);

        // Colisión con enemigo
        for (int i = 0; i < NUM_ENEMIGOS; i++) {
            if (enemigos[i].vivo && enemigos[i].x == px && enemigos[i].y == py) {
                mvwprintw(lab_win, 0, 20, "¡Perdiste!");
                wrefresh(lab_win);
                napms(1500);
                endwin();
                return 0;
            }
        }

        // Victoria
        if (px == salidaX && py == salidaY) {
            mvwprintw(lab_win, 0, 20, "¡Has escapado!");
            wrefresh(lab_win);
            reproducirVictoria();
            break;
        }
        napms(80);
        ciclo++;
    }


    // Libera memoria
    for (int i = 0; i < rows; i++)
        delete[] laberinto[i];
    delete[] laberinto;

    delwin(lab_win);
    endwin();
    return 0;
}