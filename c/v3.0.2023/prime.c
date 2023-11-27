#include <stdio.h>
#include <time.h>
#include <math.h>

int is_prime(int number) {
    int prime = 1;
    for (int divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2)
    {
        if (number % divider == 0)
        {
            prime = 0;
            break;
        }
    }
    return prime;
}

int main()
{
    int last = 10000000;
    int found = 4;   // we already know 2, 3, 5, 7
    const int arraylength = (int)(last / log(last));
    int primes[1000] = {2, 3, 5, 7};
    clock_t start, end;
    double cpu_time_used;
    printf("Calculating prime numbers until %d in C v3.0.2023\n", last);
    start = clock();
    for (int number = 11; number < last; number += 2)
    {
        found += is_prime(number);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nFound %d prime numbers.\n", found);
    printf("This took %f seconds.\n",cpu_time_used);
}
