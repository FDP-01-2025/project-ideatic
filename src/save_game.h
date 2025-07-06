#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include <fstream>
#include "ball.h"
using namespace std;

// Guarda la partida en un archivo de texto.
// Recibe el nombre del archivo, la posición del personaje, el puntaje y el arreglo de bolas.
void save_game(const char* filename, int x, int y, int score, Ball balls[], int max_balls) {
    ofstream file(filename); // Abre el archivo para escritura
    if (!file) return;       // Si no se pudo abrir, sale de la función

    // Guarda la posición del personaje y el puntaje
    file << x << " " << y << " " << score << "\n";
    // Guarda los datos de cada bola activa o inactiva
    for (int i = 0; i < max_balls; i++) {
        file << balls[i].x << " " << balls[i].y << " "
             << balls[i].dx << " " << balls[i].dy << " "
             << balls[i].active << " " << balls[i].frame << "\n";
    }
    file.close(); // Cierra el archivo
}

// Carga la partida desde un archivo de texto.
// Recupera la posición del personaje, el puntaje y el estado de las bolas.
bool load_game(const char* filename, int &x, int &y, int &score, Ball balls[], int max_balls) {
    ifstream file(filename); // Abre el archivo para lectura
    if (!file) return false; // Si no se pudo abrir, retorna false

    // Lee la posición del personaje y el puntaje
    file >> x >> y >> score;
    // Lee los datos de cada bola
    for (int i = 0; i < max_balls; i++) {
        file >> balls[i].x >> balls[i].y
             >> balls[i].dx >> balls[i].dy
             >> balls[i].active >> balls[i].frame;
    }
    file.close(); // Cierra el archivo
    return true;  // Retorna true si se cargó correctamente
}

// Carga la partida y muestra un mensaje en pantalla.
// Retorna true si se cargó correctamente, false si no existe el archivo.
bool cargar_partida(const char* filename, int &x, int &y, int &score, Ball balls[], int max_balls) {
    clear();
    refresh();
    if (load_game(filename, x, y, score, balls, max_balls)) {
        printw("Game loaded successfully!\n");
        refresh();
        napms(1000);
        return true;
    } else {
        printw("No saved game found.\n");
        refresh();
        napms(1500);
        return false;
    }
}

// Muestra un menú simple en pantalla y retorna la opción elegida por el usuario.
// 1 = Nueva partida, 2 = Cargar partida, 3 = Salir
int menu()
{
    printw("==== MENU ====\n");
    printw("1. New Game\n");
    printw("2. Load Game\n");
    printw("3. Exit\n");
    printw("Select an option: ");
    refresh();

    int opt = getch(); // Espera la opción del usuario
    return opt;        // Retorna el valor presionado ('1', '2' o '3')
}

#endif // SAVE_GAME_H