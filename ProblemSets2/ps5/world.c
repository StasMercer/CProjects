#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "world.h"
#include "container.h"
#include "room.h"
#include "item.h"

struct container* create_world(){

    struct room * r1 = create_room("first room", "your initial point");
    struct room * r2 = create_room("house of plesure", "try to satisfy me");
    struct room * r3 = create_room("house of plesur1", "try to satisfy me");
    struct room * r4 = create_room("house of plesu2", "try to satisfy me");
    struct room * r5 = create_room("house of ples3", "try to satisfy me");
    struct room * r6 = create_room("house of ple4", "try to satisfy me");
    struct room * r7 = create_room("house of p5", "try to satisfy me");
    struct room * r8 = create_room("house of 6", "try to satisfy me");
    struct room * r9 = create_room("house of7", "try to satisfy me");
    struct room * r10 = create_room("house o8", "try to satisfy me");
    struct room * r11 = create_room("house 9", "try to satisfy me");
    struct room * r12 = create_room("house10", "try to satisfy me");
    struct room * r13 = create_room("hous11", "try to satisfy me");
    struct room * r14 = create_room("house of plesure2", "try to satisfy me");
    struct room * r15 = create_room("house of plesure3", "try to satisfy me");
    struct room * r16 = create_room("house of plesure4", "try to satisfy me");

    struct container * world = NULL;
    world = add_room_to_world(NULL, r1);
    add_room_to_world(world, r2);
    add_room_to_world(world, r3);
    add_room_to_world(world, r4);
    add_room_to_world(world, r5);
    add_room_to_world(world, r6);
    add_room_to_world(world, r7);
    add_room_to_world(world, r8);
    add_room_to_world(world, r9);
    add_room_to_world(world, r10);
    add_room_to_world(world, r11);
    add_room_to_world(world, r12);
    add_room_to_world(world, r13);
    add_room_to_world(world, r14);
    add_room_to_world(world, r15);
    add_room_to_world(world, r16);
    set_exits_from_room(r1, r2, r3, r4, r5);
    set_exits_from_room(r5, r6, r7, r8, r9);
    set_exits_from_room(r9, r10, r11, r12, r13);
    set_exits_from_room(r13, r14, r15, r16, NULL);
    
    struct item * rock = create_item("just a rock", "i kiil you", EXAMINABLE | MOVABLE);
    struct item * i2 = create_item("item", "i kiil you", EXAMINABLE | MOVABLE);
    struct item * i3 = create_item("kluch", "i kiil you", EXAMINABLE | MOVABLE);
    struct item * i4 = create_item("itemm", "i kiil you", EXAMINABLE | MOVABLE);
    struct item * i5 = create_item("itemmmm", "i kiil you", EXAMINABLE | MOVABLE);
    add_item_to_room(r1, rock);
    add_item_to_room(r2, i2);
    add_item_to_room(r3, i3);
    add_item_to_room(r4, i4);
    add_item_to_room(r5, i5);
    return world;

}


struct container* add_room_to_world(struct container* world, struct room* room){
    if(!room) return NULL;

    if(!world){
        world = create_container(NULL, ROOM, room);
        
    }else{
        if(get_from_container_by_name(world, room->name) == NULL){
            create_container(world, ROOM, room);
        }else{
            return NULL;
        }
    }

    return world;
}

struct container* destroy_world(struct container* world){
    if(!world) return NULL;
    struct container * ptr = world;
    
    while(ptr){
        if(ptr->room){
            if(ptr->room->items) ptr->room->items = destroy_containers(ptr->room->items);
            
        }
        ptr = ptr->next;
    }
    
    destroy_containers(world);
    

    return NULL;
}

struct room* get_room(struct container* world, char* name){
    if(!world) return NULL;
    return get_from_container_by_name(world, name);
}