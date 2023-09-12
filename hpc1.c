#include<stdio.h>
#include<omp.h>

void PrintMes(){
    int temp = omp_get_thread_num();
    printf("Hellow World by thread no %d \n", temp);
}

int main(){
    // call omp for creating threads
    #pragma omp parallel num_threads(10)
    PrintMes();
    return 0;
}

