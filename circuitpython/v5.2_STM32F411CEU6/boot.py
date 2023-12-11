# toggle the write switch to the local file system - signal LED 2023/12/11

import time
import board
import digitalio
import storage

button_pin = board.A0
# T-Display rp2040     board.BUTTON_L    False if pressed
# T-Display ESP32-S2   board.IO0
# YD-ESP32-S3 N16R8    board.BOOT        or GPIO0
# STM32F411CEU6        board.A0          is the KEY button, needs digitalio.Pull.UP

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT
led.value = False

button = digitalio.DigitalInOut(board.A0)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

time.sleep(1)
timer = 5
print(f"Press the button in the next {timer} seconds to activate saving")
end = time.monotonic() + timer
print(timer)
while end - time.monotonic() > 0:
    if not button.value:
        print("write access activated")
        storage.remount("/", False)
        led.value = True
    if end - timer + 1 < time.monotonic():
        timer -= 1
        print(timer)
print("Not activated")
time.sleep(1)
