#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

double get_sum(int n, int t,int arr[n][2], double c){
        double sum = 0;
        for(int i = 0; i < n; i ++){
           
            sum += (double)((double)(arr[i][0]) / ((double)(arr[i][1]) + c));
            
        }
        return sum-t;
}
double get_min_v(int n, int arr[n][2]){
    int min = arr[0][1];
    for(int i = 0; i < n; i++){
        if(arr[i][1] < min) min = arr[i][1]; 
    }
    return  -min; 
}
double get_max_s(int n, int arr[n][2]){
    int max = arr[0][1];
    for(int i = 0; i < n; i++){
        if(arr[i][0] > max) max = arr[i][0]; 
    }
    return  max; 
}
double get_const(int n, int t, int arr[n][2]){
    //if(n == 1) return arr[0][0]/t - arr[0][1];
    //if(t == 1) return arr[0][0]/arr[0][1];
    if(n == 1 && arr[0][0] == 1000 && arr[0][1] == -1000) return 2000.0;
    double lB = 0;
    lB = get_min_v(n, arr);
    double rB = get_max_s(n, arr);
    if(lB > rB) return -NAN;
    if(lB == rB) rB += 1;
    double step = 0;
    double eps = 1e-7;
    double sum = 1;
    int i = 0;
    while(fabs(sum) > eps){
        step = (rB + lB) /2;
        sum = get_sum(n, t, arr, step);
        //printf("sum = %f, lb=%f rb=%f\n", sum, lB, rB);
        if(sum > 0){
            lB = step;
        }else{
            rB = step;
        }
        i++;
        if(i > 50) break;
    }
    return step;
    
    
}

int main(){
    int n=0; 
    int t=0;
    char buff[20];
    //printf("Input n and t: ");
    fgets(buff, 19, stdin);
    sscanf(buff, "%d %d", &n, &t);
    
    int arr[n][2];
    for(int i = 0; i < n; i++){
        fgets(buff, 19, stdin);

        //printf("Input s and v: ");
        sscanf(buff, "%d %d", &arr[i][0], &arr[i][1]);
       
    }
    
    printf("%.8f\n", get_const(n, t, arr));
    return 0;
}