# prime v5.0.2023 with primes as a divider list

import math, time

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

if __name__ == "__main__":
    last  = 1000000        # 1 million is a good comparison value
    found = 4              # we start from 11, know 2, 3, 5, 7
    primes = [3, 5, 7]     # exclude 2 since we only test odd numbers
    print(f"Prime numbers to {last} with algorithm v5.0.2023")
    start = time.perf_counter_ns()
    largest_divider = int(math.sqrt(last))
    if largest_divider % 2 == 0:
        largest_divider += 1
    print(f'First find prime dividers up to {largest_divider}.')
    find_primes(largest_divider)
    print(f'Found {found} primes, now use them als dividers.')
    print(primes)
    for number in range(largest_divider + 2, last, 2):
        found += is_prime_fast(number)
    end = time.perf_counter_ns()
    print(f"This took: {(end - start)/1000} microseconds.")
    print(f"I found {found} prime numbers. Should be 78498.")
