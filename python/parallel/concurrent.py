from time import sleep
from random import random
from multiprocessing import Process, SimpleQueue
 
def producer(queue):
    print('Producer: Running')
    for i in range(5):        # generate work
        value = random()      # generate a value
        sleep(value)          # block
        queue.put(value)      # add to the queue
    queue.put(None)           # all done
    print('Producer: Done')
 
def consumer(queue):
    print('Consumer: Running') 
    while True:               # consume work
        item = queue.get()    # get a unit of work
        if item is None:      # check for stop 
            break
        print(f'>got {item}') # report
    print('Consumer: Done')   # all done
 
if __name__ == '__main__':
    queue = SimpleQueue()     # create the shared queue
    consumer_process = Process(target=consumer, args=(queue,))    # start the consumer
    consumer_process.start()
    producer_process = Process(target=producer, args=(queue,))    # start the producer
    producer_process.start()
    producer_process.join()   # wait for all child processes to finish
    consumer_process.join()
