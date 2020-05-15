# Building and Running a first example

This section details how to build and run the simple `Blinky` example.

Before you start building, remember to set up the nRF5 SDK development environment first:

<a href="setup"><button data-md-color-primary="red-bud">Setup nRF5 SDK</button></a>

## Building the example

Now it's ready to build the first example. Will use the `Blinky` example here to keep it simple. 

The `Blinky` example shows how to blink the LEDs. The source code is located in [nrf52840-m2-devkit/examples/nrf5-sdk/blinky](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/nrf5-sdk/blinky).

Open terminal and navigate to the directory with the example Makefile:

``` sh
cd ./nrf52840-m2-devkit/examples/nrf5-sdk/blinky/armgcc
```

Run `make` to build the example:

``` sh
make
```

![](assets/images/build-blinky-example.png)

## Running the example

After compiled, the firmware is located in `blinky/armgcc/_build` with the name `nrf52840_xxaa.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](assets/images/programming-firmware.png)


Drag and drop the firmware `nrf52840_xxaa.hex` onto the **M2-DOCK** drive, or run the following command in `blinky/armgcc` to program the board:

``` sh
make flash
```


!!! Tip
	See **[Programming](../programming.md)** section for details about how to program the nRF52840 M.2 Module.

## Next Steps

Check out more nRF5 SDK examples for nRF52840 M.2 Developer Kit:

* **Hardware Peripheral Examples**
    - [Blinky Example](examples/blinky.md)
	- [BSP Example](examples/bsp.md)
	- [Battery Status Example](examples/battery.md)
	- [MicroSD Card Example](examples/microsd.md)
	- [NFC Tag Example](examples/nfc.md)
	- [Power Profiling Example](examples/power-profiling.md)
	- [QSPI Flash Example](examples/qspi.md)
	- [RSSI Viewer Example](examples/rssi-viewer.md)
	- [Temperature Example](examples/temperature.md)
	- [TFT LCD Display Example](examples/tft-lcd.md)

* **Bluetooth Low Energy Examples**

	- [BLE Blinky Example](examples/ble-blinky.md)
	- [BLE Beacon Example](examples/ble-beacon.md)
	- [BLE Battery Service Example](examples/ble-bas.md)
	- [BLE CLI Example](examples/ble-cli.md)
	- [BLE Heart Rate Service](examples/ble-hrs.md)
	- [BLE HID Keyboard Example](examples/ble-hids-keyboard.md)
	- [BLE HID Mouse Example](examples/ble-hids-mouse.md)

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Building%20nRF5%20SDK%20Blinky:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
