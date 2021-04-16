#define _POSIX_C_SOURCE 200201L
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <string.h>

struct Stickman {
        int head[2];
        int neck[2];
        int hands[2];
        int snake[2];
        int legs[2];
};


int stick_left(struct Stickman obj, struct timespec t, int size, int enemys[size]);

int stick_right(struct Stickman obj, struct timespec t, int size, int enemys[size]);

void draw_stickman(struct Stickman obj);

void draw_enemys(const int enemys[], int size);

int main(){
    srand(time(NULL));
    


    // initialize the library
    initscr();


    start_color();
    // color sets

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    // set implicit modes
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    // invisible cursor, visibility of cursor (0,1,2)
    curs_set(FALSE);
    // char res_str[100][100] = "";
    // char str[13] = "";
    // FILE *fp = fopen("score.txt", "rw");

    // if(fp != NULL){
    //     int i = 0;

    //     while (fgets(str, 13, fp) != NULL){
    //         int len = strlen(str);
    //         for(int j = 0; j < len; j++){
    //             res_str[i][j] = str[j];
    //         }
            
    //         i++;
    //     }

    //     for(
    // }
    
    // getch() will be non-blocking
    nodelay(stdscr, TRUE);

    
    
    // time delay 0.001s for drawing city
    struct timespec ts = {
        .tv_sec = 0,                    // nr of secs
        .tv_nsec = 0.1 * 1000000000L  // nr of nanosecs
    };

    

    // draw world
    
    struct Stickman sman =  {
        .head = { LINES - 5, COLS /2},
        .neck = { LINES - 4, (COLS /2) + 2},
        .hands = { LINES - 3, COLS /2},
        .snake = { LINES - 2, (COLS /2) + 2},
        .legs = { LINES - 1, (COLS /2) + 1}
    };

    int enemys[4] = {2, COLS-2, COLS+8, -4};
    
    int counter = 1;
    int input = getch();
    int exit = 0;
    int size = 1;
    int points = 1;
    long difficulty = 0.02 * 1000000000L;

    

    //main cykle
    while (!exit && points > 0)
    {
        clear();
        draw_stickman(sman);
        mvprintw(LINES - 11, 1, " score: %d", points);
        mvprintw(LINES - 11, COLS - 15, "speed: %ld m/s", 100/(ts.tv_nsec / 10000000));
        draw_enemys(enemys, size);
        // mvprintw(LINES /2 + 2, 0, "TOP 3 Palyers:");
        // mvprintw(LINES /2 + 3, 0, "%s\n", res_str);
        for(int i = 0; i < COLS; i++){
            mvprintw(LINES - 10, i, "_");
        }

        input = getch();
        
         switch (input){
            
            case KEY_LEFT:
                points += stick_left(sman, ts, size, enemys);
                if(size < 4 && points % 5 == 0){
                        size++;
                        ts.tv_nsec -= difficulty;
                        attron(COLOR_PAIR(size));
                }
                
                break;
            
            case KEY_RIGHT:
                points += stick_right(sman, ts, size, enemys);
                if(size < 4 && points % 5 == 0){
                        size++;
                        ts.tv_nsec -= difficulty;
                        attron(COLOR_PAIR(size));
                }
            
                break;
            default:
                break;
        }

             
            for( int i = 0; i < size; i++){

                if(enemys[i] > (COLS/2 +6)){
                    enemys[i] -=1;
                
                }else if(enemys[i] < (COLS /2 -3)) {
                    enemys[i] +=1; 
                }
                else{
                    exit =1;
                }
            }
            
            counter = 0;
        
        counter++;
        
        nanosleep(&ts, NULL);
        
        

    }

    
    mvprintw(LINES /2 , COLS/ 2 - 14, "Nice game your score is %d", points);
    mvprintw(LINES /2 + 2, COLS/ 2 - 10, "Press ESC to exit");
    refresh();
    nodelay(stdscr, FALSE);
    int c; 
    while((c = getch()) !=27);

    // end curses
    endwin();
    
    return 0;
}

//make punch to left
int stick_left(struct Stickman obj, struct timespec t,int size, int enemys[size]){

    mvprintw(obj.head[0], obj.head[1],  "(<.<)");
    mvprintw(obj.hands[0], obj.hands[1],  "      ");
    mvprintw(obj.hands[0], obj.hands[1],  "/ # ");

    refresh();
   
    int y = obj.hands[0];
    t.tv_sec = 0;
    t.tv_nsec = 0.02 * 1000000000L;  
    int x = COLS / 2 - 4;//drawing starting point
    int min = x - 6;// lengh of sword
    mvprintw(y, x+3, "| ");

    //draw sword
    for(x = COLS / 2 - 2; x > min; x--){
        mvprintw(y, x, "=");
        refresh();
        nanosleep(&t, NULL);

        //check if enemy punched
        for(int j = 0; j < size; j++){
            if(enemys[j] == x-1){
                enemys[j] = -(rand() % 10);
                return 1;
            }
        }
    }

    mvprintw(y, x, "<");
    return -1;
}

void draw_stickman(struct Stickman obj){
    mvprintw(obj.head[0], obj.head[1],  "(^.^)");
    mvprintw(obj.neck[0], obj.neck[1],  "#");
    mvprintw(obj.hands[0], obj.hands[1],  "/ # \\");
    mvprintw(obj.snake[0], obj.snake[1],  "#");
    mvprintw(obj.legs[0], obj.legs[1],  "/ \\");
    refresh();

}
//make punch to right
int stick_right(struct Stickman obj, struct timespec t, int size,  int enemys[size]){
    mvprintw(obj.head[0], obj.head[1],  "(>.>)");
    mvprintw(obj.hands[0], obj.hands[1],  "      ");
    mvprintw(obj.hands[0], obj.hands[1],  "  # \\");

    refresh();
    int y = obj.hands[0];
    t.tv_sec = 0;
    t.tv_nsec = 0.02 * 1000000000L;  

    int x = COLS / 2 + 4; // drawing starting point

    int max = x + 9; // lengh of sword

    mvprintw(y, x-1, " |");
    //draw sword
    for(x = COLS / 2 + 5; x < max; x++){
        mvprintw(y, x, "=");
        refresh();
        nanosleep(&t, NULL);
        //check if enemy punched
        for(int j = 0; j < size; j++){
            if(enemys[j] == x+1){
                enemys[j] = COLS + (rand() % 10);
                return 1;
            }
        }
    }

    mvprintw(y, x, ">");
    return -1;
}


void draw_enemys(const int enemys[], int size){
    for(int i = 0; i < size; i++){
        if( enemys[i] < COLS && enemys[i] > 0){
            mvprintw(LINES-5, enemys[i]-2, "('O')");
            mvprintw(LINES-4, enemys[i]-1, "/|\\ ");
            mvprintw(LINES-3, enemys[i], "|");
            mvprintw(LINES-2, enemys[i], "|");
            mvprintw(LINES-1, enemys[i]-1, "/ \\");
            refresh();
        }
    }

    
}