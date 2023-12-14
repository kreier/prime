# prime v5.2 2023-12-12 for esp8266 NodeMCU
# cycles through limits and writes to the filesystem

import math, time, machine, os

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000]
reference = [25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 123456789]
time_calc = [0, 0, 0, 0, 0, 0, 0, 0, 0]

led = machine.Pin(2, machine.Pin.OUT)
led.value(0)

def is_prime(number):
    global found
    flag_prime = 1
    for divider in range(3, int(math.sqrt(number)) + 1, 2):
        if number % divider == 0:
            flag_prime = 0
            break
    return flag_prime

def find_primes(largest):
    global primes
    global found
    for number in range(11, largest + 1, 2):
        if is_prime(number) > 0:
            found += 1
            primes.append(number)

def is_prime_fast(number):
    global found
    flag_prime = 1
    largest_divider = int(math.sqrt(number)) + 1
    for divider in primes:
        if number % divider == 0:
            flag_prime = 0
            break
        if divider > largest_divider:
            break
    return flag_prime

def elapsed_time(seconds):
    hours = int(seconds/3600)
    minutes = int(seconds/60 - hours*60)
    sec = int(seconds - minutes*60 - hours*3600)
    return(f"{hours}h {minutes}min {sec}s")

def lightshow():
    led.value(1)
    time.sleep(0.1)
    led.value(0)
    time.sleep(0.1)

if __name__ == "__main__":
    for i in range(len(scope)): # len(scope)
        last = scope[i]
        found = 4              # we start from 11, know 2, 3, 5, 7
        primes = [3, 5, 7]     # exclude 2 since we only test odd numbers
        print(f"\nPrime numbers v5.2 to {last} in MicroPythonn 1.21.1")
        start = time.ticks_us()
        dot = start
        column = 1
        largest_divider = int(math.sqrt(last))
        if largest_divider % 2 == 0:
            largest_divider += 1
        print(f'First find prime dividers up to {largest_divider}.')
        find_primes(largest_divider)
        print(f'Found {found} primes, now use them als dividers.')
        for number in range(largest_divider + 2, last, 2):
            found += is_prime_fast(number)
            if (time.ticks_us() - dot) > 2000000:
                print(".", end="")
                dot = time.ticks_us()
                column += 1
                if column % 2 == 0:
                    led.value(0)
                else:
                    led.value(1)
                if column > 30:
                    t = elapsed_time((time.ticks_us() - start)/1000000)
                    print(f" {t} - {number} {int(number*100/last)}% ")
                    column = 1
        duration = (time.ticks_us() - start)/1000000
        print(f'This took: {duration} seconds. {elapsed_time(duration)}')
        print(f'Found {found} primes.')
        led.value(1)
        filename = "/" + str(last) + ".txt"
        try:
            with open(filename, "w") as fp:
                freq = machine.freq()/1000000
                fp.write(f'ESP8266 with {freq} MHz')
                fp.write(f'\nPrimes to {last} took {duration} seconds. {elapsed_time(duration)}')
                fp.write(f'\nFound {found} primes. Should be {reference[i]}.\n')
                print('Exported to filesystem ')
        except:
            print("Can't write to the filesystem. Press reset and after that the boot button in the first 5 seconds")
        #print(f'Primes to {last} took {(end - start)} seconds.')
        #print(f'Found {found} primes. Should be {reference[i]}.')
        time_calc[i] = duration
    print('\nWrite summary')
    try:
        with open("summary.txt", "w") as fp:
            fp.write(f'Primes calculation v5.2 in MicroPython 1.21.0 2023/12/12\n')
            freq = machine.freq()/1000000
            fp.write(f'ESP8266 with {freq} MHz')
            fp.write('\n last       time in seconds\n')
            for i in range(len(time_calc)):
                fp.write(f' {scope[i]}   {time_calc[i]}\n')
            print('Exported to filesystem ')
    except:
        print("Can't write to the filesystem. Press reset and after that the boot button in the first 5 seconds")

    while True:
        lightshow()
