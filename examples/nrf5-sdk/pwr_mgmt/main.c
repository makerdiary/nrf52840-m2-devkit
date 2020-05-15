/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "bsp.h"
#include "bsp_nfc.h"
#include "app_timer.h"
#include "nordic_common.h"
#include "app_error.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_qspi.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_delay.h"
#include "nrfx_spim.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define ST7789_SWRESET   0x01
#define ST7789_SLPIN     0x10
#define QSPI_STD_CMD_DP  0xB9

#if NRF_PWR_MGMT_CONFIG_USE_SCHEDULER
#include "app_scheduler.h"
#define APP_SCHED_MAX_EVENT_SIZE    0   /**< Maximum size of scheduler events. */
#define APP_SCHED_QUEUE_SIZE        4   /**< Maximum number of events in the scheduler queue. */
#endif // NRF_PWR_MGMT_CONFIG_USE_SCHEDULER

#define BTN_ID_SLEEP                0   /**< ID of the button used to put the application into sleep/system OFF mode. */

static volatile bool m_stay_in_sysoff;  /**< True if the application should stay in system OFF mode. */
static volatile bool m_is_ready;        /**< True if the application is ready to enter sleep/system OFF mode. */
static volatile bool m_sysoff_started;  /**< True if the application started sleep preparation. */


static const nrfx_spim_t m_spi = NRFX_SPIM_INSTANCE(ST7789_SPI_INSTANCE);  /**< SPI instance. */
static volatile bool m_spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */

void spim_event_handler(nrfx_spim_evt_t const * p_event,
                       void *                  p_context)
{
    m_spi_xfer_done = true;
}

static inline void spi_write(const void * data, size_t size)
{
	nrfx_spim_xfer_desc_t xfer_desc;

	xfer_desc.p_tx_buffer = data;
	xfer_desc.p_rx_buffer = NULL;
	xfer_desc.tx_length = size;
	xfer_desc.rx_length = 0;

	m_spi_xfer_done = false;
	APP_ERROR_CHECK(nrfx_spim_xfer(&m_spi, &xfer_desc, 0));
	while(!m_spi_xfer_done)
	{
		//__WFE();
	}
}

static inline void write_command(uint8_t c)
{
    nrf_gpio_pin_clear(ST7789_DC_PIN);
    spi_write(&c, sizeof(c));
}


static void qspi_handler(nrf_drv_qspi_evt_t event, void * p_context)
{
    UNUSED_PARAMETER(event);
    UNUSED_PARAMETER(p_context);
}

static void configure_memory()
{
    
    uint32_t err_code;
    nrf_qspi_cinstr_conf_t cinstr_cfg = {
        .opcode    = QSPI_STD_CMD_DP,
        .length    = NRF_QSPI_CINSTR_LEN_1B,
        .io2_level = true,
        .io3_level = true,
        .wipwait   = true,
        .wren      = true
    };

    // Send Deep power down
    err_code = nrf_drv_qspi_cinstr_xfer(&cinstr_cfg, NULL, NULL);
    APP_ERROR_CHECK(err_code);
    
}

static void configure_st7789(void)
{
	ret_code_t err_code;

	nrf_gpio_cfg_output(ST7789_DC_PIN);
    nrf_gpio_cfg_output(ST7789_RST_PIN);
    nrf_gpio_cfg_output(ST7789_BL_CTRL_PIN);

	/* Configure SPI. */
    nrfx_spim_config_t spi_config = NRFX_SPIM_DEFAULT_CONFIG;
    spi_config.frequency = NRF_SPIM_FREQ_32M;
    spi_config.ss_pin    = ST7789_SS_PIN;
    spi_config.mosi_pin  = ST7789_MOSI_PIN;
    spi_config.sck_pin   = ST7789_SCK_PIN;

    err_code = nrfx_spim_init(&m_spi, &spi_config, spim_event_handler, NULL);
	APP_ERROR_CHECK(err_code);

    nrf_gpio_pin_clear(ST7789_RST_PIN);
    nrf_delay_ms(20);
    nrf_gpio_pin_set(ST7789_RST_PIN);
    nrf_delay_ms(20);

    write_command(ST7789_SWRESET);
    nrf_delay_ms(150);
    write_command(ST7789_SLPIN);
    nrf_delay_ms(10);
}


/**@brief Handler for shutdown preparation.
 */
