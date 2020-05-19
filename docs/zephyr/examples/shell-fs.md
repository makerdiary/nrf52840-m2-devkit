# File System Shell Example

The File System Shell Example demonstrates shell access to a LittleFS file system partition in flash.

You will be presented with a shell prompt. All file system related commands are available as sub-commands of `fs`.

Before you start building, the Zephyr development environment should be set up correctly:

<a href="../../setup"><button data-md-color-primary="red-bud" style="width:auto;">Setup Zephyr Toolchain</button></a>

## Build the example

You can find the source code and the project file of the example in the following folder: [examples/zephyr/shell/fs](https://github.com/makerdiary/nrf52840-m2-devkit/tree/master/examples/zephyr/shell/fs).

Build the example by performing the following steps:

1. Open terminal and navigate to the `m2devkit` directory created in the [Setup the toolchain](../setup.md) section:

	``` sh
	cd <sourcecode_root>/m2devkit
	```

2. Use `west` to build the example:

	``` sh
	west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/shell/fs
	```
	
	![](assets/images/building-shell-fs.png)

!!! tip
	If a build system is present, make the build folder pristine before building:

	``` sh
	west build -t pristine
	```

## Flash the example

After compiled successfully, the firmware is located in `m2devkit/build/zephyr` with the name `zephyr.hex`.

Connect the debugger USB port to your PC using the provided USB-C Cable. A disk drive called **M2-DOCK** will be automatically detected by the computer.

![](../assets/images/programming-firmware.png)

Run the following command to flash the board:

``` sh
west flash
```

![](assets/images/flashing-shell-fs.png)

## Testing

Test the File System Shell Example application by performing the following steps:

1. Connect the debugger USB port to your PC

2. Run a terminal application like [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/) or [screen](https://www.gnu.org/software/screen/manual/screen.html):

	``` sh
	screen /dev/cu.usbmodem14102 115200
	```

3. Press RESET button, and You will be presented with a shell prompt.

4. Run `fs` to to print the available subcommands:

	``` sh
	uart:~$ fs
	fs - File system commands
	Subcommands:
	cd       :Change working directory
	ls       :List files in current directory
	mkdir    :Create directory
	mount    :<Mount fs, syntax:- fs mount <fs type> <mount-point>
	pwd      :Print current working directory
	read     :Read from file
	rm       :Remove file
	statvfs  :Show file system state
	trunc    :Truncate file
	write    :Write file
	```

5. Try the file system related commands. For example, mount the LittleFS file system:

	``` sh
	fs mount littlefs /lfs
	```

	![](assets/images/logging-shell-fs.png)


## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Zephyr:%20Shell%20FS:%20%3Ctitle%3E"><button data-md-color-primary="red-bud"><i class="fa fa-github"></i> Create an Issue</button></a>