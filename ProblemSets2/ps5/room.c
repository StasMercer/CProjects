#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "room.h"
#include "container.h"
#include "item.h"

struct room* create_room(char *name, char *description){

    if(!name || !description) return NULL;
    if(strlen(name)<1 || strlen(description)<1) return NULL;
    struct room * new_room = malloc(sizeof(*new_room));
    
    new_room->name = malloc(strlen(name) +1);
    new_room->description = malloc(strlen(description)+1);
    memcpy(new_room->name, name, strlen(name)+1);
    memcpy(new_room->description, description, strlen(description)+1);
  
    new_room->items = NULL;
    new_room->east = NULL;
    new_room->south = NULL;
    new_room->west = NULL;
    new_room->north = NULL;

    return new_room;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
    if(room){
        room->north = north;
        room->south = south;
        room->east = east;
        room->west = west;
    }

}

void show_room(const struct room* room){

    printf("---------------\n");
    printf("%s\n", room->name);
    printf("%s\n", room->description);
    printf("Exits:\n");
    if(room->east) printf("  East\n");
    if(room->west) printf("  West\n");
    if(room->north) printf("  North\n");
    if(room->south) printf("  South\n");
    printf("Items:\n");
    struct container * ptr = room->items;
 
    while(ptr){
        printf("  %s\n", ptr->item->name);
        ptr = ptr->next;
    }
    printf("---------------\n");
    printf("\n");
}

struct room* destroy_room(struct room* room){
	if(!room) return NULL;
    free(room->name);
    free(room->description);
	free(room);
	return NULL;
}

void add_item_to_room(struct room* room, struct item* item){
	if(room && item){
		room->items = create_container(room->items, ITEM, item);		
	}
}

struct item* get_item_from_room(const struct room * room, const char* name){
	if(!room || !name) return NULL;
	if(strlen(name) < 1) return NULL;

	return get_from_container_by_name(room->items, name);

}

void delete_item_from_room(struct room* room, struct item* item){
	if(room && item){
		room->items = remove_container(room->items, item);
	}
}