# prime v5.4.2024 with primes as a divider list up to 4294967295 = 2E32 - 1

import math, time, cpuinfo

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
    last  = 2147483647     # 4294967295 is the limit for unsigned 32bit
    found = 4              # we start from 11, know 2, 3, 5, 7
    primes = [3, 5, 7]     # exclude 2 since we only test odd numbers
    print(f"Calculating prime numbers to {last} in Python with algorithm v5.4.2024")
    print(f"Running on a {cpuinfo.get_cpu_info()['brand_raw']}")
    start = time.perf_counter_ns()
    dot = start
    column = 0    
    largest_divider = int(math.sqrt(last))
    if largest_divider % 2 == 0:
        largest_divider += 1
    print(f'First find prime divisors up to {largest_divider}.')
    find_primes(largest_divider)
    print(f'Found {found} primes, now use them als divisors.')
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
    if column > 0:
        print(" ")
    duration = (time.perf_counter_ns() - start)/1000000000
    print(f"This took: {duration:.9f} seconds. {elapsed_time(duration)}")
    print(f"I found {found} prime numbers. Should be 78498.")
