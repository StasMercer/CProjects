#include <stdio.h>
#include <string.h>
#include "hangman.h"


int main(){

    char secret[30];
    get_word(secret);
    hangman(secret);

}

