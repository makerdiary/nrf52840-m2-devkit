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

<a href="../../install"><button class="md-tile md-tile--primary" style="width:auto;"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="16" height="16"><path fill-rule="evenodd" d="M16 8.5l-6 6-3-3L8.5 10l1.5 1.5L14.5 7 16 8.5zM5.7 12.2l.8.8H2c-.55 0-1-.45-1-1V3c0-.55.45-1 1-1h7c.55 0 1 .45 1 1v6.5l-.8-.8c-.39-.39-1.03-.39-1.42 0L5.7 10.8a.996.996 0 000 1.41v-.01zM4 4h5V3H4v1zm0 2h5V5H4v1zm0 2h3V7H4v1zM3 9H2v1h1V9zm0-2H2v1h1V7zm0-2H2v1h1V5zm0-2H2v1h1V3z"></path></svg> Install Python Interpreter</button></a>

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

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Python:%20LCD:%20%3Ctitle%3E"><button class="md-tile md-tile--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
