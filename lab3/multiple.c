#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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


int calculate_prime_fibs(int index, int nest, int max_number)
{
	int count = 0;
  int process_number = 4;

  pid_t child0 = 0;
	pid_t child1 = 0;

	if (nest != 0)
	{
		child0 = fork(); 
    if (child0 == 0)
    {
      int new_index = 2 * index + 1;
      exit(calculate_prime_fibs(new_index, nest - 1, max_number));
    }

    child1 = fork(); 
    if (child1 == 0)
    {
      int new_index = 2 * index + 2;
      exit(calculate_prime_fibs(new_index, nest - 1, max_number));
	  }
  }

	int check_begin = max_number / process_number * index;
	int check_end = max_number / process_number * (index + 1);
	if (index == process_number - 1)
    check_end = max_number;

	for (int i = check_begin; i < check_end; i++)
  {
    if (check_fib(i) && check_prime(i))
			count += 1;
  }
  
  if (nest != 0)
	{
		int wstatus;
		
    waitpid(child0, &wstatus, 0); 
    count += WEXITSTATUS(wstatus);

		waitpid(child1, &wstatus, 0);
    count += WEXITSTATUS(wstatus);
	}

	return count;
}


int main(int argc, char *argv[])
{
  
  int min_number = 1;
  int max_number = 1000000000;
  
 	clock_t t;
 	t = clock();
 
	printf("Timer starts\n");

  printf("Number of prime fibs between %d and %d is: %d\n", min_number, max_number, calculate_prime_fibs(0, 2, max_number));
  
  printf("Timer ends\n");
	t = clock() - t;
 
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
  printf("The program took %f seconds to execute\n", time_taken);
  return 0;
}
