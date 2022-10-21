# prime in circuitpython

I use this little algorithm to check the speed on microcontrollers. Here are the times up to 10000, finding all 1229 prime numbers.

| microcontroller            | CPU             | MHz |     time |
|----------------------------|-----------------|:---:|---------:|
| micro:bit                  | nRF51822        | 16  | 13.556 s |
| Circuit Playground Express | samd21g18       | 48  | 3.184 s  |
| Feather M0 Express         | TSAMD21G18      | 48  | 3.217 s  |
| CLUE NRF52840 Express      | nRF52840        | 64  | 2.153 s  |
| Rapsberry Pi Pico          | Dual Cortex-M0+ | 133 | 0.776 s  |

``` py
import math, time
last = 10000
found = 4          # we start from 11, know 2, 3, 5, 7
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
        prime = 1
end = time.monotonic()
print(f"This took: {(end - start)} seconds.")
print(f"I found {found} prime numbers.")
```

The adjusted MicroPython code for the micro:bit reads:

``` py
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

## code optimization

After teaching more computer science, I started to use the modulus operator - and things got faster! As seen below it increased the speed by 2x to 3x. With some further tweaks the speed increased __17 times__!

``` py
import math, time

last = 10000
found = 4     # we already know 2, 3, 5, 7
print('Prime numbers to {}'.format(last))

start = time.monotonic()

# code 1 - 45.685 seconds for 10000 on Feather M0 - 17.3x slower
"""
for number in range(11, last, 2): # we already know 2, 3, 5, 7
    prime = True
    for divider in range(2, int(math.sqrt(number))+1, 1):
        if number/divider == int(number/divider):
            prime = False
    if prime:
        #print(',', number, end='')
        found += 1
"""

# code 2 - 15.555 seconds for 10000 on Feather M0 - 5.88x slower
"""
for number in range(11, last, 2):
    prime = True
    for divider in range(2, int(math.sqrt(number))+1, 1):
        if number % divider == 0:
            prime = False

    if prime:
        #print(',', number, end='')
        found += 1
"""

# code 3 - 2.645 seconds for 10000 on Feather M0

for number in range(11, last, 2):
    prime = True
    if number % 3 == 0:
            prime = False
    elif number % 5 == 0:
            prime = False
    elif number % 7 == 0:
            prime = False
    if prime:
        for divider in range(11, int(math.sqrt(number))+1, 2):
            if number % divider == 0:
                prime = False
                break
    if prime:
        found += 1

end = time.monotonic()
print(f"This took: {(end - start)} seconds.")
print(f"I found {found} prime numbers.")

```

With further tweaks the time went from 0.653 seconds down to 0.245 seconds in the calculation up to 1000. Thats 62% less time needed, almost 3x faster on my ESP32-S2!

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
