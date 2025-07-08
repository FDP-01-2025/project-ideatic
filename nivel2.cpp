#include <iostream>
#include <ctime>
#include <string>
#include <windows.h>
using namespace std;

void wait(int milliseconds) {
    Sleep(milliseconds);
}

void clearScreen() {
    system("cls");
}

void darknessMessage() {
    clearScreen();

    string line1 = "You have managed to advance... but";
    string line2 = "you have opened a door that you may never be able to close.";
    string line3 = " ";
    string line4 = "The hidden awakens when the dust falls.";
    string line5 = "Only those who read in the shadows find the exit.";

    string message[] = { line1, line2, line3, line4, line5 };

    for (int l = 0; l < 5; l++) {
        cout << "\n\n";
        for (char c : message[l]) {
            cout << c;
            wait(20);
        }
        wait(800);
    }
    wait(150);
    clearScreen();
}

void showLabyrinthWarning() {
    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                         ⚠ WARNING ⚠                                4 ║\n";
    cout << "║                                                                      ║\n";
    cout << "║             This place was not made for the living.                  ║\n";
    cout << "║               The dust you step on... feeds it.                      ║\n";
    cout << "║                                                                      ║\n";
    cout << "║                 He awakens with every mistake.                       ║\n";
    cout << "║                                                                      ║\n";
    cout << "║            Every mistake doesn't take you away... it brings you closer. ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
    wait(5000);
    clearScreen();
}

void finalMessageLevel1() {
    wait(1000);
    clearScreen();
    string message = "You've completed the level";
    string message1 = "but don't declare victory yet!";
    string message2 = "Press Z to move on to the next level";
    string message3[] = {message, message1, message2};

    for (int i = 0; i < 3; i++) {
        cout << endl;
        for (char b : message3[i]) {
            cout << b;
            wait(50);
        }
        wait(300);
    }

    char key;
    cout << "\n\nPress Z to continue: ";
    while (true) {
        cin >> key;
        key = toupper(key);
        if (key == 'Z') {
            break;
        } else {
            cout << " Invalid input, please press Z to continue: ";
        }
    }

    wait(300);
    clearScreen();

    cout << "\n The next challenge begins, good luck.....\n";
    wait(1500);
}

void finalMessage2() {
    wait(1000);
    clearScreen();
    string message = "You lost :(";
    string message1 = "Try again to move on to the next level";
    string message2 = "Don't get discouraged :D!";
    string message3[] = {message, message1, message2};

    for (int i = 0; i < 3; i++) {
        cout << endl;
        for (char b : message3[i]) {
            cout << b;
            wait(50);
        }
        wait(300);
    }
    wait(300);
    clearScreen();
}

const int ROWS = 15;
const int COLUMNS = 60;
const int DENSITY = 150;

void gLabyrinthLevel2(bool won) {
    int matrix[ROWS][COLUMNS];
    int walls = DENSITY * 6;

    for (int a = 0; a < ROWS; a++) {
        for (int b = 0; b < COLUMNS; b++) {
            if (a == 0 || b == 0 || a == ROWS - 1 || b == COLUMNS - 1) {
                matrix[a][b] = 1;
            } else {
                matrix[a][b] = 0;
            }
        }
    }

    srand(time(NULL));
    for (int c = 0; c < DENSITY; c++) {
        int cl = rand() % (COLUMNS - 4) + 2;
        cl = (cl / 2) * 2;
        int rw = rand() % (ROWS - 4) + 2;
        rw = (rw / 2) * 2;
        matrix[rw][cl] = 1;

        for (int d = 0; d < walls; d++) {
            int mc[4] = {cl, cl, cl + 2, cl - 2};
            int mr[4] = {rw + 2, rw - 2, rw, rw};
            int ran = rand() % 4;

            if (mr[ran] >= 0 && mr[ran] < ROWS && mc[ran] >= 0 && mc[ran] < COLUMNS) {
                if (matrix[mr[ran]][mc[ran]] == 0) {
                    matrix[mr[ran]][mc[ran]] = 1;
                    int midrow = mr[ran] + (rw - mr[ran]) / 2;
                    int midcolum = mc[ran] + (cl - mc[ran]) / 2;
                    if (midrow >= 0 && midrow < ROWS && midcolum >= 0 && midcolum < COLUMNS)
                        matrix[midrow][midcolum] = 1;
                }
            }
        }
    }

    for (int e = 0; e < ROWS; e++) {
        for (int f = 0; f < COLUMNS; f++) {
            if (matrix[e][f] == 1) {
                cout << "██";
            } else {
                cout << "░░";
            }
        }
        cout << "\n";
    }

    wait(1500);

    if (won) {
        finalMessageLevel1();
    } else {
        finalMessage2();
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    darknessMessage();
    showLabyrinthWarning();

    // simulates whether the player wins or loses (randomly)
    srand(time(NULL));
    bool won = rand() % 2 == 0; // true or false randomly

    gLabyrinthLevel2(won);

    return 0;
}
