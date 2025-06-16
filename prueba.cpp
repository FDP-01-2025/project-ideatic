#include <curses.h> // Incluye la biblioteca para manejo de pantalla y teclado en consola

int main() {
    int x = 10, y = 10; // Posición inicial del personaje en la pantalla
    int ch;             // Variable para almacenar la tecla presionada

    // Posturas del personaje según la dirección (cada matriz representa una postura 3x3)
    char personaje_up[3][3] = {         // Postura cuando va hacia arriba
        {' ', 'O', ' '},                // Cabeza
        {'/', '|', '\\'},               // Brazos y torso
        {' ', '^', ' '}                 // Piernas levantadas
    };
    char personaje_down[3][3] = {       // Postura cuando va hacia abajo
        {' ', 'O', ' '},
        {'/', '|', '\\'},
        {'/', ' ', '\\'}
    };
    char personaje_left[3][3] = {       // Postura cuando va hacia la izquierda
        {' ', 'O', ' '},
        {'/', '|', '-'},
        {'/', ' ', ' '}
    };
    char personaje_right[3][3] = {      // Postura cuando va hacia la derecha
        {' ', 'O', ' '},
        {'-', '|', '\\'},
        {' ', ' ', '\\'}
    };

    // Por defecto, el personaje mira hacia abajo
    char (*personaje)[3] = personaje_down;

    initscr();              // Inicializa la pantalla para usar funciones de curses
    keypad(stdscr, TRUE);   // Habilita la lectura de teclas especiales (flechas)
    noecho();               // No muestra las teclas presionadas en pantalla
    curs_set(0);            // Oculta el cursor

    while (1) {             // Bucle principal del juego
        clear();            // Limpia la pantalla antes de dibujar
        // Dibuja el personaje (matriz 3x3) en la posición actual
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mvaddch(y + i, x + j, personaje[i][j]); // Dibuja cada parte del personaje
            }
        }
        refresh();          // Actualiza la pantalla para mostrar los cambios

        ch = getch();       // Espera y obtiene la tecla presionada
        if (ch == KEY_UP) {         // Si se presiona flecha arriba
            y--;                    // Mueve el personaje hacia arriba
            personaje = personaje_up; // Cambia la postura a "arriba"
        }
        else if (ch == KEY_DOWN) {  // Si se presiona flecha abajo
            y++;                    // Mueve el personaje hacia abajo
            personaje = personaje_down; // Cambia la postura a "abajo"
        }
        else if (ch == KEY_LEFT) {  // Si se presiona flecha izquierda
            x--;                    // Mueve el personaje hacia la izquierda
            personaje = personaje_left; // Cambia la postura a "izquierda"
        }
        else if (ch == KEY_RIGHT) { // Si se presiona flecha derecha
            x++;                    // Mueve el personaje hacia la derecha
            personaje = personaje_right; // Cambia la postura a "derecha"
        }
        else if (ch == 'q' || ch == 'Q') break; // Si se presiona 'q' o 'Q', sale del bucle
    }

    endwin();               // Finaliza el modo curses y restaura la terminal
    return 0;               // Fin del programa
}
