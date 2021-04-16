#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "transformations.h"
#include <string.h>
#include <regex.h>
#include <math.h>

struct bmp_image* flip_horizontally(const struct bmp_image* image){
    if(!image) return NULL;
    if(!image->data || !image->header) return NULL;
    size_t width = (size_t) image->header->width;
    size_t height = (size_t) image->header->height;
    size_t index = 0;
    struct pixel tmpPixels[height][width];
    
    
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            
            tmpPixels[i][j].blue = *((uint8_t*)image->data + index); 
            tmpPixels[i][j].green = *((uint8_t*)image->data + index + 1);
            tmpPixels[i][j].red = *((uint8_t*)image->data  + index + 2);
            index+=3;
            
        }
       
    }

    struct pixel p;
    
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < (int)(width/2); j++){
            p = tmpPixels[i][j];
            tmpPixels[i][j] = tmpPixels[i][width-j-1];
            tmpPixels[i][width-j-1] = p;
            
            
        }
        
    }
 
    struct bmp_image * newImage = malloc(sizeof(*newImage));
    newImage->header = malloc(sizeof(*image->header));
    newImage->data = malloc(index);
    memcpy(newImage->header, image->header, image->header->offset);
    index = 0;
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
           
            *((uint8_t*)newImage->data + index) = tmpPixels[i][j].blue; 
            *((uint8_t*)newImage->data + index + 1) = tmpPixels[i][j].green;
            *((uint8_t*)newImage->data  + index + 2) = tmpPixels[i][j].red;
            
            index +=3;
        }
    }
    return newImage;
}

struct bmp_image* flip_vertically(const struct bmp_image* image){
    if(!image) return NULL;
    if(!image->data || !image->header) return NULL;
    size_t width = (size_t) image->header->width;
    size_t height = (size_t) image->header->height;

    size_t index = 0;
    struct pixel tmpPixels[height][width];
    
    
    
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
         
            tmpPixels[i][j].blue = *((uint8_t*)image->data + index); 
            tmpPixels[i][j].green = *((uint8_t*)image->data + index + 1);
            tmpPixels[i][j].red = *((uint8_t*)image->data  + index + 2);
            index+=3;
            
        }
       
    }

    struct pixel p;
    
    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < (int)(height/2); j++){
            p = tmpPixels[j][i];
            tmpPixels[j][i] = tmpPixels[height-j-1][i];
            tmpPixels[height-j-1][i] = p;
            
            
        }
        
    }
 
    struct bmp_image * newImage = malloc(sizeof(*newImage));
    newImage->header = malloc(sizeof(*image->header));
    newImage->data = malloc(index);
    memcpy(newImage->header, image->header, image->header->offset);
    index = 0;
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){

            *((uint8_t*)newImage->data + index) = tmpPixels[i][j].blue; 
            *((uint8_t*)newImage->data + index + 1) = tmpPixels[i][j].green;
            *((uint8_t*)newImage->data  + index + 2) = tmpPixels[i][j].red;
            
            index +=3;
        }
    }
    return newImage;
}

struct bmp_image* rotate_right(const struct bmp_image* image){
    if(!image) return NULL;
    if(!image->data || !image->header) return NULL;
    size_t width = (size_t) image->header->width;
    size_t height = (size_t) image->header->height;

    size_t index = 0;
    struct pixel tmpPixels[height][width];
    
    //printf("%p\n", image->data);
    
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
   
