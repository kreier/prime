# Read SDCard lilygo_ttgo_t8_s2_st7789
import busio, board, sdcardio, storage, os, sys
import math, time, digitalio

spi = busio.SPI(board.SD_CLK, board.SD_MOSI, board.SD_MISO)
sdcard = sdcardio.SDCard(spi, board.SD_CS)
vfs = storage.VfsFat(sdcard)
storage.mount(vfs, '/sd')
sys.path.append('/sd')

scope = [100, 1000, 10000, 100000, 1000000, 10000000, 25000000, 100000000, 1000000000, 2147483647, 4294967295]

if __name__ == "__main__":
    # title, current_scope and progress
    print("Saved results from recent benchmark runs:")
    for sc in scope:
        filename = "/sd/" + str(sc) + ".txt"
        try:
            with open(filename, "r") as f:
                #print("Read line from file: " + filename)
                f.readline()
#                print(f.readline())
                print(f.readline(),end='')
        except:
            print(f"{filename} does not exist.")
    