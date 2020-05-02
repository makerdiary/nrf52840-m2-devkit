# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

# Re-direct the directory where the 'boards' directory is found from
# $ZEPHYR_BASE to this directory.
set(BOARD_ROOT $ENV{NRF52840_M2_ROOT})

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(lvgl)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
