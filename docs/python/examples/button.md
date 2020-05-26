# Button Example

| Button                | Pin      | Name             |
|-----------------------|----------|------------------|
| USR Button            | P0_19    | USR_BTN / D2     |

The USR button is pulled up. When the button is pressed, the input level of the button pin will be low (`False`).

```python
import board
import digitalio
import time
 
button = digitalio.DigitalInOut(board.USR_BTN)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

last_value = button.value

while True:
    if last_value != button.value:
        last_value = button.value
        print(button.value)
```

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Zephyr:%20Button:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
