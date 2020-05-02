/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>

#include <drivers/pwm.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

#if defined(DT_ALIAS_PWM_LED3_PWMS_CONTROLLER) && defined(DT_ALIAS_PWM_LED3_PWMS_CHANNEL)
/* get the defines from dt (based on alias 'pwm-led3') */
#define BL_PWM_DRIVER	DT_ALIAS_PWM_LED3_PWMS_CONTROLLER
#define BL_PWM_CHANNEL	DT_ALIAS_PWM_LED3_PWMS_CHANNEL
#ifdef DT_ALIAS_PWM_LED3_PWMS_FLAGS
#define BL_PWM_FLAGS	DT_ALIAS_PWM_LED3_PWMS_FLAGS
#else
#define BL_PWM_FLAGS	0
#endif
#else
#error "Choose supported PWM driver"
#endif

/*
 * 50 is flicker fusion threshold. Modulated light will be perceived
 * as steady by our eyes when blinking rate is at least 50.
 */
#define PERIOD (USEC_PER_SEC / 50U)

void main(void)
{
	u32_t count = 0U;
	char count_str[11] = {0};
    struct device *backlight_dev;
	struct device *display_dev;
	lv_obj_t *hello_world_label;
	lv_obj_t *count_label;

	backlight_dev = device_get_binding(BL_PWM_DRIVER);
	if (!backlight_dev) {
		LOG_ERR("pwm backlight not found. Aborting test.");
		return;
	}

    if (pwm_pin_set_usec(backlight_dev, BL_PWM_CHANNEL,
                PERIOD, PERIOD, BL_PWM_FLAGS)) {
        LOG_ERR("pwm backlight set fails.");
        return;
    }

	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}

	if (IS_ENABLED(CONFIG_LVGL_POINTER_KSCAN)) {
		lv_obj_t *hello_world_button;

		hello_world_button = lv_btn_create(lv_scr_act(), NULL);
		lv_obj_align(hello_world_button, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_btn_set_fit(hello_world_button, LV_FIT_TIGHT);
		hello_world_label = lv_label_create(hello_world_button, NULL);
	} else {
		hello_world_label = lv_label_create(lv_scr_act(), NULL);
	}

	lv_label_set_text(hello_world_label, "Hello world!");
	lv_obj_align(hello_world_label, NULL, LV_ALIGN_CENTER, 0, 0);

	count_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

	lv_task_handler();
	display_blanking_off(display_dev);

	while (1) {
		if ((count % 100) == 0U) {
			sprintf(count_str, "%d", count/100U);
			lv_label_set_text(count_label, count_str);
		}
		lv_task_handler();
		k_sleep(K_MSEC(10));
		++count;
	}
}
