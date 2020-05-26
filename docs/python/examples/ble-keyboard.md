# Bluetooth: Peripheral HID Keyboard

## Requirements
+ [adafruit-ble](https://github.com/adafruit/Adafruit_CircuitPython_BLE)
+ [adafruit-hid](https://github.com/adafruit/Adafruit_CircuitPython_HID)

Put the two libraries into the `lib` directory of the `CIRCUITPY` drive.

```python
CIRCUITPY
├───code.py
└───lib
	├───adafruit_ble
	└───adafruit_hid
```

## Code
Put the following content into `code.py`

```
import time
import board
import digitalio
import adafruit_ble
from adafruit_ble.advertising import Advertisement
from adafruit_ble.advertising.standard import ProvideServicesAdvertisement
from adafruit_ble.services.standard.hid import HIDService
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode


hid = HIDService()
advertisement = ProvideServicesAdvertisement(hid)
advertisement.appearance = 961
ble = adafruit_ble.BLERadio()
if ble.connected:
    for c in ble.connections:
        c.disconnect()
ble.start_advertising(advertisement)
advertising = True
ble_keyboard = Keyboard(hid.devices)

button = digitalio.DigitalInOut(board.USR_BTN)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

last_value = button.value

while True:
    if last_value != button.value:
        last_value = button.value
        print(button.value)
        if ble.connected:
            if not button.value:
                ble_keyboard.press(Keycode.A)
            else:
                ble_keyboard.release(Keycode.A)

``

When the code is running, a BLE with a name prefixed by "CIRCUITPY" can be discovered and connected.
Connect to the BLE device, you will get a BLE keyboard, and press the onboard button to send "A".


## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Zephyr:%20BLE%20HIDs:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
