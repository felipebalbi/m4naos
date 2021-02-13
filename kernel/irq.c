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
#include <m4naos/irq.h>

void local_irq_enable(void)
{
	asm("cpsie i");
}

void local_irq_disable(void)
{
	asm("cpsid i");
}

u32 __get_primask(void)
{
	u32 flags;

	asm("mrs %0, primask" : "=r" (flags));

	return flags;
}

void __set_primask(u32 flags)
{
	asm("msr primask, %0" : "=r" (flags));
}
