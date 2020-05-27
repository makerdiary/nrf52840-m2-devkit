# TFT LCD Display Example

## Description

The TFT LCD Display Example shows how to use the LCD library API functions to draw graphic objects on the LCD.

The table below shows the connections of each pin of the TFT LCD driver ST7789:

| LCD Pin          | nRF52840 Pin  | Name             |
|------------------|---------------|------------------|
| LCD DC           | P0_08         | LCD_DC           |
| LCD CS           | P0_06         | LCD_CS           |
| LCD Backlight    | P0_20         | LCD_BL           |
| LCD Reset        | P1_09         | LCD_RST          |
| SPI SCK          | P0_11         | SCK              |
| SPI MOSI         | P0_12         | MOSI             |

Before you start coding, the Python Interpreter should be installed on the nRF52840 M.2 module correctly:

<a href="../../install"><button data-md-color-primary="red-bud" style="width:auto;">Install Python Interpreter</button></a>

## Run the code

Run the TFT LCD Display Example by performing the following steps:

1. Connect the **Module USB port** to your PC as shown in the figure below. A disk drive called **CIRCUITPY** should be automatically detected by the computer:

	![](../assets/images/connect-module-usb.webp)

2. Open the `code.py` file on your **CIRCUITPY** drive, then copy and paste the following code. Your code will run as soon as the file is done saving.

	``` py
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

3. Run a terminal application like [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/) or [screen](https://www.gnu.org/software/screen/manual/screen.html):

	``` sh
	screen /dev/cu.usbmodem14102 115200
	```

4. Type something in the terminal window. Observe that the LCD will display the same thing as in the terminal:

	![LCD display image]()


## Reference

* [Adafruit's displayio Guide](https://learn.adafruit.com/circuitpython-display-support-using-displayio?view=all)

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Python:%20LCD:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
