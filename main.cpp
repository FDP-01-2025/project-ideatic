#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "src/character.h"
#include "src/save_game.h"

int main()
{
    inicial(); // Inicializa curses y la pantalla

    nodelay(stdscr, FALSE);
    int option = menu();
    nodelay(stdscr, TRUE);

    if (option == '1') {
        puntos(); // Nueva partida
    } else if (option == '2') {
        // Llama directamente a load_game
        if (load_game("save.txt", x, y, score, balls, MAX_BALLS)) {
            printw("Game loaded successfully!\n");
            refresh();
            napms(1000);
            puntos(); // Inicia el juego desde la partida cargada
        } else {
            printw("No saved game found.\n");
            refresh();
            napms(1500);
        }
    } else {
        endwin();
        return 0; // Salir
    }
    endwin();
    return 0;
}