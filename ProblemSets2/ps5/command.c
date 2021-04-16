#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch){
    if(!name || !description) return NULL;
    if(strlen(name)<1 || strlen(description)<1) return NULL;
    struct command * new_command = malloc(sizeof(*new_command));
    new_command->name = malloc(strlen(name) +1);
    new_command->description = malloc(strlen(description)+1);
    memcpy(new_command->name, name, strlen(name)+1);
    memcpy(new_command->description, description, strlen(description)+1);
    new_command->nmatch = 0;
    if(nmatch){
        new_command->nmatch = nmatch;
    }

    new_command->groups = NULL;
    if(nmatch>0){
        new_command->groups = malloc(sizeof(char *)*nmatch);
        for(int i = 0; i < nmatch; i++){
            new_command->groups[i] = NULL;
        }
    }
    if(pattern){

        if(regcomp(&new_command->preg, pattern, REG_ICASE | REG_EXTENDED)){
            fprintf(stderr, "Regular expression could not be compiled.\n");
            exit(EXIT_FAILURE);
        }
        
    }
    
    return new_command;

}
// (^\s*help\s*$|^\s*h\s*$)

struct command* destroy_command(struct command* command){
    if(command){
        
        regfree(&command->preg);
        if(command->nmatch > 0){
            for(int i = 0; i < command->nmatch; i++){

                if(command->groups[i]) free(command->groups[i]);
            }
            
            free(command->groups);
        }

        free(command->description);
        free(command->name);
        free(command);

    }
    return NULL;
}