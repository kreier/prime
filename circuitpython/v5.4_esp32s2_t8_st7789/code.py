# prime v5.4 2024-06-14
# lilygo_ttgo_t8_s2_st7789 with CircuitPython 9.0.5

import busio, board, sdcardio, storage, os, sys
import math, time, digitalio

spi = busio.SPI(board.SD_CLK, board.SD_MOSI, board.SD_MISO)
sdcard = sdcardio.SDCard(spi, board.SD_CS)
vfs = storage.VfsFat(sdcard)
storage.mount(vfs, '/sd')
sys.path.append('/sd')

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295]
reference = [25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097564, 203280221]
time_calc = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

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

if __name__ == "__main__":
    # title, current_scope and progress
    for sc in scope:
        filename = "/sd/" + str(sc) + ".txt"
        try:
            with open(filename, "r") as f:
                print("Read line from file: " + filename)
                print(f.readline())
        except:
            print(f"{filename} does not exist.")

    for i in range(len(scope)): # 8 needs less than a day - len(scope)
        last = scope[i]
        found = 4              # we start from 11, know 2, 3, 5, 7
        primes = [3, 5, 7]     # exclude 2 since we only test odd numbers

        print(f"\nPrime numbers to {last} in v5.4")
        start = time.monotonic()
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
            if (time.monotonic() - dot) > 2:
                print(f".", end="")
                dot = time.monotonic()
                column += 1
                if column > 40:
                    t = elapsed_time(time.monotonic() - start)
                    print(f" {t} - {number} {int(number*100/last)}% ")
                    column = 1
        duration = time.monotonic() - start
        print(f'This took: {duration} seconds.')
        print(f'Found {found} primes.')
        filename = "/sd/" + str(last) + ".txt"
        try:
            with open(filename, "w") as fp:
                fp.write(board.board_id)
                fp.write(f'\nPrimes to {last} took {duration} seconds.')
                fp.write(f'\nFound {found} primes. Should be {reference[i]}.')
                print('Exported to filesystem ')
        except:
            print("Can't write to the filesystem. SD Card present?")
        #print(f'Primes to {last} took {duration} seconds.')
        #print(f'Found {found} primes. Should be {reference[i]}.')
        time_calc[i] = duration
    print('\nWrite summary')
    try:
        with open("/sd/summary.txt", "w") as fp:
            fp.write(f'Primes calculation in Circuitpython v5.4 2024/06/14\n')
            fp.write(board.board_id)
            fp.write('\n last       time in seconds\n')
            for i in range(len(time_calc)):
                fp.write(f' {scope[i]}   {time_calc[i]}\n')
            print('Exported to filesystem ')
    except:
        print("Can't write to the filesystem. Press reset and after that the boot button in the first 5 seconds")
