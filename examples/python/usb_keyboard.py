
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
