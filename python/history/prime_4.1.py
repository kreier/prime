# prime v4.1
import math, time, multiprocessing

last = 100000
found = 4                 # we start from 11, know 2, 3, 5, 7
largest_divider = 7

def is_prime(number):
    flag_prime = 1
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = 0
            break
    return flag_prime

def create_dividers(last):
    global found
    global largest_divider
    dividers = [3, 5, 7]
    largest_divider = int(math.sqrt(last))
    if largest_divider % 2 == 0:
        largest_divider += 1
    for number in range(11, largest_divider + 1, 2):
        if is_prime(number) > 0:
            found += 1
            dividers.append(number)
    print(f'Found {len(dividers)} prime numbers in range to {largest_divider}.')
    return dividers

def is_prime2(div, number):
    flag_prime = True
    largest_divider2 = int(math.sqrt(number)) + 1
    for divider in div:
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
    with multiprocessing.Manager() as manager:
        print(f"Prime numbers to {last}")
        start = time.perf_counter()
        div = manager.list(create_dividers(last))
        print("Create pool")
        pool = multiprocessing.Pool()
        results = pool.starmap(is_prime2, [(div, i) for i in range(largest_divider + 2, last, 2)])
        pool.close()
        pool.join()    

    # print("Create pool")
    # pool = multiprocessing.Pool()
    # results = pool.map(is_prime2, range(largest_divider + 2, last, 2))
    # pool.close()
    for nr in results:
        if nr > 0:
            found += 1
    end = time.perf_counter()
    print(f'This took: {(end - start)} seconds.')
    print(f'Found {found} primes.')
