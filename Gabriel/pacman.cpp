#include <curses.h>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
using namespace std;

#define PLAYER 'C'
#define WALL   '#'
#define POINT  '.'
#define EMPTY  ' '

int score = 0;
int playerX = 1, playerY = 1;

// Mapa como matriz constante para evitar redefinirlo
std::vector<std::string> map = {
    "####################",
    "#........#.........#",
    "#.####.#.#.####.#..#",
    "#.#  #.#.#.#  #.#..#",
    "#.#  #.#.#.#  #.#..#",
    "#.####.#.#.####.#..#",
    "#..................#",
    "####################"
};

void drawInitialMap() {
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            mvaddch(y, x, map[y][x]);
        }
    }
    mvaddch(playerY, playerX, PLAYER);
    mvprintw(map.size(), 0, "Score: %d", score);
    refresh();
}

void updatePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (map[newY][newX] != WALL) {
        // Borrar jugador en posición anterior
        mvaddch(playerY, playerX, EMPTY);

        // Comer punto si hay
        if (map[newY][newX] == POINT) {
            map[newY][newX] = EMPTY;
            score++;
            mvaddch(map.size(), 8, ' '); // limpiar puntaje viejo
            mvprintw(map.size(), 0, "Score: %d", score);
        }

        playerX = newX;
        playerY = newY;
        mvaddch(playerY, playerX, PLAYER);  // Dibujar jugador nuevo
        refresh();
    }
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // No bloquear lectura
    timeout(0);            // No espera para getch()

    drawInitialMap();

    bool running = true;
    while (running) {
        int ch = getch();
        switch (ch) {
            case 'q': running = false; break;
            case KEY_UP:    updatePlayer(0, -1); break;
            case KEY_DOWN:  updatePlayer(0, 1);  break;
            case KEY_LEFT:  updatePlayer(-1, 0); break;
            case KEY_RIGHT: updatePlayer(1, 0);  break;
        }

       
    }

    endwin();
    return 0;
}
