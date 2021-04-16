#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "item.h"
#include "container.h"


struct item* create_item(char* name, char* description, unsigned int properties){

    if(!name || !description) return NULL;
    if(strlen(name)<1 || strlen(description)<1) return NULL;

    struct item * new_item = malloc(sizeof(*new_item));
    
    new_item->name = malloc(strlen(name) +1);
    new_item->description = malloc(strlen(description)+1);
    memcpy(new_item->name, name, strlen(name)+1);
    memcpy(new_item->description, description, strlen(description)+1);
    new_item->properties = properties;
    return new_item;
}


struct item* destroy_item(struct item* item){
    if(item){
        free(item->name);
        free(item->description);
        free(item);
    }
    return NULL;
}