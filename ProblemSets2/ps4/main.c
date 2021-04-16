#include <stdio.h>
#include "bmp.h"
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "transformations.h"

int main(int argc, char **argv){

   
    FILE *inStream = NULL; 
    FILE *outStream = NULL;
    int c;

    while ((c = getopt(argc,argv, "i:o:")) != -1)
    {
        switch (c){
            case 'i':
            
            inStream = fopen(optarg, "rb");
            
            
            break;

            case 'o':
                outStream = fopen(optarg, "wb");
                
            break;

            case '?':
                if(optopt == 'o'){
                    outStream = stdout;
                }
                if(optopt == 'i'){
                    outStream = stdin;
                }
            break;
        }
    }
    
    if(!inStream){  
        fprintf(stderr, "%s\n", "no file");
        
        return 1;
    }


    struct bmp_image * image = read_bmp(inStream);
    if(!image) return 1;
    const float factor = (float)0.5;
    struct bmp_image * newImage = crop(image, 0, 1, 1, 2);
    write_bmp(outStream, newImage);

    if(false){
        scale(image, factor);
        crop(image, 50, 100, 100, 100);
        extract(image, "bgr");
        rotate_right(image);
        flip_horizontally(image);
        flip_vertically(image);
        rotate_left(image);
    }
    
    free_bmp_image(image);
    free_bmp_image(newImage);

    struct bmp_image * i = malloc(sizeof(struct bmp_image));
    i->header = malloc(sizeof (struct bmp_header));
    i->data = NULL;
    free_bmp_image(i);

    //free_bmp_image(i);
    fclose(inStream);
    fclose(outStream);

    return 0;
}

