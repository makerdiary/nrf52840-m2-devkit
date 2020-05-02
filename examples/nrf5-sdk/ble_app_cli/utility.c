/**
* Copyright (c) 2019 makerdiary
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above
*   copyright notice, this list of conditions and the following
*   disclaimer in the documentation and/or other materials provided
*   with the distribution.

* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
/** @file utility.c
 * @brief This file contains the source code for the Out of Box Demo.
 *
 */

#include "nrf_cli.h"
#include "boards.h"
#include "low_power_pwm.h"
#include "nfc_t2t_lib.h"
#include "nfc_uri_msg.h"

static low_power_pwm_t low_power_pwm_r;
static low_power_pwm_t low_power_pwm_g;
static low_power_pwm_t low_power_pwm_b;

static const uint8_t m_board_gpio_list[] = GPIOS_LIST;

static bool m_nfc_activated = false;
/** @snippet [NFC URI usage_0] */
static const uint8_t m_nfc_url[] =
    {'m', 'a', 'k', 'e', 'r', 'd', 'i', 'a', 'r', 'y', '.', 'c', 'o', 'm'}; //URL "makerdiary.com"

uint8_t m_ndef_msg_buf[256];


/** @snippet [NFC URI usage_0] */
/**
 * @brief Callback function for handling NFC events.
 */
static void nfc_callback(void * p_context, nfc_t2t_event_t event, const uint8_t * p_data, size_t data_length)
{
    (void)p_context;

    switch (event)
    {
        case NFC_T2T_EVENT_FIELD_ON:
            bsp_board_led_on(BSP_BOARD_LED_2);
            break;

        case NFC_T2T_EVENT_FIELD_OFF:
            bsp_board_led_off(BSP_BOARD_LED_2);
            break;

        default:
            break;
    }
}

/**
 * @brief Function to be called in timer interrupt.
 *
 * @param[in] p_context     General purpose pointer (unused).
 */
static void pwm_handler(void * p_context)
{
    return;
}

/**
 * @brief Function to initalize low_power_pwm instances.
 *
 */
