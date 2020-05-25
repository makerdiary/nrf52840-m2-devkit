
import board
import digitalio
import displayio
import time
from lcd import LCD


displayio.release_displays()

spi = board.SPI()

display_bus = displayio.FourWire(
    spi, command=board.LCD_DC, chip_select=board.LCD_CS, reset=board.LCD_RST
)

display = LCD(display_bus, width=240, height=240, rowstart=80, rotation=90, backlight_pin=board.LCD_BL)

