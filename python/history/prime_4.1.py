# prime v4.1
import math, time, multiprocessing

last = 10000
found = 4             # we start from 11, know 2, 3, 5, 7
dividers = [3, 5, 7]
queue = multiprocessing.Queue()

def is_prime(number):
    flag_prime = 1
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = 0
            break
    return flag_prime

def create_dividers(largest):
    global dividers
    global found
    for number in range(11, largest, 2):
        if is_prime(number) > 0:
            found += 1
            dividers.append(number)

def is_prime2(number):
    global dividers
    flag_prime = True
    largest_divider2 = int(math.sqrt(number))+1
    for divider in dividers:
        if number % divider == 0:
            flag_prime = False
            break
        if divider > largest_divider2:
            break
    if flag_prime:
        return len(dividers)  # divider or number
    else:
        return 0
        
if __name__ == "__main__":
    print(f"Prime numbers to {last}")
    start = time.perf_counter()
    largest_divider = int(math.sqrt(last))
    if largest_divider % 2 == 0:
        largest_divider += 1
    print(f'Find dividers up to {largest_divider}.')
    create_dividers(largest_divider)
    dividers.append(largest_divider)
    # print(dividers)
    print(f'Found {found} primes, now use them als dividers')
    # Make sure the dividers are found before creating the pool!
    time.sleep(0.5)
    print("Create pool")
    pool = multiprocessing.Pool()
    results = pool.map(is_prime2, range(largest_divider + 2, last, 2))
    pool.close()
    print(len(results))
    for nr in results:
        if nr > 0:
            found += 1    
    end = time.perf_counter()
    print(f'This took: {(end - start)} seconds.')
    print(f'Found {found} primes.')
    print(results)
