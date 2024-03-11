#include <stdio.h>


int main(int argc, char *argv[])
{
  
  int min_number = 1;
  int max_number = 10000000;

  printf("Number of prime fibs between %d and %d is: %d\n", min_number, max_number, calculate_prime_fibs(min_number, max_number));
  
  return 0;
}
