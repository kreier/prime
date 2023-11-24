import time
from multiprocessing import Pool
from multiprocessing import Manager


def test(test_list,i):
    test_list.remove(i)
    print("intest : ", test_list)
    

if __name__ == '__main__':
    with Manager() as manager:
        A = manager.list(["leo", "kiki", "eden"])
        B = ["eden", "kiki"]

        print("Start : ", A)
        pool = Pool(processes=2)
        pool.starmap(test, [(A, K) for K in B])
        pool.close()
        pool.join()
        print("Final : ", A)