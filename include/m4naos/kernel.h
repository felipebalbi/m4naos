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

#include <m4naos/types.h>
#include <m4naos/version.h>

#define __used		__attribute__ ((used))
#define __packed	__attribute__ ((packed))
#define __weak(name)	__attribute__ ((weak, alias((#name))))
#define __section(name)	__attribute__ ((section(#name)))
#define __vectors	__section(.vectors)

#define NULL	((void *)(0))

#define false	0
#define true	!false

#define div_round_up(n, d)	(((n) + (d) - 1) / (d))

#define NSECS_IN_SEC		1000000000

void system_timer_init(void);

/* types */

typedef unsigned char	__u8;
typedef unsigned short	__u16;
typedef unsigned long	__u32;

typedef signed char	__s8;
typedef signed short	__s16;
typedef signed long	__s32;

#endif /* __M4NAOS_KERNEL_H */
