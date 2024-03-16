#include <stdio.h>
#include <stdbool.h>


bool check_prime(int number)
{
  if (number < 2)
		return false;

  for (int i = 2; i <= number / 2; i++) 
  {
    if (number % i == 0) 
      return false;		
  }
  
   return true; 
}


bool check_fib(int number)
{
  if (number == 1 || number == 2)
		return true;
 
	int fib1 = 1;
	int fib2 = 1;
	int fib = fib1 + fib2;
 
	while (fib < number)
  {
		fib2 = fib1;
		fib1 = fib;
		fib = fib1 + fib2;
	}
 
	if (number == fib)
  {
		return true;
  }
  
  return false;
}


int calculate_prime_fibs(int max_number, int min_number)
{
 	int count = 0;
 
	for (int i = 0; i < max_n; i++)
  {
		if (is_fibbonaci(i) && is_prime(i))
    {
			count += 1;
			printf("prime fib: %d\n", i);
		}
	}
 
	return count;
}


int main(int argc, char *argv[])
{
  
  int min_number = 1;
  int max_number = 10000000;

  printf("Number of prime fibs between %d and %d is: %d\n", min_number, max_number, calculate_prime_fibs(min_number, max_number));
  
  return 0;
}
