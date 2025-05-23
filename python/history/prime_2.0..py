import math, time
last = 1000000
found = 4     # we start from 11, know already 2, 3, 5, 7
print(f"Prime numbers to {last}")
start = time.perf_counter()
for number in range(11, last, 2):
    prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            prime = False
            break
    if prime:
        found += 1
end = time.perf_counter()
print(f"This took: {(end - start)} seconds.")
print(f"I found {found} prime numbers.")
