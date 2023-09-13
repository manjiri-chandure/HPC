#include<stdio.h>
#include<omp.h>
#define vecsize 100
int main(){
   float vector1[vecsize];
   float vector2[vecsize];
   float result = 0.0;
   
   for(int i=0; i<vecsize; i++){
      vector1[i] = i + 1.1;
      vector2[i] = i + 2.2;
   }
   double serial_start_time = omp_get_wtime();
   for(int i=0; i<vecsize; i++){
      result += vector1[i]*vector2[i];
   }
   double serial_end_time = omp_get_wtime();
   printf("serial time: %f\n", serial_end_time-serial_start_time);

   // parallel
   result = 0.0;
   double p_start_time = omp_get_wtime();
   #pragma omp parallel for schedule(dynamic) reduction(+:result) num_threads(4)
   for(int i=0;i<vecsize; i++){
      result += vector1[i]*vector2[i];
   }
   double p_end_time = omp_get_wtime();
   printf("parallel time: %f\n", p_end_time - p_start_time);
}