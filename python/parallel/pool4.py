from multiprocessing import Pool
from multiprocessing import shared_memory
import time
import primes

print(prim)

def makelist(end):
    l = []
    for i in range(end):
        l.append(i + 1)
    return l

def f(x):
    return x*x

def g(x):
    return x*2

def h(x):
    prim = shared_memory.ShareableList(primes.name)
    print(prim)
    # Lastest idea: Proxy objects? BaseProxy

if __name__ == '__main__':
    primes = shared_memory.ShareableList(makelist(4))
    print(primes)
    primes2 = Array('i', range(10))
    with Pool() as pool: 
        result = pool.apply_async(f, (3,)) # evaluate "f(10)" asynchronously in a single process
        print(result.get(timeout=1))        # prints "100" unless your computer is *very* slow

        test  = pool.apply(f, (3, ))
        test2 = pool.map(f, range(test))
        test3 = pool.map(g, test2)
        test4 = pool.map(f, primes)

        print(test4)

        test5 = pool.map(h, [0, 1, 2])


        # it = pool.imap(f, range(10))
        # print(next(it))                     # prints "0"
        # print(next(it))                     # prints "1"
        # print(it.next(timeout=1))           # prints "4" unless your computer is *very* slow
