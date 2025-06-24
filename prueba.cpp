#include <curses.h>
#include <ctime>
#include <cstdlib>

#define MAP_WIDTH 50
#define MAP_HEIGHT 15
#define DENSITY 150
#define MAX_BOLAS 10

// Estructura para las bolas lanzadas por el personaje
struct Bola {
    int x, y, dx, dy;
    bool activa;
    int frame;
};

// Función para generar y dibujar un laberinto aleatorio en la ventana
void gLabyrinth(WINDOW* win, int rows, int columns, int density, int **&matriz)
{
    // Reserva memoria para la matriz del laberinto
    matriz = new int*[rows];
    int walls = density * 8;
    for (int i = 0; i < rows; i++)
        matriz[i] = new int[columns];

    // Inicializa los bordes como paredes (1) y el resto como espacios (0)
    for (int a = 0; a < rows; a++)
        for (int b = 0; b < columns; b++)
            matriz[a][b] = (a == 0 || b == 0 || a == rows-1 || b == columns-1) ? 1 : 0;

    // Genera paredes internas aleatorias para el laberinto
    srand(time(NULL));
    for (int c = 0; c < density; c++)
    {
        int cl = rand() % (columns - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (rows - 4) + 2;
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1;
        for (int d = 0; d < walls; d++)
        {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;
            if (matriz[mr[ran]][mc[ran]] == 0)
            {
                matriz[mr[ran]][mc[ran]] = 1;
                matriz[mr[ran] + (rw - mr[ran]) / 2][mc[ran] + (cl - mc[ran]) / 2] = 1;
            }
        }
    }

    // Dibuja el laberinto en la ventana (+1 para dejar el borde)
    for (int e = 0; e < rows; e++)
        for (int f = 0; f < columns; f++)
            if (matriz[e][f] == 1)
                mvwaddch(win, e+1, f+1, 178); // Dibuja pared
            else
                mvwaddch(win, e+1, f+1, ' '); // Dibuja espacio libre
}

// Dibuja la espada en la dirección del ataque, si no hay pared
void espadaso(WINDOW *win, int x, int y, int last_dir, int **laberinto)
{
    int sx = x, sy = y;
    if (last_dir == KEY_UP)    sy--;
    if (last_dir == KEY_DOWN)  sy++;
    if (last_dir == KEY_LEFT)  sx--;
    if (last_dir == KEY_RIGHT) sx++;
    // Solo dibuja si no es pared
    if (laberinto[sy][sx] == 0) {
        if (last_dir == KEY_LEFT || last_dir == KEY_RIGHT)
            mvwaddch(win, sy+1, sx+1, '-');
        else
            mvwaddch(win, sy+1, sx+1, '|');
    }
    wrefresh(win);
    napms(120); // Pequeña pausa para mostrar la espada
}

int main()
{
    // Inicializa la pantalla y colores
    initscr();
    noecho();
    cbreak();
    start_color();
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Color del personaje
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // Color de la bola
    keypad(stdscr, TRUE);

    int rows = MAP_HEIGHT, columns = MAP_WIDTH, density = DENSITY;
    int **laberinto = nullptr;

    // Crea la ventana del laberinto centrada
    int startx = (COLS - columns) / 2;
    int starty = (LINES - rows) / 2;
    WINDOW *lab_win = newwin(rows+2, columns+2, starty, startx);
    keypad(lab_win, TRUE);
    box(lab_win, 0, 0);

    // Genera y dibuja el laberinto
    gLabyrinth(lab_win, rows, columns, density, laberinto);
    wrefresh(lab_win);

    // Busca una celda libre para el personaje '@'
    int px = 1, py = 1;
    for (int y = 1; y < rows-1; y++) {
        for (int x = 1; x < columns-1; x++) {
            if (laberinto[y][x] == 0) {
                py = y;
                px = x;
                goto encontrado;
            }
        }
    }
encontrado:

    // Inicializa las bolas
    Bola bolas[MAX_BOLAS] = {};
    for (int i = 0; i < MAX_BOLAS; i++) bolas[i].activa = false;
    int last_dir = KEY_RIGHT;
    int ch;
    nodelay(lab_win, TRUE);

    // Bucle principal del juego
    while ((ch = wgetch(lab_win)) != 'q') {
        // Redibuja el laberinto
        gLabyrinth(lab_win, rows, columns, density, laberinto);

        // Dibuja todas las bolas activas
        for (int i = 0; i < MAX_BOLAS; i++) {
            if (bolas[i].activa) {
                wattron(lab_win, COLOR_PAIR(4));
                mvwaddch(lab_win, bolas[i].y+1, bolas[i].x+1, 'o');
                wattroff(lab_win, COLOR_PAIR(4));
            }
        }

        // Dibuja el personaje
        wattron(lab_win, COLOR_PAIR(2));
        mvwaddch(lab_win, py+1, px+1, '@');
        wattroff(lab_win, COLOR_PAIR(2));
        wrefresh(lab_win);

        // Movimiento del personaje y guarda la última dirección
        if (ch == KEY_UP    && laberinto[py-1][px] == 0) { py--; last_dir = KEY_UP; }
        if (ch == KEY_DOWN  && laberinto[py+1][px] == 0) { py++; last_dir = KEY_DOWN; }
        if (ch == KEY_LEFT  && laberinto[py][px-1] == 0) { px--; last_dir = KEY_LEFT; }
        if (ch == KEY_RIGHT && laberinto[py][px+1] == 0) { px++; last_dir = KEY_RIGHT; }

        // Espadazo si se presiona 'x'
        if (ch == 'x' || ch == 'X') {
            espadaso(lab_win, px, py, last_dir, laberinto);
        }

        // Lanza una nueva bola en la dirección del último movimiento
        if (ch == ' ') {
            for (int i = 0; i < MAX_BOLAS; i++) {
                if (!bolas[i].activa) {
                    bolas[i].x = px;
                    bolas[i].y = py;
                    if (last_dir == KEY_UP)    { bolas[i].dx = 0;  bolas[i].dy = -1; }
                    if (last_dir == KEY_DOWN)  { bolas[i].dx = 0;  bolas[i].dy = 1; }
                    if (last_dir == KEY_LEFT)  { bolas[i].dx = -1; bolas[i].dy = 0; }
                    if (last_dir == KEY_RIGHT) { bolas[i].dx = 1;  bolas[i].dy = 0; }
                    bolas[i].activa = true;
                    bolas[i].frame = 0;
                    break;
                }
            }
        }

        // Mueve todas las bolas activas según su dirección
        for (int i = 0; i < MAX_BOLAS; i++) {
            if (bolas[i].activa) {
                int nx = bolas[i].x + bolas[i].dx;
                int ny = bolas[i].y + bolas[i].dy;
                // Si la siguiente celda es libre, mueve la bola
                if (laberinto[ny][nx] == 0) {
                    bolas[i].x = nx;
                    bolas[i].y = ny;
                } else {
                    bolas[i].activa = false; // Se desactiva al chocar con pared
                }
            }
        }

        napms(70); // Pequeña pausa para animación
    }

    // Limpieza de memoria
    for (int i = 0; i < rows; i++)
        delete[] laberinto[i];
    delete[] laberinto;

    delwin(lab_win);
    endwin();
    return 0;
}
