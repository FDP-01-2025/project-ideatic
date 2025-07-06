#include <curses.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <memory>

constexpr int MAP_WIDTH = 50;
constexpr int MAP_HEIGHT = 15;
constexpr int DENSITY = 150;
constexpr int MAX_BOLAS = 10;
constexpr int MAX_ENEMIGOS = 5;
constexpr int LABERINTO_CAMBIO_SEGUNDOS = 5;
constexpr int ENEMIGO_MOVIMIENTO_SEGUNDOS = 1;
constexpr int FRAME_DELAY = 70;
constexpr int SWORD_DELAY = 120;

enum class Direccion : int {
    DERECHA = 0,
    IZQUIERDA = 1,
    ARRIBA = 2,
    ABAJO = 3
};

struct Bola {
    int x, y, dx, dy;
    bool activa;
    int frame;
    
    Bola() : x(0), y(0), dx(0), dy(0), activa(false), frame(0) {}
};

struct Enemigo {
    int x, y, dx, dy;
    bool activo;
    Direccion direccion;
    
    Enemigo() : x(0), y(0), dx(0), dy(0), activo(false), direccion(Direccion::DERECHA) {}
};

class LaberintoJuego {
private:
    std::vector<std::vector<int>> laberinto;
    std::vector<Bola> bolas;
    std::vector<Enemigo> enemigos;
    WINDOW* ventana;
    
    int filas, columnas;
    int px, py;  // Posición del jugador
    int salida_x, salida_y;
    int ultima_direccion;
    
    time_t ultimo_cambio_laberinto;
    time_t ultimo_movimiento_enemigos;
    bool laberinto_generado;
    
    // Métodos privados
    void inicializarColores();
    void generarLaberinto();
    void inicializarEnemigos();
    void moverEnemigos();
    void moverBolas();
    void verificarColisiones();
    void dibujarEscena();
    void espadaso();
    void lanzarBola();
    bool verificarColisionJugador() const;
    bool moverJugador(int ch);
    void establecerDireccionEnemigo(Enemigo& enemigo, Direccion dir);
    bool esPosicionValida(int x, int y) const;
    void buscarPosicionLibre(int& x, int& y);
    
public:
    LaberintoJuego(int rows, int cols, int density);
    ~LaberintoJuego();
    
    void inicializar();
    void ejecutar();
    void limpiar();
};

LaberintoJuego::LaberintoJuego(int rows, int cols, int density) 
    : filas(rows), columnas(cols), px(1), py(1), salida_x(0), salida_y(0),
      ultima_direccion(KEY_RIGHT), ultimo_cambio_laberinto(0), 
      ultimo_movimiento_enemigos(0), laberinto_generado(false) {
    
    // Inicializar contenedores
    laberinto.resize(filas, std::vector<int>(columnas, 0));
    bolas.resize(MAX_BOLAS);
    enemigos.resize(MAX_ENEMIGOS);
    
    // Crear ventana
    int startx = (COLS - columnas) / 2;
    int starty = (LINES - filas) / 2;
    ventana = newwin(filas + 2, columnas + 2, starty, startx);
    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    box(ventana, 0, 0);
}

LaberintoJuego::~LaberintoJuego() {
    limpiar();
}

void LaberintoJuego::inicializarColores() {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);    // Enemigos
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Jugador
    init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Salida
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // Bolas
}

void LaberintoJuego::generarLaberinto() {
    time_t tiempo_actual = time(nullptr);
    
    // Solo regenera cada cierto tiempo
    if (laberinto_generado && (tiempo_actual - ultimo_cambio_laberinto) < LABERINTO_CAMBIO_SEGUNDOS) {
        return;
    }
    
    ultimo_cambio_laberinto = tiempo_actual;
    
    // Inicializar bordes como paredes
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            laberinto[i][j] = (i == 0 || j == 0 || i == filas-1 || j == columnas-1) ? 1 : 0;
        }
    }
    
    // Generar paredes internas
    int walls = DENSITY * 8;
    for (int c = 0; c < DENSITY; c++) {
        int cl = ((rand() % (columnas - 4) + 2) / 2) * 2;
        int rw = ((rand() % (filas - 4) + 2) / 2) * 2;
        
        laberinto[rw][cl] = 1;
        
        for (int d = 0; d < walls; d++) {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;
            
            if (mr[ran] >= 0 && mr[ran] < filas && mc[ran] >= 0 && mc[ran] < columnas && 
                laberinto[mr[ran]][mc[ran]] == 0) {
                laberinto[mr[ran]][mc[ran]] = 1;
                int mid_r = mr[ran] + (rw - mr[ran]) / 2;
                int mid_c = mc[ran] + (cl - mc[ran]) / 2;
                if (mid_r >= 0 && mid_r < filas && mid_c >= 0 && mid_c < columnas) {
                    laberinto[mid_r][mid_c] = 1;
                }
            }
        }
    }
    
    // Buscar posición para la salida
    for (int y = filas - 2; y > 1; y--) {
        for (int x = columnas - 2; x > 1; x--) {
            if (laberinto[y][x] == 0) {
                salida_y = y;
                salida_x = x;
                goto salida_encontrada;
            }
        }
    }
