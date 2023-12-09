# prime v3.0.2023
# cycles through limits and writes to the filesystem

import math, time, os, cpuinfo

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000]
reference = [25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534]
time_calc = [0, 0, 0, 0, 0, 0, 0, 0, 0]

def is_prime(number):
    flag_prime = True
    for divider in range(3, int(math.sqrt(number)) + 1, 2):
        if number % divider == 0:
            flag_prime = False
            break
    return flag_prime

def elapsed_time(seconds):
    hours = int(seconds/3600)
    minutes = int(seconds/60 - hours*60)
    sec = int(seconds - minutes*60 - hours*3600)
    return(f"{hours}h {minutes}min {sec}s")

if __name__ == "__main__":
    for i in range(len(scope)):
        last = scope[i]
        found = 4              # we start from 11, know 2, 3, 5, 7
        primes = [3, 5, 7]     # exclude 2 since we only test odd numbers    
        print(f"Prime numbers to {last} in Python with algorithm v3.0.2023")
        start = time.perf_counter_ns()
        dot = start
        column = 1        
        for number in range(11, last, 2):
            if is_prime(number):
                found += 1
            if (time.perf_counter_ns() - dot) > 2000000000:
                print(".", end="")
                dot = time.perf_counter_ns()
                column += 1
                if column > 30:
                    t = elapsed_time((time.perf_counter_ns() - start)/1000000000)
                    print(f" {t} - {number} {int(number*100/last)}% ")
                    column = 1                
        end = time.perf_counter_ns()
        if (end - start)/1000000000 > 2:
            print(" ")        
        print(f"This took: {(end - start)/1000} microseconds. {elapsed_time((end - start)/1000000000)}")
        print(f"I found {found} prime numbers. Should be {reference[i]}.\n")
        filename = str(last) + ".txt"
        with open(filename, "w") as fp:
            fp.write('prime v3.0.2023 in python\n')
            fp.write(cpuinfo.get_cpu_info()['brand_raw'])
            fp.write(f'\nPrimes to {last} took {(end - start)/1000} microseconds.')
            fp.write(f'\nFound {found} primes. Should be {reference[i]}.\n')
        time_calc[i] = (end - start)/1000
    with open("summary.txt", "w")as fp:
        fp.write('Summary of prime v3.0.2023 in python\n')
        fp.write(cpuinfo.get_cpu_info()['brand_raw'])
        fp.write('\n     last       time in microseconds\n')
        for i in range(len(scope)):
            skip = " " * int(10.9 - math.log10(scope[i]))
            fp.write(skip)
            fp.write(f'  {scope[i]}   {time_calc[i]} \n')
