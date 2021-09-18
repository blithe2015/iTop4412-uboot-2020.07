#ifndef _ITOP4412_COMMON_H_
#define _ITOP4412_COMMON_H_

#include <common.h>
#include <itop4412/led.h>
#include "itop4412_internal.h"
#include "exynos_4412_regs.h"
#include "partition.h"

#define arraysize(arr) (sizeof(arr)/sizeof(arr[0]))

//========= API for internal ==================================
typedef int (*irq_cb_t) (int irq, void * data);
int register_irq(int irq, irq_cb_t cb, void * data);


//========= API for extern ====================================
int itop4412_do_irq(struct pt_regs *pt_regs);
int itop4412_board_init(void);
int itop4412_partition_init(void);
#endif