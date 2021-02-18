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

#include <m4naos/driver.h>
#include <m4naos/hardware.h>
#include <m4naos/kernel.h>
#include <m4naos/io.h>
#include <m4naos/uart.h>

extern early_initcall_t		__start_early__[];
extern early_initcall_t		__end_early__[];

extern core_initcall_t		__start_core__[];
extern core_initcall_t		__end_core__[];

extern postcore_initcall_t	__start_postcore__[];
extern postcore_initcall_t	__end_postcore__[];

extern subsys_initcall_t	__start_subsys__[];
extern subsys_initcall_t	__end_subsys__[];

extern module_initcall_t	__start_module__[];
extern module_initcall_t	__end_module__[];

extern late_initcall_t		__start_late__[];
extern late_initcall_t		__end_late__[];

#define kernel_init_level_helpers(level)				\
static void kernel_init_one_##level##_driver(level##_initcall_t fn)	\
{									\
	int ret;							\
									\
	ret = fn();							\
	if (ret)							\
		uart_puts("Failed to initialize driver\n");		\
}									\
									\
static void kernel_init_##level##_drivers(void)				\
{									\
	level##_initcall_t *fn;						\
									\
	for (fn = __start_##level##__;					\
	     fn < __end_##level##__; fn++)				\
		kernel_init_one_##level##_driver(*fn);			\
}

kernel_init_level_helpers(early)
kernel_init_level_helpers(core)
kernel_init_level_helpers(postcore)
kernel_init_level_helpers(subsys)
kernel_init_level_helpers(module)
kernel_init_level_helpers(late)

static void kernel_init_drivers(void)
{
	kernel_init_early_drivers();
	kernel_init_core_drivers();
	kernel_init_postcore_drivers();
	kernel_init_subsys_drivers();
	kernel_init_module_drivers();
	kernel_init_late_drivers();

	drivers_start();
}

void kernel_init(void)
{
	kernel_init_drivers();
}
