#include <stdio.h>
#include <time.h>
#include <math.h>

int main()
{
    const int scope[] = {100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000};
    const int reference[] = {25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534};
    for (int i = 0; i < 9; i++)
    {
        int last = scope[i];
        int found = 4;   // we already know 2, 3, 5, 7
        int primes[10000] = {3, 5, 7};
        clock_t start, end;
        double cpu_time_used;
        printf("Calculating prime numbers until %d in C v2.0.2022\n", last);
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
                found += 1;
            }
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Found %d prime numbers. It should be %d.\n", found, reference[i]);
        printf("This took %f seconds.\n\n",cpu_time_used);
        char filename[20];
        sprintf(filename, "%d.txt", scope[i]);
        FILE *logfile;
        logfile = fopen(filename, "w");
        fprintf(logfile, "Calculating prime numbers until %d in C v2.0.2022\n", last);
        fprintf(logfile, "Found %d prime numbers. It should be %d.\n", found, reference[i]);
        fprintf(logfile, "This took %f seconds.\n\n", cpu_time_used);
        fclose(logfile);
    }
}
