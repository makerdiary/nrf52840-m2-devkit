
.PHONY: release_all

TARGET_NAME        := nrf52840_m2
ZEPHYR_VERSION     := zephyr-v2.3.0-1-ge77985a2f053

# Release all prebuilt firmwares
release_all:
	@echo Compiling all examples...
	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/hello_world \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/hello_world/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/hello_world/hex/hello_world_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/blinky \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/blinky/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/blinky/hex/blinky_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/button \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/button/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/button/hex/button_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/spi_flash \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/spi_flash/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/spi_flash/hex/spi_flash_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/fat_fs \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/fat_fs/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/fat_fs/hex/fat_fs_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/lvgl \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/lvgl/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/lvgl/hex/lvgl_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/shell/fs \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/shell/fs/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/shell/fs/hex/shell_fs_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/shell/shell_module \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/shell/shell_module/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/shell/shell_module/hex/shell_module_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/bluetooth/beacon \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/bluetooth/beacon/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/bluetooth/beacon/hex/beacon_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/bluetooth/hci_usb \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/bluetooth/hci_usb/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/bluetooth/hci_usb/hex/hci_usb_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/bluetooth/peripheral_dis \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/bluetooth/peripheral_dis/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/bluetooth/peripheral_dis/hex/peripheral_dis_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

	cd $(ZEPHYR_BASE)/.. && rm -rf build \
	&& west build -b nrf52840_m2 nrf52840-m2-devkit/examples/zephyr/bluetooth/peripheral_hids \
	&& rm -rf nrf52840-m2-devkit/examples/zephyr/bluetooth/peripheral_hids/hex/* \
	&& cp build/zephyr/zephyr.hex nrf52840-m2-devkit/examples/zephyr/bluetooth/peripheral_hids/hex/peripheral_hids_$(TARGET_NAME)_$(ZEPHYR_VERSION).hex

