#ifndef _XHR4412_INTERNAL_H_
#define _XHR4412_INTERNAL_H_


//======== global data ==========================
#define __XHR_FLAG_UART_IRQ_ENABLED (1 << 0)
#define __XHR_FLAG_BOARD_R          (1 << 1)

DECLARE_GLOBAL_DATA_PTR;

#define __test_xhr_flag(flag) (gd->xhr_flag & (flag))

#define __set_bit_xhr_flag(flag) (gd->xhr_flag |= (flag))

#ifdef CONFIG_UART_IRQ_ENABLE
#define is_uart_irq_enabled() __test_xhr_flag(__XHR_FLAG_UART_IRQ_ENABLED)
#endif

#define is_board_r() __test_xhr_flag(__XHR_FLAG_BOARD_R)

//======== end of global data ===================
#endif