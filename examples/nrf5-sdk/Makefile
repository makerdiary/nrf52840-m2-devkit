
.PHONY: release_all

# Release all prebuilt firmwares
release_all:
	@echo Compiling all examples...
	cd battery_status/armgcc && make release
	cd blinky/armgcc && make release
	cd bsp/armgcc && make release
	cd fatfs/armgcc && make release
	cd gfx/armgcc && make release
	cd nfc/record_url/armgcc && make release
	cd pwr_mgmt/armgcc && make release
	cd qspi/armgcc && make release
	cd radio_test/armgcc && make release
	cd rssi_viewer/armgcc && make release
	cd temperature/armgcc && make release
	cd usbd_cdc_acm/armgcc && make release
	cd ble_app_blinky/armgcc && make release
	cd ble_app_beacon/armgcc && make release
	cd ble_app_bas/armgcc && make release
	cd ble_app_cli/armgcc && make release
	cd ble_app_hrs/armgcc && make release
	cd ble_app_hids_keyboard/armgcc && make release
	cd ble_app_hids_keyboard_pairing_nfc/armgcc && make release
	cd ble_app_hids_mouse/armgcc && make release
	cd ble_app_att_mtu_throughput/tester/armgcc && make release
	cd ble_app_att_mtu_throughput/responder/armgcc && make release

# Clean all builds
clean_all:
	@echo Compiling all examples...
	cd battery_status/armgcc && make clean
	cd blinky/armgcc && make clean
	cd bsp/armgcc && make clean
	cd fatfs/armgcc && make clean
	cd gfx/armgcc && make clean
	cd nfc/record_url/armgcc && make clean
	cd pwr_mgmt/armgcc && make clean
	cd qspi/armgcc && make clean
	cd radio_test/armgcc && make clean
	cd rssi_viewer/armgcc && make clean
	cd temperature/armgcc && make clean
	cd usbd_cdc_acm/armgcc && make clean
	cd ble_app_blinky/armgcc && make clean
	cd ble_app_beacon/armgcc && make clean
	cd ble_app_bas/armgcc && make clean
	cd ble_app_cli/armgcc && make clean
	cd ble_app_hrs/armgcc && make clean
	cd ble_app_hids_keyboard/armgcc && make clean
	cd ble_app_hids_keyboard_pairing_nfc/armgcc && make clean
	cd ble_app_hids_mouse/armgcc && make clean
	cd ble_app_att_mtu_throughput/tester/armgcc && make clean
	cd ble_app_att_mtu_throughput/responder/armgcc && make clean