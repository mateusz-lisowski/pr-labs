#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>


struct Data
{
	int beg;
	int end;
};


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


DWORD WINAPI calculate_prime_fibs(void* d)
{
	Data* data = (Data*)d;

	for (int i = data->beg; i < data->end; i++)
	{
		if (check_fib(i))
		{
			// printf("fib: %d\n", i);
		}
	}

	return 0;
}


int main(int argc, char* argv[])
{

	int min_number = 1;
	int max_number = 100000000;


	for (int k = 2; k <= 64; k *= 2) {

		clock_t t;
		t = clock();

		//printf("Timer starts\n");

		HANDLE* all = (HANDLE*)malloc(sizeof(HANDLE) * k);

		for (int i = 0; i < k; i++) {

			int end = (max_number / k) * (i + 1);
			int beg = end - (max_number / k);

			Data* d = (Data*)malloc(sizeof(Data));
			d->beg = beg;
			d->end = end;

			all[i] = CreateThread(NULL, 0, calculate_prime_fibs, d, 0, NULL);

		}

		for (int i = 0; i < 2; i++) {
			WaitForSingleObject(all[i], INFINITE);
		}

		//printf("Timer ends\n");
		t = clock() - t;

		double time_taken = ((double)t) / CLOCKS_PER_SEC;
		printf("The program for %d took %f seconds to execute\n", k, time_taken);
	}

	return 0;
}