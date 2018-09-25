#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

#include "error.h"
#include "list.h"

roms* createListEntry(char name[FS_MAX_PATH], roms* next)
{
    roms *new_rom = (roms*)malloc(sizeof(roms));
    if(new_rom == NULL)
    {
        printError("Failed to allocate memory. Press any button to exit.");
    }
    strncpy(new_rom->name, name, sizeof(&name));
    strcat(new_rom->name, "\0");
    new_rom->next = next;

    return new_rom;
}

roms* appendList(roms* head, char name[FS_MAX_PATH])
{
    roms *cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;
    
    roms *new_rom = createListEntry(name, NULL);
    cursor->next = new_rom;

    return head;
}

roms* insertList(roms* head, char name[FS_MAX_PATH], roms* prev)
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