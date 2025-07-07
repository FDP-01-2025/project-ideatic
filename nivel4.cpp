#include <iostream>
#include <ctime>
#include <string>
#include <windows.h>
using namespace std;

// espera para que salgan las letras 
void esperar(int milisegundos) {
    Sleep(milisegundos);
}

// limpia la pantalla
void limpiarPantalla() {
    system("cls");
}

// mostrar mensaje con efecto de letra por letra (inicio)
void mensajeOscuridad() {
    limpiarPantalla();

    string lin1 = "¡FELICIDADES LLEGASTE AL JUEGO FINAL!";
    string lin2 = "Pero eso no te garantiza el triunfo....";
    string lin3 = "Solo quien comprende el proposito de cada herramienta logra llegar a su destino ";
    string lin3 = "Buena suertee :)";
    string mensaje[] = { lin1, lin2, lin3, };

    for (int l = 0; l < 3; l++) {
        cout << "\n \n";
        for (char p : mensaje[l]) {
            cout << p;
            esperar(40); // velocidad de escritura
        }
        esperar(800); // pausa entre líneas
    }
    esperar(150);
    limpiarPantalla();
}

// advertencia final del laberinto (nivel 4)
void mostrarAdvertenciaLaberinto() {
    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                 ⚠ ⚠ ⚠  ULTIMA   ADVERTENCIA ⚠ ⚠ ⚠                  ║\n";
    cout << "║                                                                      ║\n";
    cout << "║             Puedes ganar… o perderlo todo en segundos.               ║\n";
    cout << "║           Si fallas... serás uno más que nunca volvió.               ║\n";
    cout << "║                                                                      ║\n";
    cout << "║               ¿Estás listo para intentarlo?                          ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
    esperar(4000);
    limpiarPantalla();
}

const int ROWS = 15;
const int COLUMNS = 60;
const int DENSITY = 150;

// Laberinto idéntico al nivel 2
void gLabyrinthLevel4() {
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
                cout << "██"; // muros
            } else {
                cout << "░░"; // polvo
            }
        }
        cout << "\n";
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    mensajeOscuridad();
    mostrarAdvertenciaLaberinto();
    gLabyrinthLevel4();

    return 0;
}
