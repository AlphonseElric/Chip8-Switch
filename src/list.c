#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include "error.h"
#include "list.h"

roms* createListEntry(char *name, roms* next)
{
    roms *new_rom = (roms*)malloc(sizeof(roms));
    if(new_rom == NULL)
    {
        printError("Failed to allocate memory. Press any button to exit.");
    }
    if(strlen(name) < 256)
        strcpy(new_rom->name, name);
    else
        memmove(new_rom->name, name, 256);
    new_rom->next = next;

    return new_rom;
}

roms* appendList(roms* head, char *name)
{
    roms *cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    roms *new_rom = createListEntry(name, NULL);
    cursor->next = new_rom;

    return head;
}

roms* insertList(roms* head, char *name, roms* prev)
{
    roms *cursor = head;
    while(cursor != prev)
        cursor = cursor->next;

    if(cursor != NULL)
    {
        roms *new_rom = createListEntry(name, cursor->next);
        cursor->next = new_rom;
        return head;
    }
    else
    {
        return NULL;
    }
}

int listLength(roms *head)
{
    roms *cursor = head;
    int length = 0;
    while (cursor->next != NULL) {
        length++;
        cursor = cursor->next;
    }

    return length;
}
