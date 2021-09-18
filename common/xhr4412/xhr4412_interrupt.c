#include <command.h>
#include <xhr4412/common.h>

#define MAX_IRQ_NUMBER (160)

struct irq_entry
{
	irq_cb_t callback;
	void *   data;
	ulongx   count;
};

static struct irq_entry irq_list[MAX_IRQ_NUMBER];

int register_irq(int irq, irq_cb_t cb, void * data)
{
	if(irq < 0 || irq >= MAX_IRQ_NUMBER)
		return -EFAULT;

	if(cb == NULL)
		return -EFAULT;

	if(irq_list[irq].callback != NULL)
		return -EFAULT;

	irq_list[irq].callback = cb;
	irq_list[irq].data = data;

	return 0;
}

int xhr4412_do_irq(struct pt_regs *pt_regs)
{
	static ulongx irq_count = 0;
	static ulongx irq_null_cb_count = 0;
	struct irq_entry * entry;
	int cpu = getl(ICCIAR_CPU0);
	int irq = cpu & 0x3FF;
	int ret;
	cpu &= ~0x3FF;
	//printf("\ncpsr = 0x%08lX icciar = 0x%08lX\n", pt_regs->ARM_cpsr, irq);
	irq_count++;

	if(irq < MAX_IRQ_NUMBER)
	{
		entry = &irq_list[irq];

		if(entry->callback != NULL)
		{
			entry->count++;
			ret = entry->callback(irq, entry->data);
		}
		else
		{
			printf("\nnull irq_cb, irq_count = (%lu/%lu) cpu = %d irq = %d\n",
				++irq_null_cb_count, irq_count, cpu, irq);
			ret = -ENOTTY;
		}
	}
	else
	{
		printf("\nirq num is invalid, cpu = %d irq = %d\n", cpu, irq);
		ret = -EFAULT;
	}

	setl(ICCEOIR_CPU0, cpu | irq);
	return ret;
}

int do_show_irqlist(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	int i;
	printf("\n");
	for(i = 0; i < MAX_IRQ_NUMBER; i++)
	{
		if(irq_list[i].callback != NULL)
		{
			printf("cb = %p dat = %p irq = %d count = %ld\n",
				irq_list[i].callback, irq_list[i].data, i,
				irq_list[i].count);
		}
	}
#ifdef CONFIG_UART_IRQ_ENABLE
	extern ulongx rxcount, txcount;
	printf("txcount = %ld rxcount = %ld\n", txcount, rxcount);
#endif
	return 0;
}

U_BOOT_CMD(
	irqlist,	1,	1,	do_show_irqlist,
	"show irq list",
	""
);

