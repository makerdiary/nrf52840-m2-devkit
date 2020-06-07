# Getting Started with nRF52840 M.2 Developer Kit

## Introduction
This guide describes how to run the Out-of-Box Demo without going through the complete toolchain installation. After following along with this section, you’ll be ready to start building your projects.

## Included in the Box

Your nRF52840 M.2 Developer Kit box includes:

|    **Part**                | **Qty** |
| -------------------------- | ------- |
| nRF52840 M.2 Module        | 1       |
| M.2 Dock                   | 1       |
| 2.4 GHz Cabled PCB Antenna | 1       |
| NFC Cabled PCB Antenna     | 1       |
| USB-C Cable                | 1       |

![Parts in the Kit]()

## Assemble the hardware

1. Make sure the M.2 Dock is powered off

2. Attach the provided 2.4GHz and NFC cabled PCB antennas to the nRF52840 M.2 module as shown in the figure below:

	![Attaching Antennas](assets/images/attaching-antennas-to-m2.webp)

3. Insert the module into the connector as shown in the figure below:

	!!! Warning "Angle of Insertion"
		Angled insertion is allowable and preferred to minimize the insertion force. The angle of insertion is **5° ~ 25°**, **typically 20°**.
	
	![Module Insertion](assets/images/m2-module-insertion.png)

4. Secure the module using the provided mounting screw as shown in the figure below:

	![Secure the module](assets/images/secure-m2-module-screw.png)

## Connect the board

Connect the **Module USB port** to your PC using the provided USB-C cable as shown in the figure below. A disk drive called **CIRCUITPY** should be automatically detected by the computer:

![](python/assets/images/connect-module-usb.webp)

## Run Out-of-Box demo

Now you're ready to run our Out-of-Box demo application! This application is an endless runner game written in Python. You can find the source code of the game on GitHub: 

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/python/dino"><button class="md-tile md-tile--primary" style="width:auto;"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 12 16" width="12" height="16"><path fill-rule="evenodd" d="M8.5 1H1c-.55 0-1 .45-1 1v12c0 .55.45 1 1 1h10c.55 0 1-.45 1-1V4.5L8.5 1zM11 14H1V2h7l3 3v9zM5 6.98L3.5 8.5 5 10l-.5 1L2 8.5 4.5 6l.5.98zM7.5 6L10 8.5 7.5 11l-.5-.98L8.5 8.5 7 7l.5-1z"></path></svg> examples/python/dino</button></a>

Just press the USER button to play the game:

![]()

## Next steps

Now that you are familiar with the nRF52840 M.2 Developer Kit, it's time to explore more examples and tutorials available below:

* [Python Tutorials](../python)
* [nRF5 SDK Tutorials](../nrf5-sdk)
* [Zephyr OS Tutorials](../zephyr)

To program the nRF52840 M.2 Module, check out this tutorial:

* [How to Program the nRF52840 M.2 Module](programming.md)

To perform real-time current profiling of your applications, try this tutorial:

* [Getting Started with Power Profiling](power-profiling.md)

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Getting%20Started:%20%3Ctitle%3E"><button class="md-tile md-tile--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
