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

#ifndef __M4NAOS_ASM_H
#define __M4NAOS_ASM_H

#ifdef __ASSEMBLY__

#define NL	;

#define PROC(name)			\
	.globl name		NL	\
	.align 4		NL	\
	name:

#define ENDPROC(name)			\
	.type name, %function	NL	\
	.size name, .-name

#else /* __ASSEMBLY__ */

#include <m4naos/kernel.h>
#include <m4naos/hardware.h>

static inline __always_inline void preempt_enable(void)
{
	asm("cpsie f");
}

static inline __always_inline void preempt_disable(void)
{
	asm("cpsid f");
}

static inline __always_inline void local_irq_enable(void)
{
	asm("cpsie i");
}

static inline __always_inline void local_irq_disable(void)
{
	asm("cpsid i");
}

static inline __always_inline void __sev(void)
{
	asm("sev");
}

static inline __always_inline void __svc(void)
{
	asm("svc #0");
}

static inline __always_inline void __wfi(void)
{
	asm("wfi");
}

static inline __always_inline void __wfe(void)
{
	asm("wfe");
}

static inline __always_inline void __dsb(void)
{
	asm("dsb");
}

static inline __always_inline void __dmb(void)
{
	asm("dmb");
}

static inline __always_inline void __isb(void)
{
	asm("isb");
}

static inline __always_inline u32 __get_msp(void)
{
	u32 reg;

	asm("mrs %0, msp" : "=r" (reg));

	return reg;
}

static inline __always_inline void __set_msp(u32 value)
{
	asm("msr msp, %0" : : "r" (value));
}

static inline __always_inline u32 __get_psp(void)
{
	u32 reg;

	asm("mrs %0, psp" : "=r" (reg));

	return reg;
}

static inline __always_inline void __set_psp(u32 value)
{
	asm ("msr psp, %0" : : "r" (value));
}

static inline __always_inline u32 __get_psr(void)
{
	u32 flags;

	asm("mrs %0, psr" : "=r" (flags));

	return flags;
}

static inline __always_inline void __set_psr(u32 flags)
{
	asm("msr psr, %0" : : "r" (flags));
}

static inline __always_inline u32 __get_primask(void)
{
	u32 flags;

	asm("mrs %0, primask" : "=r" (flags));

	return flags;
}

static inline __always_inline void __set_primask(u32 flags)
{
	asm("msr primask, %0" : : "r" (flags));
}

static inline __always_inline u32 __get_faultmask(void)
{
	u32 flags;

	asm("mrs %0, faultmask" : "=r" (flags));

	return flags;
}

static inline __always_inline void __set_faultmask(u32 flags)
{
	asm("msr faultmask, %0" : : "r" (flags));
}

static inline __always_inline u32 __get_basepri(void)
{
	u32 flags;

	asm("mrs %0, basepri" : "=r" (flags));

	return flags;
}

static inline __always_inline void __set_basepri(u32 flags)
{
	asm("msr basepri, %0" : : "r" (flags));
}

static inline __always_inline u32 __get_control(void)
{
	u32 flags;

	asm("mrs %0, control" : "=r" (flags));

	return flags;
}

static inline __always_inline void __set_control(u32 flags)
{
	asm("msr control, %0" : : "r" (flags));
}

#endif /* __ASSEMBLY__ */

#endif /* __M4NAOS_ASM_H */
