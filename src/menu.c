#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <switch.h>

#include "list.h"
#include "menu.h"
#include "error.h"

int currentIdx = 0;
roms *currentHead = NULL;
char *currentDir = "/";

void listRoms(roms* head)
{
    consoleClear();
    printf("CHIP-8 EMULATOR by AlphonseElric\n\nPlease select a ROM:\n\n");

    roms* current = head;
    int idx = 0;
    while(current->next != NULL)
    {
        if(idx == currentIdx)
          printf("==>%s\n", current->name);
        else
          printf("%s\n", current->name);
        current = current->next;
        idx++;
    }
}

roms* getRoms(DIR* directory)
{
    struct dirent* entry;

    roms *head = createListEntry("..", NULL);
    roms *current = NULL;

    while((entry = readdir(directory)))
    {
        if(strstr(entry->d_name, ".ch8") != NULL || strstr(entry->d_name, ".bin") != NULL || strstr(entry->d_name, ".rom") != NULL)
        {
            head = appendList(head, entry->d_name);
        }
        else if(entry->d_type == DT_DIR)
        {
            char* dirName = (char*)malloc(256);
            if(strlen(entry->d_name) <= 256)
            {
                strcpy(dirName, entry->d_name);
                strcat(dirName, "/");
            }

            //TODO: Organize directories alphabetically.
            if(current != NULL)
                head = insertList(head, dirName, current);
            else
                head = insertList(head, dirName, head);
            current = head;
        }
    }

    appendList(head, "end");
    currentHead = head;

    return head;
}

void updateList()
{
    if(!currentIdx)
    {
      char *prevDir = strrchr(currentDir, '/');
      if(prevDir == currentDir)
      {
        currentDir = "/"
      }
    }

    roms *current = currentHead;
    int idx = 0;

    while(idx <= currentIdx)
    {
        current = current->next;
        idx++;
    }

    if(strrchr(currentDir, '/') == currentDir)
    {
        strcat(currentDir, current->name);
    }
    else
    {
        strcat(currentDir, "/");
        strcat(currentDir, current->name);
    }

    DIR *directory = opendir(currentDir);
    if(!directory)
        printError("Failed to open directory. Press any button to exit.");

    listRoms(getRoms(directory));
}

void updateSelection(int downUp)
{
    if(downUp && (currentIdx + 2) <= listLength(currentHead))
    {
        currentIdx++;
        listRoms(currentHead);
    }
    else if(!downUp && currentIdx >= 1)
    {
        currentIdx--;
        listRoms(currentHead);
    }
}

void initRomList()
{
    DIR *directory = opendir("/");
    if(directory == NULL)
        printError("Failed to open SD card. Press any button to exit.");

    listRoms(getRoms(directory));
}
