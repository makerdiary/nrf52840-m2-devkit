# Blinky Example

## Description

Blinky Example is a simple application which blinks an LED forever using the `digitalio` module. The source code shows how to configure the GPIO pin as output, then turn it on and off.

The table below shows the available LEDs on the nRF52840 M.2 Developer Kit:

| Available LEDs          | Pin      | Name             |
|-------------------------|----------|------------------|
| Red LED on M.2 Module   | P0_30    | LED_RED          |
| Green LED on M.2 Module | P0_29    | LED_GREEN        |
| Blue LED on M.2 Module  | P0_31    | LED_BLUE         |
| Green LED on M.2 Dock   | P1_07    | D13              |


Before you start coding, the Python Interpreter should be installed on the nRF52840 M.2 module correctly:

<a href="../../install"><button data-md-color-primary="red-bud" style="width:auto;">Install Python Interpreter</button></a>

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

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Python:%20Blinky:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
