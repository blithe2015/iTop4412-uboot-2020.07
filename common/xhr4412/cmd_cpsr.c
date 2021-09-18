/*
 * Copyright (c) 2011 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 */

#include <command.h>
#include <xhr4412/common.h>

int do_print_cpsr(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	struct e4412_gpio_regs* gpx1 = (void*)GPIO_GPX1;

	print_cpsr();

	printf("EXT_INT41_CON  = 0x%08lX\n",
		(*((volatile ulongx*)(EXT_INT41_CON))));

	printf("EXT_INT41_MASK = 0x%08lX\n",
		(*((volatile ulongx*)(EXT_INT41_MASK))));

	printf("EXT_INT41_PEND = 0x%08lX\n",
		(*((volatile ulongx*)(EXT_INT41_PEND))));

	printf ("x1->con = 0x%08lX x1->dat = 0x%08lX\n"
			"x1->pud = 0x%08lX x1->drv = 0x%08lX\n", 
			gpx1->con, gpx1->dat, gpx1->pud, gpx1->drv);

	printf(
		"ICDDCR         = 0x%08lX\n"  // 1
		"ICDISER1_CPU0  = 0x%08lX\n"  // 1<<25
		"ICDIPTR14_CPU0 = 0x%08lX\n"  // 1<<8
		"ICCICR_CPU0    = 0x%08lX\n"  // 1
		"ICCPMR_CPU0    = 0x%08lX\n", // 0xFF
		getl(ICDDCR),
		getl(ICDISER1_CPU0),
		getl(ICDIPTR14_CPU0),
		getl(ICCICR_CPU0),
		getl(ICCPMR_CPU0)
	);

	return 0;
}

U_BOOT_CMD(
	cpsr,	1,	1,	do_print_cpsr,
	"print cpsr register's value",
	""
);
