# BLE HID Mouse Example

The BLE HID Mouse Example demonstrates how to implement the HID over GATT profile for mouse.

The application includes the three mandatory services needed for the HID over GATT profile:

* Human Interface Device Service
* Device Information Service
* Battery Service

!!! Tip
	Before you start building, remember to set up the nRF5 SDK development environment first. See [Setup the nRF5 SDK](../setup.md) for details.

## Building the example

You can find the source code and the project file of the example in the following folder: [examples/nrf5-sdk/ble_app_hids_mouse](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/nrf5-sdk/ble_app_hids_mouse).

Open terminal and navigate to the directory with the example Makefile:

``` sh
cd ./examples/nrf5-sdk/ble_app_hids_mouse/armgcc
```

Run `make merge` to build the application and merge with the Softdevice:

``` sh
make merge
```

## Programming the firmware

If compiled successfully, the firmware is located in `ble_app_hids_mouse/armgcc/_build` with the name `nrf52840_xxaa_s140.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../../assets/images/programming-firmware.webp)

Run the following command in `ble_app_hids_mouse/armgcc` to program the board:

``` sh
make flash_all
```

!!! Tip
	See **[Programming](../../programming.md)** section for details about how to program the nRF52840 M.2 Module.

## Testing

Use a computer with Bluetooth Low Energy supported to test the HID Mouse Example. Here goes with macOS.

1. After the application starts, observe that GREEN LED is blinking. This indicates that the device is advertising.

2. Go to **System Preferences** -> **Bluetooth Preferences**, observe that the BLE HID Mouse named **nRF5_Mouse** is found.

3. Connect to the mouse. Observe that GREEN constant light, that is, the connections is established.

4. Press USER button on the board. Observe that the mouse pointer on the screen moves to the left.


!!! Note
	RESET the board to clear bond information from persistent storage before the next connection.

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=nRF5%20SDK-BLE%20HIDS%20Mouse:%20%3Ctitle%3E"><button class="md-tile md-tile--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
