# prime v4.0.2023 with running python in parallel

import math, time, multiprocessing

def is_prime(number):
    flag_prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = False
            break
    if flag_prime:
        return number
    else:
        return 0

if __name__ == "__main__":
    last = 1000000         # 1 million is a good comparison value
    found = 4              # we start from 11, know 2, 3, 5, 7
    queue = multiprocessing.Queue()
    print(f"Prime numbers to {last} in python with algorithm v4.0.2023")
    start = time.perf_counter_ns()
    print("Create pool")
    pool = multiprocessing.Pool()
    results = pool.map(is_prime, range(11, last, 2))
    pool.close()
    for nr in results:
        if nr > 0:
            found += 1 
    end = time.perf_counter_ns()
    print(f"This took: {(end - start)/1000} microseconds.")
    print(f"I found {found} prime numbers. Should be 78498.")
    print(f"We used {multiprocessing.cpu_count()} parallel processes.")
