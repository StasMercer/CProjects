#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>

#include "container.h"
#include "room.h"
#include "command.h"
#include "item.h"


struct container* create_container(struct container* first, enum container_type type, void* entry){
    if(!entry) return NULL;
    struct container * ptr = NULL;
    struct container * new_container = NULL;
    if(first){

        if(first->type != type) return NULL;
        ptr = first;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        new_container = malloc(sizeof(*new_container));
        ptr->next = new_container;
        //printf("%p %p\n", ptr->next, new_container);
        
    }else{
        new_container = malloc(sizeof(*new_container));
        
    }
    
        
    new_container->type = type;
    switch (type){
        case ROOM: new_container->room = entry; break;
        case ITEM: new_container->item = entry; break;
        case COMMAND: new_container->command = entry; break;
        case TEXT: new_container->text = entry; break;
        default: break;
    }
    new_container->next = NULL;
    
    return new_container;
}

struct container* destroy_containers(struct container* first){
    if(!first) return NULL;
    if(first->next) destroy_containers(first->next);
    
    switch (first->type){
        case ROOM:{

         if(first->room) first->room = destroy_room(first->room); 
         break;
        }
        case ITEM: {

         if(first->item) destroy_item(first->item); 
         break;
        }
        case COMMAND: {

         if(first->command) destroy_command(first->command); 
         break;
        }
        case TEXT: {

         if(first->text) free(first->text); 
         break;
        }
        default: break;
    }
    
    free(first);
    
    return NULL;
}

void * get_from_container_by_name(struct container * first, const char * name)
{
    if (!first || !name)
        return NULL;

    regex_t regex;
    if (regcomp(&regex, name, REG_ICASE | REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Regular expression could not be compiled.\n");
        exit(EXIT_FAILURE);
    }

    struct container *ptr = first;

    enum container_type type = first->type;
    while (ptr)
    {
        switch (type)
        {
            case ROOM:{

                int result = regexec(&regex, ptr->room->name, 0, NULL, 0);
                
                if (result != REG_NOMATCH){
                    regfree(&regex);
                    return ptr->room;
                }
                break;
            }
                
            case ITEM:{

                int result = regexec(&regex, ptr->item->name, 0, NULL, 0);
                
                if (result != REG_NOMATCH){
                    regfree(&regex);
                    return ptr->item;
                }
                break;
            }
            case COMMAND:{

                int result = regexec(&regex, ptr->command->name, 0, NULL, 0);
                
                if (result != REG_NOMATCH){
                    regfree(&regex);
                    return ptr->command;
                }
                break;
            }
            case TEXT:{

                int result = regexec(&regex, ptr->text, 0, NULL, 0);
                
                if (result != REG_NOMATCH){
                    regfree(&regex);
                    return ptr->text;
                }
                break;
            }
            default:
                break;
        }
        ptr = ptr->next;
    }
    regfree(&regex);
    return NULL;
}

struct container * remove_container(struct container * first, void * entry){
    if(!first) return NULL;
    struct container * new_first = NULL;
    switch(first->type){
        case ROOM:{
            if(first->room == entry){
                printf("here\n");
                new_first = first->next;
                free(first);
                return(new_first);
            }
            break;
        }
        case ITEM:{
            if(first->item == entry){
                new_first = first->next;
                free(first);
                return(new_first);
            }
            break;
        }
        case COMMAND:{
            if(first->command == entry){
                new_first = first->next;
                free(first);
                return(new_first);
            }
            break;
        }
        case TEXT:{
            if(first->text == entry){
                new_first = first->next;
                free(first);
                return(new_first);
            }
            break;
        }
            
    }
    
    struct container * ptr  = first;
    struct container * prev = first;
    while (ptr)
    {
       switch (first->type){
            case ROOM: {
                if(ptr->room == entry){
                    
                    prev->next = ptr->next;
                    free(ptr);
                    return first;
                }
                break;
            }
            case ITEM:{
                if(ptr->item == entry){
                    
                    prev->next = ptr->next;
                    free(ptr);
                    return first;
                }
                break;
            }
            case COMMAND: {
                if(ptr->command == entry){
                    
                    prev->next = ptr->next;
                    free(ptr);
                    return first;
                }
                break;
            }
            case TEXT:{
                if(ptr->text == entry){
                    
                    prev->next = ptr->next;
                    free(ptr);
                    return first;
                }
                break;
            }
            default: break;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    
    
    return first;

}
