#include <iostream>
#include <ctime>
using namespace std;

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

    // Generar laberinto
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
                    int mid_r = mr[ran] + (rw - mr[ran]) / 2;
                    int mid_c = mc[ran] + (cl - mc[ran]) / 2;
                    if (mid_r >= 0 && mid_r < ROWS && mid_c >= 0 && mid_c < COLUMNS)
                        matriz[mid_r][mid_c] = 1;
                }
            }
        }
    }

    for (int e = 0; e < ROWS; e++) {
    for (int f = 0; f < COLUMNS; f++) {
        if (matriz[e][f] == 1) {
            cout << "██"; // uros del laberinto
        } else {
            cout << "░░"; // El polvo del nivel 2 
        }
    }
    cout << "\n";
}
}

int main() {
    gLabyrinthLevel2();
    return 0;
}
