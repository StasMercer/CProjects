#include <stdlib.h>
#include "hof.h"
#include <stdio.h>


void insert(struct player * list, int *size, int index, struct player player){
    struct player * list_copy = malloc(sizeof(struct player) * 10);
    for(int i = 0; i < *size-1; i++) list_copy[i] = list[i];

    list[index] = player;
    
    for(int i = index+1; i < *size; i++){
        list[i] = list_copy[i - 1];
    }

    free(list_copy);

}

int cmpfunc (const void * a, const void * b) {
    struct player * p1 = (struct player*) a;
    struct player * p2 = (struct player*) b;
   return ( p2->score - p1->score );
}

int load(struct player list[]){
    FILE * fp;
    if(!(fp = fopen(HOF_FILE,"r"))) return -1;

    int i = 0;
    int size = 0;
    char buffer[100];
    while(fgets(buffer, 100, fp) && size < 10){
        sscanf(buffer, "%s %d", list[i].name, &list[i].score);
        
        i++;
        size++;
    }

    qsort(list, (size_t)size, sizeof(struct player), cmpfunc);



    fclose(fp);
    return size;
}

bool add_player(struct player list[], int* size, const struct player player){
    

    if(*size < 10){
        for(int i = 0; i < *size; i++){
            if(list[i].score < player.score || list[i].score == player.score){
                *size +=1;
                insert(list, size, i, player);
                return true; 
            }

        }

        list[*size] = player;

        *size+=1;
        
        return true;
    }
    for(int i = 0; i < *size; i++){
        if(list[i].score == player.score||list[i].score < player.score){
                
            insert(list, size, i, player);
            return true;
        }

    }

    return false;
}

bool save(const struct player list[], const int size){
    FILE * fp;
    if(!(fp = fopen(HOF_FILE,"w"))) return false;

    
    for(int i = 0; i < size; i++){
        fprintf(fp, "%s %d\n", list[i].name, list[i].score); 
    }




    fclose(fp);
    return true;
}