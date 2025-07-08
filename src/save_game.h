#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include <fstream>
#include "ball.h"
#include "music.h"

void level1message(WINDOW *win);
void puntos();
using namespace std;

// Guarda la partida en un archivo de texto.
// Recibe el nombre del archivo, la posición del personaje, el puntaje y el arreglo de bolas.
// Guarda los datos en formato similar a guardarPuntajes
void save_game(const char *filename, int x, int y, int score, Ball balls[], int max_balls)
{
    ofstream archivo(filename);
    if (archivo.is_open())
    {
        // Guarda la posición y el puntaje del jugador principal
        archivo << x << " " << y << " " << score << endl;
        // Guarda los datos de cada bola activa o inactiva
        for (int i = 0; i < max_balls; ++i)
        {
            archivo << balls[i].x << " " << balls[i].y << " " << balls[i].active << endl;
        }
        archivo.close();
        printw("Game saved successfully.\n");
    }
    else
    {
        printw("Could not save the game.\n");
    }
}

// Carga la partida desde un archivo de texto.
// Recupera la posición del personaje, el puntaje y el estado de las bolas.
bool load_game(const char *filename, int &x, int &y, int &score, Ball balls[], int max_balls)
{
    ifstream file(filename); // Abre el archivo para lectura
    if (!file)
        return false; // Si no se pudo abrir, retorna false

    // Lee la posición del personaje y el puntaje
    file >> x >> y >> score;
    // Lee los datos de cada bola
    for (int i = 0; i < max_balls; i++)
    {
        file >> balls[i].x >> balls[i].y >> balls[i].dx >> balls[i].dy >> balls[i].active >> balls[i].frame;
    }
    file.close(); // Cierra el archivo
    return true;  // Retorna true si se cargó correctamente
}

// Carga la partida y muestra un mensaje en pantalla.
// Retorna true si se cargó correctamente, false si no existe el archivo.
bool cargar_partida(const char *filename, int &x, int &y, int &score, Ball balls[], int max_balls)
{
    clear();
    refresh();
    if (load_game(filename, x, y, score, balls, max_balls))
    {
        printw("Game loaded successfully!\n");
        refresh();
        napms(1000);
        return true;
    }
    else
    {
        printw("No saved game found.\n");
        refresh();
        napms(1500);
        return false;
    }
}

// Muestra un menú interactivo en pantalla y retorna la opción elegida por el usuario.
// 1 = Nueva partida, 2 = Cargar partida, 3 = Salir
int menu()
{
    reproducirFondo();
    clear(); // Limpia la pantalla antes de mostrar el menú

    // Mostrar el menú con formato mejorado usando caracteres ASCII simples
    printw("+----------------------------------------+\n");
    printw("|          Welcome to the Game Menu      |\n");
    printw("+----------------------------------------+\n");
    printw("| 1. New Game                            |\n");
    printw("| 2. Load Game                           |\n");
    printw("| 3. Exit                                |\n");
    printw("+----------------------------------------+\n");
    printw("Select an option (1-3): ");
    refresh();

    // Validar la entrada del usuario
    int opt;
    while (true)
    {
        opt = getch(); // Espera la opción del usuario
        if (opt == '1' || opt == '2' || opt == '3')
        {
            break; // Salir del bucle si la entrada es válida
        }
        printw("\nInvalid option. Please select 1, 2, or 3: ");
        refresh();
    }

    return opt - '0'; // Retorna el valor como entero (1, 2 o 3)
}

// Función para manejar el menú principal y las acciones según la opción elegida
int iniciar_juego_menu(int option, int &x, int &y, int &score, Ball balls[], int max_balls)
{
    if (option == 1)
    {                          // Nueva partida
        level1message(stdscr); // Muestra el mensaje de introducción al nivel 1
        puntos();              // Inicia una nueva partida
    }
    else if (option == 2)
    { // Cargar partida
        if (load_game("save.txt", x, y, score, balls, max_balls))
        {
            printw("Game loaded successfully!\n");
            refresh();
            napms(1000);
            puntos(); // Inicia el juego desde la partida cargada
        }
        else
        {
            printw("No saved game found.\n");
            refresh();
            napms(1500);
        }
    }
    else
    { // Salir
        endwin();
        return 0;
    }
    endwin();
    return 0;
}
// Devuelve true si el usuario quiere salir, false si quiere regresar al juego
bool menu_guardar_partida(int x, int y, int score, Ball balls[], int max_balls)
{
    while (true)
    {
        nodelay(stdscr, FALSE); // Espera la entrada
        clear();
        printw("Do you want to save the game? (y/n) or (r to return): ");
        refresh();
        int save_opt = getch();
        if (save_opt == 'y' || save_opt == 'Y')
        {
            save_game("save.txt", x, y, score, balls, max_balls);
            printw("\nGame saved!\n");
            refresh();
            napms(1000);
            return true; // Sale del juego
        }
        else if (save_opt == 'n' || save_opt == 'N')
        {
            return true; // Sale del juego sin guardar
        }
        else if (save_opt == 'r' || save_opt == 'R')
        {
            return false; // Regresa al juego
        }
        else
        {
            printw("\nInvalid option. Please press y, n, or r.");
            refresh();
            napms(1000);
        }
    }
}

#endif // SAVE_GAME_H