#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "src/character.h"
#include "src/save_game.h"
#include "src/labyrinth.h"
#include "src/message.h"

int main()
{

    inicial(); // Inicializa curses y la pantalla

    nodelay(stdscr, FALSE);
    int option = menu(); // Llama al menú y obtiene la opción seleccionada
    nodelay(stdscr, TRUE);

    if (option == 1)
    {                          // Nueva partida
        level1message(stdscr); // Muestra el mensaje de introducción al nivel 1
        puntos();              // Inicia una nueva partida
    }
    else if (option == 2)
    { // Cargar partida
        if (load_game("save.txt", x, y, score, balls, MAX_BALLS))
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