salida_encontrada:
    
    laberinto_generado = true;
}

void LaberintoJuego::establecerDireccionEnemigo(Enemigo& enemigo, Direccion dir) {
    enemigo.direccion = dir;
    switch (dir) {
        case Direccion::DERECHA:  enemigo.dx = 1;  enemigo.dy = 0;  break;
        case Direccion::IZQUIERDA: enemigo.dx = -1; enemigo.dy = 0; break;
        case Direccion::ARRIBA:   enemigo.dx = 0;  enemigo.dy = -1; break;
        case Direccion::ABAJO:    enemigo.dx = 0;  enemigo.dy = 1;  break;
    }
}

bool LaberintoJuego::esPosicionValida(int x, int y) const {
    return x > 0 && x < columnas-1 && y > 0 && y < filas-1 && laberinto[y][x] == 0;
}

void LaberintoJuego::buscarPosicionLibre(int& x, int& y) {
    for (int i = 1; i < filas-1; i++) {
        for (int j = 1; j < columnas-1; j++) {
            if (laberinto[i][j] == 0) {
                y = i;
                x = j;
                return;
            }
        }
    }
}

void LaberintoJuego::inicializarEnemigos() {
    for (auto& enemigo : enemigos) {
        bool posicion_valida = false;
        int intentos = 0;
        
        while (!posicion_valida && intentos < 100) {
            int x = rand() % (columnas - 2) + 1;
            int y = rand() % (filas - 2) + 1;
            
            if (esPosicionValida(x, y)) {
                enemigo.x = x;
                enemigo.y = y;
                enemigo.activo = true;
                establecerDireccionEnemigo(enemigo, static_cast<Direccion>(rand() % 4));
                posicion_valida = true;
            }
            intentos++;
        }
        
        if (!posicion_valida) {
            enemigo.activo = false;
        }
    }
}

void LaberintoJuego::moverEnemigos() {
    time_t tiempo_actual = time(nullptr);
    
    if ((tiempo_actual - ultimo_movimiento_enemigos) < ENEMIGO_MOVIMIENTO_SEGUNDOS) {
        return;
    }
    
    ultimo_movimiento_enemigos = tiempo_actual;
    
    for (auto& enemigo : enemigos) {
        if (!enemigo.activo) continue;
        
        int nx = enemigo.x + enemigo.dx;
        int ny = enemigo.y + enemigo.dy;
        
        if (esPosicionValida(nx, ny)) {
            enemigo.x = nx;
            enemigo.y = ny;
        } else {
            // Cambiar dirección
            int nueva_dir = (static_cast<int>(enemigo.direccion) + 1) % 4;
            establecerDireccionEnemigo(enemigo, static_cast<Direccion>(nueva_dir));
        }
    }
}

void LaberintoJuego::moverBolas() {
    for (auto& bola : bolas) {
        if (!bola.activa) continue;
        
        int nx = bola.x + bola.dx;
        int ny = bola.y + bola.dy;
        
        if (esPosicionValida(nx, ny)) {
            bola.x = nx;
            bola.y = ny;
        } else {
            bola.activa = false;
        }
    }
}

void LaberintoJuego::verificarColisiones() {
    for (auto& bola : bolas) {
        if (!bola.activa) continue;
        
        for (auto& enemigo : enemigos) {
            if (!enemigo.activo) continue;
            
            if (bola.x == enemigo.x && bola.y == enemigo.y) {
                bola.activa = false;
                enemigo.activo = false;
            }
        }
    }
}

bool LaberintoJuego::verificarColisionJugador() const {
    for (const auto& enemigo : enemigos) {
        if (enemigo.activo && enemigo.x == px && enemigo.y == py) {
            return true;
        }
    }
    return false;
}

