#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"
#define FILETYPE  0x4d42


struct bmp_header* read_bmp_header(FILE* stream){
    if(!stream) return NULL;
    rewind(stream);
    struct bmp_header * header = malloc(sizeof(*header));
    
    
    size_t read = fread(header, sizeof(*header), 1, stream);
    if(header->type != FILETYPE){
        fprintf(stderr, "%s\n", "Error: This is not a BMP file.");
        free(header);
        return NULL;
    }
    if(!read){
        free(header);
        return NULL;
    } 
    return header;
    
}


struct pixel* read_data(FILE* stream, const struct bmp_header* header){
    if(!stream || !header) return NULL;
    rewind(stream);
    fseek(stream, header->offset, SEEK_SET);
    int padding = header->width % 4;
    int read = 0;

    struct pixel * p = malloc(header->width* header->height*3);
    int index = 0;
    for(int i = 0; i < header->height; i++){
        for(int j = 0; j < (int)header->width+padding; j++){
            if(j >= header->width){
                
                fseek(stream, 1L, SEEK_CUR);
               
                continue;
               
            }

            read = (int)fread(p+index, 3, 1, stream);
            index++;
            if(read != 1){
                fprintf(stderr, "%s\n", "Error: Corrupted BMP file.");
                free(p);
                return NULL;
            }

        }
    }


    return p;
}

struct bmp_image* read_bmp(FILE* stream){

    if(!stream) return NULL;
    struct bmp_image * image = malloc(sizeof(struct bmp_image));
    
    image->header = read_bmp_header(stream);
    if(!image->header){
        free(image);
        return NULL;
    };
    image->data = read_data(stream, image->header);
    if(!image->data){
        free_bmp_image(image);    
        return NULL;
    };
    
    
    return image;

}

bool write_bmp(FILE* stream, const struct bmp_image* image){
    if(!stream || !image) return false;
    size_t write = fwrite(image->header, sizeof(*image->header), 1, stream);
    int index = 0;
    int padding = image->header->width % 4;
    if(!write) return false;
    for(int i = 0; i < image->header->height; i++){
        for(int j = 0; j < (int)image->header->width+padding; j++){
            if(j >=image->header->width){
                write = fwrite("", 1, 1, stream);
                if(!write) return false;
                continue;
            }

           write = fwrite(image->data+index, 3, 1, stream);
           index++;
           if(!write) return false;
        }
    }

    
    
    
    return true;
}

void free_bmp_image(struct bmp_image * image){
    if(image){
        if(image->header) free(image->header);
        if(image->data) free(image->data);
        free(image);
    }
    
}
