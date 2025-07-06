#ifndef MUSIC_H
#define MUSIC_H

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void reproducirFondo() {
    PlaySound("music/Musicafondo.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void reproducirMoneda() {
    PlaySound("music/coin.wav", NULL, SND_FILENAME | SND_ASYNC);
}

#endif // MUSIC_H