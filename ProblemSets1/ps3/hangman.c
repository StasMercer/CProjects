#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <string.h>
#include <ctype.h>

int is_letter_in_secret(const char secret[], const char letter);

int get_word(char secret[]){
    
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]){
    int length = strlen(secret);
    int length_letters = strlen(letters_guessed);
    int count = 0;
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length_letters; j++){
            if (secret[i] == letters_guessed[j]){
                count++;
                break;
            }
        }
    }

    return (count == length) ? 1 : 0 ;
    
} 
void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    int length = strlen(secret)+1;
    int length_letters = strlen(letters_guessed);
    
    for(int i = 0; i < length; i++){     
       guessed_word[i] = '_';  
    }
   

    for(int i = 0; i < length-1; i++){
        for(int j = 0; j < length_letters; j++){
            if (secret[i] == letters_guessed[j]){
                guessed_word[i] = letters_guessed[j];
                break;
            }
        }
    }

    guessed_word[length-1] = '\0';
    
}

void get_available_letters(const char letters_guessed[], char available_letters[]){
    

    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int len = strlen(letters_guessed);
    int flag = 0;
    int count = 0;
    for (int i = 0; i < 26; i++){
        for(int j = 0; j < len; j++){
            if(alphabet[i] == letters_guessed[j]){
                flag = 1;
            }
        }

        if(!flag){
            available_letters[count] = alphabet[i];
            
            count++;
        }
        flag = 0;
    }
    available_letters[count] = '\0';
    
}


void hangman(const char secret[]){
   
    int guesses = 8;
    char guessed_letters[27] = "";
    int secret_length = strlen(secret);
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n" , secret_length);
    
    char buffer[30] = "";
    
    while(!is_word_guessed(secret, guessed_letters) && guesses != 0){
        int length = (strlen(secret)*2);
        char guessed_word[30] = {};
        char letters_availible[27] = "";
        
        char formated_word[length];
        printf("-------------\n");
        printf("You have %d guesses left.\n", guesses);
        
        get_available_letters(guessed_letters, letters_availible);
        
        printf("Available letters: %s\n", letters_availible);
        printf("Please guess a letter: ");
        
        scanf("%20s", buffer);
        
        
        if(strlen(buffer) == 1){


            
            buffer[0] = (char) tolower(buffer[0]);
            
            strcat(guessed_letters, buffer);
            get_guessed_word(secret, guessed_letters, guessed_word);
            char *ret = NULL;
            ret = strchr(guessed_letters, (int) buffer[0]);
            
            for(int i=0; i < length-1; i++){
                if(i%2 ==0){
                    formated_word[i] = '_';
                }else{
                    formated_word[i] = ' ';
                }
            }

            int len = strlen(guessed_word);
            for(int i = 0; i < len; i++){
                formated_word[i*2] = guessed_word[i];
            }

            formated_word[length-1] = '\0';

            if(strlen(ret) > 1){
                printf("Oops! You've already guessed that letter: %s\n", formated_word);
                continue;
            }else if(!is_letter_in_secret(secret, buffer[0]) && (buffer[0] >= 'a' && buffer[0] <= 'z')){
                printf("Oops! That letter is not in my word: %s\n", formated_word);
                guesses--;
                continue;
            }else if(buffer[0] < 'a' || buffer[0] > 'z'){
                printf("Oops! '%c' is not a valid letter: %s\n", buffer[0], formated_word);
            }else{
                
                printf("Good guess: %s\n", formated_word);
            }

            
            
           
            
        }else
        {
            strcat(guessed_letters, buffer);
            if(is_word_guessed(secret, guessed_letters)){
                
                printf("Congratulations, you won!\n");
                return ;
                
            }else
            {
                printf("Sorry, bad guess. The word was %s.\n", secret);
                return;
            }
            
        }
        
    }

    if(guesses == 0){
        printf("-------------\n");
        printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
    }else
    {
        printf("-------------\n");
        printf("Congratulations, you won!\n");
    }
    



}

int is_letter_in_secret(const char secret[], const char letter){
    int length = strlen(secret);
    for(int i=0; i < length; i++){
        if(secret[i] == letter){
            return 1;
        }
    }

    return 0;
}

