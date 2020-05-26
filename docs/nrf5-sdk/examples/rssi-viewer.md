# RSSI Viewer Example

## Description

The RSSI Viewer Example shows how to behave a RSSI Viewer and send RSSI data over serial port.

The [nRF Connect RSSI Viewer](https://github.com/NordicSemiconductor/pc-nrfconnect-rssi) app shows dBm per frequency in the 2400-2480 MHz range, and allows the user to tweak settings like sweep delay and animation duration.


!!! Tip
	Before you start building, remember to set up the nRF5 SDK development environment first. See [Setup the nRF5 SDK](../setup.md) for details.

## Building the example

You can find the source code and the project file of the example in the following folder: [examples/nrf5-sdk/rssi_viewer](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/nrf5-sdk/rssi_viewer).

Open terminal and navigate to the directory with the example Makefile:

``` sh
cd ./examples/nrf5-sdk/rssi_viewer/armgcc
```

Run `make` to build the example:

``` sh
make
```

## Programming the firmware

If compiled successfully, the firmware is located in `rssi_viewer/armgcc/_build` with the name `nrf52840_xxaa.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../../assets/images/programming-firmware.webp)

Run the following command in `rssi_viewer/armgcc` to program the board:

``` sh
make flash_all
```

!!! Tip
	See **[Programming](../../programming.md)** section for details about how to program the nRF52840 M.2 Module.

## Testing

Test the RSSI Viewer Example application by performing the following steps:

1. Install the **RSSI Viewer** app in [nRF Connect for Desktop](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Connect-for-desktop) by clicking <kbd>Install</kbd>.

	![](assets/images/install-rssi-viewer-app.webp)

2. Connect to the nRF52840 M.2 Module USB port, open the RSSI Viewer app and select the **USB CDC ACM** port.

	![](assets/images/rssi-viewer-connecting.webp)

3. Observe the RSSI data chart and try to tweak settings like sweep delay and animation duration.

	![](assets/images/running-rssi-viewer.webp)

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=nRF5%20SDK-RSSI%20Viewer:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>
