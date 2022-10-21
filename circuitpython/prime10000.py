import math, time

last = 10000
count = 4          # we start from 11, know 2, 3, 5, 7
start = time.monotonic()
print(f"Prime numbers to {last}")

#print('2, 3, 5, 7',end='')
for number in range(11, last, 2):
    prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number/divider == int(number/divider):
            prime = False
            break

    if prime:
        #print(',', number, end='')
        count += 1
        prime = 1

end = time.monotonic()
print(f"This took: {(end - start)} seconds.")
print(f"I found {count} prime numbers.")
