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
// NIVEL 2 - Mensaje de oscuridad
void mensajeOscuridad(WINDOW *win) {
    wclear(win);
    wrefresh(win);

    string mensaje[] = {
        "Has logrado avanzar... pero",
        "has abierto una puerta que puede que nunca logres cerrar.",
        " ",
        "Lo oculto despierta cuando el polvo cae.",
        "Solo quien lee entre las sombras encuentra la salida."
    };

    for (int i = 0; i < 5; i++) {
        wprintw(win, "\n\n");
        for (char c : mensaje[i]) {
            wprintw(win, "%c", c);
            wrefresh(win);
            napms(20);
        }
        napms(800);
    }

    napms(150);
    wclear(win);
    wrefresh(win);
}

// NIVEL 2 - Advertencia del laberinto
void mostrarAdvertenciaLaberinto(WINDOW *win) {
    wclear(win);
    wrefresh(win);

    string advertencia[] = {
        "╔══════════════════════════════════════════════════════════════════════╗",
        "║                         ⚠ ADVERTENCIA ⚠                              ║",
        "║                                                                      ║",
        "║             Este lugar no fue hecho para los vivos.                  ║",
        "║               El polvo que pisas... lo alimenta.                     ║",
        "║                                                                      ║",
        "║                 Él despierta con cada error.                         ║",
        "║                                                                      ║",
        "║            Cada error no te aleja... te acerca.                      ║",
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

// NIVEL 2 - Mensaje de derrota
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
<<<<<<< HEAD
        string << endl;
=======
        wprintw(win, "\n");
>>>>>>> b5b201d8b066d64b3c4c6133df8d11f8dae5c45c
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
        string << endl;
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

//NIVEL 4 
void mensajeOscuridad(WINDOW *win) {
    wclear(win);
    string lin1 = "¡FELICIDADES LLEGASTE AL JUEGO FINAL!";
    string lin2 = "Pero eso no te garantiza el triunfo....";
    string lin3 = "Solo quien comprende el proposito de cada herramienta logra llegar a su destino";
    string lin4 = "Buena suertee :)";
    string mensaje[] = { lin1, lin2, lin3, lin4 };

    for (int l = 0; l < 4; l++) {
        string << "\n\n";
        for (char p : mensaje[l]) {
            string << p;
            esperar(30);
        }
        esperar(800);
    }
    esperar(150);
    wclear(win);
}

void mostrarAdvertenciaLaberinto(WINDOW *win) {
    string << "\n\n";
    string << "╔══════════════════════════════════════════════════════════════════════╗\n";
    string << "║                 ⚠ ⚠ ⚠  ULTIMA ADVERTENCIA ⚠ ⚠ ⚠                      ║\n";
    string << "║                                                                      ║\n";
    string << "║             Puedes ganar… o perderlo todo en segundos.               ║\n";
    string << "║           Si fallas... serás uno más que nunca volvió.               ║\n";
    string << "║                                                                      ║\n";
    string << "║               ¿Estás listo para intentarlo?                          ║\n";
    string << "╚══════════════════════════════════════════════════════════════════════╝\n";
    esperar(5000);
    wclear(win);
}

void finalmessagelevel1(WINDOW *win) {
    esperar(1000);
    wclear(win);

    string msj1 = "¡FELICIDADES, HAS LLEGADO AL FINAL!";
    string msj2 = "Eres uno de los pocos que logró superar todos los desafíos.";
    string msj3 = "Has gano por lo que tanto luchaste";

    string mensajes[] = {msj1, msj2, msj3};

    for (string linea : mensajes) {
        string << "\n";
        for (char c : linea) {
            string << c;
            esperar(50);
        }
        esperar(800);
        wclear(win);
    }

    // Calificación
    string << "\n\nQueremos saber tu opinión. ¿Qué te pareció esta experiencia?\n";
    string << "Califica de 1 a 5 estrellas: ";

    int estrellas;
    while (true) {
        cin >> estrellas;
        if (cin.fail() || estrellas < 1 || estrellas > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            string << "Por favor, ingresa un número válido entre 1 y 5: ";
        } else {
            break;
        }
    }

    string << "\nMostrando tu calificación";
    for (int i = 0; i < 3; i++) {
        string << ".";
        esperar(500);
    }

    string << "\nTu calificación fue: ";
    for (int i = 0; i < estrellas; i++) {
        string << "★ ";
        esperar(300);
    }

    // Mensaje final de despedida
    limpiarPantalla();
    esperar(1200);
    string << "\n\nGracias por jugar, Vuelve cuando desees.\n";
    esperar(1500);
    limpiarPantalla();
}
#endif // MESSAGE_H