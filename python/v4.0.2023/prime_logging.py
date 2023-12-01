# prime v4.0.2023
# cycles through limits and writes to the filesystem

import math, time, cpuinfo, multiprocessing

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000]
reference = [25, 168, 1229, 9592, 78498, 664579, 1565927, 5761455, 50847534]
time_calc = [0, 0, 0, 0, 0, 0, 0, 0, 0]

def is_prime(number):
    flag_prime = True
    for divider in range(3, int(math.sqrt(number))+1, 2):
        if number % divider == 0:
            flag_prime = False
            break
    if flag_prime:
        return number
    else:
        return 0

if __name__ == "__main__":
    for i in range(len(scope)):
        last = scope[i]
        found = 4              # we start from 11, know 2, 3, 5, 7
        primes = [3, 5, 7]     # exclude 2 since we only test odd numbers    
        print(f"Prime numbers to {last} in Python with algorithm v4.0.2023")
        start = time.perf_counter_ns()
        pool = multiprocessing.Pool()
        results = pool.map(is_prime, range(11, last, 2))
        pool.close()
        for nr in results:
            if nr > 0:
                found += 1 
        end = time.perf_counter_ns()
        print(f"This took: {(end - start)/1000} microseconds.")
        print(f"I found {found} prime numbers. Should be {reference[i]}.")
        print(f"We used {multiprocessing.cpu_count()} parallel processes.\n")

        filename = str(last) + ".txt"
        with open(filename, "w") as fp:
            fp.write('prime v4.0.2023 in python\n')
            fp.write(cpuinfo.get_cpu_info()['brand_raw'])
            fp.write(f'\nPrimes to {last} took {(end - start)/1000} microseconds.\n')
            fp.write(f'Found {found} primes. Should be {reference[i]}.\n')
            fp.write(f'We used {multiprocessing.cpu_count()} parallel processes.\n')
        time_calc[i] = (end - start)/1000
    with open("summary.txt", "w")as fp:
        fp.write('Summary of prime v4.0.2023 in python\n')
        fp.write(cpuinfo.get_cpu_info()['brand_raw'])
        fp.write('\n     last       time in microseconds\n')
        for i in range(len(scope)):
            skip = " " * int(10.9 - math.log10(scope[i]))
            fp.write(skip)
            fp.write(f'  {scope[i]}   {time_calc[i]} \n')
