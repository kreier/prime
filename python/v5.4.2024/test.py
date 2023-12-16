import time

# from https://stackoverflow.com/questions/49418144/why-python-works-faster-when-declaring-integer-variable-with-int
print("Test 1")

repeat = 1000000

start = time.time()
x = 0
for i in range(repeat):
    x += 1
no_type_time = time.time() - start

start = time.time()
y = int(0)
for i in range(repeat):
    y += 1
int_time = time.time() - start

print(f'{no_type_time} - No type')
print(f'{int_time} - Int')
