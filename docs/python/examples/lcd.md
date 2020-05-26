# LCD Example

The onboard LCD is based ST7789. Its driver is included in the firmware.


| LCD              | Pin      | Name             |
|------------------|----------|------------------|
| LCD DC           | P0_19    | LCD_DC           |
| LCD CS           | P0_06    | LCD_CS           |
| LCD Backlight    | P0_20    | LCD_BL           |
| LCD Reset        | P1_09    | LCD_RST          |
| SPI SCK          | P0_11    | SCK              |
| SPI MOSI         | P0_12    | MOSI             |
| SPI MISO         | P1_08    | MISO             |


```python
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
```

You can follow [Adafruit's displayio guide](https://learn.adafruit.com/circuitpython-display-support-using-displayio?view=all) to use the LCD.

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Zephyr:%20Button:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
