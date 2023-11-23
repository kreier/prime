import math, time

last = 10000000
found = 4             # we start from 11, know 2, 3, 5, 7

def is_prime(number):
    global found
    flag_prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = False
            break
    if flag_prime:
        found += 1

if __name__ == "__main__":
    print(f"Prime numbers to {last}")
    start = time.perf_counter()
    for number in range(11, last, 2):
        is_prime(number)
    end = time.perf_counter()
    print(f"This took: {(end - start)} seconds.")
