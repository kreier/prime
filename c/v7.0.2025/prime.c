// prime to 2^32 version 5.5.2025 (Parallelized with OpenMP)
// Original version from 2025/04/26

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <omp.h> // Include OpenMP header

// Note: Array size should be sufficient for primes up to sqrt(2^32) ~ 65536.
// The number of primes below 65536 is 6542. Let's keep the size reasonable.
#define MAX_PRIMES_SQRT 6550
int32_t primes[MAX_PRIMES_SQRT] = {3, 5, 7}; // Primes for sieving: 3, 5, 7 pre-filled
int32_t primes_count_sqrt = 3;              // Count of primes found by find_primes (initially 3)

// --- Original is_prime function (used only by find_primes) ---
// Checks primality by trial division up to sqrt(number).
// Less efficient but only used for the relatively small range up to sqrt(last).
int is_prime(int32_t number) {
    // We start checking from 3, skipping even numbers.
    int32_t limit = (int32_t)(sqrt(number)) + 1;
    for (int32_t divider = 3; divider < limit; divider += 2) {
        if (number % divider == 0) {
            return 0; // Not prime
        }
    }
    return 1; // Prime
}

// --- Finds primes up to 'limit' (used for divisors) ---
// Fills the 'primes' array sequentially.
void find_primes(int32_t limit) {
    // Start checking from 11 (since 3, 5, 7 are already included)
    for (int32_t number = 11; number <= limit; number += 2) {
        if (is_prime(number)) {
            if (primes_count_sqrt < MAX_PRIMES_SQRT) {
                primes[primes_count_sqrt] = number;
                primes_count_sqrt++;
            } else {
                fprintf(stderr, "Error: Exceeded MAX_PRIMES_SQRT limit.\n");
                // Decide how to handle this: exit, break, etc.
                // For now, we just stop adding more primes.
                break;
            }
        }
    }
    // The original code added 'limit' at the end, which seems incorrect
    // if 'limit' itself isn't prime. Removing that line.
    // primes[primes_count_sqrt - 1] = limit; // Removed this
}

// --- Fast primality test using pre-calculated primes ---
// Checks divisibility only by primes in the 'primes' array up to sqrt(number).
int is_prime_fast(uint32_t number) {
    uint32_t largest_divider = (uint32_t)(sqrt(number));
    // Check divisibility by the primes found earlier
    for (int i = 0; i < primes_count_sqrt; i++) {
        // If the current prime divisor is already larger than sqrt(number),
        // then 'number' must be prime (if it wasn't divisible by smaller primes).
        if (primes[i] > largest_divider) {
            break;
        }
        if (number % primes[i] == 0) {
            return 0; // Not prime
        }
    }
    return 1; // Prime
}

int main() {
    uint32_t last = 10000000; //4294967295; // 2^32 - 1
    clock_t start_time, end_time;
    double cpu_time_used;

    // Use uint64_t for the total count to prevent potential overflow
    uint64_t total_primes_found = 0;

    printf("Calculating prime numbers in C up to %u using OpenMP\n", last);
    printf("Algorithm v5.5.2025 (Parallel)\n");

    // --- Phase 1: Find primes up to sqrt(last) sequentially ---
    start_time = clock(); // Use clock() for overall time, omp_get_wtime() for wall time
    double wall_start = omp_get_wtime();

    int32_t largest_divider_sqrt = (int32_t)(sqrt(last));
    // Ensure the limit for find_primes is odd if needed, though the function handles it.
    // if (largest_divider_sqrt % 2 == 0) {
    //     largest_divider_sqrt--; // Or adjust logic in find_primes
    // }

    // Add prime '2' to the initial count explicitly
    total_primes_found = 1; // For prime '2'

    // Add initial primes {3, 5, 7} to count
    total_primes_found += primes_count_sqrt;

    // Find primes needed for divisors up to sqrt(last)
    find_primes(largest_divider_sqrt);

    // Update the count of primes found so far
    total_primes_found = primes_count_sqrt + 1; // +1 for prime '2'

    // Update count based on how many primes find_primes actually found
    // This replaces the initial += 3 with the actual count found by find_primes
    // total_primes_found = 1 + primes_count_sqrt; // Recalculate based on actual count

    printf("Phase 1: Found %d primes up to %d to use as divisors.\n",
           primes_count_sqrt, largest_divider_sqrt);
    printf("Primes found so far (including 2): %lu\n", total_primes_found);

    // --- Phase 2: Check numbers from sqrt(last) to last in parallel ---
    printf("Phase 2: Starting parallel check from %u to %u...\n",
           largest_divider_sqrt + 1, last);

    // Counter for primes found in the parallel section
    uint64_t primes_in_parallel = 0;

    // Determine the starting number for the parallel loop.
    // It should be the first odd number *after* largest_divider_sqrt.
    uint32_t parallel_start_num = (largest_divider_sqrt % 2 == 0) ?
                                     largest_divider_sqrt + 1 :
                                     largest_divider_sqrt + 2;


    // *** OpenMP Parallel Loop ***
    // The loop iterates over odd numbers starting from parallel_start_num up to 'last'.
    // 'primes_in_parallel' is the reduction variable. Each thread calculates its
    // own sum, and OpenMP combines them at the end.
    #pragma omp parallel for reduction(+:primes_in_parallel) schedule(dynamic)
    for (uint32_t number = parallel_start_num; number < last; number += 2) {
         // Check for potential overflow if number + 2 exceeds UINT32_MAX in the next iteration.
         // Although the loop condition 'number < last' handles the final value,
         // adding 2 to last-1 or last could wrap around if not careful.
         // However, since 'last' is UINT32_MAX, 'number < last' prevents 'number'
         // from reaching UINT32_MAX, so 'number += 2' is safe here.

        primes_in_parallel += is_prime_fast(number);
    }
    // End of parallel region. 'primes_in_parallel' now holds the total count from all threads.

    // Add the count from the parallel phase to the total
    total_primes_found += primes_in_parallel;

    end_time = clock();
    double wall_end = omp_get_wtime();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // Total CPU time might exceed wall time
    double wall_time_used = wall_end - wall_start; // Actual time elapsed

    printf("\nCalculation complete.\n");
    printf("Found %lu prime numbers up to %u.\n", total_primes_found, last);
    printf("Total CPU time used: %f seconds.\n", cpu_time_used);
    printf("Total Wall clock time: %f seconds.\n", wall_time_used);
    printf("Number of threads used (max): %d\n", omp_get_max_threads());


    // Optional: Print the last few primes found by find_primes
    // printf("Last few primes used as divisors: ");
    // int print_start = (primes_count_sqrt > 10) ? primes_count_sqrt - 10 : 0;
    // for (int i = print_start; i < primes_count_sqrt; i++) {
    //     printf("%d ", primes[i]);
    // }
    // printf("\n");

    return 0;
}