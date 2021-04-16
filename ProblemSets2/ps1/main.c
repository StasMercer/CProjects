#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "playfair.h"
#include "bmp.h"


int main(){
    
 
    unsigned char* b = bmp_encrypt("secretsss","lorem ipsum dolor sit amet");

    char *d = bmp_decrypt("secretsss", b);

char * c = playfair_encrypt("asdfa", "asdfa");
    char * m = playfair_decrypt("asdfa", c);

    free(c);
    free(m);
    free(b);
    free(d);
}