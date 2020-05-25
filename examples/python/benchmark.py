

import digitalio
import board
import time

def count():
    a = 0
    b = 1000000
    t = time.monotonic_ns()
    while a < b:
        a += 1

    dt = time.monotonic_ns() - t
    print('it takes {} ns to count 1 million times'.format(dt))
    # about 7002048000 ns


led = digitalio.DigitalInOut(board.D13)
led.direction = digitalio.Direction.OUTPUT

def blink():
    t = time.monotonic_ns()
    for _ in range(1000):
        led.value = True
        led.value = False
    dt = time.monotonic_ns() - t
    print('it takes {} ns to blink 1000 times'.format(dt))
    # about 40824000 ns
    
while True:
    count()
    blink()

