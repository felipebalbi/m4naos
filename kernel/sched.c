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

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <m4naos/asm.h>
#include <m4naos/io.h>
#include <m4naos/list.h>
#include <m4naos/kernel.h>
#include <m4naos/sched.h>

void __iomem *scb = (void __iomem *) SCB_BASE;

void __schedule(void)
{
	writel(scb, SCB_ICSR, SCB_ICSR_PENDSVSET);
}

void schedule(void)
{
	local_irq_disable();
	__schedule();
	local_irq_enable();
}
