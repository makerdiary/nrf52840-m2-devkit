# USB Keyboard

## Requirements
+ [adafruit-hid](https://github.com/adafruit/Adafruit_CircuitPython_HID)

Put the two libraries into the `lib` directory of the `CIRCUITPY` drive.

```
CIRCUITPY
├───code.py
└───lib
	└───adafruit_hid
```

## Code
Put the following content into `code.py`

```python
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
        print(button.value)
        if not button.value:
            usb_keyboard.press(Keycode.A)
        else:
            usb_keyboard.release(Keycode.A)


``

When the code is running, you will get a USB keyboard. Pressing the onboard button will output the key `A`.


## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Zephyr:%20BLE%20HIDs:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
