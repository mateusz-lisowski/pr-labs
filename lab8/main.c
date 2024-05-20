#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_THREADS 4
#define UPPER_LIMIT 100
#define MAX_PRIME 100

int primes[MAX_PRIME];
int curr_p = 0;
pthread_mutex_t m_p;

// Funkcja do sprawdzania, czy liczba jest pierwsza
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Funkcja wykonywana przez wątki
void *check_prime(void *arg) {
    int num = *((int *)arg);
    if (is_prime(num)) {
        pthread_mutex_lock(&m_p);
        if (curr_p < MAX_PRIME) {
            primes[curr_p++] = num;
        }
        pthread_mutex_unlock(&m_p);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&m_p, NULL);
    int numbers[UPPER_LIMIT - 1];

    for (int i = 2; i <= UPPER_LIMIT; ++i) {
        numbers[i - 2] = i;
    }

    int current_index = 0;

    while (current_index < UPPER_LIMIT - 1) {
        for (int i = 0; i < NUM_THREADS && current_index < UPPER_LIMIT - 1; ++i) {
            pthread_create(&threads[i], NULL, check_prime, (void *)&numbers[current_index]);
            ++current_index;
        }

        for (int i = 0; i < NUM_THREADS && current_index <= UPPER_LIMIT; ++i) {
            pthread_join(threads[i], NULL);
        }
    }

    printf("Liczby pierwsze znalezione w przedziale od 2 do %d:\n", UPPER_LIMIT);
    for (int i = 0; i < curr_p; ++i) {
        printf("%d ", primes[i]);
    }
    printf("\n");

    pthread_mutex_destroy(&m_p);
    return 0;
}
