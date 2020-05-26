# SD Card

## Requirements
+ A Micro SD formated with FATFS

## Code
The following example shows how to write & read a file on a SD card.

```python
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

```

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Zephyr:%20SPI%20Flash:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
