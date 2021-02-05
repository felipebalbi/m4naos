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

#include <m4naos/irq.h>
#include <m4naos/kernel.h>
#include <m4naos/hardware.h>
#include <m4naos/lock.h>

static u32 lock_level;

void __lock(void)
{
	if (lock_level++ == 0) {
		local_irq_disable();
		__dmb();
	}
}

void __unlock(void)
{
	if (--lock_level == 0) {
		__dmb();
		local_irq_enable();
	}
}

void __save_irq_flags(u32 *flags)
{
	u32 tmp;

	tmp = __get_primask();
	*flags = tmp;
}

void __restore_irq_flags(u32 *flags)
{
	u32 tmp = *flags;

	__set_primask(tmp);
}
