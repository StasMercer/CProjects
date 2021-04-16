#include <stdlib.h>
#include <curses.h>
#include "hof.h" 
#include "k.h" 
#include "ui.h"
#include <string.h>

bool is_empty_cell(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(game.board[i][j] == ' ') return true;
        }
    }
    return false;
};

int main(){
    

    struct game game = {
        .board = {
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        .score = 0
    };
    struct player list[10];
    struct player player = {
        .name = "",
        .score = 912
    };


    while(strlen(player.name) < 3){
        printf("Input your name:\n");
        scanf(" %30[a-zA-Z]", player.name);
    }
    

    //get player list
    int list_len = load(list);
    printf("%s\n", list[0].name);

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    // invisible cursor, visibility of cursor (0,1,2)
    curs_set(FALSE);
    //nodelay(stdscr, TRUE);
    init_pair(8, COLOR_CYAN, COLOR_CYAN);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_RED);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);        
    
    add_random_tile(&game);
    add_random_tile(&game);
    int input = 0;
    while(!is_game_won(game) && is_move_possible(game)){
          
        render(game);
        
        bool was_update = false;
        input = getch();
        
        switch (input)
        {
            case KEY_LEFT:
                was_update = update(&game, 0, -1);
                break;
            case KEY_RIGHT:
                was_update = update(&game, 0, 1);
                break;
            case KEY_UP:
                was_update = update(&game, -1, 0);
                break;
            case KEY_DOWN:
                was_update = update(&game, 1, 0);
                break;

            default:
                break;
        }
        
        if(input == 97) break;
        if(is_empty_cell(game) && was_update) add_random_tile(&game);
        render(game);
        
    }
    player.score = game.score;
    if(add_player(list, &list_len, player)) save(list, list_len);
    
    clear();
    attrset(COLOR_PAIR(6));
    

    while(input != 'q'){
        if(!is_move_possible(game)){
            mvprintw(1,1, "You lose");
            mvprintw(2,1, "Best players:");
            //output best players
            int i = 0;
            for(i = 0; i < list_len; i++){
                mvprintw(3+i,2,"%s: %d", list[i].name, list[i].score);
                
            }
            mvprintw(4+i,1, "Press q to exit");
            refresh();
            input = getch();
        }else{
            mvprintw(1,1, "Ohh my god how you did it???");
            mvprintw(2,1, "Best players:");
            //output best players
            int i = 0;
            for(i = 0; i < list_len; i++){
                mvprintw(3+i,2,"%s: %d", list[i].name, list[i].score);
                
            }
            mvprintw(4+i,1, "Press q to exit");
            refresh();
            input = getch();
        }
        
    }
    
    clear();
    endwin();
    return 0;
}