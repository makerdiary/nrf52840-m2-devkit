# Bluetooth: Peripheral HIDs Example

The Peripheral HIDs Example demonstrates how to use the Bluetooth Low Energy HID GATT Service. The report map used is for a generic mouse.

Before you start building, the Zephyr development environment should be set up correctly:

<a href="../../setup"><button class="md-tile md-tile--primary" style="width:auto;"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="16" height="16"><path fill-rule="evenodd" d="M16 8.5l-6 6-3-3L8.5 10l1.5 1.5L14.5 7 16 8.5zM5.7 12.2l.8.8H2c-.55 0-1-.45-1-1V3c0-.55.45-1 1-1h7c.55 0 1 .45 1 1v6.5l-.8-.8c-.39-.39-1.03-.39-1.42 0L5.7 10.8a.996.996 0 000 1.41v-.01zM4 4h5V3H4v1zm0 2h5V5H4v1zm0 2h3V7H4v1zM3 9H2v1h1V9zm0-2H2v1h1V7zm0-2H2v1h1V5zm0-2H2v1h1V3z"></path></svg> Setup Zephyr Toolchain</button></a>

## Build the example

You can find the source code and the project file of the example in the following folder: [examples/zephyr/bluetooth/peripheral_hids](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/zephyr/bluetooth/peripheral_hids).

Build the example by performing the following steps:

1. Open terminal and navigate to the `m2devkit` directory created in the [Setup the toolchain](../setup.md) section:

	``` sh
	cd <sourcecode_root>/m2devkit
	```

2. Use `west` to build the example:

	``` sh
	west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/bluetooth/peripheral_hids
	```

	![](assets/images/building-ble-hids.webp)

!!! tip
	If a build system is present, make the build folder pristine before building:

	``` sh
	west build -t pristine
	```

## Flash the example

After compiled successfully, the firmware is located in `m2devkit/build/zephyr` with the name `zephyr.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../../assets/images/programming-firmware.webp)

Run the following command to flash the board:

``` sh
west flash
```

![](assets/images/flashing-ble-hids.webp)

## Testing

Test the Peripheral HIDs Example application by performing the following steps:

1. Connect the debugger USB port to your PC

2. Run a terminal application like [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/) or [screen](https://www.gnu.org/software/screen/manual/screen.html):

	``` sh
	screen /dev/cu.usbmodem14102 115200
	```

3. Press RESET button, and observe the output of the terminal:

	``` sh
	*** Booting Zephyr OS build zephyr-v2.3.0-1-ge77985a2f053  ***
	Bluetooth initialized
	[00:00:00.006,988] <inf> fs_nvs: 4 Sectors of 4096 bytes
	[00:00:00.006,988] <inf> fs_nvs: alloc wra: 0, fd8
	Advertising successfully started
	[00:00:00.007,019] <inf> fs_nvs: data wra: 0, 1c
	[00:00:00.008,544] <inf> bt_hci_core: HW Platform: Nordic Semiconductor (0x0002)
	[00:00:00.008,575] <inf> bt_hci_core: HW Variant: nRF52x (0x0002)
	[00:00:00.008,575] <inf> bt_hci_core: Firmware: Standard Bluetooth controller (0x00) Version 2.3 Build 99
	[00:00:00.008,880] <inf> bt_hci_core: No ID address. App must call settings_load()
	[00:00:00.011,260] <inf> bt_hci_core: Identity: f0:9f:05:d9:4f:45 (random)
	[00:00:00.011,260] <inf> bt_hci_core: HCI: version 5.2 (0x0b) revision 0x0000, manufacturer 0x05f1
	[00:00:00.011,291] <inf> bt_hci_core: LMP: version 5.2 (0x0b) subver 0xffff
	```

4. Use a computer with Bluetooth Low Energy supported to connect the device. Here goes with macOS: Go to **System Preferences** -> **Bluetooth Preferences**, observe that the BLE HID Mouse named **Test HoG mouse** is found and click <kbd>Connect</kbd>.

5. You will be asked for a passkey. Enter the passkey printed in the terminal, then click <kbd>Connect</kbd>:

	![](assets/images/macos-ble-hids.webp)


## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Zephyr:%20BLE%20HIDs:%20%3Ctitle%3E"><button class="md-tile md-tile--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
