# Calculating prime numbers

The main goal is to serve as a small benchmark to compare algorithms, programming languages and CPUs from microcomputers to workstations.

Today even microcontroller can drive color-tft displays, like here with a Raspberry Pi Pico 2040 on a 240px display with SP7789, running circuitpython:

![rp2040 with 240px display](circuitpython/rp2040_240px_tft.jpg)

The code is just a few lines:

``` py
import math, time, board, busio, terminalio, displayio
from adafruit_st7789 import ST7789
displayio.release_displays()
spi = busio.SPI(clock=board.GP10, MOSI=board.GP11)
tft_cs = board.GP9
tft_dc = board.GP8
display_bus = displayio.FourWire(
    spi, command=tft_dc, chip_select=tft_cs, reset=board.GP12
)
display = ST7789(display_bus, width=240, height=240, rowstart=80)
#splash = displayio.Group()
#display.show(splash)

last = 500
disp = True
found = 4             # we start from 11, know 2, 3, 5, 7
print(f"Prime numbers to {last}")
print("2, 3, 5, 7", end="")

start = time.monotonic()
for number in range(11, last, 2):
    prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            prime = False
            break
    if prime:
        found += 1
        if disp:
            print(number, sep=', ', end=' ')
end = time.monotonic()
print(f"\nThis took: {(end - start)} seconds.")
print(f"I found {found} prime numbers.")

```

## Does my code work

A quick check (aside from obvious mistakes with even prime numbers as result) you can check how many primes your code finds to check if it works correctly:

|   range   | prime numbers |
|----------:|--------------:|
|        10 |             4 |
|       100 |            25 |
|     1,000 |           168 |
|    10,000 |         1,229 |
| 100,000   |         9,592 |
| 1,000,000 |        78,498 |

## Speed comparison on a M1 Mac

The same algorithm compiled in C for the prime numbers to 1,000,000 need just 0.054 seconds while Python3 needs 2.54 seconds to interpret the code and give the answer.

|      language       | prime numbers | factor |
|--------------------:|--------------:|-------:|
|                   C |      0.0498 s |     51 |
|             Python3 |      2.5394 s |      1 |
|                Java |               |        |
|               Swift |               |        |
|          Javascript |               |        |
| Playgrounds (Swift) |      7.0413 s |   0.36 |

TBC.
