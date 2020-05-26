# Install Python on nRF52840 M.2 Developer Kit

There is a pre-compiled CircuitPython firmware for the nRF52840 M.2 Developer Kit.

+ [CircuiPython 5.3.0](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/firmware/nrf52840_m2_devkit_circuitpython_5.3.0.hex)

To use it, we can just drag-n-drop it into the drive `DAPLink`, or use `pyocd flash -t nrf52840 nrf52840_m2_devkit_circuitpython_5.3.0.hex` to flash the firmware.

After we flashed the firmware, we will get a usb drive named `CIRCUITPY` when we plug in the board with the USB port near by the `USR` button. The `CIRCUITPY` drive is used to store our Python code. We can also get a USB virtual serial port. When connecting to the serial port, we will get a Python REPL.

```
>>>print('hello, world')
```
