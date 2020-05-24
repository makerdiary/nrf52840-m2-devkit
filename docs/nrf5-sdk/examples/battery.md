# Battery Status Example

## Description

The Battery Status Example shows how to get the status of the battery charger, including the battery level and charging state.

The example initializes the SAADC driver and configures one channel to sample the voltage of the battery. Application Timer module is used to generate a timeout event. When the timer expires, the callback function will be called to print the measurement.

!!! Tip
	Before you start building, remember to set up the nRF5 SDK development environment first. See [Setup the nRF5 SDK](../setup.md) for details.

## Building the example

You can find the source code and the project file of the example in the following folder: [examples/nrf5-sdk/battery_status](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/nrf5-sdk/battery_status).

Open terminal and navigate to the directory with the example Makefile:

``` sh
cd ./examples/nrf5-sdk/battery_status/armgcc
```

Run `make` to build the example:

``` sh
make
```

## Programming the firmware

If compiled successfully, the firmware is located in `battery_status/armgcc/_build` with the name `nrf52840_xxaa.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../../assets/images/programming-firmware.png)

Run the following command in `battery_status/armgcc` to program the board:

``` sh
make flash_all
```

!!! Tip
	See **[Programming](../../programming.md)** section for details about how to program the nRF52840 M.2 Module.

## Testing

Test the example by performing the following steps:

1. Connect a **3.7V Li-Po battery** with 2-pin JST-PH 2.0 connector to the Battery connector.

2. Run a terminal application like [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/) or [screen](https://www.gnu.org/software/screen/manual/screen.html):

	``` sh
	screen /dev/cu.usbmodem14102 115200
	```

3. Observe that the battery status is printed every 2 seconds.

	![](assets/images/battery-status.png)

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=nRF5%20SDK-Battery:%20%3Ctitle%3E"><button data-md-color-primary="marsala"><i class="fa fa-github"></i> Create an Issue</button></a>
