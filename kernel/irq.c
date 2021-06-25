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
#include <m4naos/kernel.h>
#include <m4naos/hardware.h>
#include <m4naos/irq.h>

/*
 * Specific to STM32F07.
 *
 * All Interrupts except for M4-generic (Reset, NMI, HardFault, MemManage,
 * BusFault, UsageFault, SVCall, DebugMonitor, PendSV, and SysTick
 */
#define NUM_IRQS		(82)

struct irq_desc {
	irq_handler_t handler;
	void *cookie;
	unsigned int flags;
	const char *name;
};

static struct irq_desc irq_all_descs[NUM_IRQS];

int request_irq(unsigned int irq, irq_handler_t handler,
		unsigned int flags, const char *name, void *cookie)
{
	struct irq_desc *desc = &irq_all_descs[irq];

	if (desc->handler)
		return -EBUSY;

	desc->handler = handler;
	desc->cookie = cookie;
	desc->flags = flags;
	desc->name = name;

	return 0;
}

void release_irq(unsigned int irq, void *cookie)
{
	struct irq_desc *desc = &irq_all_descs[irq];

	if (!desc->handler)
		return;

	/* Do we print an error? */
	if (desc->cookie != cookie)
		return;

	desc->handler = NULL;
	desc->cookie = NULL;
	desc->flags = 0;
	desc->name = NULL;
}

void irq_generic_handler(int irq)
{
	struct irq_desc *desc = &irq_all_descs[irq];

	/* Trigger fault? */
	if (!desc->handler)
		return;

	desc->handler(irq, desc->cookie);
}
