#include <windows.h>
#include <mmsystem.h>  // Necesaria para PlaySound()
#pragma comment(lib, "winmm.lib")  // Enlaza con la librería de sonido


int main() {
    // Reproduce un sonido WAV en segundo plano
    PlaySound(TEXT("Makarov.wav"), NULL, SND_FILENAME | SND_ASYNC);
    
    // Espera para que la música siga sonando
    Sleep(100000); // espera 5 segundos
    return 0;
}

