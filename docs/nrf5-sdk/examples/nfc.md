# NFC Tag Example

## Description

The NFC Tag Example demonstrates how to use the NFC tag to expose a URL record to NFC devices.

When the application starts, it initializes the NFC tag and generates a URI message with a URI record containing the URL [https://makerdiary.com](https://makerdiary.com). Then it sets up the NFC library to use the generated message and sense the external NFC field. The only events handled by the application are the NFC events.

!!! Tip
	Before you start building, remember to set up the nRF5 SDK development environment first. See [Setup the nRF5 SDK](../setup.md) for details.


## Building the example

You can find the source code and the project file of the example in the following folder: [examples/nrf5-sdk/nfc/record_url](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/nrf5-sdk/nfc/record_url).

Open terminal and navigate to the directory with the example Makefile:

``` sh
cd ./examples/nrf5-sdk/nfc/record_url/armgcc
```

Run `make` to build the example:

``` sh
make
```

## Programming the firmware

If compiled successfully, the firmware is located in `nfc/record_url/armgcc/_build` with the name `nrf52840_xxaa.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../assets/images/programming-firmware.png)


Run the following command in `nfc/record_url/armgcc` to program the board:

``` sh
make flash_all
```

!!! Tip
	See **[Programming](../../programming.md)** section for details about how to program the nRF52840 M.2 Module.

## Testing

Test the NFC Tag Example with a smartphone or a tablet with NFC support by performing the following steps:

1. Make sure that the cabled NFC PCB Antenna is connected to nRF52840 M.2 Module through the U.FL connector.

2. Touch the NFC PCB Antenna with the smartphone or tablet and observe that GREEN LED is lit.

3. Observe that the smartphone/tablet tries to open the URL [https://makerdairy.com](https://makerdairy.com) in a web browser.

4. Move the smartphone/tablet away from the NFC PCB Antenna and observe that GREEN LED turns off.

![NFC image]()

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=nRF5%20SDK-NFC:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>