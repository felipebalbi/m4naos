/* SPDX-License-Identifier: GPL-3.0-or-later */

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
#include <m4naos/rcc.h>

#include "reset.h"

extern u32 __end_stack__;

extern u32 __load_ccm__;
extern u32 __start_ccm__;
extern u32 __end_ccm__;

extern u32 __load_data__;
extern u32 __start_data__;
extern u32 __end_data__;

extern u32 __bss_start__;
extern u32 __bss_end__;

extern void __libc_init_array(void);

void reset_handler(void)
{
	unsigned int *src;
	unsigned int *dst;

	/* copy data from flash to SRAM */
	for (src = &__load_data__, dst = &__start_data__;
		dst < &__end_data__; src++, dst++)
		*dst = *src;

	/* zero bss */
	while (dst < &__bss_end__)
		*dst++ = 0;

	__libc_init_array();
	machine_init();
	main();
}

void default_handler(void)
{
	while (true)
		__wfi();
}

static void *vector_table[] __vectors __used = {
	[VTABLE_STACK_POINTER]	= &__end_stack__,
	[VTABLE_RESET]		= reset_handler,
	[VTABLE_NMI]		= nmi_handler,
	[VTABLE_HARDFAULT]	= hard_fault_handler,
	[VTABLE_MMU_FAULT]	= mmu_fault_handler,
	[VTABLE_BUS_FAULT]	= bus_fault_handler,
	[VTABLE_USAGE_FAULT]	= usage_fault_handler,
	NULL,
	NULL,
	NULL,
	NULL,
	[VTABLE_SVC]		= service_call_handler,
	[VTABLE_DBGMON]		= debug_monitor_handler,
	NULL,
	[VTABLE_PENDSV]		= pending_service_handler,
	[VTABLE_SYSTICK]	= sys_tick_handler,
	[VTABLE_IRQ0]		= default_handler,
	[VTABLE_IRQ1]		= default_handler,
	[VTABLE_IRQ2]		= default_handler,
	[VTABLE_IRQ3]		= default_handler,
	[VTABLE_IRQ4]		= default_handler,
	[VTABLE_IRQ5]		= default_handler,
	[VTABLE_IRQ6]		= default_handler,
	[VTABLE_IRQ7]		= default_handler,
	[VTABLE_IRQ8]		= default_handler,
	[VTABLE_IRQ9]		= default_handler,
	[VTABLE_IRQ10]		= default_handler,
	[VTABLE_IRQ11]		= default_handler,
	[VTABLE_IRQ12]		= default_handler,
	[VTABLE_IRQ13]		= default_handler,
	[VTABLE_IRQ14]		= default_handler,
	[VTABLE_IRQ15]		= default_handler,
	[VTABLE_IRQ16]		= default_handler,
	[VTABLE_IRQ17]		= default_handler,
	[VTABLE_IRQ18]		= default_handler,
	[VTABLE_IRQ19]		= default_handler,
	[VTABLE_IRQ20]		= default_handler,
	[VTABLE_IRQ21]		= default_handler,
	[VTABLE_IRQ22]		= default_handler,
	[VTABLE_IRQ23]		= default_handler,
	[VTABLE_IRQ24]		= default_handler,
	[VTABLE_IRQ25]		= default_handler,
	[VTABLE_IRQ26]		= default_handler,
	[VTABLE_IRQ27]		= default_handler,
	[VTABLE_IRQ28]		= default_handler,
	[VTABLE_IRQ29]		= default_handler,
	[VTABLE_IRQ30]		= default_handler,
	[VTABLE_IRQ31]		= default_handler,
	[VTABLE_IRQ32]		= default_handler,
	[VTABLE_IRQ33]		= default_handler,
	[VTABLE_IRQ34]		= default_handler,
	[VTABLE_IRQ35]		= default_handler,
	[VTABLE_IRQ36]		= default_handler,
	[VTABLE_IRQ37]		= default_handler,
	[VTABLE_IRQ38]		= default_handler,
	[VTABLE_IRQ39]		= default_handler,
	[VTABLE_IRQ40]		= default_handler,
	[VTABLE_IRQ41]		= default_handler,
	[VTABLE_IRQ42]		= default_handler,
	[VTABLE_IRQ43]		= default_handler,
	[VTABLE_IRQ44]		= default_handler,
	[VTABLE_IRQ45]		= default_handler,
	[VTABLE_IRQ46]		= default_handler,
	[VTABLE_IRQ47]		= default_handler,
	[VTABLE_IRQ48]		= default_handler,
	[VTABLE_IRQ49]		= default_handler,
	[VTABLE_IRQ50]		= default_handler,
	[VTABLE_IRQ51]		= default_handler,
	[VTABLE_IRQ52]		= default_handler,
	[VTABLE_IRQ53]		= default_handler,
	[VTABLE_IRQ54]		= default_handler,
	[VTABLE_IRQ55]		= default_handler,
	[VTABLE_IRQ56]		= default_handler,
	[VTABLE_IRQ57]		= default_handler,
	[VTABLE_IRQ58]		= default_handler,
	[VTABLE_IRQ59]		= default_handler,
	[VTABLE_IRQ60]		= default_handler,
	[VTABLE_IRQ61]		= default_handler,
	[VTABLE_IRQ62]		= default_handler,
	[VTABLE_IRQ63]		= default_handler,
	[VTABLE_IRQ64]		= default_handler,
	[VTABLE_IRQ65]		= default_handler,
	[VTABLE_IRQ66]		= default_handler,
	[VTABLE_IRQ67]		= default_handler,
	[VTABLE_IRQ68]		= default_handler,
	[VTABLE_IRQ69]		= default_handler,
	[VTABLE_IRQ70]		= default_handler,
	[VTABLE_IRQ71]		= default_handler,
	[VTABLE_IRQ72]		= default_handler,
	[VTABLE_IRQ73]		= default_handler,
	[VTABLE_IRQ74]		= default_handler,
	[VTABLE_IRQ75]		= default_handler,
	[VTABLE_IRQ76]		= default_handler,
	[VTABLE_IRQ77]		= default_handler,
	[VTABLE_IRQ78]		= default_handler,
	[VTABLE_IRQ79]		= default_handler,
	[VTABLE_IRQ80]		= default_handler,
	[VTABLE_IRQ81]		= default_handler,
};
