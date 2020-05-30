# USB HID Keyboard Example

## Description

The USB HID Keyboard Example demonstrates use of a USB Human Interface Device (HID) driver by Adafruit. 

The example code enumerates the nRF52840 M.2 Developer Kit into a HID keyboard that has an <kbd>A</kbd> key pressed by the USER button. The code depends on:

* [adafruit_hid driver](https://github.com/adafruit/Adafruit_CircuitPython_HID)

Before you start coding, the Python Interpreter should be installed on the nRF52840 M.2 module correctly:

<a href="../../install"><button class="md-issue-button md-issue-button--primary" style="width:auto;">Install Python Interpreter</button></a>

## Run the code

Run the USB HID Keyboard Example by performing the following steps:

1. Connect the **Module USB port** to your PC as shown in the figure below. A disk drive called **CIRCUITPY** should be automatically detected by the computer:

	![](../assets/images/connect-module-usb.webp)

2. The example code depends on the [adafruit_hid](https://github.com/adafruit/Adafruit_CircuitPython_HID) driver. Download and extract it into your **`CIRCUITPY/lib`** folder. This should give you the following folder structure:

	``` sh
	CIRCUITPY
	├── boot_out.txt
	├── code.py
	└── lib
		└── adafruit_hid
			├── __init__.py
			├── keyboard.py
			└── keycode.py
	```

3. Open the `code.py` file on your **CIRCUITPY** drive, then copy and paste the following code:

	``` py
	import time
	import board
	import digitalio
	import usb_hid
	from adafruit_hid.keyboard import Keyboard
	from adafruit_hid.keycode import Keycode

	usb_keyboard = Keyboard(usb_hid.devices)

	button = digitalio.DigitalInOut(board.USR_BTN)
	button.direction = digitalio.Direction.INPUT
	button.pull = digitalio.Pull.UP

	last_value = button.value

	while True:
		if last_value != button.value:
			last_value = button.value
			if not button.value:
				print('Button is pressed')
				usb_keyboard.press(Keycode.A)
			else:
				print('Button is released')
				usb_keyboard.release(Keycode.A)

	```

4. Your code will run as soon as the file is done saving. The board will enumerate as a HID keyboard. Press the USER button and observe that a letter **`a`** will output on the host computer.

## Reference

* [Adafruit_CircuitPython_HID Repository](https://github.com/adafruit/Adafruit_CircuitPython_HID)

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Python:%20USB%20HID%20Keyboard:%20%3Ctitle%3E"><button class="md-issue-button md-issue-button--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
