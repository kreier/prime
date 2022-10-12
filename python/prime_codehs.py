import math, time

start = time.monotonic()
last  = 10000

print(f"Calculating prime numbers until {last}.")
count = 0
for number in range(2, last):
    prime = True
    for divisor in range(2, number - 1):
        if number/divisor == int(number/divisor):
            prime = False
            break
    if prime:
        print(number, end=", ")
        count += 1

end = time.monotonic()
print(f"\nPrime numbers found: {count}")
print(f"This took {end - start} seconds.")

# time on CodeHS: 1.51 seconds
# time on M1 Mac: 0.61 seconds
