# prime v4.1
import math, time, multiprocessing

last = 10000
found = 4             # we start from 11, know 2, 3, 5, 7
dividers = [3, 5, 7]
largest_divider = 7
# queue = multiprocessing.Queue()

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
    div = [3, 5, 7]
    largest_divider = int(math.sqrt(last))
    if largest_divider % 2 == 0:
        largest_divider += 1
    print(f'Find dividers up to {largest_divider}.')
    for number in range(11, largest_divider, 2):
        if is_prime(number) > 0:
            found += 1
            div.append(number)
    div.append(largest_divider) 
    print(div)
    return div

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
    # p = multiprocessing.Process(target=create_dividers, args=(last, ))
    # p.start()
    # p.join()
    lock = multiprocessing.Lock()
    print(dividers)
    with lock:
        create_dividers(last)  # racecondition because of macOS?
    print(dividers)

    print("Create pool")
    pool = multiprocessing.Pool()
    # dividers = pool.apply(create_dividers, args = (last, ))
    # result1.join()
    # pool.apply()
 
    # create_dividers(largest_divider)
    # time.sleep(1)


    print(dividers)
    print(f'Found {found} primes, now use them als dividers')
    # Make sure the dividers are found before creating the pool!

    results = pool.map(is_prime2, range(largest_divider + 2, last, 2))
    # results = pool.apply(is_prime2, args = range(largest_divider + 2, last, 2))

    pool.close()
    print(dividers)


    print(len(results))
    for nr in results:
        if nr > 0:
            found += 1    
    end = time.perf_counter()
    print(f'This took: {(end - start)} seconds.')
    print(f'Found {found} primes.')
    print(dividers)
    # print(results)
