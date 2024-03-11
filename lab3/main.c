#include <stdio.h>
#include <stdbool.h>


bool check_prime(int number)
{
  return false;
}


bool check_fib(int number)
{
  return false;
}


bool calculate_prime_fibs(int max_number, int min_number)
{
  return false;
}


int main(int argc, char *argv[])
{
  
  int min_number = 1;
  int max_number = 10000000;

  printf("Number of prime fibs between %d and %d is: %d\n", min_number, max_number, calculate_prime_fibs(min_number, max_number));
  
  return 0;
}
