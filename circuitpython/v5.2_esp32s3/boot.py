# toggle the write switch to the local file system - signal NEOPIXEL

import time
import board
import digitalio
import storage
import neopixel

button_pin = board.BOOT
# T-Display rp2040     board.BUTTON_L    False if pressed
# T-Display ESP32-S2   board.IO0
# YD-ESP32-S3 N16R8    board.BOOT        or GPIO0

led = neopixel.NeoPixel(board.NEOPIXEL, 1)
led.brightness = 0.3
led[0] = (255, 0, 0)

button = digitalio.DigitalInOut(button_pin)
button.direction = digitalio.Direction.INPUT

time.sleep(1)
timer = 5
print(f"Press the button in the next {timer} seconds to activate saving")
end = time.monotonic() + timer
print(timer)
while end - time.monotonic() > 0:
    if not button.value:
        print("write access activated")
        storage.remount("/", False)
        led[0] = (0, 255, 0)
    if end - timer + 1 < time.monotonic():
        timer -= 1
        print(timer)
print("Not activated")
time.sleep(1)
