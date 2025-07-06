#include <curses.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void reproducirFondo() {
    PlaySound("music/exploration.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void reproducirVictoria() {
    PlaySound(NULL, 0, 0); // Detiene fondo
    PlaySound("music/Ganaste.wav", NULL, SND_FILENAME | SND_SYNC);
}