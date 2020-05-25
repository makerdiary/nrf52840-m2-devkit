# SD card usage
import board
import digitalio
import sdcard
import storage

spi = board.SPI()
cs = digitalio.DigitalInOut(board.P7)
sd = sdcard.SDCard(spi, cs)
vfs = storage.VfsFat(sd)
storage.mount(vfs, "/sd")

# write to sd card
with open("/sd/test.txt", "w") as f:
    f.write("Hello world\n")

# read from sd card
with open("/sd/test.txt", "r") as f:
    data = f.read()
    print(data)
