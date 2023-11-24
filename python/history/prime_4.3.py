# prime v4.3 - use the initializer of the pool in multiprocessing
import math, time, multiprocessing

last = 100
found = 4                 # we start from 11, know 2, 3, 5, 7
largest_divider = 7
dividers = [3, 5, 7]

def is_prime(number):
    flag_prime = 1
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = 0
            break
    return flag_prime

def primelist(last):
    global found
    global largest_divider
    primes = [3, 5, 7]
    largest_divider = int(math.sqrt(last))
    if largest_divider % 2 == 0:
        largest_divider += 1
    for number in range(11, largest_divider + 1, 2):
        if is_prime(number) > 0:
            found += 1
            primes.append(number)
    print(f'Found {len(primes)} prime numbers in range to {largest_divider}.')
    return primes

def is_prime_fast(number):
    flag_prime = True
    largest_divider2 = int(math.sqrt(number)) + 1
    for divider in dividers:
        if number % divider == 0:
            flag_prime = False
            break
        if divider > largest_divider2:
            break
    if flag_prime:
        return number  # divider or number
    else:
        return 0
        
if __name__ == "__main__":
    # print(primelist(last))
    print(f"Prime numbers to {last}")
    start = time.perf_counter()
    # print("Create pool")
    # pool = multiprocessing.Pool()
    # results = pool.starmap(is_prime2, [(div, i) for i in range(largest_divider + 2, last, 2)])
    # pool.close()
    # pool.join()    

    print("Create pool")
    pool = multiprocessing.Pool(initializer=primelist, initargs=(last))
    results = pool.map(is_prime_fast, range(largest_divider + 2, last, 2))
    pool.close()
    for nr in results:
        if nr > 0:
            found += 1
    end = time.perf_counter()
    print(f'This took: {(end - start)} seconds.')
    print(f'Found {found} primes.')
