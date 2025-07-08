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

    string linea1 = "Has logrado avanzar... pero";
    string linea2 = "has abierto una puerta que puede que nunca logres cerrar.";
    string linea3 = " ";
    string linea4 = "Lo oculto despierta cuando el polvo cae.";
    string linea5 = "Solo quien lee entre las sombras encuentra la salida.";

    string mensaje[] = { linea1, linea2, linea3, linea4, linea5 };

    for (int l = 0; l < 5; l++) {
        cout << "\n\n";
        for (char c : mensaje[l]) {
            cout << c;
            esperar(20);
        }
        esperar(800);
    }
    esperar(150);
    limpiarPantalla();
}

void mostrarAdvertenciaLaberinto() {
    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                         ⚠ ADVERTENCIA ⚠                             4 ║\n";
    cout << "║                                                                      ║\n";
    cout << "║             Este lugar no fue hecho para los vivos.                  ║\n";
    cout << "║               El polvo que pisas... lo alimenta.                     ║\n";
    cout << "║                                                                      ║\n";
    cout << "║                 Él despierta con cada error.                         ║\n";
    cout << "║                                                                      ║\n";
    cout << "║            Cada error no te aleja... te acerca.                      ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
    esperar(5000);
    limpiarPantalla();
}

void finalmessagelevel1() {
    esperar(1000);
    limpiarPantalla();
    string message = "You've completed the level";
    string message1 = "but don't declare victory yet!";
    string message2 = "Press Z to move on to the next level";
    string message3[] = {message, message1, message2};

    for (int i = 0; i < 3; i++) {
        cout << endl;
        for (char b : message3[i]) {
            cout << b;
            esperar(50);
        }
        esperar(300);
    }

    char tecla;
    cout << "\n\nPresiona Z para continuar: ";
    while (true) {
        cin >> tecla;
        tecla = toupper(tecla);
        if (tecla == 'Z') {
            break;
        } else {
            cout << " Entrada inválida, por favor, presiona Z para continuar: ";
        }
    }

    esperar(300);
    limpiarPantalla();

    cout << "\n Comienza el siguiente desafío, suerte.....\n";
    esperar(1500);
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

void gLabyrinthLevel2(bool gano) {
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

    // Simula si el jugador gana o pierde (de forma aleatoria)
    srand(time(NULL));
    bool gano = rand() % 2 == 0; // true o false aleatoriamente

    gLabyrinthLevel2(gano);

    return 0;
}
