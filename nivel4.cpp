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
    string lin1 = "CONGRATULATIONS, YOU'VE REACHED THE FINAL GAME!";
    string lin2 = "But that doesn't guarantee victory....";
    string lin3 = "Only those who understand the purpose of each tool can reach their destination";
    string lin4 = "Good luck :)";
    string message[] = { lin1, lin2, lin3, lin4 };

    for (int l = 0; l < 4; l++) {
        cout << "\n\n";
        for (char p : message[l]) {
            cout << p;
            wait(30);
        }
        wait(800);
    }
    wait(150);
    clearScreen();
}

void showLabyrinthWarning() {
    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                 ⚠ ⚠ ⚠  FINAL WARNING ⚠ ⚠ ⚠                          ║\n";
    cout << "║                                                                      ║\n";
    cout << "║             You may win… or lose everything in seconds.              ║\n";
    cout << "║           If you fail... you’ll be just another who never returned.  ║\n";
    cout << "║                                                                      ║\n";
    cout << "║               Are you ready to try?                                  ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
    wait(5000);
    clearScreen();
}

void finalMessageLevel1() {
    wait(1000);
    clearScreen();

    string msg1 = "CONGRATULATIONS, YOU'VE REACHED THE END!";
    string msg2 = "You are one of the few who overcame all the challenges.";
    string msg3 = "You’ve won what you fought so hard for";

    string messages[] = {msg1, msg2, msg3};

    for (string line : messages) {
        cout << "\n";
        for (char c : line) {
            cout << c;
            wait(50);
        }
        wait(800);
        clearScreen();
    }

    // Rating
    cout << "\n\nWe want your feedback. What did you think of this experience?\n";
    cout << "Rate from 1 to 5 stars: ";

    int stars;
    while (true) {
        cin >> stars;
        if (cin.fail() || stars < 1 || stars > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number between 1 and 5: ";
        } else {
            break;
        }
    }

    cout << "\nShowing your rating";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        wait(500);
    }

    cout << "\nYour rating was: ";
    for (int i = 0; i < stars; i++) {
        cout << "★ ";
        wait(300);
    }

    // Final farewell message
    clearScreen();
    wait(1200);
    cout << "\n\nThank you for playing, come back anytime.\n";
    wait(1500);
    clearScreen();
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

void gLabyrinthLevel4(bool won) {
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

    bool won = true; // Change to false to test loss
    gLabyrinthLevel4(won);

    return 0;
}
