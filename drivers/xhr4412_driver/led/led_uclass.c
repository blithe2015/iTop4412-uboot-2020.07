
#include <xhr4412/led.h>

#define led_get_ops(dev)       ((struct led_ops_t *)(dev)->driver->ops)

int led_set_val(struct udevice *dev, led_state_t val)
{
	const struct led_ops_t * ops = led_get_ops(dev);

	if(ops && ops->set_val)
		return ops->set_val(dev, val);

	return LED_FAULT;
}

led_state_t led_get_val(struct udevice *dev)
{
	const struct led_ops_t * ops = led_get_ops(dev);

	if(ops && ops->get_val)
		return ops->get_val(dev);

	return LED_FAULT;
}

int xhr_led_uclass_init(void)
{
	int ret;
	struct uclass *uc;
	struct udevice *dev;

	ret = uclass_get(UCLASS_XHR_LED, &uc);
	if (ret)
		return ret;

	uclass_foreach_dev(dev, uc) {
		ret = device_probe(dev);
		if (ret)
			pr_err("%s - probe failed: %d\n", dev->name, ret);
	}

	return 0;
}

static int led_uclass_post_bind(struct udevice *dev)
{
	struct led_plat_data_t *plat = dev_get_uclass_platdata(dev);
	plat->name = "<led_uclass_drv>";
	return 0;
}

UCLASS_DRIVER(xhr_led) = {
	.id			= UCLASS_XHR_LED,
	.name		= "xhr_led",
	.post_bind	= led_uclass_post_bind,
	.per_device_platdata_auto_alloc_size = sizeof(struct led_plat_data_t),
};



