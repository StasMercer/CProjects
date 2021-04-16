#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include "k.h"
#include <math.h>
void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
        
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

int get_score(const char symb){
    //get n-power of sybol by normalizing it to (1 ... )range
    // 'A' has ascii 66(but in ascii 65:) ),
    // so if 2^(66-65) = 2. So we get the score
    int score = (int)pow(2, symb-65);
    score +=score;
    return score;
}

bool is_game_won(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(game.board[i][j] == 'K') return true;
        }
    }
    
    return false;
}



bool is_move_possible(const struct game game){
    
    for(int i = 0; i < SIZE; i++){
        for(int j =0; j < SIZE; j++){
            if(game.board[i][j] == ' ') return true;
            if( i + 1 < 4 && game.board[i+1][j] == game.board[i][j]) return true;  
            if( i - 1 >= 0 && game.board[i-1][j] == game.board[i][j]) return true;  
            if( j + 1 < 4 && game.board[i][j+1] == game.board[i][j]) return true;  
            if( j - 1 >= 0 && game.board[i][j-1] == game.board[i][j]) return true;  
        }
    }

    return false;

}

bool update(struct game *game, int dy, int dx){
    
    int was_move = 0;
    // to the down
    if(dy == 1 && dx == 0){
        
        for(int y = 0; y < SIZE; y++){
            //move all to the bottom corner
            int x = 3;
            int space = -1;
            
            while(x >= 0){ 
                

                if(space != -1 && game->board[x][y] != ' '){
                    game->board[space][y] = game->board[x][y];
                    game->board[x][y] = ' ';
                    x = space;
                    space = -1;
                    was_move = 1;
                }

                if(game->board[x][y] == ' ' && space == -1){
                    space = x;
                    
                }
                x--;
            }

            //sumurize neighbours
            x = 3;

            while(x >= 0){
                
                if(x>0 && game->board[x][y] != ' ' && game->board[x][y] == game->board[x-1][y]){
                    
                    game->board[x-1][y] = ' ';
                    game->board[x][y] = (char)((int)game->board[x][y] + 1);
                    game->score += get_score(game->board[x][y]);
                    was_move = 1;
                    
                }
                x--;
            }

            //again move all to the bottom corner
            x = 3;
            
            space = -1;
            while(x >=0){
                
                if(space != -1 && game->board[x][y] != ' '){
                    game->board[space][y] = game->board[x][y];
                    game->board[x][y] = ' ';
                    x = space;
                    was_move = 1;
                    space = -1;
                }

                if(game->board[x][y] == ' ' && space == -1){
                    space = x;
                    
                }
                x--;
            }
            
                
            
        }
        
    }
    
    //to the up
    if(dy == -1 && dx == 0){
        for(int y = 0; y < SIZE; y++){
            //move all to the upper corner
            int x = 0;
            int space = -1;
            
            while(x < SIZE){ 
                
                if(space != -1 && game->board[x][y] != ' '){
                    game->board[space][y] = game->board[x][y];
                    game->board[x][y] = ' ';
                    x = space;
                    was_move = 1;
                    space = -1;
                }

                if(game->board[x][y] == ' ' && space == -1){
                    space = x;
                    
                }
                x++;
            }

            //sumurize neighbours
            x = 0;

            while(x < SIZE){
                if(x<SIZE-1 && game->board[x][y] != ' ' && game->board[x][y] == game->board[x+1][y]){
                    
                    game->board[x+1][y] = ' ';
                    game->board[x][y] = (char)((int)game->board[x][y] + 1);
                    game->score += get_score(game->board[x][y]);
                    was_move = 1;
                    
                }
                x++;
            }

            //again move all to the upper corner
            x = 0;
            
            space = -1;
            while(x < SIZE){
                
                if(space != -1 && game->board[x][y] != ' '){
                    game->board[space][y] = game->board[x][y];
                    game->board[x][y] = ' ';
                    x = space;
                    was_move = 1;
                    space = -1;
                }

                if(game->board[x][y] == ' ' && space == -1){
                    space = x;
                    
                }
                x++;
            }
            
                
            
        }
        
    }

    // to the right
    if(dx == 1 && dy == 0){
        for(int x = 0; x < SIZE; x++){
            //move all to the right corner
            int y = 3;
            int space = -1;
            
            while(y >= 0){ 
                
                if(space != -1 && game->board[x][y] != ' '){
                    game->board[x][space] = game->board[x][y];
                    game->board[x][y] = ' ';
                    y = space;
                    was_move = 1;
                    space = -1;
                }

                if(game->board[x][y] == ' ' && space == -1){
                    space = y;
                    
                }
                y--;
            }

            //sumurize neighbours
            y = 3;

            while(y >= 0){
                if(y>0 && game->board[x][y] != ' ' && game->board[x][y] == game->board[x][y-1]){
                    
                    game->board[x][y-1] = ' ';
                    game->board[x][y] = (char)((int)game->board[x][y] + 1);
                    game->score += get_score(game->board[x][y]);
                    was_move = 1;
                    
                }
                y--;
            }

            //again move all to the right corner
            y = 3;
            
            space = -1;
            while(y >= 0){
                
                if(space != -1 && game->board[x][y] != ' '){
                    game->board[x][space] = game->board[x][y];
                    game->board[x][y] = ' ';
                    y = space;
                    was_move = 1;
                    space = -1;
                }

                if(game->board[x][y] == ' ' && space == -1){
                    space = y;
                    
                }
                y--;
            }
            
                
            
        }
    }
    
    //to the left
    if(dx == -1 && dy == 0){
        
        for(int x = 0; x < SIZE; x++){

            //move all to the left corner
            int y = 0;
            int space = -1;
            while(y < SIZE){
                
                if(space != -1 && game->board[x][y] != ' '){
                    game->board[x][space] = game->board[x][y];
                    game->board[x][y] = ' ';
                    y = space;
                    was_move = 1;
                    space = -1;
                }

                if(game->board[x][y] == ' ' && space == -1){
                    space = y;
                    
                }
                y++;
            }

            //sumurize neighbours
            y = 0;

            while(y < SIZE){
                if(y<SIZE-1 && game->board[x][y] != ' ' && game->board[x][y] == game->board[x][y+1]){
                    
                    game->board[x][y+1] = ' ';
                    game->board[x][y] = (char)((int)game->board[x][y] + 1);
                    game->score += get_score(game->board[x][y]);
                    was_move = 1;
                    
                }
                y++;
            }

            //again move all to the left corner
            y = 0;
            
            space = -1;
            while(y < SIZE){
                
                if(space != -1 && game->board[x][y] != ' '){
                    game->board[x][space] = game->board[x][y];
                    game->board[x][y] = ' ';
                    y = space;
                    was_move = 1;
                    space = -1;
                }

                if(game->board[x][y] == ' ' && space == -1){
                    space = y;
                    
                }
                y++;
            }
            
                
            
        }
    }
    if(!was_move) return false;
    return true;
}