bool shutdown_handler(nrf_pwr_mgmt_evt_t event)
{
    uint32_t err_code;

    if (m_is_ready == false)
    {
        m_sysoff_started = true;
        return false;
    }

    switch (event)
    {
        case NRF_PWR_MGMT_EVT_PREPARE_SYSOFF:
            NRF_LOG_INFO("NRF_PWR_MGMT_EVT_PREPARE_SYSOFF");
            err_code = bsp_buttons_disable();
            APP_ERROR_CHECK(err_code);
            break;

        case NRF_PWR_MGMT_EVT_PREPARE_WAKEUP:
            NRF_LOG_INFO("NRF_PWR_MGMT_EVT_PREPARE_WAKEUP");
            err_code = bsp_buttons_disable();
            // Suppress NRF_ERROR_NOT_SUPPORTED return code.
            UNUSED_VARIABLE(err_code);

            // err_code = bsp_wakeup_button_enable(BTN_ID_WAKEUP);
            // Suppress NRF_ERROR_NOT_SUPPORTED return code.
            UNUSED_VARIABLE(err_code);

            err_code = bsp_nfc_sleep_mode_prepare();
            // Suppress NRF_ERROR_NOT_SUPPORTED return code.
            UNUSED_VARIABLE(err_code);
            break;

        case NRF_PWR_MGMT_EVT_PREPARE_DFU:
            NRF_LOG_ERROR("Entering DFU is not supported by this example.");
            APP_ERROR_HANDLER(NRF_ERROR_API_NOT_IMPLEMENTED);
            break;

        case NRF_PWR_MGMT_EVT_PREPARE_RESET:
            NRF_LOG_INFO("NRF_PWR_MGMT_EVT_PREPARE_RESET");
            break;
    }

    err_code = app_timer_stop_all();
    APP_ERROR_CHECK(err_code);

    return true;
}

/**@brief Register application shutdown handler with priority 0. */
NRF_PWR_MGMT_HANDLER_REGISTER(shutdown_handler, 0);


/**@brief Function for handling BSP events.
 */
static void bsp_evt_handler(bsp_event_t evt)
{
#if NRF_PWR_MGMT_CONFIG_STANDBY_TIMEOUT_ENABLED
    nrf_pwr_mgmt_feed();
    NRF_LOG_INFO("Power management fed");
#endif // NRF_PWR_MGMT_CONFIG_STANDBY_TIMEOUT_ENABLED

    switch (evt)
    {
        case BSP_EVENT_KEY_0:
            if (m_is_ready)
            {
                m_is_ready = false;
                NRF_LOG_INFO("System is not ready for shutdown");
            }
            else
            {
                m_is_ready = true;
                NRF_LOG_INFO("System is ready for shutdown");
            }
            if (m_sysoff_started && m_is_ready)
            {
                nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_CONTINUE);
            }
            break;

        case BSP_EVENT_SYSOFF:
            m_stay_in_sysoff = true;
            break;

        case BSP_EVENT_SLEEP:
            if (m_stay_in_sysoff)
            {
                nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_STAY_IN_SYSOFF);
            }
            else
            {
                nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_GOTO_SYSOFF);
            }
            break;

        case BSP_EVENT_RESET:
            nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_RESET);
            break;

        default:
            return; // no implementation needed
    }
}


/**@brief Function for initializing low-frequency clock.
 */
static void lfclk_config(void)
{
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}


/**@brief Function for initializing the BSP module.
 */
static void bsp_configuration()
{
    uint32_t err_code;

    err_code = bsp_init(BSP_INIT_BUTTONS, bsp_evt_handler);
    APP_ERROR_CHECK(err_code);

    err_code = bsp_event_to_button_action_assign(BTN_ID_SLEEP,
                                                 BSP_BUTTON_ACTION_LONG_PUSH,
                                                 BSP_EVENT_SYSOFF);
    APP_ERROR_CHECK(err_code);

    err_code = bsp_event_to_button_action_assign(BTN_ID_SLEEP,
                                                 BSP_BUTTON_ACTION_RELEASE,
                                                 BSP_EVENT_SLEEP);
    APP_ERROR_CHECK(err_code);
}


/**
 * @brief Function for application main entry.
 */
int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    nrf_delay_ms(100); // Wait for UART initialized

    NRF_LOG_INFO("Power Management example");

    lfclk_config();

    uint32_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

#if NRF_PWR_MGMT_CONFIG_USE_SCHEDULER
    APP_SCHED_INIT(APP_SCHED_MAX_EVENT_SIZE, APP_SCHED_QUEUE_SIZE);
#endif // NRF_PWR_MGMT_CONFIG_USE_SCHEDULER
    bsp_configuration();

    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_qspi_config_t config = NRF_DRV_QSPI_DEFAULT_CONFIG;
    err_code = nrf_drv_qspi_init(&config, qspi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    configure_memory(); // Put the QSPI flash into deep power down mode

	configure_st7789(); // Put the TFT into sleep mode

    nrf_delay_ms(100);

    while (true)
    {
#if NRF_PWR_MGMT_CONFIG_USE_SCHEDULER
        app_sched_execute();
#endif // NRF_PWR_MGMT_CONFIG_USE_SCHEDULER

        if (NRF_LOG_PROCESS() == false)
        {
            nrf_pwr_mgmt_run();
        }
    }
}
