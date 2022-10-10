# prime in micropython

The micro:bit v1 only runs micropython v1.9.2 and has only 9312 kByte free (`import gc` && `gc.mem_free()`). The nRF51822 has a 16 MHz ARM Cortex-M0 core with 256 KB Flash and 16 KB RAM.

| Microcomputer                | time  | MHz |
|------------------------------|-------|-----|
| micro:bit v1                 | 4.001 | 16  |
| LilyGO T8 T-Display ESP32-S2 | 0.638 | 160 |

Both were running this code:

``` py
import math, time

last = 1000

start = time.ticks_us()
print('Prime numbers to {}'.format(last))

#print('2, 3, 5, 7',end='')
for number in range(11, last, 2):
    prime = 1
    for divider in range(2, int(math.sqrt(number))+1, 1):
        if number/divider == int(number/divider):
            prime = 0

    if prime == 1:
        #print(',', number, end='')
        prime = 1

end = time.ticks_us()
print('\nThis took:', (end - start)/1000000, 'seconds.')

```
