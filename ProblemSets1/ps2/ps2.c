#include <stdio.h>
#include <math.h>


float lift_a_car(const int stick_length, const int human_weight, const int car_weight);
float unit_price(const float pack_price, const int rolls_count, const int pieces_count);
int collatz(int number);
int opposite_number(int n, int number);
void counter(int input_array[], int array_size, int result_array[2]);
unsigned long sum_squared(const int line);
int array_max(const int input_array[], const int array_size);
int array_min(const int input_array[], const int array_size);
unsigned long special_counter(const int input_array[], const int array_size);
int special_numbers(const int input_array[], const int array_size, int result_array[]);


int main(){
    // printf("%.4f\n", unit_price(4.79, 16, 150));
    // int input_array[] = {1,2,3,4,5};
    // int result_array[2];
    // counter(input_array, 5, result_array);
    // printf("%d %d\n", result_array[0], result_array[1]);
    
    //printf("%lu\n", sum_squared(40));
    //int input_array[] = {1,2,3,4,5};
    
    //printf("%d\n", array_max(NULL, 5));
    //int input_array[] = {11,12,13,14,15};
    //printf("%lu\n", special_counter(input_array, 5));
    
    int input_array[] = {16,17,4,3,5,2};
    int result_array[6];
    int count = special_numbers(input_array, 6, result_array);
    for(int i = 0; i < count; i++){
        printf("%d ", result_array[i]);
    }
    printf("\n");
    
    return 0;
}

float lift_a_car(const int stick_length, const int human_weight, const int car_weight){
    return roundf((float)(stick_length * human_weight) / (human_weight + car_weight) * 100) / 100;  
}

float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
    
    float result = (pack_price/rolls_count)/pieces_count*100;
    return roundf(result*100)/100;
}

int collatz(int number){
    int steps_count = 1;
     
    while(number != 1){
        if (number % 2 == 0){
            steps_count ++;
            number = number / 2;
        }else
        {
            steps_count ++;
            number = (3* number) + 1;

        }
        
    }

    return steps_count;
}


int opposite_number(int n, int number){
    return number + (n/2) >= n ? number - (n/2) : number + (n/2); 
}

void counter(int input_array[], int array_size, int result_array[2]){
    int paired_sum = 0;
    int unpaired_sum = 0;

    for(int i = 0; i < array_size; i++){
        if(i % 2 == 0 ){
            paired_sum += input_array[i];
        }else{
            unpaired_sum += input_array[i];
        }
    }

    result_array[0] = paired_sum;
    result_array[1] = unpaired_sum;
}

unsigned long sum_squared(const int line){
    
    unsigned long result = 0;
    unsigned long pascal[line+1][line+2];

    pascal[0][0] = 1;
    pascal[1][0] = 1;
    pascal[1][1] = 1;

    for(int i = 1; i < line; i++){
        for(int j = 1; j < i+1; j++){
            pascal[i+1][0] = 1; 
            pascal[i+1][j] = pascal[i][j-1] + pascal[i][j];
        }
        pascal[i+1][i+1] = 1; 
    }

    for(int i = 0; i < line+1; i++){
        result += pascal[line][i] * pascal[line][i];
    }

    return result;
}

int array_min(const int input_array[], const int array_size){

    if(input_array == NULL){
        return -1;
    }

    int min = input_array[0];
    for(int i = 0; i < array_size; i++){
        if(input_array[i] < min){
            min = input_array[i];
        }
    }
    return min;
}

int array_max(const int input_array[], const int array_size){
    if(input_array == NULL){
        return -1;
    }
    int max = input_array[0];
    for(int i = 0; i < array_size; i++){
        if(input_array[i] > max){
            max = input_array[i];
        }
    }
    return max;
}

unsigned long special_counter(const int input_array[], const int array_size){

    unsigned long result = 0;
    for(int i = 0; i<array_size; i++){
        if(i % 2 != 0){
            result += (unsigned long) (input_array[i] * input_array[i]);
        }else{
            result += (unsigned long) input_array[i];
        }
    }

    return result;










}


int special_numbers(const int input_array[], const int array_size, int result_array[]){
    int count = 0;
    
    for(int i = 0; i < array_size; i++){
        int sum = 0;
        for(int j = i + 1; j < array_size; j++){
            sum += input_array[j];
        }

        if(input_array[i] > sum){
            result_array[count] = input_array[i];
            count++;
        }
    }
    return count;
}













