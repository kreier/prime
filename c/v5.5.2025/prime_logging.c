// prime to 2E32 version 5.4.2024 uint32 from 2023/12/23

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
    const uint32_t scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295};
    const int reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221};
    for (int i = 0; i < 11; i++)
    {
        uint32_t last = scope[i];
        found = 4;
        clock_t start, end;
        double cpu_time_used;
        printf("Calculating prime numbers in C v5.4.2024 until %u \n", last);
        start = clock();
        int32_t largest_divider = (int32_t)(sqrt(last));
        if(largest_divider % 2 == 0)
        {
            largest_divider += 1;
        }
        find_primes(largest_divider);
        printf("Found %d primes until %d to use as dividers.\n", found, largest_divider);
        for(uint32_t number = largest_divider + 2; number < last; number += 2)
        {
            found += is_prime_fast(number);
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Found %d prime numbers. It should be %d.\n", found, reference[i]);
        printf("This took %f seconds.\n\n",cpu_time_used);
        char filename[20];
        sprintf(filename, "%u.txt", scope[i]);
        FILE *logfile;
        logfile = fopen(filename, "w");
        fprintf(logfile, "Calculating prime numbers until %u in C v5.0.2023\n", last);
        fprintf(logfile, "Found %d prime numbers. It should be %d.\n", found, reference[i]);
        fprintf(logfile, "This took %f seconds.\n\n", cpu_time_used);
        fclose(logfile);
    }
}
