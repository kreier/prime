# prime v5.4 2026-10-11 for AI-C3 (ESP32-C3) with board.NEOPIXEL
# cycles through limits and writes the results to /data
# - the limit itself is included in the search (matters for 2147483647, a prime)
# - while loop instead of range(), so limits near 2**31 / 2**32 can't overflow
# - checks for write access and creates /data before the long calculation starts
# - uses neopixel_write, no neopixel library needed

import math, time, os, board, digitalio, storage, neopixel_write

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295]
reference = [25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534, 105097565, 203280221]
time_calc = [0] * len(scope)

FIRST = 0   # index in scope to start with (0 = 100)
LAST = 10   # index in scope to end with (9 = 2147483647 = 2**31 - 1, 10 = 4294967295)

# ---------- NeoPixel without library ----------
pixel = digitalio.DigitalInOut(board.NEOPIXEL)
pixel.direction = digitalio.Direction.OUTPUT
BRIGHTNESS = 0.3
RED   = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE  = (0, 0, 255)

def set_led(color):
    r, g, b = color
    neopixel_write.neopixel_write(
        pixel, bytearray([int(g * BRIGHTNESS), int(r * BRIGHTNESS), int(b * BRIGHTNESS)]))

# ---------- helper functions ----------
def is_prime(number):
    for divider in range(3, int(math.sqrt(number)) + 1, 2):
        if number % divider == 0:
            return 0
    return 1

def find_primes(largest):
    global primes, found
    for number in range(11, largest + 1, 2):
        if is_prime(number):
            found += 1
            primes.append(number)

def is_prime_fast(number):
    largest_divider = int(math.sqrt(number)) + 1
    for divider in primes:
        if number % divider == 0:
            return 0
        if divider > largest_divider:
            break
    return 1

def elapsed_time(seconds):
    hours = int(seconds / 3600)
    minutes = int(seconds / 60 - hours * 60)
    sec = int(seconds - minutes * 60 - hours * 3600)
    return f"{hours}h {minutes}min {sec}s"

def lightshow():
    for i in range(1000):
        R = int(abs(255 * math.sin(i / 100)))
        G = int(abs(255 * math.sin((i + 105) / 100)))
        B = int(abs(255 * math.sin((i + 210) / 100)))
        set_led((R, G, B))
        time.sleep(0.002)

def check_filesystem():
    """Stop before the long calculation if we can't save the result."""
    if storage.getmount("/").readonly:
        print("Filesystem is read-only. Press reset, then the button in the first 5 seconds.")
        while True:
            set_led(RED)
            time.sleep(0.5)
            set_led((0, 0, 0))
            time.sleep(0.5)
    try:
        os.mkdir("/data")
        print("Created /data")
    except OSError:
        pass  # already exists

# ---------- main ----------
if __name__ == "__main__":
    check_filesystem()
    set_led(RED)
    lightshow()

    for i in range(FIRST, LAST + 1):
        last = scope[i]
        found = 4              # we start from 11, know 2, 3, 5, 7
        primes = [3, 5, 7]     # exclude 2 since we only test odd numbers
        print(f"\nPrime numbers to {last} in v5.4 on {board.board_id}")
        start = time.monotonic_ns()
        dot = start
        column = 1
        largest_divider = int(math.sqrt(last))
        if largest_divider % 2 == 0:
            largest_divider += 1
        print(f"First find prime dividers up to {largest_divider}.")
        find_primes(largest_divider)
        print(f"Found {found} primes, now use them as dividers.")

        number = largest_divider + 2
        count = 0
        while number <= last:          # <= includes the limit itself
            found += is_prime_fast(number)
            number += 2
            count += 1
            if (count & 0x3FF) == 0 and (time.monotonic_ns() - dot) > 2_000_000_000:
                print(".", end="")
                dot = time.monotonic_ns()
                column += 1
                set_led(BLUE if column % 2 == 0 else GREEN)
                if column > 30:
                    t = elapsed_time((dot - start) / 1e9)
                    print(f" {t} - {number} {(number / (last / 100)):.3f}% ")
                    column = 1

        duration = (time.monotonic_ns() - start) / 1e9
        time_calc[i] = duration
        set_led(RED)
        print(f"\nThis took: {duration} seconds. {elapsed_time(duration)}")
        print(f"Found {found} primes. Should be {reference[i]}.")

        filename = "/data/" + str(last) + ".txt"
        try:
            with open(filename, "w") as fp:
                fp.write(board.board_id)
                fp.write(f"\nPrimes to {last} took {duration} seconds.")
                fp.write(f"\nFound {found} primes. Should be {reference[i]}.")
            print("Exported to filesystem")
            set_led(GREEN)
        except OSError as e:
            print("Can't write to the filesystem:", e)
            set_led(RED)

    print("\nWrite summary")
    try:
        with open("/data/summary.txt", "w") as fp:
            fp.write("Primes calculation in Circuitpython v5.4 2026/10/11\n")
            fp.write(board.board_id)
            fp.write("\n last       time in seconds\n")
            for i in range(len(time_calc)):
                if time_calc[i] > 0:
                    fp.write(f" {scope[i]}   {time_calc[i]}\n")
        print("Exported to filesystem")
    except OSError as e:
        print("Can't write the summary:", e)

while True:
    lightshow()