#include <stdio.h>
#include <switch.h>

#include "error.h"

void printError(const char* err)
{
    consoleClear();
    
    printf(err);
    while(!hidKeysDown(CONTROLLER_P1_AUTO))
    {
        continue;
    }

    appletExit();
}
