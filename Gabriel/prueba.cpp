#include <curses.h>
// #include <windows.h>  // Para PlaySound
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Dirección: 0=arriba, 1=derecha, 2=abajo, 3=izquierda
struct Snake {
    vector<pair<int, int>> cuerpo;
    int direccion;
    int puntaje;
    char simbolo;
    int color;
};

int maxWidth, maxHeight;

pair<int, int> generarFruta(const Snake& s1, const Snake& s2) {
    pair<int, int> f;
    while (true) {
        f.first = rand() % (maxHeight - 2) + 1;
        f.second = rand() % (maxWidth - 2) + 1;

        bool enSnake = false;
        for (auto& p : s1.cuerpo)
            if (p == f) enSnake = true;
        for (auto& p : s2.cuerpo)
            if (p == f) enSnake = true;

        if (!enSnake) break;
    }
    return f;
}

void moverSnake(Snake& s) {
    auto cabeza = s.cuerpo.front();
    switch (s.direccion) {
        case 0: cabeza.first--; break;
        case 1: cabeza.second++; break;
        case 2: cabeza.first++; break;
        case 3: cabeza.second--; break;
    }
    s.cuerpo.insert(s.cuerpo.begin(), cabeza);
    s.cuerpo.pop_back();
}

bool colision(const Snake& s) {
    auto cabeza = s.cuerpo.front();
    if (cabeza.first <= 0 || cabeza.first >= maxHeight - 1 ||
        cabeza.second <= 0 || cabeza.second >= maxWidth - 1)
        return true;

    for (size_t i = 1; i < s.cuerpo.size(); i++)
        if (s.cuerpo[i] == cabeza)
            return true;

    return false;
}

void dibujarSnake(const Snake& s) {
    attron(COLOR_PAIR(s.color));
    for (auto& p : s.cuerpo) {
        mvaddch(p.first, p.second, s.simbolo);
    }
    attroff(COLOR_PAIR(s.color));
}

int main() {
    srand(time(0));
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100);
    getmaxyx(stdscr, maxHeight, maxWidth);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK); // Jugador 1
        init_pair(2, COLOR_CYAN, COLOR_BLACK);  // Jugador 2
        init_pair(3, COLOR_RED, COLOR_BLACK);   // Fruta
    }

    Snake s1 = {{{5, 10}}, 1, 0, 'O', 1};
    Snake s2 = {{{10, 40}}, 3, 0, '<', 2};

    pair<int, int> fruta = generarFruta(s1, s2);

    while (true) {
        clear();

        // Dibujar borde
        box(stdscr, 0, 0);

        // Fruta
        attron(COLOR_PAIR(3));
        mvaddch(fruta.first, fruta.second, '*');
        attroff(COLOR_PAIR(3));

        // Mover serpientes
        moverSnake(s1);
        moverSnake(s2);

        // Comer fruta
        if (s1.cuerpo.front() == fruta) {
            s1.cuerpo.push_back(s1.cuerpo.back());
            s1.puntaje++;
            // PlaySound(TEXT("comer.wav"), NULL, SND_FILENAME | SND_ASYNC);
            fruta = generarFruta(s1, s2);
        }
        if (s2.cuerpo.front() == fruta) {
            s2.cuerpo.push_back(s2.cuerpo.back());
            s2.puntaje++;
            // PlaySound(TEXT("comer.wav"), NULL, SND_FILENAME | SND_ASYNC);
            fruta = generarFruta(s1, s2);
        }

        // Dibujo
        mvprintw(0, 2, "J1: %d", s1.puntaje);
        mvprintw(0, 15, "J2: %d", s2.puntaje);
        dibujarSnake(s1);
        dibujarSnake(s2);

        refresh();

        // Colisiones
        if (colision(s1) || colision(s2)) break;

        // Controles
        int ch = getch();
        switch (ch) {
            // Jugador 1 - Flechas
            case KEY_UP:    if (s1.direccion != 2) s1.direccion = 0; break;
            case KEY_RIGHT: if (s1.direccion != 3) s1.direccion = 1; break;
            case KEY_DOWN:  if (s1.direccion != 0) s1.direccion = 2; break;
            case KEY_LEFT:  if (s1.direccion != 1) s1.direccion = 3; break;
            // Jugador 2 - W A S D
            case 'w': case 'W': if (s2.direccion != 2) s2.direccion = 0; break;
            case 'd': case 'D': if (s2.direccion != 3) s2.direccion = 1; break;
            case 's': case 'S': if (s2.direccion != 0) s2.direccion = 2; break;
            case 'a': case 'A': if (s2.direccion != 1) s2.direccion = 3; break;
        }
    }

    endwin();
    printf("Juego terminado. P1: %d | P2: %d\n", s1.puntaje, s2.puntaje);
    return 0;
}