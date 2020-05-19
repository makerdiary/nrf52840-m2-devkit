# BLE HID Keyboard Example

The BLE HID Keyboard Example demonstrates how to implement the HID over GATT profile for keyboard.

The application includes the three mandatory services needed for the HID over GATT profile:

* Human Interface Device Service
* Device Information Service
* Battery Service

!!! Tip
	Before you start building, remember to set up the nRF5 SDK development environment first. See [Setup the nRF5 SDK](../setup.md) for details.

## Building the example

You can find the source code and the project file of the example in the following folder: [examples/nrf5-sdk/ble_app_hids_keyboard](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/nrf5-sdk/ble_app_hids_keyboard).

Open terminal and navigate to the directory with the example Makefile:

``` sh
cd ./examples/nrf5-sdk/ble_app_hids_keyboard/armgcc
```

Run `make merge` to build the application and merge with the Softdevice:

``` sh
make merge
```

## Programming the firmware

If compiled successfully, the firmware is located in `ble_app_hids_keyboard/armgcc/_build` with the name `nrf52840_xxaa_s140.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../assets/images/programming-firmware.png)

Run the following command in `ble_app_hids_keyboard/armgcc` to program the board:

``` sh
make flash_all
```

!!! Tip
	See **[Programming](../../programming.md)** section for details about how to program the nRF52840 M.2 Module.

## Testing

Use a computer with Bluetooth Low Energy supported to test the HID Keyboard Example. Here goes with macOS.

1. After the application starts, observe that GREEN LED is blinking. This indicates that the device is advertising.

2. Go to **System Preferences** -> **Bluetooth Preferences**, observe that the BLE HID keyboard named **Nordic_Keyboard** is found.

3. Connect to the keyboard. Observe that GREEN constant light, that is, the connections is established.

4. Put your cursor in the following text area and press the USER button on the board to input `hello`:
	
	<textarea name="textarea" placeholder="Input your text here..." style="width:80%;height:150px;font-size:1.2em;"></textarea>

!!! Note
	RESET the board to clear bond information from persistent storage before the next connection.

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=nRF5%20SDK-BLE%20HIDS%20Keyboard:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>

