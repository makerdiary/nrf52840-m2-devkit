# Setup the Zephyr Development Environment

## Set up the toolchain

This section describes how to set up the Zephyr development environment on your system. Follow one of the following guides for your host operating system:

* [macOS](#macos)
* [Linux](#Linux)
* [Windows](#windows)

For more latest information, see [Development Environment Setup](https://docs.zephyrproject.org/latest/getting_started/index.html) in Zephyr’s Getting Started Guide.

### macOS

Follow the steps below to set up the development environment on macOS:

1. Install the dependencies:

	``` sh
	brew install cmake ninja gperf ccache dfu-util dtc python3
	```

2. Download and install the [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads). The `8-2019-q3-update` version is recommended. Then set the following environment variables:

	- Set `ZEPHYR_TOOLCHAIN_VARIANT` to `gnuarmemb`.
	- Set `GNUARMEMB_TOOLCHAIN_PATH` to the toolchain installation directory.

    ``` sh
	echo 'export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb' >> ~/.bash_profile
	echo 'export GNUARMEMB_TOOLCHAIN_PATH="<the toolchain installation directory>"' >> ~/.bash_profile
	source ~/.bash_profile
    ```
    Type the following in your terminal to verify if the variables are set correctly:

    ``` sh
    echo $ZEPHYR_TOOLCHAIN_VARIANT
    echo $GNUARMEMB_TOOLCHAIN_PATH
    ```

3. Install `west` to manage the combination of repositories and versions:

	``` sh
	pip3 install west
	```

4. Initialize west and clone the manifest repository `nrf52840-m2-devkit`:

	``` sh
	cd <sourcecode_root>
	mkdir m2devkit
	cd m2devkit
	west init -m https://github.com/makerdiary/nrf52840-m2-devkit
	west update
	```

5. The Zephyr repository contains a list of required Python modules. Install these modules by entering the following command:

	``` sh
	cd <sourcecode_root>/m2devkit
	pip3 install -r zephyr/scripts/requirements.txt
	```

### Linux

This guide covers Ubuntu version 18.04 LTS and later. These steps should be similar for other Linux distributions.

1. Ensure your host system is up to date before proceeding.

	``` sh
	sudo apt update
	sudo apt upgrade
	```

2. Use `apt` to install dependencies:

	``` sh
	sudo apt install --no-install-recommends git cmake ninja-build gperf \
	ccache dfu-util device-tree-compiler wget \
	python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
	make gcc gcc-multilib g++-multilib libsdl2-dev
	```

2. Download and install the [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads). The `8-2019-q3-update` version is recommended. Then set the following environment variables:

	- Set `ZEPHYR_TOOLCHAIN_VARIANT` to `gnuarmemb`.
	- Set `GNUARMEMB_TOOLCHAIN_PATH` to the toolchain installation directory.

    ``` sh
	echo 'export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb' >> ~/.bashrc
	echo 'export GNUARMEMB_TOOLCHAIN_PATH="<the toolchain installation directory>"' >> ~/.bashrc
	source ~/.bashrc
    ```
    Type the following in your terminal to verify if the variables are set correctly:

    ``` sh
    echo $ZEPHYR_TOOLCHAIN_VARIANT
    echo $GNUARMEMB_TOOLCHAIN_PATH
    ```
3. Install west, and make sure `~/.local/bin` is on your PATH environment variable:

	``` sh
	pip3 install --user -U west
	echo 'export PATH=~/.local/bin:"$PATH"' >> ~/.bashrc
	source ~/.bashrc
	```

4. Initialize west and clone the manifest repository `nrf52840-m2-devkit`:

	``` sh
	cd <sourcecode_root>
	mkdir m2devkit
	cd m2devkit
	west init -m https://github.com/makerdiary/nrf52840-m2-devkit
	west update
	```

5. The Zephyr repository contains a list of required Python modules. Install these modules by entering the following command:

	``` sh
	cd <sourcecode_root>/m2devkit
	pip3 install --user -r zephyr/scripts/requirements.txt
	```

### Windows

The following instructions rely on [Chocolatey](https://chocolatey.org/). If Chocolatey isn’t an option, you can install dependencies from their respective websites and ensure the command line tools are on your PATH environment variable.

1. [Install chocolatey](https://chocolatey.org/install)

2. Open an **Administrator** `cmd.exe` window

3. Disable global confirmation to avoid having to confirm installation of individual programs:

	``` sh
	choco feature enable -n allowGlobalConfirmation
	```

4. Use `choco` to install dependencies:

	``` sh
	choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
	choco install ninja gperf python git
	```

5. Open a new `cmd.exe` window **as a regular user** to continue.

6. Install `west` to manage the combination of repositories and versions:

	``` sh
	pip3 install west
	```

7. Initialize west and clone the manifest repository `nrf52840-m2-devkit`:

	``` sh
	cd <sourcecode_root>
	mkdir m2devkit
	cd m2devkit
	west init -m https://github.com/makerdiary/nrf52840-m2-devkit
	west update
	```

5. The Zephyr repository contains a list of required Python modules. Install these modules by entering the following command:

	``` sh
	cd <sourcecode_root>/m2devkit
	pip3 install -r zephyr/scripts/requirements.txt
	```

## Next Step

If everything works as expected, it's ready to build and run the Zephyr examples to verify the development environment setup.

The steps that are described in [Build & Run a first example](building.md) will walk you through verifying your setup with the simple [Blinky](examples/blinky.md) example.

## Reference

* [Zephyr Project: Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html#getting-started)
* [Zephyr Project: Beyond the Getting Started Guide](https://docs.zephyrproject.org/latest/guides/beyond-GSG.html#)

## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Setup%20the%20Zepnyr%20Toolchain:%20%3Ctitle%3E"><button class="md-issue-button md-issue-button--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
