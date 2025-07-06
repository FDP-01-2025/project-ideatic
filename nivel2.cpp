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

// mostrar mensaje con efecto de letra por letra
void mensajeOscuridad() {
    limpiarPantalla();

    string linea1 = "Has logrado avanzar... pero";
    string linea2 = "has abierto una puerta que puede que nunca logres cerrar.";
    string linea3 = " ";
    string linea4 = "Lo oculto despierta cuando el polvo cae.";
    string linea5 = "Solo quien lee entre las sombras encuentra la salida.";

   
    string mensaje[] = { linea1, linea2, linea3, linea4, linea5 };//

    for (int l = 0; l < 5; l++) {
        cout << "\n\n";
        for (char c : mensaje[l]) {
            cout << c << flush;
            esperar(40); //velocidad de escritura
        }
        esperar(800); //pausa entre líneas
    }
    esperar(150); //espera final antes de iniciar el laberinto
    limpiarPantalla();
}

void mostrarAdvertenciaLaberinto() {
    void esperar(int milisegundos);
void limpiarPantalla();
void mostrarAdvertenciaLaberinto();

    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                         ⚠ ADVERTENCIA ⚠                              ║\n";
    cout << "║                                                                      ║\n";
    cout << "║             Este lugar no fue hecho para los vivos.                  ║\n";
    cout << "║               El polvo que pisas... lo alimenta.                     ║\n";
    cout << "║                                                                      ║\n";
    cout << "║                 Él despierta con cada error.                         ║\n";
    cout << "║                                                                      ║\n";
    cout << "║            Cada error no te aleja... te acerca.                      ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
    esperar(3000); // 3 segundos de pausa para leer
    limpiarPantalla(); // limpiar antes del laberinto
}


const int ROWS = 15;
const int COLUMNS = 60;
const int DENSITY = 150;


void gLabyrinthLevel2() {
    int matriz[ROWS][COLUMNS];
    int walls = DENSITY * 6;

    // Inicializar matriz
    for (int a = 0; a < ROWS; a++) {
        for (int b = 0; b < COLUMNS; b++) {
            if (a == 0 || b == 0 || a == ROWS - 1 || b == COLUMNS - 1) {
                matriz[a][b] = 1;
            } else {
                matriz[a][b] = 0;
            }
        }
    }

    // generar laberinto
    srand(time(NULL));
    for (int c = 0; c < DENSITY; c++) {
        int cl = rand() % (COLUMNS - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (ROWS - 4) + 2;
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1;// rw rows, cl columns.

        for (int d = 0; d < walls; d++) {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;

            if (mr[ran] >= 0 && mr[ran] < ROWS && mc[ran] >= 0 && mc[ran] < COLUMNS) {// mr move rows, mc move columns
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
            cout << "██"; // muros del laberinto simbolos de ascii
        } else {
            cout << "░░"; // el polvo del nivel 2 simbolos de ascii
        }
    }
    cout << "\n";
}
}

int main() {
    // forzar UTF-8 y limpiar
    SetConsoleOutputCP(65001);// compatibilidad y cambio cambio de codificacion y version.
    system("chcp 65001 > nul");// permite que se muestren correctamente caracteres especiales
    system("cls");// limpia la consola antes de mostrar contenido nuevo 
    SetConsoleOutputCP(CP_UTF8);// cambia la codificación de salida de la la consola UTF-8 para que se vean bien los símbolos especiales del laberinto
    mensajeOscuridad();
    mostrarAdvertenciaLaberinto();
    gLabyrinthLevel2();
    return 0;
}
