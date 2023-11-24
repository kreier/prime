import math, time, multiprocessing

last = 10000
found = 4             # we start from 11, know 2, 3, 5, 7
queue = multiprocessing.Queue()

def is_prime(number):
    flag_prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = False
            break
    if flag_prime:
        return divider # or number
    else:
        return 0

if __name__ == "__main__":
    print(f"Prime numbers to {last}")
    start = time.perf_counter()
    print("Create pool")
    pool = multiprocessing.Pool()
    results = pool.map(is_prime, range(11, last, 2))
    pool.close()
    for nr in results:
        if nr > 0:
            found += 1
    end = time.perf_counter()
    print(f"This took: {(end - start)} seconds.")
    print(f"I found {found} prime numbers.")
    # print(results)