void LaberintoJuego::dibujarEscena() {
    // Dibujar laberinto
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            char ch = (laberinto[i][j] == 1) ? 178 : ' ';
            mvwaddch(ventana, i + 1, j + 1, ch);
        }
    }
    
    // Dibujar enemigos
    wattron(ventana, COLOR_PAIR(1));
    for (const auto& enemigo : enemigos) {
        if (enemigo.activo) {
            mvwaddch(ventana, enemigo.y + 1, enemigo.x + 1, 'E');
        }
    }
    wattroff(ventana, COLOR_PAIR(1));
    
    // Dibujar bolas
    wattron(ventana, COLOR_PAIR(4));
    for (const auto& bola : bolas) {
        if (bola.activa) {
            mvwaddch(ventana, bola.y + 1, bola.x + 1, 'o');
        }
    }
    wattroff(ventana, COLOR_PAIR(4));
    
    // Dibujar jugador
    wattron(ventana, COLOR_PAIR(2));
    mvwaddch(ventana, py + 1, px + 1, '@');
    wattroff(ventana, COLOR_PAIR(2));
    
    // Dibujar salida
    wattron(ventana, COLOR_PAIR(3));
    mvwaddch(ventana, salida_y + 1, salida_x + 1, 'X');
    wattroff(ventana, COLOR_PAIR(3));
    
    // Información
    mvwprintw(ventana, 0, 2, "Usa flechas para moverte, ESPACIO para disparar, X para espada, Q para salir");
    
    wrefresh(ventana);
}

void LaberintoJuego::espadaso() {
    int sx = px, sy = py;
    
    switch (ultima_direccion) {
        case KEY_UP:    sy--; break;
        case KEY_DOWN:  sy++; break;
        case KEY_LEFT:  sx--; break;
        case KEY_RIGHT: sx++; break;
    }
    
    // Verificar si golpea a un enemigo
    for (auto& enemigo : enemigos) {
        if (enemigo.activo && enemigo.x == sx && enemigo.y == sy) {
            enemigo.activo = false;
        }
    }
    
    // Dibujar espada si la posición es válida
    if (esPosicionValida(sx, sy)) {
        char espada_char = (ultima_direccion == KEY_LEFT || ultima_direccion == KEY_RIGHT) ? '-' : '|';
        mvwaddch(ventana, sy + 1, sx + 1, espada_char);
        wrefresh(ventana);
        napms(SWORD_DELAY);
    }
}

void LaberintoJuego::lanzarBola() {
    for (auto& bola : bolas) {
        if (!bola.activa) {
            bola.x = px;
            bola.y = py;
            bola.activa = true;
            bola.frame = 0;
            
            switch (ultima_direccion) {
                case KEY_UP:    bola.dx = 0;  bola.dy = -1; break;
                case KEY_DOWN:  bola.dx = 0;  bola.dy = 1;  break;
                case KEY_LEFT:  bola.dx = -1; bola.dy = 0;  break;
                case KEY_RIGHT: bola.dx = 1;  bola.dy = 0;  break;
            }
            break;
        }
    }
}

bool LaberintoJuego::moverJugador(int ch) {
    int nx = px, ny = py;
    
    switch (ch) {
        case KEY_UP:    ny--; break;
        case KEY_DOWN:  ny++; break;
        case KEY_LEFT:  nx--; break;
        case KEY_RIGHT: nx++; break;
        default: return false;
    }
    
    if (esPosicionValida(nx, ny)) {
        px = nx;
        py = ny;
        ultima_direccion = ch;
        return true;
    }
    return false;
}

void LaberintoJuego::inicializar() {
    srand(time(nullptr));
    inicializarColores();
    generarLaberinto();
    buscarPosicionLibre(px, py);
    inicializarEnemigos();
}

void LaberintoJuego::ejecutar() {
    int ch;
    
    while ((ch = wgetch(ventana)) != 'q') {
        // Verificar condiciones de juego
        if (verificarColisionJugador()) {
            mvwprintw(ventana, filas/2, columnas/2 - 5, "GAME OVER!");
            wrefresh(ventana);
            napms(2000);
            break;
        }
        
        if (px == salida_x && py == salida_y) {
            mvwprintw(ventana, filas/2, columnas/2 - 4, "VICTORIA!");
            wrefresh(ventana);
            napms(2000);
            break;
        }
        
        // Actualizar juego
        generarLaberinto();
        moverEnemigos();
        moverBolas();
        verificarColisiones();
        
        // Procesar entrada
        if (ch == ' ') {
            lanzarBola();
        } else if (ch == 'x' || ch == 'X') {
            espadaso();
        } else {
            moverJugador(ch);
        }
        
        // Dibujar y actualizar
        dibujarEscena();
        napms(FRAME_DELAY);
    }
}

void LaberintoJuego::limpiar() {
    if (ventana) {
        delwin(ventana);
        ventana = nullptr;
    }
}

int main() {
    // Inicializar ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    
    // Crear y ejecutar juego
    LaberintoJuego juego(MAP_HEIGHT, MAP_WIDTH, DENSITY);
    juego.inicializar();
    juego.ejecutar();
    
    // Limpiar
    endwin();
    return 0;
}