#include<stdio.h>
#include<omp.h>
#define vecsize 100000
int main(){
    int s = 5;
    float vector[vecsize];
    for(int i=0; i<vecsize; i++){
        vector[i] = i;
    }

    double start_time = omp_get_wtime();
    for(int i=0; i<vecsize; i++){
           vector[i] += s;
    }
    double end_time = omp_get_wtime();
    printf("serial time: %f\n", end_time-start_time);

    // parallel

    for(int i=0; i<vecsize; i++){
        vector[i] = i;
    }

    double s_t = omp_get_wtime();
    #pragma omp parallel for private(s) num_threads(1000)
    for(int i=0; i<vecsize; i++){
        vector[i] += s;
    }
    double e_t = omp_get_wtime();

    printf("parallel time: %f\n",e_t-s_t);
    return 0;
}