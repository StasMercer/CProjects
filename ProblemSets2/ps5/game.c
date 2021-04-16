#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "world.h"
#include "container.h"
#include "room.h"
#include "item.h"
#include "game.h"
#include "backpack.h"

struct game* create_game(){

    struct game * game = malloc(sizeof(*game));
    game->parser = create_parser();
    game->world = create_world();
    game->state = PLAYING;
    game->backpack = create_backpack(4);
    game->current_room = game->world->room;
    printf("%s\n", game->world->room->name);
    return game;
}

struct game* destroy_game(struct game* game){
    if(game){

        destroy_parser(game->parser);
        destroy_backpack(game->backpack);
        destroy_world(game->world);
        free(game);
    }

    return NULL;
}

void play_game(struct game* game){
    char buff[100] = "";
    struct command * cmd = NULL;
    while(game->state == PLAYING){
        
        fgets(buff, 100, stdin);
        
        cmd = parse_input(game->parser, buff);
        execute_command(game, cmd);
        if(game->state == RESTART){
            game->current_room = game->world->room;
            game->parser->history = destroy_containers(game->parser->history);
            game->state = PLAYING;
        }
        
    }



}


void execute_command(struct game* game, struct command* command){
    if(!command) printf("command not found(\n");
    if(game && command){
        
        if(!strcmp(command->name, "verzia")){
            printf("stas mercer v0.1\n");
            
        }

        if(!strcmp(command->name, "koniec")){
             printf("game over\n");
             game->state = GAMEOVER;
             
        }

        if(!strcmp(command->name, "juh")){
            if(game->current_room->south){
                game->current_room = game->current_room->south;
                // if(!game->parser->history){
                //     game->parser->history = create_container(NULL, COMMAND, command);
                // }else{
                //     create_container(game->parser->history, COMMAND, command);
                // }
            }else{
                printf("Miestnost ne existuje\n");
            }
             
             
        }

        if(!strcmp(command->name, "sever")){
            if(game->current_room->north){
                game->current_room = game->current_room->north;
                // if(!game->parser->history){
                //     game->parser->history = create_container(NULL, COMMAND, command);
                // }else{
                //     create_container(game->parser->history, COMMAND, command);
                // }
            }else{
                printf("Miestnost ne existuje\n");
            }
             
             
        }

        if(!strcmp(command->name, "zapad")){
            if(game->current_room->west){
                game->current_room = game->current_room->west;
                // if(!game->parser->history){
                //     game->parser->history = create_container(NULL, COMMAND, command);
                // }else{
                //     create_container(game->parser->history, COMMAND, command);
                // }
            }else{
                printf("Miestnost ne existuje\n");
            }
             
             
        }

        if(!strcmp(command->name, "vychod")){
            if(game->current_room->east){
                game->current_room = game->current_room->east;
                // if(!game->parser->history){
                //     game->parser->history = create_container(NULL, COMMAND, command);
                // }else{
                //     create_container(game->parser->history, COMMAND, command);
                // }
            }else{
                printf("Miestnost ne existuje\n");
            }
             
             
        }

        if(!strcmp(command->name, "rozhliadni sa")){
            show_room(game->current_room);
        }

        if(!strcmp(command->name, "prikazy")){
            struct container * cmds = game->parser->commands;
            while(cmds){
                printf("%s\n", cmds->command->name);
                printf("%s\n", cmds->command->description);
                cmds = cmds->next;
            }
        }

        if(!strcmp(command->name, "restart")){
            game->state = RESTART;
        }

        
        if(!strcmp(command->name, "o hre")){
            printf("%s\n", command->description);
        }

        if(!strcmp(command->name, "vezmi")){
            if(command->groups[2]){
                struct item * item = get_item_from_room(game->current_room, command->groups[2]);
                if(item){
                    add_item_to_backpack(game->backpack, item);
                    delete_item_from_room(game->current_room, item);
                    // if(!game->parser->history){
                    //     game->parser->history = create_container(NULL, COMMAND, command);
                    // }else{
                    //     create_container(game->parser->history, COMMAND, command);
                    // }

                }else{
                    printf("taky item ne existuje\n");
                }

            }else{
                printf("Co vziat?\n");
            }
             
             
        }

           
    }


}