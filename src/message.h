#ifndef MESSAGE_H
#define MESSAGE_H

#include <curses.h>

//mensaje de introducción al nivel 1
void level1message(WINDOW *win)
{
    wclear(win); // Limpia la ventana
    wrefresh(win);

    string message1 = "Welcome :D!";
    string message2 = "You have entered the pyramid, use the arrow keys to move forward and grab the coins.";
    string message3 = "If you collect the coins and manage to escape the labyrinth by defeating the villain, you will move on to the next level.";
    string message4 = "Good luck!, see you at the next level ";
    string message5 = "...";
    string message6 = "or not :)";

    string messages[] = {message1, message2, message3, message4, message5, message6};

    for (int i = 0; i < 6; i++)
    {
        wprintw(win, "\n"); // Imprime un salto de línea
        for (char a : messages[i])
        {
            wprintw(win, "%c", a); // Imprime carácter por carácter
            wrefresh(win);         // Refresca la ventana para mostrar el texto
            napms(20);             // Pausa breve entre caracteres
        }
        napms(800); // Pausa entre mensajes
    }

    wclear(win); // Limpia la ventana al final
    wrefresh(win);
    napms(150); // Pausa final
}
#endif // MESSAGE_H