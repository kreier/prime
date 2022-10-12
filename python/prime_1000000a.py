import math, time

last   = 1000000
result = ""

print(f"Calculating prime numbers until {last}.")
count = 0
start  = time.monotonic()
for number in range(2, last):
    prime = True
    for divisor in range(2, int(math.sqrt(number))+1):
        if number/divisor == int(number/divisor):
            prime = False
            break
    if prime:
        result += str(number) + ", "
        count += 1

time_calc = time.monotonic() - start
print(result)
print("\nPrime numbers found: " + str(count))
print(f"The calculation took {time_calc} seconds.")
time_print = time.monotonic() - start - time_calc
print(f"The printout took {time_print} seconds.")
