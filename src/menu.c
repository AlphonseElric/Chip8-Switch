#include <stdio.h>
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
    current = current->next;
    printf("%s\n", current->name);
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
            char* dirName = "\0";
            if(sizeof(&entry->d_name) < 50)
            {
                strcpy(dirName, entry->d_name);
                strcat(dirName, "/");
            }
            else
            {
                memmove(dirName, entry->d_name, 47);
                strcat(dirName, "../");
            }

            if(currentDir != NULL)
                backButton = insertList(backButton, dirName, currentDir);
            else
                backButton = insertList(backButton, dirName, backButton);
            currentDir = backButton;
        }
    }

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