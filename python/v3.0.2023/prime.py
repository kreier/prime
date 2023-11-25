# prime v3.0.2023 with prime_check() in a function
import math, time
def is_prime(number):
    flag_prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = False
            break
    return flag_prime
if __name__ == "__main__":
    last = 1000000         # 1 million is a good comparison value
    found = 4              # we start from 11, know 2, 3, 5, 7
    print(f"Prime numbers to {last} with algorithm v3.0.2023")
    start = time.perf_counter_ns()
    for number in range(11, last, 2):
        if is_prime(number):
            found += 1 
    end = time.perf_counter_ns()
    print(f"This took: {(end - start)/1000} microseconds.")
    print(f"I found {found} prime numbers. Should be 78498.")
