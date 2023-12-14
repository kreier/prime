import time, board, neopixel

led = neopixel.NeoPixel(board.NEOPIXEL, 1)
led.brightness = 0.3
led[0] = (255, 0, 0)

while True:
    led[0] = (255, 0, 0)
    time.sleep(0.3)
    led[0] = (0, 255, 0)
    time.sleep(0.3)
    led[0] = (0, 0, 255)
    time.sleep(0.3)
