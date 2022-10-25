import math, time
last = 10000
found = 4          # we start from 11, know 2, 3, 5, 7
print('Prime numbers to {}'.format(last))
start = time.ticks_us()
for number in range(11, last, 2):
    prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            prime = False
            break
    if prime:
        found += 1
        prime = True
end = time.ticks_us()
print("This took: {} seconds.".format((end - start)/1000000))
print("I found {:.4} prime numbers.".format(found))
