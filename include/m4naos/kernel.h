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

#ifndef __M4NAOS_KERNEL_H
#define __M4NAOS_KERNEL_H

#include <sys/cdefs.h>

#include <m4naos/types.h>
#include <m4naos/version.h>

/*
 * container - cast a member of a structure out to the containing structure
 * @p: the pointer to the member.
 * @t: the type of the container struct this is embedded in.
 * @m: the name of the member within the struct.
 */
#define container(p, t, m) ({					\
	const typeof(((type *)0)->m ) *____p = (p);		\
	(type *)((char *)____p - offsetof((t), (m)) );})

#define prefetch(x) __builtin_prefetch(x)

#define __weak		__attribute__ ((weak))
#define __alias(name)	__attribute__ ((alias(#name)))
#define __vectors	__section(".vectors")
#define __iomem
#define __force

#define __early_initcall	__section(".initcall0")
#define __core_initcall		__section(".initcall1")
#define __postcore_initcall	__section(".initcall2")
#define __subsys_initcall	__section(".initcall3")
#define __module_initcall	__section(".initcall4")
#define __late_initcall		__section(".initcall5")

#define __ccm			__section(".ccm")

typedef int (*early_initcall_t)(void);
typedef int (*core_initcall_t)(void);
typedef int (*postcore_initcall_t)(void);
typedef int (*subsys_initcall_t)(void);
typedef int (*module_initcall_t)(void);
typedef int (*late_initcall_t)(void);

#define level_init(level, fn)					\
	static level##_initcall_t __##level##_initcall_##fn	\
	__used __##level##_initcall = fn

#define level_driver_register(level, __drv)			\
	static int __drv##_init(void)				\
	{							\
		return register_driver(&__drv);			\
	}							\
	level##_init(__drv##init)

#define early_init(fn)		level_init(early, fn)
#define core_init(fn)		level_init(core, fn)
#define postcore_init(fn)	level_init(postcore, fn)
#define subsys_init(fn)		level_init(subsys, fn)
#define module_init(fn)		level_init(module, fn)
#define late_init(fn)		level_init(late, fn)

#define early_driver_register(__drv)				\
	level_driver_register(early, __drv)

#define core_driver_register(__drv)				\
	level_driver_register(core, __drv)

#define postcore_driver_register(__drv)				\
	level_driver_register(postcore, __drv)

#define subsys_driver_register(__drv)				\
	level_driver_register(subsys, __drv)

#define module_driver_register(__drv)				\
	level_driver_register(module, __drv)

#define late_driver_register(__drv)				\
	level_driver_register(late, __drv)

#define false	0
#define true	!false

#define div_round_up(n, d)	(((n) + (d) - 1) / (d))
#define ARRAY_SIZE(arr)		((sizeof((arr)))/(sizeof((arr)[0])))

#define NSECS_IN_SEC		1000000000

void system_timer_init(void);
void kernel_init(void);

/* types */

typedef unsigned char	__u8;
typedef unsigned short	__u16;
typedef unsigned long	__u32;

typedef signed char	__s8;
typedef signed short	__s16;
typedef signed long	__s32;

typedef __u32		phys_addr_t;

#endif /* __M4NAOS_KERNEL_H */
