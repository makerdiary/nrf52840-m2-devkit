
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
advertisement.complete_name = 'CIRCUITPY KEYBOARD'
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
        print('Button is ' + ('released' if button.value else 'pressed'))
        if ble.connected:
            if not button.value:
                ble_keyboard.press(Keycode.A)
            else:
                ble_keyboard.release(Keycode.A)
