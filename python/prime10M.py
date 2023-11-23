import math, time

last = 10000000
found = 4             # we start from 11, know 2, 3, 5, 7
print(f"Prime numbers to {last}")

def is_prime(number):
    flag_prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = False
            break
    return flag_prime

if __name__ == "__main__":
    start = time.monotonic()
    for number in range(11, last, 2):
        if is_prime(number):
            found += 1
    end = time.monotonic()
    print(f"This took: {(end - start)} seconds.")
    print(f"I found {found} prime numbers. For 10M it should be 664,579.")
