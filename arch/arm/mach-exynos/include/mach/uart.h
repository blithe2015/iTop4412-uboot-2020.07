/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2009 Samsung Electronics
 * Minkyu Kang <mk7.kang@samsung.com>
 * Heungjun Kim <riverful.kim@samsung.com>
 */

#ifndef __ASM_ARCH_UART_H_
#define __ASM_ARCH_UART_H_

#ifndef __ASSEMBLY__
/* baudrate rest value */
union br_rest {
	unsigned short	slot;		/* udivslot */
	unsigned char	value;		/* ufracval */
};
#if !defined(CONFIG_XHR4412) && !defined(CONFIG_ITOP4412)
struct s5p_uart {
	unsigned int	ulcon;
	unsigned int	ucon;
	unsigned int	ufcon;
	unsigned int	umcon;
	unsigned int	utrstat;
	unsigned int	uerstat;
	unsigned int	ufstat;
	unsigned int	umstat;
	unsigned char	utxh;
	unsigned char	res1[3];
	unsigned char	urxh;
	unsigned char	res2[3];
	unsigned int	ubrdiv;
	union br_rest	rest;
	unsigned char	res3[0xffd0];
};
#else
struct s5p_uart {
	unsigned int	ulcon;		//  0
	unsigned int	ucon;		//  4
	unsigned int	ufcon;		//  8
	unsigned int	umcon;		//  C
	unsigned int	utrstat;	// 10
	unsigned int	uerstat;	// 14
	unsigned int	ufstat;		// 18
	unsigned int	umstat;		// 1C
	unsigned char	utxh;		// 20
	unsigned char	res1[3];
	unsigned char	urxh;		// 24
	unsigned char	res2[3];
	unsigned int	ubrdiv;		// 28
	//unsigned int	ufracval;	// 2C
	union br_rest	rest;		// 2C
	unsigned int	uintp;		// 30 pending
	unsigned int	uintsp;		// 34
	unsigned int	uintm;		// 38 mask
};
#endif
static inline int s5p_uart_divslot(void)
{
	return 0;
}

#endif	/* __ASSEMBLY__ */

#endif
