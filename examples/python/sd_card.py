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
print("microSD Card mounted.")

# write to sd card
print("Writing to file /sd/test.txt ...")
with open("/sd/test.txt", "w") as f:
	f.write("This is the written string.\n")

# read from sd card
print("Reading from file /sd/test.txt ...")
with open("/sd/test.txt", "r") as f:
	data = f.read()
	print(data)
