#include <stdio.h>
#include <switch.h>

#include "menu.h"
#include "error.h"

int main(int argc, char const *argv[])
{
    consoleInit(NULL);

    initRomList();

    while(appletMainLoop())
    {
        hidScanInput();
        u64 keyDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if(keyDown & KEY_PLUS)
            break;
        else if(keyDown & KEY_DUP)
            updateSelection(0);
        else if(keyDown & KEY_DDOWN)
            updateSelection(1);
        else if (keyDown & KEY_A)
            updateList();
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
