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


#define PWM_BACKLIGHT_NODE	DT_ALIAS(pwm_led3)

/*
 * Devicetree helper macro which gets the 'flags' cell from the node's
 * pwms property, or returns 0 if the property has no 'flags' cell.
 */

#define FLAGS_OR_ZERO(node)						\
	COND_CODE_1(DT_PHA_HAS_CELL(node, pwms, flags),		\
		    (DT_PWMS_FLAGS(node)),				\
		    (0))

#if DT_NODE_HAS_STATUS(PWM_BACKLIGHT_NODE, okay)
#define PWM_BACKLIGHT_LABEL	    DT_PWMS_LABEL(PWM_BACKLIGHT_NODE)
#define PWM_BACKLIGHT_CHANNEL	DT_PWMS_CHANNEL(PWM_BACKLIGHT_NODE)
#define PWM_BACKLIGHT_FLAGS	    FLAGS_OR_ZERO(PWM_BACKLIGHT_NODE)
#else
#error "Unsupported board: pwm-led3 devicetree alias is not defined"
#define PWM_BACKLIGHT_LABEL	    ""
#define PWM_BACKLIGHT_CHANNEL	0
#define PWM_BACKLIGHT_FLAGS	    0
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

	backlight_dev = device_get_binding(PWM_BACKLIGHT_LABEL);
	if (!backlight_dev) {
		LOG_ERR("pwm backlight not found. Aborting test.");
		return;
	}

    if (pwm_pin_set_usec(backlight_dev, PWM_BACKLIGHT_CHANNEL,
                PERIOD, PERIOD, PWM_BACKLIGHT_FLAGS)) {
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
