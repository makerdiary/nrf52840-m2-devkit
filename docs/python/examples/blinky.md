# Blinky Example

## Description

Blinky Example is a simple application which blinks an LED forever using the `digitalio` module. The source code shows how to configure the GPIO pin as output, then turn it on and off.

The table below shows the available LEDs on the nRF52840 M.2 Developer Kit:

| Available LEDs | Mounted on |  Pin  | Name      |
|--------------- | ---------- | ----- | --------- |
| Red LED        | M.2 Module | P0_30 | LED_RED   |
| Green LED      | M.2 Module | P0_29 | LED_GREEN |
| Blue LED       | M.2 Module | P0_31 | LED_BLUE  |
| Green LED      | M.2 Dock   | P1_07 | D13       |


Before you start coding, the Python Interpreter should be installed on the nRF52840 M.2 module correctly:

<a href="../../install"><button class="md-tile md-tile--primary" style="width:auto;">Install Python Interpreter</button></a>

## Run the code

Run the Blinky Example by performing the following steps:

1. Connect the **Module USB port** to your PC as shown in the figure below. A disk drive called **CIRCUITPY** should be automatically detected by the computer:

	![](../assets/images/connect-module-usb.webp)

2. Open the `code.py` file on your **CIRCUITPY** drive, then copy and paste the following code:

	``` py
	import digitalio
	import board
	import time

	led = digitalio.DigitalInOut(board.D13)
	led.direction = digitalio.Direction.OUTPUT
	while True:
		led.value = True
		time.sleep(0.5)
		led.value = False
		time.sleep(0.5)
	```

3. Your code will run as soon as the file is done saving. Observe that the LED starts to blink:

	![Blinky image]()

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Python:%20Blinky:%20%3Ctitle%3E"><button class="md-tile md-tile--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
