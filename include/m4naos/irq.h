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

#ifndef __M4NAOS_IRQ_H
#define __M4NAOS_IRQ_H

#include <m4naos/kernel.h>

/**
 * enum irqreturn
 * @IRQ_NONE: irq was not handled
 * @IRQ_HANDLED: irq was properly handled
 */
enum irqreturn {
	IRQ_NONE		= 0,
	IRQ_HANDLED		= 1,
};

#define IRQ_TRIGGER_TYPE_NONE		0
#define IRQ_TRIGGER_TYPE_EDGE_RISING	BIT(0)
#define IRQ_TRIGGER_TYPE_EDGE_FALLING	BIT(1)
#define IRQ_TRIGGER_TYPE_LEVEL_HIGH	BIT(2)
#define IRQ_TRIGGER_TYPE_LEVEL_LOW	BIT(3)

typedef enum irqreturn irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

int request_irq(unsigned int irq, irq_handler_t handler,
		unsigned int flags, void *cookie);
void release_irq(unsigned int irq, void *cookie);

#endif /* __M4NAOS_IRQ_H */
