#include <stdio.h>

char to_low(const char sym){

    if(sym >= 'A' && sym <= 'Z'){
        return sym + 32;
    }
    return sym;
    
}

char * to_num(int num){

    

    float n = (float) num;
    int l = 0;
    float pow = 10.01;
    static char result[100];

    if(num == 0){
        result[0] = '0';
        result[1] = '\0';
        return result;
    
    }

    while(n >= 1){
        n = n / 10.0;
        l++;
    }

    for(int i = 0; i < l; i++){
        n *= (float)pow;
        
        int new_num = (int)n;
        
        
        
        result[i] = (char) (new_num + 48);
        
        
        
        //printf("new num = %f\n", (float)new_num);
        n -= new_num;
        //printf("n = %f\n", n);
    }

    result[l] = '\0';
    return result;

}

int main(int argc, char* argv[]){

    if(argc != 2){
        return 0;
    }
    
    FILE *fp = fopen(argv[1], "r");
    char ananas[] = "ananas";
    int sym_count = 0; 
    int result_count = 0;
    char sym;
    sym = fgetc(fp);
    int i = 0;
    while(sym != EOF){

        if(to_low(sym) != ananas[i]){
             i=0;
             sym_count = 0;
             
        }
        
        if(to_low(sym) == ananas[i]){
            sym_count++;
            i++;
        }
             

        if(sym_count == 6){
            
            result_count++;
            //printf("%d\n", result_count);
            sym_count = 0;
        }
        sym = fgetc(fp);
    }
    
    fclose(fp);

    fp = fopen(argv[1], "w");
    //printf("%d\n", result_count);
    char* res  = to_num(result_count);
    //printf("%s\n", res);

    int len = 0;
    while(res[len]){
        len++;
    }

    for(int i = 0; i < len; i++){
        fputc(res[i], fp);
    }
    
    
    fclose(fp);

    return 0;


}