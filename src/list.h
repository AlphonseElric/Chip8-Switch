#ifndef LIST_H
#define LIST_H

#include <switch.h>

typedef struct roms{
    char name[FS_MAX_PATH];
    struct roms* next;
} roms;

roms* createListEntry(char name[FS_MAX_PATH], roms* next);
roms* appendList(roms* head, char name[FS_MAX_PATH]);
roms* insertList(roms* head, char name[FS_MAX_PATH], roms* prev);

#endif /* LIST_H */