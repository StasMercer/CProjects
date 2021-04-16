#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


void encode_char(const char character, bool bits[8]);
char decode_byte(bool bits[8]);

void encode_string(const char string[], bool bytes[strlen(string)+1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

void ten_to_two(int num, bool bits[8]);
int two_to_ten(bool bits[8]);

int main(){
    

    // char a = 'A';
    // bool bits[8] = {};
    // encode_char(a, bits);
    // for(int i = 0; i < 8; i++){
    //     printf("%d", bits[i]);
    // }
    // printf("\n");

    // printf("%c\n", decode_byte(bits));
    
    // char* text = "Hello, how are you?";
    // const int len = strlen(text);
    // bool bytes1[len+1][8];

    // encode_string(text, bytes1);

    // for(int j = 0; j <= len; j++){
    //     printf("%c: ", text[j]);
    //     for(int i = 0; i < 8; i++){
    //         printf("%d", bytes1[j][i]);
    //     }
    //     printf("\n");
    // }

    // bool bytes2[7][8] = {
    //     {0,1,0,0,1,0,0,0},
    //     {0,1,1,0,0,1,0,1},
    //     {0,1,1,0,1,1,0,0},
    //     {0,1,1,0,1,1,0,0},
    //     {0,1,1,0,1,1,1,1},
    //     {0,0,1,0,0,0,0,1},
    //     {0,0,0,0,0,0,0,0}
    // };
    // char string[7];
    // decode_bytes(7, bytes2, string);
    // printf("%s\n", string);
int length = 5, cols = 2, offset = 3;
         
bool bytes[5][8] = {
	{0, 1, 1, 0, 0, 0, 1, 0},
	{0, 1, 1, 0, 1, 1, 1, 1},
	{0, 1, 1, 0, 1, 1, 1, 1},
	{0, 1, 1, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};
bool blocks[3*8][2];
        bytes_to_blocks(cols, offset, blocks, length, bytes);
        for(int j = 0; j < offset*8; j++){
            for(int i = 0; i < cols; i++){
                printf("%d ", (blocks[j][i] == true) ? 1 : 0);
            }
            printf("\n");
            if(j % 8 == 7){
                printf("\n");
            }
        }

//     bool blocks[5*8][2] = {
// 	{0, 0},
// 	{1, 1},
// 	{1, 1},
// 	{1, 1},
// 	{1, 0},
// 	{0, 1},
// 	{1, 1},
// 	{0, 0},
// 	{0, 0},
// 	{1, 1},
// 	{1, 1},
// 	{0, 0},
// 	{1, 0},
// 	{1, 0},
// 	{0, 0},
// 	{0, 1},
// 	{0, 0},
// 	{1, 1},
// 	{1, 1},
// 	{1, 1},
// 	{0, 0},
// 	{0, 1},
// 	{1, 0},
// 	{1, 0},
// 	{0, 0},
// 	{1, 1},
// 	{1, 1},
// 	{0, 0},
// 	{1, 0},
// 	{1, 1},
// 	{1, 0},
// 	{0, 1},
// 	{0, 0},
// 	{0, 0},
// 	{0, 0},
// 	{0, 0},
// 	{0, 0},
// 	{0, 0},
// 	{0, 0},
// 	{0, 0}
// };
// bool bytes[9][8];
//     blocks_to_bytes(cols, offset, blocks, length, bytes);
//     for(int j = 0; j < length; j++){
//         for(int i = 0; i < 8; i++){
//             printf("%d ", bytes[j][i]);
//         }
//         printf("\n");
//     }
        
    return 0;
}


void ten_to_two(int num, bool bits[8]){
    int k = 0;
    
    for(int i = 7; i >= 0; i--){
        k = num >> i;
       
        if(k & 1){
            bits[abs(i-7)] = 1;
        }else
        {
            bits[abs(i-7)] = 0;
        }
        
    }
    
}

int two_to_ten(bool bits[8]){
    double num = 0;
    for(int i = 8; i > 0; i--){
        if(bits[i-1] == 1){
            num += pow((double) 2, (double) abs(i-8));
        }
    }

    return (int) num;
}

void encode_char(const char character, bool bits[8]){
    int numchar = (int) character;
    ten_to_two(numchar, bits);
}

char decode_byte(bool bits[8]){
    return (char) two_to_ten(bits);
}

void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
    
    int len = strlen(string) + 1;
    
    for(int i=0; i < len; i++){
        bool tmp[8];
        encode_char((int) string[i], tmp);
        for(int j = 0; j < 8; j++){
            bytes[i][j] = tmp[j];
        }
    }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]){

    for(int i =0; i < rows; i++){
        
        string[i] = decode_byte(bytes[i]);
    }

}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int r = 0;

    for(int i = 0; i < offset*8; i++){
        for(int k = 0; k < cols; k++){

            if(bytes[k+r][i%8] && k+r < rows){
                blocks[i][k] = true;
            }else{
                blocks[i][k] = false;
            }
               
        }
        if(i % 8 == 7) r += cols;
        
    }

}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int r = 0;

    for(int i = 0; i < offset*8; i++){

        for(int k = 0; k < cols; k++){ 
            
            if(blocks[i][k] && k+r < rows){
                
                bytes[k+r][i%8] = true;

            }else{
                bytes[k+r][i%8] = false;
                  
            }
            
            
        }

        if(i % 8 == 7){ 
            r += cols;  
        }
        
    }
}
