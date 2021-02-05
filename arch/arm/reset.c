/*
 * This file is part of M4naos
 *
 * M4naos is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * M4naos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with M4naos.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <m4naos/hardware.h>
#include <m4naos/io.h>
#include <m4naos/kernel.h>
#include <m4naos/string.h>
#include <m4naos/sys-tick.h>

extern u32 __start_vectors__;
extern u32 __end_vectors__;

extern u32 __start_stack__;
extern u32 __end_stack__;

extern u32 __start_text__;
extern u32 __end_text__;

extern u32 __start_data__;
extern u32 __end_data__;

extern u32 __start_bss__;
extern u32 __end_bss__;

/* main is called from within reset_handler */
extern int main(void);

void reset_handler(void);
void nmi_handler(void) __weak(default_handler);
void hard_fault_handler(void) __weak(default_handler);
void service_call_handler(void) __weak(default_handler);
void pending_service_handler(void) __weak(default_handler);
void sys_tick_handler(void);
void default_irq_handler(void);

#define VTABLE_STACK_POINTER		0
#define VTABLE_RESET_HANDLER		1
#define VTABLE_NMI_HANDLER		2
#define VTABLE_HARDFAULT_HANDLER	3
#define VTABLE_MMU_FAULT		4
#define VTABLE_BUS_FAULT		5
#define VTABLE_USAGE_FAULT		6
/* Reserved 7 - 10 */
#define VTABLE_SVC			11
/* Reserved 12 - 13 */
#define VTABLE_PENDSV			14
#define VTABLE_SYSTICK			15
#define VTABLE_IRQ0			(16+0)
#define VTABLE_IRQ1			(16+1)
#define VTABLE_IRQ2			(16+2)
#define VTABLE_IRQ3			(16+3)
#define VTABLE_IRQ4			(16+4)
#define VTABLE_IRQ5			(16+5)
#define VTABLE_IRQ6			(16+6)
#define VTABLE_IRQ7			(16+7)
#define VTABLE_IRQ8			(16+8)
#define VTABLE_IRQ9			(16+9)
#define VTABLE_IRQ10			(16+10)
#define VTABLE_IRQ11			(16+11)
#define VTABLE_IRQ12			(16+12)
#define VTABLE_IRQ13			(16+13)
#define VTABLE_IRQ14			(16+14)
#define VTABLE_IRQ15			(16+15)

void *vector_table[] __vectors __used = {
	&__end_stack__,
	reset_handler,
	nmi_handler,
	hard_fault_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	NULL,
	NULL,
	NULL,
	NULL,
	service_call_handler,
	NULL,
	NULL,
	pending_service_handler,
	sys_tick_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
	default_irq_handler,
};

static void scb_init(void)
{
	writel(SCB_BASE, SCB_VTOR, SCB_VTOR_TBLOFF(__start_vectors__));
}

void reset_handler(void)
{
	u8 *src;
	u8 *dst;
	u8 len;

	/* copy data from flash to SRAM */
	src = (u8 *) &__end_text__;
	dst = (u8 *) &__start_data__;
	len = &__end_data__ - &__start_data__;
	memcpy(dst, src, len);

	/* zero bss */
	src = (u8 *) &__start_bss__;
	len = &__end_bss__ - &__start_bss__;
	memset(src, 0x00, len);

	scb_init();
	main();
}

void default_handler(void)
{
	while (true)
		__wfi();
}

void default_irq_handler(void)
{
	/* must clear interrupt */
	default_handler();
}
