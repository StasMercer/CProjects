#include <stdio.h>
#include <math.h>
#define M_PI acos(-1.0)

double getSliceVol(double sliceStart, double sliceEnd, int m,  double wholes[m][4]){
       
        double sliceVolume = (sliceEnd - sliceStart) * 100.0 * 100.0;
        double wholesVolume = 0.0;
        double singleWhole = 0.0;

        for(int k = 0; k < m; k++){
            double wholeX0 = wholes[k][3] - wholes[k][0];
            double wholeX1 = wholes[k][3] + wholes[k][0];
            //printf("wx0=%f,wx1=%f\n", wholeX0, wholeX1);
            //printf("st=%f,end=%f\n", sliceStart, sliceEnd);
            singleWhole = 0;
            double wVol = 0;

                if(wholeX0 >= sliceStart && wholeX1 <= sliceEnd){
                    singleWhole = (4.0/3.0) * M_PI * pow(wholes[k][0], 3.0);
                    //printf("wholes = %f\n", singleWhole);
                }
                
                if(wholeX0 < sliceStart && wholeX1 >= sliceStart && wholes[k][3] <= sliceStart){
                    double h = wholeX1- sliceStart;
                    //printf("st=%f, end=%f, w0=%f, w1=%f\n", sliceStart, sliceEnd, wholeX0, wholeX1);
                    //printf("h1 = %f\n", h);
                    wVol = M_PI * pow(h, 2.0) * (wholes[k][0] - ((1.0/3.0) * h)); // the volume of sphere part
                    //printf("volh1 = %f\n", wVol);
                    singleWhole += wVol;
                }
                
                if(wholeX0 < sliceStart && wholes[k][3] >= sliceStart && wholeX1 >= sliceStart){
                    double h = sliceStart - wholeX0;
                    //printf("h2 = %f\n", h);
                    wVol = M_PI * pow(h, 2.0) * (wholes[k][0] - ((1.0/3.0) * h)); // the volume of sphere part
                    
                    singleWhole -= wVol;
                }
                
                if(wholeX1 > sliceEnd && wholeX0 <= sliceEnd && wholes[k][3] >= sliceEnd){
                    
                    double h =  sliceEnd - wholeX0;
                    //printf("h3 = %f\n", h);
                    wVol = M_PI * pow(h, 2.0) * (wholes[k][0] - ((1.0/3.0) * h)); // the volume of sphere part
                    singleWhole += wVol;
                }
                
                if(wholeX1 > sliceEnd && wholeX0 <= sliceEnd && wholes[k][3] <= sliceEnd){
                    
                    double h =  wholeX1 - sliceEnd;
                    //printf("h4 = %f\n", h);
                    wVol = M_PI * pow(h, 2.0) * (wholes[k][0] - ((1.0/3.0) * h)); // the volume of sphere part
                    //printf("vol4 = %f\n", wVol);
                    singleWhole -= wVol;

                }
                

                if(singleWhole < 0){
                    singleWhole += (4.0/3.0) * M_PI * pow(wholes[k][0], 3.0);
                }
                wholesVolume += singleWhole; 
                
        }
        
        

        sliceVolume = sliceVolume - wholesVolume;
        
        return sliceVolume;
    

    

}

void get_slices(int m, int s, double slices[s], double wholes[m][4]){
    
    int counter = 0;
    double x0 = 0.0;
    double x1 = 200.0;
    double c = 0.0;
    double start = 0;
    double pureVol = getSliceVol(0.0, 100.0, m, wholes);
    //printf("pure = %f\n", pureVol);
    double targetVol = pureVol / s;

    //printf("pure = %f\n", targetVol);
        for(int i = 0; i < s; i++){
            
             
            
            x0 = 0;
            x1 = 200.0;
            double singleSlice = 1.0;
            while(fabs(targetVol - singleSlice) > 1e-6){
                c = (x0 + x1) /2.0;
                singleSlice = getSliceVol(start, start+c, m, wholes);
                if(singleSlice < targetVol){
                    x0 = c;
                }else if(singleSlice == targetVol){
                    break;
                }else{
                    x1= c;
                }
                
                //printf("x0=%f,x1=%f\n", x0, x1);
                counter++;
                if(counter > 50) break;
            }
            //printf("sliceVol=%f, c=%.9f\n", singleSlice, c);
            //printf("x0=%f, x1=%.9f\n", x0, x1);
            slices[i] = c;
            counter = 0;
            start += c;
            //printf("\n");
            
        }
        
            
    

}


int main(){
    
    int m=0; 
    int s=0;
    
    scanf("%d %d", &m, &s);

    double arr[m][4];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < 3; j++){
            scanf("%lf ",&arr[i][j]);
            arr[i][j] /= 1000.0;
        }
        scanf("%lf\n", &arr[i][3]);
        arr[i][3] /= 1000.0;
    }
    
    
    double slices[s];
    get_slices(m, s, slices, arr);
    for(int i = 0; i < s; i++){
        printf("%.9f\n", slices[i]);
    }
    //printf("%d\n", get_different(n, k, arr));
    
    return 0;
}