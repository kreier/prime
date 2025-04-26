// prime to 2E31 version 5.4.2024 int32 from 2023/12/16

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

int32_t primes[6550] = {3, 5, 7};    // to store the 6542 primes to sqr(2E32)
int32_t found = 4;                   // we already know 2, 3, 5, 7

int is_prime(int32_t number) {
    int prime = 1;
    for (int32_t divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2)
    {
        if (number % divider == 0)
        {
            prime = 0;
            break;
        }
    }
    return prime;
}

void find_primes(int32_t limit) {
    for(int32_t number=11; number < limit + 1; number += 2) { 
        if( is_prime(number) == 1) {
            primes[found - 1] = number;
            found++;
        }
    }
    primes[found-1] = limit;
}

int is_prime_fast(uint32_t number)
{
    uint32_t largest_divider = (uint32_t)(sqrt(number));
    int flag_prime = 1;
    for(int i=0; i < found; i++)
    {
        if(number % primes[i] == 0) 
        {
            flag_prime = 0;
            break;
        }
        if(primes[i] >= largest_divider)
        {
            break;
        }
    }
    return flag_prime;
}

int main()
{
    uint32_t last = 10000000; // 4294967295
    clock_t start, end;
    double cpu_time_used;
    printf("Calculating prime numbers in C until %u with algorithm v5.4.2024\n", last);
    start = clock();
    int32_t largest_divider = (int32_t)(sqrt(last));
    if(largest_divider % 2 == 0)
    {
        largest_divider += 1;
    }
    find_primes(largest_divider);
    printf("Found %d primes until %d to use as divisors.\n", found, largest_divider);
    for(uint32_t number = largest_divider + 2; number < last; number += 2)
    {
        found += is_prime_fast(number);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Found %u prime numbers. ", found);
    printf("This took %f seconds.\n",cpu_time_used);
}
