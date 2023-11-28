# prime v1.0.1991  
import math, time
last = 1000000         # 1 million is a good comparison value
found = 4              # we start from 11, know 2, 3, 5, 7
print(f"Prime numbers to {last} in Python with algorithm v1.0.1991")
start = time.perf_counter_ns()
for number in range(11, last, 2):
    prime = True
    for divisor in range(3, int(math.sqrt(number)) + 1, 2):
        if int(number / divisor) == number / divisor:
            prime = False
            break
    if prime:
        found += 1
end = time.perf_counter_ns()
print(f"This took: {(end - start)/1000} microseconds.")
print(f"I found {found} prime numbers. Should be 78498.")
