#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "container.h"
#include "parser.h"
#include "command.h"

char * trim(char * str){
    int left = 0;
    int right = (int)strlen(str);
    for(int i = 0; i < strlen(str); i++){
        if(isspace(str[i])){
            left++;

        }else{break;}
    }
    
    for(int i = (int)strlen(str) - 1; i >= 0; i--){
        if(isspace(str[i])){
            right --;

        } else{break;}
    }

    char * res = malloc((size_t)(right-left+1));
    
    int k = 0;
    for(int i = left; i < right; i++){
        res[k] = str[i];
        k++;
    }
    res[k] = '\0';
    return res;
}

struct parser *create_parser()
{

    struct parser *parser = malloc(sizeof(*parser));

    parser->commands = create_container(NULL, COMMAND, create_command("koniec", "ukonci hru", "^(quit|exit|koniec)$", 1));
    create_container(parser->commands, COMMAND, create_command("sever", "prejs na sever", "^(S|sever)$", 1));
    create_container(parser->commands, COMMAND, create_command("juh", "prejst na juh", "^(J|juh)$", 1));
    create_container(parser->commands, COMMAND, create_command("vychod", "prejst na vychod", "^(V|vychod)$", 1));
    create_container(parser->commands, COMMAND, create_command("zapad", "prejst na zapad", "^(Z|ZAPAD)$", 1));
    create_container(parser->commands, COMMAND, create_command("rozhliadni sa", "ukazat miestnost", "^(rozhliadni\\ssa)$", 1));
    create_container(parser->commands, COMMAND, create_command("verzia", "zobrazit versiu hry", "^(verzia)$", 1));
    create_container(parser->commands, COMMAND, create_command("restart", "restart hry", "^(restart)$", 1));
    create_container(parser->commands, COMMAND, create_command("o hre", "kde bolo tam bolo", "^(o\\shre|about)$", 1));
    create_container(parser->commands, COMMAND, create_command("vezmi", "zoberie predmet", "^(vezmi)\\s(\\w+)$", 3));
    create_container(parser->commands, COMMAND, create_command("poloz", "polozi predmet do miestnosti", "^(poloz)\\s(\\w+)$", 3));
    create_container(parser->commands, COMMAND, create_command("inventar", "zobrazi obsah batohu", "^(inventar|i)$", 1));
    create_container(parser->commands, COMMAND, create_command("pouzi", "pouzi predmet z batohu/miestnosti", "^(pouzi)\\s(\\w+)$", 3));
    create_container(parser->commands, COMMAND, create_command("preskumaj", "vipise obsah predmet z batohu/miestnosti", "^(PRESKUMAJ)\\s(\\w+)$", 3));
    create_container(parser->commands, COMMAND, create_command("uloz", "ulozit hru", "^(ULOZ|SAVE)\\s(\\w+)$", 3));
    create_container(parser->commands, COMMAND, create_command("nahraj", "nahraj hru", "^(nahraj|load)\\s(\\w+)$", 3));
    create_container(parser->commands, COMMAND, create_command("prikazy", "zobrazi prikazy", "^(prikazy)$", 1));

    parser->history = NULL;
    return parser;
}

struct parser *destroy_parser(struct parser *parser)
{
    if (parser)
    {
        destroy_containers(parser->commands);
        
        free(parser);
    }
    return NULL;
}

struct command *parse_input(struct parser *parser, char *input)
{
    if (!parser || !input) return NULL;
    if (strlen(input) < 1) return NULL;

    struct container *ptr = parser->commands;
    char * trimed = trim(input);
    while (ptr)
    {
        
        
        regmatch_t groups2[ptr->command->nmatch];
        int r = regexec(&ptr->command->preg, trimed, ptr->command->nmatch, groups2, 0);
        //printf("%s\n", ptr->command->name);
        //printf("%ld\n", ptr->command->nmatch);
        if (r != REG_NOMATCH)
        {
            
            for (int i = 0; i < ptr->command->nmatch; i++)
            {
                if (groups2[i].rm_so == -1)
                    break;

                int len = groups2[i].rm_eo - groups2[i].rm_so + 1;
                if(!ptr->command->groups[i]){

                    ptr->command->groups[i] = malloc((size_t)len);
                }
                int k = 0;
                for (int j = groups2[i].rm_so; j < groups2[i].rm_eo; j++)
                {
                    ptr->command->groups[i][k] = input[j];
                    k++;
                }
            }
           
            
            
            free(trimed);
            return ptr->command;
        }
        

        ptr = ptr->next;
    }
    free(trimed);
    return NULL;
}