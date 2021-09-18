#ifndef _EXYNOS_4412_REGS_H_
#define _EXYNOS_4412_REGS_H_

#include <asm/proc-armv/ptrace.h>
#include <asm/ptrace.h>
#include <asm/u-boot-arm.h>

typedef unsigned long ulongx;

#define setl(reg, val) (*((ulongx*)(reg)) = (val))
#define getl(reg)      (*((ulongx*)(reg)))
#define orrl(reg, val) (*((ulongx*)(reg)) |= (val))
#define bicl(reg, val) (*((ulongx*)(reg)) &= ~(val))
#define xorl(reg, val) (*((ulongx*)(reg)) ^= (val))
#define frcl(reg, val, mask) do{bicl(reg, mask); orrl(reg, val);}while(0)

static inline void enable_arm_irq(void)
{
	ulongx i;
	__asm__ __volatile__ ( 
		"mrs %0, cpsr\n\t"
		"bic %0, %0, #0x80\n\t"
		"msr cpsr, %0\n\t": "=r" (i) :);
}

static inline void disable_arm_irq(void)
{
	ulongx i;
	__asm__ __volatile__ ( 
		"mrs %0, cpsr\n\t"
		"orr %0, %0, #0x80\n\t"
		"msr cpsr, %0\n\t": "=r" (i) :);
}

static inline void print_cpsr(void)
{
	ulongx cpsr_reg;
	__asm__ __volatile__ ( 
		"mrs %0, cpsr\n\t": "=r" (cpsr_reg) :);
	printf("\n>> cpsr = 0x%08lX\n", cpsr_reg);
}

#define ARM_MOD_USR 0x10
#define ARM_MOD_SVC 0X13

#ifdef CONFIG_UART_IRQ_ENABLE
static inline void spin_lock_xhr(void)
{
	ulongx cpsr = 0;
	ulongx mode;
	__asm__ __volatile__ ( 
		"mrs %0, cpsr\n\t"
		"and %1, %0, #0x1F\n\t"
		: "+r" (cpsr), "=r" (mode)
		:);
	if(mode == ARM_MOD_SVC || mode == ARM_MOD_USR)
	{
		__asm__ __volatile__ ( 
			"orr %0, %0, #0x80\n\t"
			"msr cpsr, %0\n\t" : : "r" (cpsr));
	}
}

static inline void spin_unlock_xhr(void)
{
	ulongx cpsr = 0;
	ulongx mode;
	__asm__ __volatile__ ( 
		"mrs %0, cpsr\n\t"
		"and %1, %0, #0x1F\n\t"
		: "+r" (cpsr), "=r" (mode)
		:);
	if(mode == ARM_MOD_SVC || mode == ARM_MOD_USR)
	{
		__asm__ __volatile__ ( 
			"bic %0, %0, #0x80\n\t"
			"msr cpsr, %0\n\t" : : "r" (cpsr));
	}
}
#endif

// GPIO DEFINE
struct e4412_gpio_regs
{
    ulongx con;
    ulongx dat;
    ulongx pud;
    ulongx drv;
};

#define GPIO_GPX0 0x11000C00
#define GPIO_GPX1 0x11000C20
#define GPIO_GPX2 0x11000C40
#define GPIO_GPX3 0x11000C60

#define GPIO_GPL2 0x11000100
#define GPIO_GPK1 0x11000060

#define GPIO_GPA1 0x11400020
// GPIO DEFINE

// INTERRUPT
#define EXT_INT41_CON       0x11000E04
#define EXT_INT41_FLTCON0   0x11000E88
#define EXT_INT41_FLTCON1   0x11000E8C
#define EXT_INT41_MASK      0x11000F04
#define EXT_INT41_PEND      0x11000F44
// INTERRUPT


// GIC

#define ICDDCR              0x10490000
#define ICDISER0_CPU0       0x10490100
#define ICDISER1_CPU0       0x10490104
#define ICDISER2_CPU0       0x10490108
#define ICDISER3_CPU0       0x1049010C
#define ICDISER4_CPU0       0x10490110
#define ICDISER0_CPU1       0x10494100
#define ICDISER0_CPU2       0x10498100
#define ICDISER0_CPU3       0x1049C100
#define ICDIPTR14_CPU0      0x10490838
#define ICDIPTR21_CPU0      0x10490854
#define ICCICR_CPU0         0x10480000
#define ICCPMR_CPU0         0x10480004

#define ICCIAR_CPU0         0x1048000C
#define ICCEOIR_CPU0        0x10480010
// GIC

#if 1
static inline void led_xor(void)
{
	(*((unsigned long*)(GPIO_GPL2 + 4)) ^= (1)); // led
}
#endif
static inline void led_on(int bit)
{
	if(bit & 1)
	{
		(*((unsigned long*)(GPIO_GPL2 + 0)) = (1)); // led
		(*((unsigned long*)(GPIO_GPL2 + 4)) = (1)); // led
	}

	if(bit & 2)
	{
		(*((unsigned long*)(GPIO_GPK1 + 8)) = (0)); // led
		(*((unsigned long*)(GPIO_GPK1 + 0)) = (0x10)); // led
		(*((unsigned long*)(GPIO_GPK1 + 4)) = (2)); // led
	}
	
	//while(1);
}


#endif
