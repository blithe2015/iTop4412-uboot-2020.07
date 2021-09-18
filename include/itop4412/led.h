#ifndef _ITOP4412_DRV_LED_H
#define _ITOP4412_DRV_LED_H
#include <common.h>
#include <dm.h>
#include <errno.h>
#include <dm/root.h>
#include <dm/uclass-internal.h>
#include <dm/device-internal.h>
#include <itop4412/common.h>

typedef unsigned long led_state_t;

// internal ================================================
struct led_ops_t {
	int (*set_val)(struct udevice *dev, led_state_t val);
	led_state_t (*get_val)(struct udevice *dev);
};

struct led_plat_data_t {
	const char * name;
};

int itop_led_uclass_init(void);

// external ================================================
#define LED_STD_ON  (1)
#define LED_STD_OFF (0)
#define LED_FAULT   (-1)
// see led_state_t

led_state_t led_get_val(struct udevice *dev);
int led_set_val(struct udevice *dev, led_state_t val);


#endif 
