
#include <iostream>
#include <ctime> //para generar valores aleatorios, en este caso, los laberintos xd.
using namespace std;

void gLabyrinth(int rows, int columns, int density) //funcion base para ajustar los valores.
{
    int **matriz;
    matriz = new int *[rows]; // esta matriz inicializara el numero de filas que tendra el laberinto.
    int walls = density * 8; // revisar si ese valor esta bien.
    int wallsd = rows * columns * density / 4; // formula para sacar las medidas que tendra el laberinto
    for (int i = 0; i < rows; i++) // para cada fila, se creara el numero de columnas
    {                                
        matriz[i] = new int[columns]; // numero de columnas.
    }
    // definicion de los valores de las columnas y filas del laberinto.
    for (int a = 0; a < rows; a++)
    {
        for (int b = 0; b < columns ; b++)
        {
            if (a == 0 || b == 0 || a == rows-1  || b == columns-1)
            {
                matriz[a][b] = 1;
            }
            else
            {
                matriz[a][b] = 0;
            }
        }
    }
    // creacion del laberinto.
    srand(time(NULL)); // se utiliza para generar nuevos valores para las filas o variables cada que el programa se ejecute.
    for (int c = 0; c < density; c++)
    {
        int cl = rand() % (columns - 4) + 2; // se coloca despues del rand esa operacion porque debe de estar dentro del laberinto, se le resta 4, para que tome valores dentro del numero de columnas.
        cl = (cl /2) * 2;
        int rw = rand() % (rows - 4) + 2;      // lo mismo para las filas.
        rw = (rw /2) * 2;
        matriz[rw][cl] = 1;
        for (int d = 0; d < walls; d++)
        {
            int mc[4] = {cl, cl, cl + 2, cl - 2}; // longitud para las columnas, los ultimos dos valores corresponden a cuando las filas se mantengan en 0 y viceversa para las columnas.
            int mr[4] = {rw + 2, rw - 2, rw, rw}; // longitud para las filas
            int ran = rand() % 4; //ran=numeros random xd

            if (matriz[mr[ran]][mc[ran]] == 0)
            {
                matriz[mr[ran]][mc[ran]] = 1;
                matriz[mr[ran] + (rw - mr[ran]) / 2][mc[ran] + (cl - mc[ran]) / 2] = 1;
            }
        }
    }
    // agregar color xd
    for (int e = 0; e < rows; e++)
    {
        for (int f = 0; f < columns; f++)
        {
            if (matriz[e][f] == 1)
            {
                char x = 178;
                cout << x <<x;
                //cout << "1 "; // si la matriz es igual a 1, mostrara 1.
            }
            if (matriz[e][f] == 0)
            {
            cout << "  "; }
        }
        cout << "\n";
    }
}
    int main()
    {
        gLabyrinth(15, 50, 150);
        return 0;
    }