#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n)
{
  int i, j;
  if (n < 2)
    return n;
  else
  {
#pragma omp task shared(i)
    i = fibonacci(n - 1);
#pragma omp task shared(j)
    j = fibonacci(n - 2);

#pragma omp taskwait
    return i + j;
  }
}
int main(int argc, char **argv)
{
  char *a = argv[1];
  int n = atoi(a), result;
#pragma omp parallel
  {
#pragma omp single

    result = fibonacci(n);
  }
  printf("Result is %d\n", result);
  return 0;
}
