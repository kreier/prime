import math

print("Prime numbers until 10000")
print("2, 3, 5, 7, 11, 13, 17, 19, 23, 29,")
c = 1
count = 10
for x in range(31,10000):
    prime = 1
    for d in range(2,int(math.sqrt(x+1))):
        if x % d == 0:
            prime = 0
            break
    if prime == 1:
        print(x, end=", ")
        c += 1
        count += 1
    if c % 10 == 0:
        c += 1
        print(" ")

print("\nPrime numbers found: " + str(count))
