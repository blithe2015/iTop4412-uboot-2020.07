#ifndef _ITOP4412_INTERNAL_H_
#define _ITOP4412_INTERNAL_H_


//======== global data ==========================
#define __ITOP_FLAG_UART_IRQ_ENABLED (1 << 0)
#define __ITOP_FLAG_BOARD_R          (1 << 1)

DECLARE_GLOBAL_DATA_PTR;

#define __test_itop_flag(flag) (gd->itop_flag & (flag))

#define __set_bit_itop_flag(flag) (gd->itop_flag |= (flag))

#ifdef CONFIG_UART_IRQ_ENABLE
#define is_uart_irq_enabled() __test_itop_flag(__ITOP_FLAG_UART_IRQ_ENABLED)
#endif

#define is_board_r() __test_itop_flag(__ITOP_FLAG_BOARD_R)

//======== end of global data ===================
#endif