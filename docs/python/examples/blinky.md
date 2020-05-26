# Blinky Example

There are 4 LEDs on the devkit:

| LEDs                  | Pin      | Name             |
|-----------------------|----------|------------------|
| Red LED on M.2        | P0_30    | LED_RED          |
| Green LEDs on M.2     | P0_29    | LED_GREEN        |
| Blue LEDs on M.2      | P0_31    | LED_BLUE         |
| Green LED on M.2 Dock | P1_07    | D13              |

To control a LED, we can connect to the board's REPL and use the `digitalio` module.
For example, run the following code to turn on the LED on the M.2 Dock:

```
>>>import digitialio
>>>import board
>>>led = digitalio.DigitalInOut(board.D13)
>>>led.value = 0
```

Then turn the LED off:
```
>>>led.value = 1
```

We can also put Python code into `code.py` of the `CIRCUITPY` drive. To blink the LED, set the content of `code.py` to:

```python
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

These Python code will be executed when the board powers on.

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Zephyr:%20Hello%20World:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
