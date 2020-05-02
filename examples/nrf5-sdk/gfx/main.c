/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @file
 * @brief TFT Example Application main file.
 *
 * This file contains the source code for a sample application using the
 * GFX library based on the ILI9341 controller.
 *
 */

#include "nrf_gfx.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


// Some ready-made 16-bit ('565') color settings:
#define ST7789_BLACK       0x0000
#define ST7789_WHITE       0xFFFF
#define ST7789_RED         0xF800
#define ST7789_GREEN       0x07E0
#define ST7789_BLUE        0x001F
#define ST7789_CYAN        0x07FF
#define ST7789_MAGENTA     0xF81F
#define ST7789_YELLOW      0xFFE0
#define ST7789_ORANGE      0xFC00

static const char * test_text = "makerdiary";

extern const nrf_gfx_font_desc_t orkney_24ptFontInfo;
extern const nrf_lcd_t nrf_lcd_st7789;

static const nrf_gfx_font_desc_t * p_font = &orkney_24ptFontInfo;
static const nrf_lcd_t * p_lcd = &nrf_lcd_st7789;

static void gfx_initialization(void)
{
    APP_ERROR_CHECK(nrf_gfx_init(p_lcd));
}

static void brackground_set(void)
{
    nrf_gfx_screen_fill(p_lcd, ST7789_BLACK);
}

static void text_print(void)
{
    nrf_gfx_point_t text_start = NRF_GFX_POINT(25, 5);
    APP_ERROR_CHECK(nrf_gfx_print(p_lcd, &text_start, ST7789_WHITE, test_text, p_font, true));

    text_start.x = 25;
    text_start.y = 43;
    APP_ERROR_CHECK(nrf_gfx_print(p_lcd, &text_start, ST7789_RED, test_text, p_font, true));

    text_start.x = 25;
    text_start.y = 81;
    APP_ERROR_CHECK(nrf_gfx_print(p_lcd, &text_start, ST7789_GREEN, test_text, p_font, true));

    text_start.x = 25;
    text_start.y = 119;
    APP_ERROR_CHECK(nrf_gfx_print(p_lcd, &text_start, ST7789_BLUE, test_text, p_font, true));

    text_start.x = 25;
    text_start.y = 157;
    APP_ERROR_CHECK(nrf_gfx_print(p_lcd, &text_start, ST7789_CYAN, test_text, p_font, true));

    text_start.x = 25;
    text_start.y = 195;
    APP_ERROR_CHECK(nrf_gfx_print(p_lcd, &text_start, ST7789_ORANGE, test_text, p_font, true));
}

static void screen_clear(void)
{
    nrf_gfx_screen_fill(p_lcd, ST7789_BLACK);
}

int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("GFX usage example application started.")
    NRF_LOG_FLUSH();

    gfx_initialization();
    
    brackground_set();

    while (1)
    {
       text_print();
       nrf_delay_ms(2000);
       screen_clear();
    }
}

