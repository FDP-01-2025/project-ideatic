#include <iostream>
#include <ctime>
#include <string>
#include <windows.h>
using namespace std;

void esperar(int milisegundos) {
    Sleep(milisegundos);
}

void limpiarPantalla() {
    system("cls");
}

void mensajeOscuridad() {
    limpiarPantalla();
    string lin1 = "¡FELICIDADES LLEGASTE AL JUEGO FINAL!";
    string lin2 = "Pero eso no te garantiza el triunfo....";
    string lin3 = "Solo quien comprende el proposito de cada herramienta logra llegar a su destino";
    string lin4 = "Buena suertee :)";
    string mensaje[] = { lin1, lin2, lin3, lin4 };

    for (int l = 0; l < 4; l++) {
        cout << "\n\n";
        for (char p : mensaje[l]) {
            cout << p;
            esperar(30);
        }
        esperar(800);
    }
    esperar(150);
    limpiarPantalla();
}

void mostrarAdvertenciaLaberinto() {
    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                 ⚠ ⚠ ⚠  ULTIMA ADVERTENCIA ⚠ ⚠ ⚠                      ║\n";
    cout << "║                                                                      ║\n";
    cout << "║             Puedes ganar… o perderlo todo en segundos.               ║\n";
    cout << "║           Si fallas... serás uno más que nunca volvió.               ║\n";
    cout << "║                                                                      ║\n";
    cout << "║               ¿Estás listo para intentarlo?                          ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
    esperar(5000);
    limpiarPantalla();
}

void finalmessagelevel1() {
    esperar(1000);
    limpiarPantalla();

    string msj1 = "¡FELICIDADES, HAS LLEGADO AL FINAL!";
    string msj2 = "Eres uno de los pocos que logró superar todos los desafíos.";
    string msj3 = "Has gano por lo que tanto luchaste";

    string mensajes[] = {msj1, msj2, msj3};

    for (string linea : mensajes) {
        cout << "\n";
        for (char c : linea) {
            cout << c;
            esperar(50);
        }
        esperar(800);
        limpiarPantalla();
    }

    // Calificación
    cout << "\n\nQueremos saber tu opinión. ¿Qué te pareció esta experiencia?\n";
    cout << "Califica de 1 a 5 estrellas: ";

    int estrellas;
    while (true) {
        cin >> estrellas;
        if (cin.fail() || estrellas < 1 || estrellas > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Por favor, ingresa un número válido entre 1 y 5: ";
        } else {
            break;
        }
    }

    cout << "\nMostrando tu calificación";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        esperar(500);
    }

    cout << "\nTu calificación fue: ";
    for (int i = 0; i < estrellas; i++) {
        cout << "★ ";
        esperar(300);
    }

    // Mensaje final de despedida
    limpiarPantalla();
    esperar(1200);
    cout << "\n\nGracias por jugar, Vuelve cuando desees.\n";
    esperar(1500);
    limpiarPantalla();
}

void finalmessage2() {
    esperar(1000);
    limpiarPantalla();
    string message = "You lost :(";
    string message1 = "Try again to move on to the next level";
    string message2 = "Don't get discouraged :D!";
    string message3[] = {message, message1, message2};

    for (int i = 0; i < 3; i++) {
        cout << endl;
        for (char b : message3[i]) {
            cout << b;
            esperar(50);
        }
        esperar(300);
    }
    esperar(300);
    limpiarPantalla();
}

const int ROWS = 15;
const int COLUMNS = 60;
const int DENSITY = 150;

void gLabyrinthLevel4(bool gano) {
    int matriz[ROWS][COLUMNS];
    int walls = DENSITY * 6;

    for (int a = 0; a < ROWS; a++) {
        for (int b = 0; b < COLUMNS; b++) {
            if (a == 0 || b == 0 || a == ROWS - 1 || b == COLUMNS - 1) {
                matriz[a][b] = 1;
            } else {
                matriz[a][b] = 0;
            }
        }
    }

    srand(time(NULL));
    for (int c = 0; c < DENSITY; c++) {
        int cl = rand() % (COLUMNS - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (ROWS - 4) + 2;
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1;

        for (int d = 0; d < walls; d++) {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;

            if (mr[ran] >= 0 && mr[ran] < ROWS && mc[ran] >= 0 && mc[ran] < COLUMNS) {
                if (matriz[mr[ran]][mc[ran]] == 0) {
                    matriz[mr[ran]][mc[ran]] = 1;
                    int midrow = mr[ran] + (rw - mr[ran]) / 2;
                    int midcolum = mc[ran] + (cl - mc[ran]) / 2;
                    if (midrow >= 0 && midrow < ROWS && midcolum >= 0 && midcolum < COLUMNS)
                        matriz[midrow][midcolum] = 1;
                }
            }
        }
    }

    for (int e = 0; e < ROWS; e++) {
        for (int f = 0; f < COLUMNS; f++) {
            if (matriz[e][f] == 1) {
                cout << "██";
            } else {
                cout << "░░";
            }
        }
        cout << "\n";
    }

    esperar(1500);

    if (gano) {
        finalmessagelevel1();
    } else {
        finalmessage2();
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    mensajeOscuridad();
    mostrarAdvertenciaLaberinto();

    bool gano = true; // Cambia a false para probar la derrota
    gLabyrinthLevel4(gano);

    return 0;
}
