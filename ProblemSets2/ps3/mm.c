#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int getNumber(char str[]) {
    //return --n %9 +1;
    
    int len = strlen(str);
    int sum = 0;
       
    while(len > 1){
        sum =0;
        
        for(int i = 0; i< len; i++){
            sum += str[i] - '0';
        }
        //printf("%d\n", sum);
        sprintf(str, "%d", sum);
        len = strlen(str);
    }
  
    return sum;
}

int main(){

    int strsize = 20;
    char * str = malloc(sizeof(char)* strsize);
    int i = 0;
    char c;
    
    do{
        c = fgetc(stdin);
        str[i] = c;
        i++;
        if(i >= strsize){
            strsize += 10;
            
            char * tmp = realloc(str, strsize * sizeof(char));
            if(tmp){
                str = tmp;
            }else
            {
                free(str);
            }
            
        }
    }while(!feof(stdin) && c != '\n');
    str[i-1] = '\0';

    int k = getNumber(str);
    
    printf("%d\n", k);
    free(str);
    return 0;
}