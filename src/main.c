#include <stdio.h>
#include <switch.h>

#include "menu.h"

int main(int argc, char const *argv[])
{
    gfxInitDefault();
    consoleInit(NULL);

    printf("CHIP-8 EMULATOR by AlphonseElric\n\nPlease select a ROM:\n\n");

    initRomList();

    while(appletMainLoop())
    {
        hidScanInput();
        u64 keyDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if(keyDown & KEY_PLUS)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
    }

    gfxExit();
    return 0;
}
