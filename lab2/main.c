#include <stdio.h>
#include <time.h>

#define PERF_ITER 10000000

float invsqrt(float number);
float opt_invsqrt(float number);
float fast_invsqrt(float number);


int main(int argc, char *argv[])
{
  clock_t begin, end;

  float res1 = invsqrt(9.0F);
  float res2 = opt_invsqrt(9.0F);
  float res3 = fast_invsqrt(9.0F);
  printf("%f\n", res1);
  printf("%f\n", res2);
  printf("%f\n", res3);

  begin = clock();
  for (int i = 0; i < PERF_ITER; i++) {
    invsqrt(9.0F);
  }
  end = clock();
  printf("invsqrt = %f\n", (float)(end - begin) / CLOCKS_PER_SEC);

   begin = clock();
  for (int i = 0; i < PERF_ITER; i++) {
    opt_invsqrt(9.0F);
  }
  end = clock();
  printf("optsqrt = %f\n", (float)(end - begin) / CLOCKS_PER_SEC);
 
  begin = clock();
  for (int i = 0; i < PERF_ITER; i++) {
    fast_invsqrt(9.0F);
  }
  end = clock();
  printf("fastsqrt = %f\n", (float)(end - begin) / CLOCKS_PER_SEC);



  return 0;
}