static void pwm_init(void)
{
    uint32_t err_code;
    low_power_pwm_config_t low_power_pwm_config;

    APP_TIMER_DEF(lpp_timer_0);
    low_power_pwm_config.active_high    = false;
    low_power_pwm_config.period         = 255;
    low_power_pwm_config.bit_mask       = BSP_LED_1_MASK;
    low_power_pwm_config.p_timer_id     = &lpp_timer_0;
    low_power_pwm_config.p_port         = BSP_LED_1_PORT;

    err_code = low_power_pwm_init((&low_power_pwm_g), &low_power_pwm_config, pwm_handler);
    APP_ERROR_CHECK(err_code);
    nrf_gpio_port_dir_output_set(low_power_pwm_config.p_port, low_power_pwm_g.bit_mask);
    err_code = low_power_pwm_duty_set(&low_power_pwm_g, 0);
    APP_ERROR_CHECK(err_code);

    APP_TIMER_DEF(lpp_timer_1);
    low_power_pwm_config.active_high    = false;
    low_power_pwm_config.period         = 255;
    low_power_pwm_config.bit_mask       = BSP_LED_2_MASK;
    low_power_pwm_config.p_timer_id     = &lpp_timer_1;
    low_power_pwm_config.p_port         = BSP_LED_2_PORT;

    err_code = low_power_pwm_init((&low_power_pwm_r), &low_power_pwm_config, pwm_handler);
    APP_ERROR_CHECK(err_code);
    nrf_gpio_port_dir_output_set(low_power_pwm_config.p_port, low_power_pwm_r.bit_mask);
    err_code = low_power_pwm_duty_set(&low_power_pwm_r, 0);
    APP_ERROR_CHECK(err_code);

    APP_TIMER_DEF(lpp_timer_2);
    low_power_pwm_config.active_high    = false;
    low_power_pwm_config.period         = 255;
    low_power_pwm_config.bit_mask       = BSP_LED_3_MASK;
    low_power_pwm_config.p_timer_id     = &lpp_timer_2;
    low_power_pwm_config.p_port         = BSP_LED_3_PORT;

    err_code = low_power_pwm_init((&low_power_pwm_b), &low_power_pwm_config, pwm_handler);
    APP_ERROR_CHECK(err_code);
    nrf_gpio_port_dir_output_set(low_power_pwm_config.p_port, low_power_pwm_b.bit_mask);
    err_code = low_power_pwm_duty_set(&low_power_pwm_b, 0);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for application initialization.
 */
void app_setup(void)
{
    /*Initialize low power PWM for all 3  channels of RGB LED*/
    pwm_init();
}

/**@brief Function for processing application events.
 */
void app_process(void)
{

}

/**@brief led command implementation.
 */
static void cmd_led(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    uint8_t duty_r, duty_g, duty_b;
    uint32_t err_code;

    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc != 4)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(low_power_pwm_r.pwm_state == NRFX_DRV_STATE_INITIALIZED)
    {
        err_code = low_power_pwm_start((&low_power_pwm_r), low_power_pwm_r.bit_mask);
        APP_ERROR_CHECK(err_code);
    }

    if(low_power_pwm_g.pwm_state == NRFX_DRV_STATE_INITIALIZED)
    {
        err_code = low_power_pwm_start((&low_power_pwm_g), low_power_pwm_g.bit_mask);
        APP_ERROR_CHECK(err_code);
    }

    if(low_power_pwm_b.pwm_state == NRFX_DRV_STATE_INITIALIZED)
    {
        err_code = low_power_pwm_start((&low_power_pwm_b), low_power_pwm_b.bit_mask);
        APP_ERROR_CHECK(err_code);
    }

    duty_r = atoi(argv[1]);
    duty_g = atoi(argv[2]);
    duty_b = atoi(argv[3]);

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "R:%d, G:%d, B:%d\r\n", duty_r, duty_g, duty_b);

    if(duty_r == 0 && duty_g == 0 && duty_b == 0)
    {
        err_code = low_power_pwm_stop(&low_power_pwm_r);
        APP_ERROR_CHECK(err_code); 
        err_code = low_power_pwm_stop(&low_power_pwm_g);
        APP_ERROR_CHECK(err_code);
        err_code = low_power_pwm_stop(&low_power_pwm_b);
        APP_ERROR_CHECK(err_code);

        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Closed\r\n");
        return;
    }

    err_code = low_power_pwm_duty_set(&low_power_pwm_r, duty_r);
    APP_ERROR_CHECK(err_code);

    err_code = low_power_pwm_duty_set(&low_power_pwm_g, duty_g);
    APP_ERROR_CHECK(err_code);

    err_code = low_power_pwm_duty_set(&low_power_pwm_b, duty_b);
    APP_ERROR_CHECK(err_code);

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Done\r\n");
}

/**@brief gpio command implementation.
 */
static void cmd_gpio(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "%s %s: command not found\r\n", argv[0], argv[1]);
}

/**@brief gpio set command implementation.
 */
static void cmd_gpio_set(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc > 2)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
        return;
    }

    uint32_t pin_no = atoi(argv[1]);

    if (pin_no > 0 && pin_no <= GPIOS_NUMBER)
    {
        nrf_gpio_cfg_output(m_board_gpio_list[pin_no]);
        nrf_gpio_pin_set(m_board_gpio_list[pin_no]);
    }
    else
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown GPIO number\r\n");
        return;
    }
    
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Done\r\n");
}

/**@brief gpio clear command implementation.
 */
static void cmd_gpio_clear(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc > 2)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
        return;
    }

    uint32_t pin_no = atoi(argv[1]);

    if (pin_no > 0 && pin_no <= GPIOS_NUMBER)
    {
        nrf_gpio_cfg_output(m_board_gpio_list[pin_no]);
        nrf_gpio_pin_clear(m_board_gpio_list[pin_no]);
    }
    else
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown GPIO number\r\n");
        return;
    }
    
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Done\r\n");
}

