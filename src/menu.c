#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <switch.h>

#include "list.h"
#include "menu.h"
#include "error.h"

void listRoms(roms* head)
{
    roms* current = head;
    while(current->next != NULL)
    {
        printf("%s\n", current->name);
        current = current->next;
    }
}

roms* getRoms(DIR* directory)
{
    struct dirent* entry;

    roms *backButton = createListEntry("..", NULL);
    roms *currentDir = NULL;
    
    while((entry = readdir(directory)))
    {
        if(strstr(entry->d_name, ".ch8") != NULL || strstr(entry->d_name, ".bin") != NULL || strstr(entry->d_name, ".rom") != NULL)
        {
            backButton = appendList(backButton, entry->d_name);
        }
        else if(entry->d_type == DT_DIR)
        {
            char* dirName = (char*)malloc(256);
            if(strlen(entry->d_name) < 50)
            {
                strcpy(dirName, entry->d_name);
                strcat(dirName, "/");
            }
            else
            {
                memmove(dirName, entry->d_name, 45);
                strcat(dirName, ".../");
            }

            if(currentDir != NULL)
                backButton = insertList(backButton, dirName, currentDir);
            else
                backButton = insertList(backButton, dirName, backButton);
            currentDir = backButton;
        }
    }
    
    appendList(backButton, "end");

    return backButton;
}

void initRomList()
{
    DIR* directory = opendir("/");
    if(directory == NULL)
    {
        printError("Failed to open SD card. Press any button to exit.");
    }

    roms* head = getRoms(directory);
    listRoms(head);
}