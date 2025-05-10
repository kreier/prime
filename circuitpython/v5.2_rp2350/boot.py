# toggle the write switch to the local file system 2025/05/10

import time
import board
import digitalio
import storage

button_pin = board.GP0
# T-Display rp2040     board.BUTTON_L    False if pressed
# T-Display ESP32-S2   board.IO0
# Waveshare rp2350     board.GP0         False if connected to GND

button = digitalio.DigitalInOut(button_pin)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

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
        storage.disable_usb_drive()
        led.value = False
    if end - timer + 1 < time.monotonic():
        timer -= 1
        print(timer)
        led.value = False
        time.sleep(0.1)
        led.value = True
if led.value:
    print("Not activated")
    storage.enable_usb_drive()
time.sleep(1)
