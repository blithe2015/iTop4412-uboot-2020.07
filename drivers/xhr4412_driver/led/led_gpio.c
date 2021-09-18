#include <xhr4412/led.h>

#define dprint(fmt, args...) //printf("[%s][%d] " fmt, __func__, __LINE__, ##args)

struct led_gpio_priv_t {
	struct e4412_gpio_regs * regs;
	unsigned long pos;
	const char * name;
};

static int led_gpio_set_val(struct udevice *dev, led_state_t val)
{
	struct led_gpio_priv_t *priv = dev_get_priv(dev);
	if(val)
		priv->regs->dat |= priv->pos;
	else
		priv->regs->dat &= ~priv->pos;
	return 0;
}

static led_state_t led_gpio_get_val(struct udevice *dev)
{
	struct led_gpio_priv_t *priv = dev_get_priv(dev);
	if(priv->regs->dat & priv->pos)
		return LED_STD_ON;
	return LED_STD_OFF;
}

static const struct led_ops_t led_gpio_ops = {
	.set_val = led_gpio_set_val,
	.get_val = led_gpio_get_val,
};

static int led_gpio_probe(struct udevice *dev)
{
	__maybe_unused struct led_plat_data_t *plat = dev_get_uclass_platdata(dev);
	struct led_gpio_priv_t *priv = dev_get_priv(dev);
	int ret;
	u32 tmp;

	priv->name = ofnode_read_string(dev->node, "led_name");
	ret = ofnode_read_u32(dev->node, "reg_addr", &tmp);
	if(ret) return ret;
	priv->regs = (void*)tmp;
	ret = ofnode_read_u32(dev->node, "position", &tmp);
	if(ret) return ret;
	priv->pos = 1 << tmp;
	dprint("uclass=%s led=%s reg= %p pos= %d\n",
		plat->name, priv->name, priv->regs, tmp);

	priv->regs->con &= ~((0xF) << (tmp << 2));
	priv->regs->con |= 1 << (tmp << 2);
	priv->regs->pud &= ~((0x3) << (tmp << 1));

	led_gpio_set_val(dev, LED_STD_ON);

	return 0;
}

static int led_gpio_remove(struct udevice *dev)
{
	__maybe_unused struct led_plat_data_t *plat = dev_get_uclass_platdata(dev);
	__maybe_unused struct led_gpio_priv_t *priv = dev_get_priv(dev);
	dprint("uclass=%s led=%s\n", plat->name, priv->name);
	return 0;
}

static const struct udevice_id led_gpio_ids[] = {
	{ .compatible = "xhr-led-gpio" },
	{ }
};

U_BOOT_DRIVER(led_gpio) = {
	.name		= "led_gpio_xhr",
	.id			= UCLASS_XHR_LED,
	.of_match	= led_gpio_ids,
	.ops		= &led_gpio_ops,
	.probe		= led_gpio_probe,
	.remove		= led_gpio_remove,
	.priv_auto_alloc_size = sizeof(struct led_gpio_priv_t),
};

