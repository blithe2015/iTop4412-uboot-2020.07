#include <xhr4412/common.h>

#ifndef CONFIG_XHR_DRV_LED_GPIO
static void boot_init_test_led(void)
{
	struct e4412_gpio_regs * gpl2 = (void*)GPIO_GPL2;
	gpl2->con = 1;
	gpl2->dat = 0;
}
#endif

static int home_btn_irq(int irq, void * data)
{
	static ulongx home_btn_irq_count = 0;
	led_xor();
	orrl(EXT_INT41_PEND, (1 << 1)); // clear interrupt
	printf("\n home_btn_irq_count = %lu\n", ++home_btn_irq_count);
	return 0;
}

static void enable_home_btn_irq(void)
{
	struct e4412_gpio_regs* gpx = (void*)GPIO_GPX1;
	gpx->pud = 0; // GPX1_1 disable pull up & down
	gpx->con = 0xF << 4; // WAKEUP_INT1[1] --- EXT_INT41[1]
	setl(EXT_INT41_CON, 2 << 4);
	bicl(EXT_INT41_MASK, (1 << 1));
	setl(ICDDCR, 1);
	setl(ICDISER1_CPU0, (1 << 25));
	setl(ICDIPTR14_CPU0, (1 << 8));
	setl(ICCICR_CPU0, 1);
	setl(ICCPMR_CPU0, 0xFF);
	register_irq(57, home_btn_irq, NULL);
}

int xhr4412_board_init(void)
{
	__set_bit_xhr_flag(__XHR_FLAG_BOARD_R);
	//printf("-- board_r --\n");
#ifndef CONFIG_XHR_DRV_LED_GPIO
	boot_init_test_led();
#endif
	enable_home_btn_irq();
	enable_arm_irq();
	return 0;
}
