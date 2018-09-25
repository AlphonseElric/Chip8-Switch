#include <stdio.h>
#include <string.h>
#include <switch.h>

#include "list.h"
#include "menu.h"
#include "error.h"

void listRoms(roms* head)
{
    roms* current = head;
    while(current->next != NULL)
    {
        printf("%s", current->name);
        current = current->next;
    }
    current = current->next;
    printf("%s", current->name);
}

roms* getRoms(FsDir* directory)
{
    FsDirectoryEntry* entry;

    roms *backButton = createListEntry("..", NULL);
    roms *currentDir;
    
    while(entry = readdir(directory))
    {
        if(strstr(entry->name, ".ch8") != NULL || strstr(entry->name, ".bin") != NULL || strstr(entry->name, ".rom") != NULL)
        {
            appendList(backButton, entry->name);
        }
        else if(entry->type == 0)
        {
            char* dirName;
            strcpy(dirName, entry->name);
            strcat(dirName, '/');
            if(currentDir != NULL)
                insertList(backButton, dirName, currentDir);
            else
                insertList(backButton, dirName, backButton);
        }
    }

    return backButton;
}

void initRomList()
{
    FsDir* directory = opendir("/");
    if(directory == NULL)
    {
        printError("Failed to open SD card. Press any button to exit.");
    }

    roms* head = getRoms(directory);
    listRoms(head);
}