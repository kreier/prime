#include <stdio.h>
#include <time.h>
#include <math.h>

int primes[10000] = {3, 5, 7};
int found = 4;                   // we already know 2, 3, 5, 7

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

int find_primes(int limit) {
    for(int number=11; number < limit + 1; number += 2) { 
        if( is_prime(number) == 1) {
            primes[found - 1] = number;
            found++;
        }
    }
    primes[found-1] = limit;
}

int is_prime_fast(int number)
{
    int largest_divider = (int)(sqrt(number));
    int flag_prime = 1;
    for(int i=0; i < found; i++)
    {
        if(number % primes[i] == 0) 
        {
            flag_prime = 0;
            break;
        }
        if(primes[i] > largest_divider)
        {
            break;
        }
    }
    return flag_prime;
}

int main()
{
    int last = 10000000;
    clock_t start, end;
    double cpu_time_used;
    printf("Calculating prime numbers until %d in C v5.0.2023\n", last);
    start = clock();
    int largest_divider = (int)(sqrt(last));
    if(largest_divider % 2 == 0)
    {
        largest_divider += 1;
    }
    find_primes(largest_divider);
    printf("Found %d primes until %d to use as dividers.\n", found, largest_divider);
    for(int number = largest_divider + 2; number < last; number += 2)
    {
        found += is_prime_fast(number);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Found %d prime numbers. ", found);
    printf("This took %f seconds.\n",cpu_time_used);
}