            tmpPixels[i][j].blue = *((uint8_t*)image->data + index); 
            tmpPixels[i][j].green = *((uint8_t*)image->data + index + 1);
            tmpPixels[i][j].red = *((uint8_t*)image->data  + index + 2);
            //printf("m %x %x %x\n", tmpPixels[i][j].blue, tmpPixels[i][j].green, tmpPixels[i][j].red);
            index+=3;
            
        }
       
    }

    struct pixel rightPixels[width][height];
    //printf("wh %ld %ld\n", width, height);
    for(int i = 0; i <height; i++){
        for(int j = 0; j < (int)width; j++){
            rightPixels[(int)width-j-1][i] = tmpPixels[i][j];
            // printf("m %x %x %x\n", rightPixels[(int)width-j-1][i].blue,
            //  rightPixels[(int)width-j-1][i].green,
            //   rightPixels[(int)width-j-1][i].red);

            // printf("m %d %d\n", (int)width-j-1, i);
            // printf("r %d %d\n", j, i);
        }
    }
 
    struct bmp_image * newImage = malloc(sizeof(struct bmp_image));
    size_t newPadding = (height % 4) * width;
    newImage->header = malloc(sizeof(struct bmp_header));
    newImage->data = malloc(index);
    memcpy(newImage->header, image->header, image->header->offset);
    //printf("%d %d")
    newImage->header->width = (uint32_t)height;
    newImage->header->height = (uint32_t)width;
    newImage->header->size = (uint32_t)((height*width*3) + newPadding + sizeof(*newImage->header));
    newImage->header->image_size = (uint32_t)((height*width*3) + newPadding);
    index = 0;
    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < height; j++){
            // printf("%x ", rightPixels[i][j].blue);
            // printf("%x ", rightPixels[i][j].green);
            // printf("%x \n", rightPixels[i][j].red);
            *((uint8_t*)newImage->data + index) = rightPixels[i][j].blue; 
            *((uint8_t*)newImage->data + index + 1) = rightPixels[i][j].green;
            *((uint8_t*)newImage->data  + index + 2) = rightPixels[i][j].red;
            
            index +=3;
        }
        //printf("\n");
    }
     //printf("-------------\n");
    return newImage;
}

struct bmp_image* rotate_left(const struct bmp_image * image){
    if(!image) return NULL;
    if(!image->data || !image->header) return NULL;
    struct bmp_image * newImage = rotate_right(image);
    struct bmp_image * newImage2 = rotate_right(newImage);
    free_bmp_image(newImage);
    struct bmp_image * newImage3 = rotate_right(newImage2);
    free_bmp_image(newImage2);
    return newImage3;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep){
    if(!image || !colors_to_keep) return NULL;
    if(strlen(colors_to_keep) > 3) return NULL;
    regex_t regex;
    if(regcomp(&regex, "[^rgb]", REG_ICASE) != 0){
        fprintf(stderr, "Regular expression could not be compiled.\n");
        exit(EXIT_FAILURE);
    }

    int reti = regexec(&regex, colors_to_keep, 0, NULL, 0);

    if(!reti){
        //printf("wrong colors\n");
        regfree(&regex);
        return NULL;
    }
    regfree(&regex);

    size_t width = (size_t) image->header->width;
    size_t height = (size_t) image->header->height;

    size_t index = 0;
    struct pixel tmpPixels[height][width];
    
    
    
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){

            tmpPixels[i][j].blue = strstr(colors_to_keep, "b") ? *((uint8_t*)image->data + index) : 0x0; 
            tmpPixels[i][j].green = strstr(colors_to_keep, "g")? *((uint8_t*)image->data + index + 1) : 0x0;
            tmpPixels[i][j].red = strstr(colors_to_keep, "r")? *((uint8_t*)image->data  + index + 2) : 0x0;
            index+=3;
            
        }
       
    }

 
    struct bmp_image * newImage = malloc(sizeof(*newImage));
    size_t newPadding = (width % 4) * height;
    newImage->header = malloc(sizeof(*image->header));
    newImage->data = malloc(index);
    memcpy(newImage->header, image->header, image->header->offset);
    newImage->header->size = (uint32_t)((height*width*3) + newPadding + sizeof(*newImage->header));
    newImage->header->image_size = (uint32_t)((height*width*3) + newPadding);
    index = 0;
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){

            *((uint8_t*)newImage->data + index) = tmpPixels[i][j].blue; 
            *((uint8_t*)newImage->data + index + 1) = tmpPixels[i][j].green;
            *((uint8_t*)newImage->data  + index + 2) = tmpPixels[i][j].red;
            
            index +=3;
        }
    }
    return newImage;
}

struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width){
    if(!image) return NULL;
    if(!image->header) return NULL;
    if(!image->data) return NULL;
    if(height > image->header->height || height <= 0) return NULL;
    if(width > image->header->width || width <= 0) return NULL;
    if(start_y < 0 || start_y > image->header->height) return NULL;
    if(start_x < 0 || start_x > image->header->width) return NULL;
    if(width+start_x > image->header->width) return NULL;
    if(height+start_y > image->header->height) return NULL;
    size_t index = 0;
    struct pixel tmpPixels[image->header->height][image->header->width];
    
    printf("%d %d %d %d\n", start_y, start_x, width, height);
    printf("%d %d\n", image->header->width, image->header->height);
    printf("--------\n");
    

    for(int i = (int)image->header->height-1; i > -1; i--){
        for(size_t j = 0; j < image->header->width; j++){
   
            tmpPixels[i][j].blue = *((uint8_t*)image->data + index); 
            tmpPixels[i][j].green = *((uint8_t*)image->data + index + 1);
            tmpPixels[i][j].red = *((uint8_t*)image->data  + index + 2);
            // printf("m %x %x %x\n", tmpPixels[i][j].blue, tmpPixels[i][j].green, tmpPixels[i][j].red);
            index+=3;
            
        }
        // printf("\n");
       
    }

    struct bmp_image * newImage = malloc(sizeof(*newImage));
    newImage->header = malloc(sizeof(*image->header));
    size_t newPadding = (size_t)((width % 4) * height);
    newImage->data = malloc((size_t)(width*height*3));

    memcpy(newImage->header, image->header, image->header->offset);
    newImage->header->height = (uint32_t)height;
    newImage->header->width = (uint32_t)width;
    newImage->header->size = (uint32_t)((size_t)(height*width*3) + newPadding + sizeof(struct bmp_header));
    newImage->header->image_size = (uint32_t)((size_t)(height*width*3) + newPadding);
    index = 0;
    printf("%d %d\n", newImage->header->width, newImage->header->height);
    printf("********\n");
    for(int i = (int)(height+start_y-1); i >= (int)start_y; i--){
        for(uint32_t j = start_x; j < width+start_x; j++){
            *((uint8_t*)newImage->data + index) = tmpPixels[i][j].blue; 
            *((uint8_t*)newImage->data + index + 1) = tmpPixels[i][j].green;
            *((uint8_t*)newImage->data  + index + 2) = tmpPixels[i][j].red;
            index +=3;
        }
    }

    return newImage;
}

struct bmp_image* scale(const struct bmp_image* image, float factor){
    if(!image) return NULL;
    if(!image->data || !image->header) return NULL;
    if(factor <= 0) return NULL;
    int width = (int) image->header->width;
    int height = (int) image->header->height;

    int index = 0;
    struct pixel tmpPixels[height][width];
    
    
    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
   
            tmpPixels[i][j].blue = *((uint8_t*)image->data + index); 
            tmpPixels[i][j].green = *((uint8_t*)image->data + index + 1);
            tmpPixels[i][j].red = *((uint8_t*)image->data  + index + 2);
            //printf("m %x %x %x\n", tmpPixels[i][j].blue, tmpPixels[i][j].green, tmpPixels[i][j].red);
            index+=3;
            
        }
       
    }

    int newWidth = (int)round((float)width * factor);
    int newHeight = (int)round((float)height * factor);

    struct pixel scaledPixels[newHeight][newWidth];
    for(int i = 0; i < newHeight; i++){
        for(int j = 0; j < newWidth; j++){
            scaledPixels[i][j] =  tmpPixels[(int) ((i*height) / newHeight)][(int) ((j*width) / newWidth)];
        }
    }

    struct bmp_image * newImage = malloc(sizeof(*newImage));
    newImage->header = malloc(sizeof(*image->header));
    int newPadding = (newWidth % 4) * newHeight;
    newImage->data = malloc((size_t)(newWidth*newHeight*3));

    memcpy(newImage->header, image->header, image->header->offset);
    newImage->header->height = (uint32_t)newHeight;
    newImage->header->width = (uint32_t)newWidth;
    newImage->header->size = (uint32_t)((newWidth*newHeight*3) + newPadding + (int)sizeof(struct bmp_header));
    newImage->header->image_size = (uint32_t)((newWidth*newHeight*3) + newPadding);
    index = 0;

    for(int i = 0; i < newHeight; i++){
        for(int j = 0; j < newWidth; j++){
            *((uint8_t*)newImage->data + index) = scaledPixels[i][j].blue; 
            *((uint8_t*)newImage->data + index + 1) = scaledPixels[i][j].green;
            *((uint8_t*)newImage->data  + index + 2) = scaledPixels[i][j].red;
            index +=3;
        }
    }

    return newImage;
}