/**@brief gpio read command implementation.
 */
static void cmd_gpio_read(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc > 2)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
        return;
    }

    uint32_t pin_no = atoi(argv[1]);

    if (pin_no > 0 && pin_no <= GPIOS_NUMBER)
    {
        nrf_gpio_cfg_input(m_board_gpio_list[pin_no], NRF_GPIO_PIN_PULLUP);
        uint32_t val = nrf_gpio_pin_read(m_board_gpio_list[pin_no]);

        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "D%d is %s\r\n", pin_no, val == 0? "LOW" : "HIGH");
    }
    else
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown GPIO number\r\n");
    }
}

static void cmd_nfc(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ASSERT(p_cli);
    ASSERT(p_cli->p_ctx && p_cli->p_iface && p_cli->p_name);

    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "%s %s: command not found\r\n", argv[0], argv[1]);
}

static void cmd_nfc_start(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ret_code_t err_code;

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc != 1)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
        return;     
    }

    if(m_nfc_activated)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "NFC: Activated\r\n");
        return;
    }

    /* Set up NFC */
    err_code = nfc_t2t_setup(nfc_callback, NULL);
    APP_ERROR_CHECK(err_code);

    /** @snippet [NFC URI usage_1] */
    /* Provide information about available buffer size to encoding function */
    uint32_t len = sizeof(m_ndef_msg_buf);

    /* Encode URI message into buffer */
    err_code = nfc_uri_msg_encode( NFC_URI_HTTPS,
                                   m_nfc_url,
                                   sizeof(m_nfc_url),
                                   m_ndef_msg_buf,
                                   &len);

    APP_ERROR_CHECK(err_code);
    /** @snippet [NFC URI usage_1] */

    /* Set created message as the NFC payload */
    err_code = nfc_t2t_payload_set(m_ndef_msg_buf, len);
    APP_ERROR_CHECK(err_code);

    /* Start sensing NFC field */
    err_code = nfc_t2t_emulation_start();
    APP_ERROR_CHECK(err_code);

    m_nfc_activated = true;

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Done\r\n");
}

static void cmd_nfc_stop(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    ret_code_t err_code;

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc != 1)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
        return;     
    }

    if(!m_nfc_activated)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "NFC: Deactivated\r\n");
        return;
    }

    /* Start sensing NFC field */
    err_code = nfc_t2t_emulation_stop();
    APP_ERROR_CHECK(err_code);

    err_code = nfc_t2t_done();
    APP_ERROR_CHECK(err_code);

    m_nfc_activated = false;

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Done\r\n");
}

static void cmd_nfc_status(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if(argc != 1)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Unknown parameters\r\n");
        return;     
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "NFC: %s\r\n", m_nfc_activated? "Activated" : "Deactivated");
}



NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_gpio)
{
    NRF_CLI_CMD(set, NULL, "Set a GPIO pin. Usage: gpio set {0~21}", cmd_gpio_set),
    NRF_CLI_CMD(clear, NULL, "Clear a GPIO pin. Usage: gpio clear {0~21}", cmd_gpio_clear),
    NRF_CLI_CMD(read, NULL, "Read a GPIO pin. Usage: gpio read {0~21}", cmd_gpio_read),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(gpio, &m_sub_gpio, "Commands for GPIO access", cmd_gpio);

NRF_CLI_CMD_REGISTER(led, NULL, "Set RGB LED color(0~255). Usage: led {R} {G} {B}", cmd_led);

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_nfc)
{
    NRF_CLI_CMD(start, NULL, "Activate the NFC frontend", cmd_nfc_start),
    NRF_CLI_CMD(stop, NULL, "Deactivate the NFC frontend", cmd_nfc_stop),
    NRF_CLI_CMD(status, NULL, "Show the NFC frontend status", cmd_nfc_status),
    NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(nfc, &m_sub_nfc, "Commands for NFC access", cmd_nfc);

