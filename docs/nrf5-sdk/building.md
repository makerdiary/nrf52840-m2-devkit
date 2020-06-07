# Building and Running a first example

This section details how to build and run the simple `Blinky` example.

Before you start building, remember to set up the nRF5 SDK development environment first:

<a href="../setup"><button class="md-tile md-tile--primary" style="width:auto;"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="16" height="16"><path fill-rule="evenodd" d="M16 8.5l-6 6-3-3L8.5 10l1.5 1.5L14.5 7 16 8.5zM5.7 12.2l.8.8H2c-.55 0-1-.45-1-1V3c0-.55.45-1 1-1h7c.55 0 1 .45 1 1v6.5l-.8-.8c-.39-.39-1.03-.39-1.42 0L5.7 10.8a.996.996 0 000 1.41v-.01zM4 4h5V3H4v1zm0 2h5V5H4v1zm0 2h3V7H4v1zM3 9H2v1h1V9zm0-2H2v1h1V7zm0-2H2v1h1V5zm0-2H2v1h1V3z"></path></svg> Setup the nRF5 SDK</button></a>

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

![](assets/images/build-blinky-example.webp)

## Running the example

After compiled, the firmware is located in `blinky/armgcc/_build` with the name `nrf52840_xxaa.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../assets/images/programming-firmware.webp)


Run the following command in `blinky/armgcc` to program the board:

``` sh
make flash_all
```

!!! Tip
	See **[Programming](../programming.md)** section for more details about how to program the nRF52840 M.2 Module.

After programmed, the application will run automatically. Observe that the LEDs will start to blink as shown in this figure:

![Blinky image]()

## Next steps

Check out more nRF5 SDK examples for nRF52840 M.2 Developer Kit:

* **Hardware Peripheral Examples**
    - [Blinky Example](examples/blinky.md)
	- [BSP Example](examples/bsp.md)
	- [Battery Status Example](examples/battery.md)
	- [microSD Card Example](examples/microsd.md)
	- [NFC Tag Example](examples/nfc.md)
	- [Power Profiling Example](examples/power-profiling.md)
	- [QSPI Flash Example](examples/qspi.md)
	- [RSSI Viewer Example](examples/rssi-viewer.md)
	- [Temperature Example](examples/temperature.md)
	- [TFT LCD Display Example](examples/tft-lcd.md)
	- [USB CDC ACM Example](examples/usb-cdc-acm.md)

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

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Building%20nRF5%20SDK%20Blinky:%20%3Ctitle%3E"><button class="md-tile md-tile--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
