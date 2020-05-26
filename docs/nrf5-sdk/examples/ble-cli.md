# BLE CLI Example

## Description

The Command Line Interface over BLE (BLE CLI) Application is an example that demonstrates how BLE NUS (Nordic UART service) can be used as a transport for a console.

[Web Device CLI](https://github.com/makerdiary/web-device-cli) is a web-based command line interface using Web Bluetooth API. It implements the Nordic UART Service (NUS) with Bluetooth Low Energy. This web utility can be used to connect to the BLE CLI example.

!!! Tip
	Before you start building, remember to set up the nRF5 SDK development environment first. See [Setup the nRF5 SDK](../setup.md) for details.

## Building the example

You can find the source code and the project file of the example in the following folder: [examples/nrf5-sdk/ble_app_cli](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/nrf5-sdk/ble_app_cli).

Open terminal and navigate to the directory with the example Makefile:

``` sh
cd ./examples/nrf5-sdk/ble_app_cli/armgcc
```

Run `make merge` to build the application and merge with the Softdevice:

``` sh
make merge
```

## Programming the firmware

If compiled successfully, the firmware is located in `ble_app_cli/armgcc/_build` with the name `nrf52840_xxaa_s140.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../../assets/images/programming-firmware.webp)


Run the following command in `ble_app_cli/armgcc` to program the board:

``` sh
make flash_all
```

!!! Tip
	See **[Programming](../../programming.md)** section for details about how to program the nRF52840 M.2 Module.

## Testing

Perform the following steps to test the BLE CLI example:

1. Open the [Web Device CLI](https://wiki.makerdiary.com/web-device-cli/) page in a Chrome 56+ [browser](https://github.com/WebBluetoothCG/web-bluetooth/blob/master/implementation-status.md).

	<a href="https://wiki.makerdiary.com/web-device-cli/" target="_blank"><button data-md-color-primary="red-bud">Web Device CLI</button></a>

2. Click <kbd>Connect</kbd> to scan devices.

3. Pair the **Nordic_CLI** discovered in the list.

4. Observe that the LED stays GREEN and the `ble_cli:~$` prompt is displayed.

5. Press the <kbd>Tab</kbd> on your keyboard to print the available commands.

6. Use command `led {R} {G} {B}` to set the RGB LED color and observe the RGB LED on the module.

[![](assets/images/ble-app-cli-example.webp)](assets/images/ble-app-cli-example.webp)

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=nRF5%20SDK-BLE%20CLI:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
