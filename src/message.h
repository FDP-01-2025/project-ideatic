#ifndef MESSAGE_H
#define MESSAGE_H

#include <curses.h>

// mensaje de introducción al nivel 1
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
void level3message(WINDOW *win)
{

    wclear(win);
    wrefresh(win);
    string message1 = "Congratulations! You've made it to level 3 :D";
    string message2 = "Now you must defeat the enemy of this level to move on to the last one.";
    string message3 = "Good luck!, see you at the next level";

    string message[] = {message1, message2, message3};

    for (int i = 0; i < 3; i++)
    {
        wprintw(win, "\n");
        for (char a : message[i])
        {
            wprintw(win, "%n", a);
            wclear(win);
            napms(20);
        }
        napms(800);
    }
    wclear(win);
    wrefresh(win);
    napms(150);
}
void loading(WINDOW *win)
{
    wclear(win);
    wrefresh(win);
    string message = "loading";
    string message1 = "...";
    string message2[] = {message, message1};

    for (int j = 0; j < 2; j++)
    {
        for (char c : message2[j])
        {
            wprintw(win, "%n", c);
            napms(50);
        }
    }
    napms(300);
    wclear(win);
    wrefresh(win);
}
void finalmessagelevel1(WINDOW * win)
{
    napms(1000);
    wclear(win);
    string message = "You've completed the level";
    string message1 = "but don't declare victory yet!";
    string message2 = "Press Z to move on to the next level";
    string message3[] = {message, message1, message2};
    for (int i = 0; i < 3; i++)
    {
        cout << endl;
        for (char b : message3[i])
        {
            wprintw(win, "%n", b);
            napms(50);
        }
        napms(300);
    }
    napms(300);
    wclear(win);
}
void finalmessage2(WINDOW* win)
{
    napms(500);
    wclear(win);
    string message = "You lost :(";
    string message1 = "Try again to move on to the next level";
    string message2 = "Don't get discouraged :D!";
    string message3[] = {message, message1, message2};
    for (int i = 0; i < 3; i++)
    {
        cout << endl;
        for (char b : message3[i])
        {
            wprintw(win, "%n", b);
            napms(50);
        }
        napms(300);
    }
    napms(500);
    wclear(win);
}
#endif // MESSAGE_H