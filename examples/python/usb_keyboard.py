
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
            usb_keyboard.press(Keycode.LEFT_GUI)
        else:
            usb_keyboard.release(Keycode.LEFT_GUI)
