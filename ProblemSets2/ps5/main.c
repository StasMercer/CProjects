#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "item.h"
#include "command.h"
#include "world.h"
#include "backpack.h"
#include "parser.h"
#include "game.h"

void print_containers(struct container *first)
{

    struct container *ptr = first;
    printf("....containers start....\n");
    while (ptr)
    {
        switch (ptr->type)
        {
        case ROOM:
        {
            if (ptr->room)
            {
                show_room(ptr->room);
            }
            break;
        }
        case ITEM:
        {

            if (ptr->item)
                printf("itemname = %s\n", ptr->item->name);
            break;
        }
        case COMMAND:
        {

            if (ptr->command)
                printf("commandname = %s\n", ptr->command->name);
            break;
        }
        case TEXT:
        {
            if (ptr->text)
                printf("text = %s\n", ptr->text);
            break;
        }
        default:
            break;
        }

        printf("      ↓↓   \n");
        ptr = ptr->next;
    }
    printf("...containers end...\n");
}

int main()
{
    
    struct parser* parser = create_parser();
    char* input = "rozhliadni sa";
    printf("parser, input != NULL:%s\n", parse_input(parser, input)->name);
    destroy_parser(parser);
    struct game * game = create_game();
    print_containers(game->world);
    play_game(game);
    destroy_game(game);

    if (0)
    {   
        struct item *rem_item = get_item_from_room(NULL, "rock");
        delete_item_from_room(NULL, rem_item);
        show_room(get_room(NULL, "first room"));
    }


    
    struct backpack *backpack = create_backpack(5);
    struct item *item = create_item("STOLICKA", "Drevena stolicka, mozno posluzi ako podpera.", EXAMINABLE | MOVABLE);
    add_item_to_backpack(backpack, item);
    struct item *backpack_item = get_item_from_backpack(backpack, item->name);
    printf("backpack_item != NULL:%d\n", backpack_item != NULL);
    printf("backpack_item->name: %s\n", backpack_item->name);

    delete_item_from_backpack(backpack, backpack_item);
    destroy_backpack(backpack);
    destroy_item(item);

    if (0)
    {
        struct command *cmd = create_command("help", "just press it", "(^\\s*help\\s*$|^\\s*h\\s*$)", 1);
        printf("%s\n", cmd->name);
        cmd = destroy_command(cmd);
        printf("%ld\n", sizeof(*cmd));
    }


    return 0;
}
