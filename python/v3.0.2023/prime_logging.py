# prime v3.0.2023
# cycles through limits and writes to the filesystem

import math, time, os, cpuinfo

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000]
reference = [25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 123456789]

def is_prime(number):
    flag_prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = False
            break
    return flag_prime

if __name__ == "__main__":
    for i in range(len(scope)):
        last = scope[i]
        found = 4              # we start from 11, know 2, 3, 5, 7
        primes = [3, 5, 7]     # exclude 2 since we only test odd numbers    
        print(f"Prime numbers to {last} with algorithm v3.0.2023")
        start = time.perf_counter_ns()
        for number in range(11, last, 2):
            if is_prime(number):
                found += 1
        end = time.perf_counter_ns()
        print(f"This took: {(end - start)/1000} microseconds.")
        print(f"I found {found} prime numbers. Should be {reference[i]}.")
        filename = str(last) + ".txt"
        with open(filename, "w") as fp:
            fp.write('prime v3.0.2023\n')
            fp.write(cpuinfo.get_cpu_info()['brand_raw'])
            fp.write(f'\nPrimes to {last} took {(end - start)/1000} microseconds.')
            fp.write(f'\nFound {found} primes. Should be {reference[i]}.\n')
