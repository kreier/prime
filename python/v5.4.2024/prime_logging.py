# prime v5.4.2023
# cycles through limits and writes to the filesystem

import math, time, os, cpuinfo

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295]
reference = [25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221]
time_calc = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

def is_prime(number):
    global found
    flag_prime = 1
    for divider in range(3, int(math.sqrt(number)) + 1, 2):
        if number % divider == 0:
            flag_prime = 0
            break
    return flag_prime

def find_primes(largest):
    global primes
    global found
    for number in range(11, largest + 1, 2):
        if is_prime(number) > 0:
            found += 1
            primes.append(number)

def is_prime_fast(number):
    global found
    flag_prime = 1
    largest_divider = int(math.sqrt(number)) + 1
    for divider in primes:
        if number % divider == 0:
            flag_prime = 0
            break
        if divider > largest_divider:
            break
    return flag_prime

def elapsed_time(seconds):
    hours = int(seconds/3600)
    minutes = int(seconds/60 - hours*60)
    sec = int(seconds - minutes*60 - hours*3600)
    return(f"{hours}h {minutes}min {sec}s")

if __name__ == "__main__":
    for i in range(len(scope)):
        last = scope[i]
        found = 4              # we start from 11, know 2, 3, 5, 7
        primes = [3, 5, 7]     # exclude 2 since we only test odd numbers    
        print(f"Prime numbers to {last} in Python with algorithm v5.4.2024")
        start = time.perf_counter_ns()
        dot = start
        column = 1
        largest_divider = int(math.sqrt(last))
        if largest_divider % 2 == 0:
            largest_divider += 1
        print(f'First find primes up to {largest_divider}.')
        find_primes(largest_divider)
        print(f'Found {found} primes, now use them as divisors.')
        for number in range(largest_divider + 2, last, 2):
            found += is_prime_fast(number)
            if (time.perf_counter_ns() - dot) > 2000000000:
                print(".", end="")
                dot = time.perf_counter_ns()
                column += 1
                if column > 30:
                    t = elapsed_time((time.perf_counter_ns() - start)/1000000000)
                    print(f" {t} - {number} {int(number*100/last)}% ")
                    column = 1
        end = time.perf_counter_ns()
        if (end - start)/1000000000 > 2:
            print(" ")
        print(f"This took: {(end - start)/1000} microseconds. {elapsed_time((end - start)/1000000000)}")
        print(f"I found {found} prime numbers. Should be {reference[i]}.\n")
        filename = str(last) + ".txt"
        with open(filename, "w") as fp:
            fp.write('prime v5.0.2023 in python\n')
            fp.write(cpuinfo.get_cpu_info()['brand_raw'])
            fp.write(f'\nPrimes to {last} took {(end - start)/1000} microseconds. ')
            fp.write(elapsed_time((end - start)/1000000000))
            fp.write(f'\nFound {found} primes. Should be {reference[i]}.\n')
        time_calc[i] = (end - start)/1000
    with open("summary.txt", "w")as fp:
        fp.write('Summary of prime v5.0.2023 in python\n')
        fp.write(cpuinfo.get_cpu_info()['brand_raw'])
        fp.write('\n     last       time in microseconds\n')
        for i in range(len(scope)):
            skip = " " * int(10.9 - math.log10(scope[i]))
            fp.write(skip)
            fp.write(f'  {scope[i]}   {time_calc[i]} \n')
