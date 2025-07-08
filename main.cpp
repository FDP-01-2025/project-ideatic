#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "src/character.h"
#include "src/save_game.h"
#include "src/labyrinth.h"
#include "src/message.h"
#include "src/enemy.h"

int main()
{

    inicial(); // Inicializa curses y la pantalla

    nodelay(stdscr, FALSE);
    int option = menu(); // Llama al menú y obtiene la opción seleccionada
    nodelay(stdscr, TRUE);
    iniciar_juego_menu(option, x, y, score, balls, MAX_BALLS);

    return 0;
}