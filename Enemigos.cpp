#include <iostream>
#include <ctime>
#include <cstdlib>
#include <curses.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define WIDTH 20
#define HEIGHT 10
#define NUM_ENEMIGOS 3

struct Enemigo {
    int x, y;
    int dx, dy;
};

void inicializarEnemigos(Enemigo enemigos[], int num) {
    srand(time(NULL));
    for (int i = 0; i < num; i++) {
        enemigos[i].x = rand() % (WIDTH - 2) + 1;
        enemigos[i].y = rand() % (HEIGHT - 2) + 1;
        enemigos[i].dx = (rand() % 2) ? 1 : -1;
        enemigos[i].dy = (rand() % 2) ? 1 : -1;
    }
}

void moverEnemigos(Enemigo enemigos[], int num) {
    for (int i = 0; i < num; i++) {
        enemigos[i].x += enemigos[i].dx;
        enemigos[i].y += enemigos[i].dy;
        // Rebote en paredes
        if (enemigos[i].x <= 0 || enemigos[i].x >= WIDTH - 1)
            enemigos[i].dx *= -1;
        if (enemigos[i].y <= 0 || enemigos[i].y >= HEIGHT - 1)
            enemigos[i].dy *= -1;
    }
}

void dibujarLaberinto(WINDOW* win) {
    box(win, 0, 0);
}

void dibujarEnemigos(WINDOW* win, Enemigo enemigos[], int num) {
    for (int i = 0; i < num; i++) {
        mvwaddch(win, enemigos[i].y, enemigos[i].x, 'E');
    }
}

int main() {
    
    initscr();
    noecho();
    curs_set(0);
    srand(time(NULL));

    WINDOW* win = newwin(HEIGHT, WIDTH, 1, 1);
    nodelay(win, TRUE);

    Enemigo enemigos[NUM_ENEMIGOS];
    inicializarEnemigos(enemigos, NUM_ENEMIGOS);

    int ch;
    int tiempo = 0;
    while ((ch = wgetch(win)) != 'q') {
        werase(win);
        dibujarLaberinto(win);
        dibujarEnemigos(win, enemigos, NUM_ENEMIGOS);
        wrefresh(win);

        Sleep(200); // Tiempo entre movimientos
        moverEnemigos(enemigos, NUM_ENEMIGOS);
    }

    delwin(win);
    endwin();
    return 0;
}