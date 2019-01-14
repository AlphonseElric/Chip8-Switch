#ifndef LIST_H
#define LIST_H

#include <switch.h>

typedef struct roms{
    char name[256];
    struct roms* next;
} roms;

roms* createListEntry(char *name, roms* next);
roms* appendList(roms* head, char *name);
roms* insertList(roms* head, char *name, roms* prev);

int listLength(roms* head);
#endif /* LIST_H */
