#include <stdio.h>

char to_low(const char sym){

    if(sym >= 'A' && sym <= 'Z'){
        return sym + 32;
    }
    return sym;
}


int main(int argc, char* argv[]){

    if(argc != 3){
        
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    char text[100000];
    int len = 0;
    text[len] = fgetc(fp);
    
    while(text[len] != EOF){
        len++;
        text[len] = fgetc(fp);
    }

    text[len] = '\0';
    int start_index = 0;
    int stop_index = 0;

    
    for(int i = 0; i < len; i++){
        if(text[i] == 'S' &&
           text[i+1] == 'T' &&
           text[i+2] == 'A' &&
           text[i+3] == 'R' &&
           text[i+4] == 'T'){
                start_index = i + 6;
                
           }
        
        if(text[i] == 'S' &&
           text[i+1] == 'T' &&
           text[i+2] == 'O' &&
           text[i+3] == 'P'){
                stop_index = i-1;
                break;
           }
        
    }

    int space = 1;
    int total_spaces = 0;
    for(int i = start_index; i < stop_index; i++){
        if(text[i] == ' ') total_spaces ++;

    }

    for(int i = start_index; i < stop_index; i++){
        if(space % 2 == 0){
            if(text[i] != ' '){
                fputc(text[i], output);
            }else if(text[i] == ' ' && space != total_spaces)
            {
                
                fputc(text[i], output);
            }
            
        }

        if(text[i] == ' '){
            space++;
            
        }
           
        
        
    }


    fclose(fp);
    fclose(output);


    return 0;


}