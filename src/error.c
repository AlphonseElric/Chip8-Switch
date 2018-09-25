#include <stdio.h>
#include <switch.h>

#include "error.h"

void printError(const char* err)
{
    printf(err);
    while(hidKeysDown(CONTROLLER_P1_AUTO) == 0)
    {
        continue;
    }

    appletExit();
}