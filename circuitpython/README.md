# prime in circuitpython

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

## code optimization

After teaching more computer science, I started to use the modulus operator - and things got faster! As seen below it increased the speed by 2x.

With further tweaks the time went from 0.653 seconds down to 0.245 seconds. Thats 62% less time needed, almost 3x faster on my ESP32-S2!

``` py
import math
import time

last = 1000
found = 4
start = time.monotonic()
print('Prime numbers to {}'.format(last))

# code 1 - 0.65332 seconds
"""
for number in range(11, last, 2):
    prime = 1
    for divider in range(2, int(math.sqrt(number))+1, 1):
        if number/divider == int(number/divider):
            prime = 0

    if prime == 1:
        #print(',', number, end='')
        found += 1
"""

# code 2 - 0.333008 seconds
"""
for number in range(11, last, 2):
    prime = 1
    for divider in range(2, int(math.sqrt(number))+1, 1):
        if number % divider == 0:
            prime = 0

    if prime == 1:
        #print(',', number, end='')
        found += 1
"""

# code 3 - 0.245117 seconds

for number in range(11, last, 2):
    prime = 1
    if number % 3 == 0:
            prime = 0
    elif number % 5 == 0:
            prime = 0
    elif number % 7 == 0:
            prime = 0
    
    if prime == 1:
        for divider in range(11, int(math.sqrt(number))+1, 2):
            if number % divider == 0:
                prime = 0
                break

    if prime == 1:
        found += 1


end = time.monotonic()
print('\nThis took:', (end - start), 'seconds.')
print('Found: ',found)

```
