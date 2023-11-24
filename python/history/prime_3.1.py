# prime v3.1
import math, time, digitalio, board

last = 1000000
found = 4             # we start from 11, know 2, 3, 5, 7
dividers = [3, 5, 7]

def is_prime(number):
    global found
    flag_prime = 1
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = 0
            break
    return flag_prime

def create_dividers(largest):
    global dividers
    global found
    for number in range(11, largest, 2):
        if is_prime(number) > 0:
            found += 1
            dividers.append(number)

def is_prime2(number):
    global found
    flag_prime = 1
    largest_divider2 = int(math.sqrt(number))+1
    for divider in dividers:
        if number % divider == 0:
            flag_prime = 0
            break
        if divider > largest_divider2:
            break
    return flag_prime

if __name__ == "__main__":
    print(f"Prime numbers to {last}")
    start = time.monotonic()
    largest_divider = int(math.sqrt(last))
    if largest_divider % 2 == 0:
        largest_divider += 1
    print(f'Find dividers up to {largest_divider}.')
    create_dividers(largest_divider)
    print(f'Found {found} primes, now use them als dividers')
    for number in range(largest_divider, last, 2):
        found += is_prime2(number)
    end = time.monotonic()
    print(f'This took: {(end - start)} seconds.')
    print(f'Found {found} primes.')

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

while True:
    led.value = True
    print(f'LED on - to {last} needs {end - start} s')
    time.sleep(10)
    led.value = False
    print('LED off')
    time.sleep(1)
    pass
