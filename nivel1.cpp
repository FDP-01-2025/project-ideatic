#include <iostream>
#include <windows.h>
#include <conio.h> //se ocupa esta libreria para que se puedan leer las teclas del teclado para que el personaje se mueva
#include <string>
#include <ctime> //para generar valores aleatorios, en este caso, los laberintos xd.
using namespace std;

// funciones para mostrar en la terminal antes del laberinto

// para limpiar la terminal antes de generar el laberinto
void cleanscreen()
{
    system("cls");
}

// para esperar cierto tiempo entre cada texto que se mostrara
void waitscreen(int milliseconds)
{
    Sleep(milliseconds);
}
// para mostrar la pantalla principal
void homescreen()
{
    cout << "Welcome to Lost city :D" << endl;
    waitscreen(5000);
    cleanscreen();
}
// para mostrar el menu
void showmenu()
{
    waitscreen(1500);

    cout << "|-----------------------------|" << endl;
    cout << "|            MENU             |" << endl;
    cout << "|          1) Play            |" << endl;
    cout << "|       2) Show levels        |" << endl;
    cout << "|          3) Exit            |" << endl;
    cout << "|        4) Save game         |" << endl;
    cout << "|-----------------------------|" << endl;
    waitscreen(800);
    cleanscreen();
}
// mensaje de introduccion al nivel 1
void level1message()
{
    waitscreen(1000);
    cleanscreen();
    string message1 = "Welcome :D!";
    string message2 = "You have entered the pyramid, use the arrow keys to move forward and grab the coins.";
    string message3 = "If you collect the coins and manage to escape the labyrint by defeating the villain, you will move on to the next level.";
    string message4 = "Good luck!, see you at the next level ";
    string message5 = "...";
    string message6 = "or not :)";

    string message[] = {message1, message2, message3, message4, message5, message6};
    for (int i = 0; i < 6; i++)
    {
        cout << endl;
        for (char a : message[i])
        {
            cout << a;
            waitscreen(50);
        }
        waitscreen(800);
    }
    cleanscreen();
    waitscreen(175);
}
void loading()
{
    waitscreen(1000);
    cleanscreen();
    string message = "loading";
    string message1 = "...";
    string message2[] = {message, message1};

    for (int j = 0; j < 2; j++)
    {
        for (char c : message2[j])
        {
            cout << c;
            waitscreen(50);
        }
    }
    waitscreen(300);
    cleanscreen();
}

// mensaje de finalizacion del nivel
void finalmessagelevel1()
{
    waitscreen(1000);
    cleanscreen();
    string message = "You've completed the level";
    string message1 = "but don't declare victory yet!";
    string message2 = "Press Z to move on to the next level";
    string message3[] = {message, message1, message2};
    for (int i = 0; i < 3; i++)
    {
        cout << endl;
        for (char b : message3[i])
        {
            cout << b;
            waitscreen(50);
        }
        waitscreen(300);
    }
    waitscreen(300);
    cleanscreen();
}
void finalmessage2()
{
    waitscreen(1000);
    cleanscreen();
    string message = "You lost :(";
    string message1 = "Try again to move on to the next level";
    string message2 = "Don't get discouraged :D!";
    string message3[] = {message, message1, message2};
    for (int i = 0; i < 3; i++)
    {
        cout << endl;
        for (char b : message3[i])
        {
            cout << b;
            waitscreen(50);
        }
        waitscreen(300);
    }
    waitscreen(300);
    cleanscreen();
}
#define rows 15     // numero de filas que tendra la matriz para el laberint (altura del laberinto)
#define columns 60  // numero de columnas que tendra la matriz para formar el laberinto (paredes externas, longitud del laberinto)
#define density 150 // densidad que debe de tener el laberinto para formar las paredes internas del laberinto

void generatelab(int matriz[rows][columns]) //
{
    waitscreen(800);
    int walls = density * 6;

    for (int i = 0; i < rows; i++) // para cada fila, se creara el numero de columnas
    {
        for (int a = 0; a < columns; a++)
        {
            if (a == 0 || i == 0 || a == columns - 1 || i == rows - 1)
            {
                matriz[i][a] = 1;
            }
            else
            {
                matriz[i][a] = 0;
            }
        }
    }

    // para generar el laberinto:

    srand(time(NULL)); // para poder generar el laberinto cada cierto tiempo.

    for (int c = 0; c < density; c++)
    {
        int cl = rand() % (columns - 4) + 2; // se coloca despues del rand esa operacion porque debe de estar dentro del laberinto, se le resta 4, para que tome valores dentro del numero de columnas.
        cl = (cl / 2) * 2;
        int rw = rand() % (rows - 4) + 2; // lo mismo para las filas.
        rw = (rw / 2) * 2;
        matriz[rw][cl] = 1;

        for (int d = 0; d < walls; d++)
        {
            int mc[4] = {cl, cl, cl + 2, cl - 2}; // longitud para las columnas, los ultimos dos valores corresponden a cuando las filas se mantengan en 0 y viceversa para las columnas.
            int mr[4] = {rw + 2, rw - 2, rw, rw}; // longitud para las filas
            int ran = rand() % 4;                 // ran=numeros random xd

            if (mr[ran] >= 0 && mr[ran] < rows && mc[ran] >= 0 && mc[ran] < columns)
            {
                if (matriz[mr[ran]][mc[ran]] == 0)
                {
                    matriz[mr[ran]][mc[ran]] = 1;
                    int midrow = mr[ran] + (rw - mr[ran]) / 2;
                    int midcolumn = mc[ran] + (cl - mc[ran]) / 2;
                    if (midrow >= 0 && midrow < rows && midcolumn >= 0 && midcolumn < columns)
                    {
                        matriz[midrow][midcolumn] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matriz[i][j] == 1)
            {
                cout << "██";
            }
            else
            {
                cout << "░░";
            }
        }
        cout << endl;
    }
}


int main()
{
    srand(time(NULL));
    int lab[rows][columns];
    system("cls");
    SetConsoleOutputCP(CP_UTF8); // para poder tener el mismo formato de simbolos en las computadoras.
    // pantalla prncipal y menu
    homescreen();
    waitscreen(5000);
    showmenu();
    waitscreen(5000);
    int option;
   
    cout << "Select a option to continue: ";
    cin >> option;
    switch (option)

    {
    case 1:
        loading();
        waitscreen(1000);
        level1message();
        loading();
        generatelab(lab);

        // case 2:
    }

    // generatelab(lab);
    // finalmessagelevel1();

    return 0;
}
