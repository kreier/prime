# prime in python

With Python 3.9.12 on a M1 it takes 2.2611 seconds to find all 78,498 prime numbers from 1 to 1 million. It only uses one core.

``` py
import math, time
last = 1000000
found = 4     # we start from 11, know already 2, 3, 5, 7
print(f"Prime numbers to {last}")
start = time.monotonic()
for number in range(11, last, 2):
    prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            prime = False
            break
    if prime:
        found += 1
end = time.monotonic()
print(f"This took: {(end - start)} seconds.")
print(f"I found {found} prime numbers.")
```

## History

The standard algorithm I use since 1991 is:

``` py
import math, time

last = 1000
found = 4
start = time.monotonic()
print('Prime numbers to {}'.format(last))
print('2, 3, 5, 7',end='')

for number in range(11, last, 2):
    prime = 1
    for divider in range(2, int(math.sqrt(number))+1, 1):
        if number/divider == int(number/divider):
            prime = 0

    if prime == 1:
        print(',', number, end='')
        found += 1
      
end = time.monotonic()
print('\nThis took:', (end - start), 'seconds.')
print('Found: ',found)
```

## Code optimization

After teaching more computer science, I started to use the modulus operator - and things got faster! As seen below it increased the speed by 2x to 3x. With some further tweaks the speed increased __17 times__!

## Missing module `cpuinfo`

And it is not installed with the expected name, but `pip install py-cpuinfo`.
