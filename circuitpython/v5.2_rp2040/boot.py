# toggle the write switch to the local file system 2023/12/11

import time
import board
import digitalio
import storage

button_pin = board.BUTTON_L
# T-Display rp2040     board.BUTTON_L    False if pressed
# T-Display ESP32-S2   board.IO0

button = digitalio.DigitalInOut(button_pin)
button.direction = digitalio.Direction.INPUT

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT
led.value = True

time.sleep(1)
timer = 5
print(f"Press the button in the next {timer} seconds to activate saving")
end = time.monotonic() + timer
print(timer)
while end - time.monotonic() > 0:
    if not button.value:
        print("write access activated")
        storage.remount("/", False)
        led.value = False
    if end - timer + 1 < time.monotonic():
        timer -= 1
        print(timer)
print("Not activated")
time.sleep(1)
