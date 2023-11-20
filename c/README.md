# Calculating prime numbers in C

Obviously this is one of the fastest way to calculate or execute any code. Here is the code, for regular x86 or x86_64 as well as ARM on M1 from Apple. Compilation is done by `gcc prime.c -lm -o prime` on the command promt. Without the `-lm` linker command the math import will not work for the sqrt function.

## Code

``` c
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

int main()
{
    int last = 1000000;
    int found = 4;   // we already know 2, 3, 5, 7
    const int arraylength = (int)(last / log(last));
    // printf("%d",arraylength);
    int primes[1000000] = {2, 3, 5, 7};
    clock_t start, end;
    double cpu_time_used;
    printf("Calculating prime numbers until %d\n", last);
    start = clock();
    for (int number = 11; number < last; number += 2)
    {
        int prime = 1;
        for (int divider = 3; divider < (int)(sqrt(number)) + 1; divider += 2)
        {
            if (number % divider == 0)
            {
                prime = 0;
                break;
            }
        }
        if (prime ==  1)
        {
            primes[found] = number;
            found += 1;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    for (int i = 0; i < found - 1; i++)
    {
        printf("%d, ",primes[i]);
    }
    printf("\nFound %d prime numbers.\n", found);
    printf("This took %f seconds.",cpu_time_used);
}
```
