#ifndef MESSAGE_H
#define MESSAGE_H

#include <curses.h>
#include <string>

// Mensaje de introducción al nivel 1
void level1message(WINDOW *win)
{
    wclear(win);
    wrefresh(win);

    string messages[] = {
        "Welcome :D!",
        "You have entered the pyramid, use the arrow keys to move forward and grab the coins.",
        "If you collect the coins and manage to escape the labyrinth by defeating the villain, you will move on to the next level.",
        "Good luck!, see you at the next level ",
        "...",
        "or not :)"
    };

    for (int i = 0; i < 6; i++)
    {
        wprintw(win, "\n");
        for (char a : messages[i])
        {
            wprintw(win, "%c", a);
            wrefresh(win);
            napms(20);
        }
        napms(800);
    }

    wclear(win);
    wrefresh(win);
    napms(150);
}

// Mensaje de oscuridad
void mensajeOscuridad(WINDOW *win) {
    wclear(win);
    wrefresh(win);

    string mensaje[] = {
        "¡FELICIDADES LLEGASTE AL JUEGO FINAL!",
        "Pero eso no te garantiza el triunfo....",
        "Solo quien comprende el proposito de cada herramienta logra llegar a su destino",
        "Buena suertee :)"
    };

    for (int l = 0; l < 4; l++) {
        wprintw(win, "\n\n");
        for (char p : mensaje[l]) {
            wprintw(win, "%c", p);
            wrefresh(win);
            napms(30);
        }
        napms(800);
    }
    napms(150);
    wclear(win);
    wrefresh(win);
}

// Advertencia del laberinto
void mostrarAdvertenciaLaberinto(WINDOW *win) {
    wclear(win);
    wrefresh(win);

    string advertencia[] = {
        "╔══════════════════════════════════════════════════════════════════════╗",
        "║                 ⚠ ⚠ ⚠  ULTIMA ADVERTENCIA ⚠ ⚠ ⚠                   ║",
        "║                                                                      ║",
        "║             Puedes ganar… o perderlo todo en segundos.               ║",
        "║           Si fallas... serás uno más que nunca volvió.               ║",
        "║                                                                      ║",
        "║               ¿Estás listo para intentarlo?                          ║",
        "╚══════════════════════════════════════════════════════════════════════╝"
    };

    for (const string& linea : advertencia) {
        wprintw(win, "%s\n", linea.c_str());
        wrefresh(win);
        napms(300);
    }

    napms(5000);
    wclear(win);
    wrefresh(win);
}

// Mensaje de derrota
void finalmessage2(WINDOW *win) {
    napms(1000);
    wclear(win);
    wrefresh(win);

    string mensaje[] = {
        "You lost :(",
        "Try again to move on to the next level",
        "Don't get discouraged :D!"
    };

    for (int i = 0; i < 3; i++) {
        wprintw(win, "\n");
        for (char b : mensaje[i]) {
            wprintw(win, "%c", b);
            wrefresh(win);
            napms(50);
        }
        napms(300);
    }

    napms(300);
    wclear(win);
    wrefresh(win);
}

// Mensaje para nivel 3
void level3message(WINDOW *win)
{
    wclear(win);
    wrefresh(win);
    string message[] = {
        "Congratulations! You've made it to level 3 :D",
        "Now you must defeat the enemy of this level to move on to the last one.",
        "Good luck!, see you at the next level"
    };

    for (int i = 0; i < 3; i++)
    {
        wprintw(win, "\n");
        for (char a : message[i])
        {
            wprintw(win, "%c", a);
            wrefresh(win);
            napms(20);
        }
        napms(800);
    }
    wclear(win);
    wrefresh(win);
    napms(150);
}

// Mensaje de loading
void loading(WINDOW *win)
{
    wclear(win);
    wrefresh(win);
     string message[] = {"loading", "..."};

    for (int j = 0; j < 2; j++)
    {
        for (char c : message[j])
        {
            wprintw(win, "%c", c);
            wrefresh(win);
            napms(100);
        }
    }
    napms(300);
    wclear(win);
    wrefresh(win);
}

// Mensaje final de nivel 1
void finalmessagelevel1(WINDOW *win)
{
    napms(1000);
    wclear(win);
    wrefresh(win);

     string message[] = {
        "You've completed the level",
        "but don't declare victory yet!",
        "Press Z to move on to the next level"
    };
    for (int i = 0; i < 3; i++)
    {
        wprintw(win, "\n");
        for (char b : message[i])
        {
            wprintw(win, "%c", b);
            wrefresh(win);
            napms(50);
        }
        napms(300);
    }
    napms(300);
    wclear(win);
    wrefresh(win);
}

#endif // MESSAGE_H