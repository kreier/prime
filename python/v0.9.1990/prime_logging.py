# prime v0.9.1990  
# cycles through limits and writes to the filesystem

import math, time, os, cpuinfo

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000]
reference = [25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534]
time_calc = [0, 0, 0, 0, 0, 0, 0, 0, 0]

if __name__ == "__main__":
    for i in range(len(scope)):
        last = scope[i]
        found = 4              # we start from 11, know 2, 3, 5, 7
        print(f"Prime numbers to {last} in Python with algorithm v0.9.1990")
        start = time.perf_counter_ns()
        for number in range(11, last):
            prime = True
            for divisor in range(2, int(math.sqrt(number)) + 1):
                result = number / divisor
                if int(result) == result:
                    prime = False
                    break
            if prime:
                found += 1
        end = time.perf_counter_ns()
        print(f"This took: {(end - start)/1000} microseconds.")
        print(f"I found {found} prime numbers. Should be {reference[i]}.\n")
        filename = str(last) + ".txt"
        with open(filename, "w") as fp:
            fp.write('prime v0.9.1990 in python\n')            
            fp.write(cpuinfo.get_cpu_info()['brand_raw'])
            fp.write(f'\nPrimes to {last} took {(end - start)/1000} microseconds.')
            fp.write(f'\nFound {found} primes. Should be {reference[i]}.\n')
        time_calc[i] = (end - start)/1000
    with open("summary.txt", "w")as fp:
        fp.write('Summary of prime v0.9.1990 in python\n')
        fp.write(cpuinfo.get_cpu_info()['brand_raw'])
        fp.write('\n     last       time in microseconds\n')
        for i in range(len(scope)):
            skip = " " * int(10.9 - math.log10(scope[i]))
            fp.write(skip)
            fp.write(f'  {scope[i]}   {time_calc[i]} \n')

