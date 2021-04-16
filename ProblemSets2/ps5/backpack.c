#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "backpack.h"
#include "item.h"
#include "container.h"

struct backpack* create_backpack(const int capacity){

    struct backpack * new_backpack = malloc(sizeof(*new_backpack));
    new_backpack->capacity = capacity;
    new_backpack->size = 0;
    new_backpack->items = NULL;
    return new_backpack;
}


struct backpack* destroy_backpack(struct backpack* backpack){
    if(backpack){
        free(backpack);
    }
    return NULL;
}

bool add_item_to_backpack(struct backpack * backpack, struct item * item){
    if(!backpack || !item) return false;
    if(!(item->properties & MOVABLE)) return false;
    if((backpack->size + 1) > backpack->capacity) return false;
    backpack->size += 1;
    if(backpack->items == NULL){
        backpack->items = create_container(NULL, ITEM,  item);
    }else{
        create_container(backpack->items, ITEM,  item);
    }
    
    return true;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
    if(!backpack || !name) return NULL;
    if(strlen(name) < 1) return NULL;
    return get_from_container_by_name(backpack->items, name);

}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if(backpack && item){
        backpack->items = remove_container(backpack->items, item);
        backpack->size -= 1;
    }
}

