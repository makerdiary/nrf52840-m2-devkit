# Setup the nRF5 SDK Development Environment

This section describes how to set up the nRF5 SDK development environment on your system.

## Set up the toolchain

To build the nRF5 SDK applications, [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads) is required. Follow one of the following guides for your host operating system:

* [macOS](#macos)
* [Windows](#windows)
* [Linux](#linux)

### macOS

Follow the steps below to set up the development environment on macOS:

1. GNU make is bundled with Xcode tools. Verify by running:
	``` sh
	make --v
	```

2. Download and install the [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads). The `7-2018-q2-update` version is recommended. Then ensure the path is added to your OS PATH environment variable.

    ``` sh
	echo 'export PATH="<path to install directory>/gcc-arm-none-eabi-7-2018-q2-update/bin:${PATH}"' >> ~/.bash_profile
	source ~/.bash_profile
    ```
    Type the following in your terminal to verify if the path is set correctly:

    ``` sh
    arm-none-eabi-gcc --version
    ```

3. Download the [nRF5x-Command-Line-Tools-OSX](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools/Download#infotabs), then extract the `.tar` archive anywhere on your filesystem. Ensure the extracted directory is added to your OS PATH environment variable.

    ``` sh 
	echo 'export PATH="<the path to the extracted directory>/mergehex:${PATH}"' >> ~/.bash_profile
	source ~/.bash_profile
    ```

    Type the following in your terminal to verify if `mergehex` works:
    ``` sh
    mergehex --version
    ```

4. Install the latest stable version of [pyOCD](https://github.com/mbedmicro/pyOCD) via `pip` as follows. **Skip** this step if pyOCD already exists.

	``` sh
	pip install -U pyocd
	```

	Type the following in your terminal to verify if `pyocd` works:
	``` sh
	pyocd --version
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
	choco install git make python
	```

5. Open a new `cmd.exe` window as a **regular user** to continue

6. Download and install the [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads). The `7-2018-q2-update` version is recommended. Run the installer and follow the given instructions. Upon completion, check the *Add path to environment variable* option. Then verify if the compiler works:

    ``` sh
    arm-none-eabi-gcc --version
    ```

7. Download the [nRF5x-Command-Line-Tools for Win32](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools/Download#infotabs). Run the installer and follow the given instructions. Then verify if `mergehex` works:

    ``` sh
    mergehex --version
    ```

8. Install the latest stable version of [pyOCD](https://github.com/mbedmicro/pyOCD) via `pip` as follows. **Skip** this step if pyOCD already exists.

	``` sh
	pip install -U pyocd
	```
	Type the following in your terminal to verify if `pyocd` works:
	``` sh
	pyocd --version
	```

### Linux

Here we describe how to set up the toolchain on Ubuntu version 18.04 LTS. The steps should be similar for other Linux distributions.

1. Ensure your host system is up to date before proceeding.

    ``` sh
    sudo apt update
    sudo apt upgrade
    ```

2. Install the following packages using your system’s package manager.

    ``` sh
    sudo apt install build-essential checkinstall
    ```

3. Download and install the [GNU ARM Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads). The `7-2018-q2-update` version is recommended. Then ensure the path is added to your OS PATH environment variable.

    ``` sh
	echo 'export PATH="<path to install directory>/gcc-arm-none-eabi-7-2018-q2-update/bin:${PATH}"' >> ~/.bashrc
	source ~/.bashrc
    ```
    Type the following in your terminal to verify if the path is set correctly:

    ``` sh
    arm-none-eabi-gcc --version
    ```

4. Download the [nRF5x-Command-Line-Tools-Linux-xxx](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools/Download#infotabs), then extract the `.tar` archive anywhere on your filesystem. Ensure the extracted directory is added to your OS PATH environment variable.

    ``` sh
	echo 'export PATH="<the path to the extracted directory>/mergehex:${PATH}"' >> ~/.bashrc
	source ~/.bashrc
    ```

    Type the following in your terminal to verify if `mergehex` works:
    ``` sh
    mergehex --version
    ```

5. Install the latest stable version of [pyOCD](https://github.com/mbedmicro/pyOCD) via `pip` as follows. **Skip** this step if pyOCD already exists.

	``` sh
	pip install -U pyocd
	```

	Type the following in your terminal to verify if `pyocd` works:
	``` sh
	pyocd --version
	```

## Clone the repository

Clone the `nrf52840-m2-devkit` repository from GitHub:

``` sh
git clone https://github.com/makerdiary/nrf52840-m2-devkit
```

## Install the nRF5 SDK

Download the SDK file [nRF5_SDK_16.0.0_98a08e2](https://www.nordicsemi.com/Software-and-Tools/Software/nRF5-SDK/Download#infotabs) from [www.nordicsemi.com](https://www.nordicsemi.com). Note that the current version is `16.0.0`.

<a href="https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK160098a08e2.zip"><button class="md-issue-button md-issue-button--primary" style="width:auto;"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="16" height="16"><path fill-rule="evenodd" d="M9 12h2l-3 3-3-3h2V7h2v5zm3-8c0-.44-.91-3-4.5-3C5.08 1 3 2.92 3 5 1.02 5 0 6.52 0 8c0 1.53 1 3 3 3h3V9.7H3C1.38 9.7 1.3 8.28 1.3 8c0-.17.05-1.7 1.7-1.7h1.3V5c0-1.39 1.56-2.7 3.2-2.7 2.55 0 3.13 1.55 3.2 1.8v1.2H12c.81 0 2.7.22 2.7 2.2 0 2.09-2.25 2.2-2.7 2.2h-2V11h2c2.08 0 4-1.16 4-3.5C16 5.06 14.08 4 12 4z"></path></svg> nRF5_SDK_16.0.0_98a08e2</button></a>

Extract the zip file to the `nrf52840-m2-devkit/nrf_sdks` directory. This should give you the following folder structure:

``` sh
./nrf52840-m2-devkit/
├── LICENSE
├── README.md
├── boards
├── config
├── docs
├── examples
├── firmware
├── mkdocs.yml
├── nrf_sdks
│   ├── README.md
│   └── nRF5_SDK_16.0.0_98a08e2
└── tools
```

To use the nRF5 SDK you first need to set the toolchain path in `makefile.windows` or `makefile.posix` depending on platform you are using. That is, the `.posix` should be edited if your are working on either Linux or macOS. These files are located in:

``` sh
cd <nRF5 SDK>/components/toolchain/gcc
```

Open the file in a text editor ([Visual Studio Code](https://code.visualstudio.com/) is recommended), and make sure that the `GNU_INSTALL_ROOT` variable is pointing to your GNU Arm Embedded Toolchain install directory.

``` sh
GNU_INSTALL_ROOT ?= $(HOME)/gcc-arm-none-eabi/gcc-arm-none-eabi-7-2018-q2-update/bin/
GNU_VERSION ?= 7.3.1
GNU_PREFIX ?= arm-none-eabi
```

## Next Step

If everything works as expected, it's ready to build and run the examples to verify the development environment setup.

The steps that are described in [Build & Run a first example](building.md) will walk you through verifying your setup with the simple `Blinky` example.


## Create an Issue

Interested in contributing to this project? Want to report a bug? Feel free to click here:

<a href="https://github.com/makerdiary/nrf52840-m2-devkit/issues/new?title=Setup%20the%20nRF5%20SDK:%20%3Ctitle%3E"><button class="md-issue-button md-issue-button--primary"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 14 16" width="14" height="16"><path fill-rule="evenodd" d="M7 2.3c3.14 0 5.7 2.56 5.7 5.7s-2.56 5.7-5.7 5.7A5.71 5.71 0 011.3 8c0-3.14 2.56-5.7 5.7-5.7zM7 1C3.14 1 0 4.14 0 8s3.14 7 7 7 7-3.14 7-7-3.14-7-7-7zm1 3H6v5h2V4zm0 6H6v2h2v-2z"></path></svg> Create an Issue</button></a>
