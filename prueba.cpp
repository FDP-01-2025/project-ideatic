#include <curses.h>

#include <curses.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int x = 10, y = 5;
    int coin_x, coin_y;
    int ch, score = 0;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    srand(time(NULL));

    // Posición inicial de la moneda
    coin_x = rand() % (COLS - 2) + 1;
    coin_y = rand() % (LINES - 2) + 1;

    while (1) {
        clear();
        box(stdscr, 0, 0);
        mvprintw(0, 2, "Recoge monedas ($) con '@'. Puntos: %d | 'q' para salir", score);
        mvaddch(coin_y, coin_x, '$');
        mvaddch(y, x, '@');
        refresh();

        ch = getch();
        if (ch == 'q') break;
        if (ch == KEY_UP    && y > 1)         y--;
        if (ch == KEY_DOWN  && y < LINES-2)   y++;
        if (ch == KEY_LEFT  && x > 1)         x--;
        if (ch == KEY_RIGHT && x < COLS-2)    x++;

        // Si recoge la moneda
        if (x == coin_x && y == coin_y) {
            score++;
            coin_x = rand() % (COLS - 2) + 1;
            coin_y = rand() % (LINES - 2) + 1;
        }
    }

    endwin();
    return 0;
}