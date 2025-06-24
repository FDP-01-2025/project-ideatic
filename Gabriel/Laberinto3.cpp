#include <curses.h>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int WIDTH = 39;   // Ancho del laberinto (impar)
const int HEIGHT = 21;  // Alto del laberinto (impar)
const char WALL = '#';
const char PATH = ' ';
const char PLAYER = 'P';

vector<vector<char>> maze(HEIGHT, vector<char>(WIDTH, WALL));

int playerX = 1, playerY = 1; // Posición inicial del jugador

struct Cell {
    int x, y;
};

bool isValid(int x, int y) {
    return x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1;
}

void generateMaze(int startX, int startY) {
    stack<Cell> stack;
    stack.push({startX, startY});
    maze[startY][startX] = PATH;

    int dx[] = {0, 0, -2, 2};
    int dy[] = {-2, 2, 0, 0};

    while (!stack.empty()) {
        Cell current = stack.top();
        vector<int> dirs = {0, 1, 2, 3};
        random_shuffle(dirs.begin(), dirs.end());

        bool moved = false;
        for (int i : dirs) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValid(nx, ny) && maze[ny][nx] == WALL) {
                maze[current.y + dy[i] / 2][current.x + dx[i] / 2] = PATH;
                maze[ny][nx] = PATH;
                stack.push({nx, ny});
                moved = true;
                break;
            }
        }

        if (!moved) stack.pop();
    }
}

void drawMaze() {
    clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mvaddch(y, x, maze[y][x]);
        }
    }
    mvaddch(playerY, playerX, PLAYER);
    refresh();
}

void movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (maze[newY][newX] == PATH) {
        mvaddch(playerY, playerX, PATH); // Borra el jugador anterior
        playerX = newX;
        playerY = newY;
        mvaddch(playerY, playerX, PLAYER); // Dibuja nueva posición
        refresh();
    }
}

int main() {
    srand(time(NULL));
    generateMaze(1, 1);
    maze[HEIGHT - 2][WIDTH - 2] = PATH; // Salida

    initscr();      // Iniciar PDCurses
    noecho();       // No mostrar teclas
    curs_set(0);    // Ocultar cursor
    keypad(stdscr, TRUE); // Teclas especiales
    nodelay(stdscr, TRUE); // No bloquear lectura

    drawMaze();

    bool running = true;
    while (running) {
        int ch = getch();
        switch (ch) {
            case 'q': running = false; break;
            case KEY_UP:    movePlayer(0, -1); break;
            case KEY_DOWN:  movePlayer(0, 1); break;
            case KEY_LEFT:  movePlayer(-1, 0); break;
            case KEY_RIGHT: movePlayer(1, 0); break;
        }
        napms(60); // Pausa para evitar sobrecarga de CPU
    }

    endwin(); // Cerrar modo curses
    return 0;
}
