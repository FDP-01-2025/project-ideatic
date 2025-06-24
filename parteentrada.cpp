#include <curses.h>
#include <string>
#include <ctime>
#include <iostream>
#include <windows.h>
using namespace std;

void esperar(int ms) { //Se hace para la hora del mensaje al entrar a la piramide y que este un milisegundito y que salga el texto 
    Sleep(ms);
}

void dibujarPiramide() {
    int total_lineas = 25;// altura de la piramide
    int ancho_base = (total_lineas * 2) - 1;// el calculo del ancho de la piramide asiendo el calculo con lo de las lineas para que sea asimetrica 
    int fila_inicial = 2;//donde se empieza a dibujar la piramide osea la base 

    for (int nlinea = 1; nlinea <= total_lineas; nlinea++) {// dibuja linea a linea la piramide con el valor d elineas desde 1 a 25
        int nast = (nlinea * 2) - 1;// calcula los asterisco que usamo spara que aumenten de dos en dos 
        int nesp = (ancho_base - nast) / 2;

        string linea = string(nesp, ' ') + string(nast, '*');// calcula los espacios y los asteriscos
        mvprintw(fila_inicial + nlinea, 10, linea.c_str());
    }

    mvprintw(fila_inicial + total_lineas + 1, 10 + ancho_base / 2 - 2, " |||| ");
}

void mensajeOscuridad() {
    clear();// empezamos desde 0, limpiamos la pantalla 
    string mensaje = "Has empezado la busqueda... cuidado todo tiene su concecuencia...";
    for (size_t i = 0; i < mensaje.size(); ++i) {// dependiendo el texto se imprimira letra por letra y lo que se guardo en mensaje se manda a llamar y se pone el tamano
        mvaddch(10, 5 + i, mensaje[i]);
        refresh();
        esperar(60);// espera 60 sg para que la letra aparezca una por una y no tan rapido 
    }
    esperar(1500);// tiempo de leer el mensaje para el juf=gador 
}

void generarLaberinto(int filas, int columnas, float densidad) {
    int **matriz;
    matriz = new int *[filas];

    int FParedes = densidad * 8;
    densidad = filas * columnas * densidad / 4;

    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1) {
                matriz[i][j] = 1;
            }
            else {
                matriz[i][j] = 0;
            }
        }
    }

    srand(time(NULL));
    for (int i = 0; i < densidad; i++) {
        int x = rand() % (columnas - 4) + 2;
        x = (x / 2) * 2;
        int y = rand() % (filas - 4) + 2;
        y = (y / 2) * 2;
        matriz[y][x] = 1;
        for (int j = 0; j < FParedes; j++) {
            int mx[4] = { x,  x,  x + 2, x - 2 };
            int my[4] = { y + 2,y - 2, y ,  y };
            int r = rand() % 4;
            if (matriz[my[r]][mx[r]] == 0) {
                matriz[my[r]][mx[r]] = 1;
                matriz[my[r] + (y - my[r]) / 2][mx[r] + (x - mx[r]) / 2] = 1;
            }
        }
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == 1) {
                char a = 178;
                cout << a << a;
            }
            if (matriz[i][j] == 0) {
                cout << "  ";
            }
        }
        cout << "\n";
    }
}

void mostrarLaberinto() {
    generarLaberinto(20, 70, 0.75);
    system("pause");
}

int main() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int px = 15, py = 12;
    int ch;

    while (true) {
        clear();
        dibujarPiramide();
        mvprintw(py, px, "A");
        refresh();

        ch = getch();
        if (ch == KEY_UP) py--;
        else if (ch == KEY_DOWN) py++;
        else if (ch == KEY_LEFT) px--;
        else if (ch == KEY_RIGHT) px++;

        // detectar si toca cualquier parte de la pirámide y empeiza el juegp
        char simbolo = mvinch(py, px) & A_CHARTEXT;

        if (simbolo == '*') { // Si toca cualquier parte de la pirámide
            mensajeOscuridad();
            endwin();
            mostrarLaberinto();
            break;
        }

        // Coordenadas de la de la pirámide
        if (py == 9 && (px >= 15 && px <= 18)) {
            mensajeOscuridad();
            mostrarLaberinto();
            break;
        }

        if (py == 28 && (px >= 35 && px <= 40)) {
            mensajeOscuridad();
            endwin();
            mostrarLaberinto();
            break;
        }
    }

    getch();
    endwin();
    return 0;
}
