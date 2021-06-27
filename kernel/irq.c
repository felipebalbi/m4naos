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
#include <m4naos/io.h>

#define NVIC_ISER(n)			((n) + 0x0000)
#define NVIC_ICER(n)			((n) + 0x0080)
#define NVIC_ISPR(n)			((n) + 0x0100)
#define NVIC_ICPR(n)			((n) + 0x0180)
#define NVIC_IABR(n)			((n) + 0x0200)
#define NVIC_IPR(n)			((n) + 0x0300)
#define NVIC_STIR			0x0e00

/*
 * Specific to STM32F07.
 *
 * All Interrupts except for M4-generic (Reset, NMI, HardFault, MemManage,
 * BusFault, UsageFault, SVCall, DebugMonitor, PendSV, and SysTick
 */
#define NUM_IRQS			82

#define IRQ_TOO_MANY_SPURIOUS		100000
#define IRQ_CHIP_IRQS_PER_REGISTER	32
#define IRQ_CHIP_IRQ_BIT_MASK		0x1f

struct irq_desc {
	irq_handler_t handler;
	void *cookie;
	unsigned int flags;
	int spurious;
};

static struct irq_desc irq_all_descs[NUM_IRQS] __ccm;
static void __iomem *chip;

static int irq_chip_irqn_to_reg(int irq)
{
	return irq / IRQ_CHIP_IRQS_PER_REGISTER;
}

static int irq_chip_irqn_to_bit(int irq)
{
	return BIT(irq & IRQ_CHIP_IRQ_BIT_MASK);
}

static void irq_chip_disable_irq(int irq)
{
	u32 offset = irq_chip_irqn_to_reg(irq);
	u32 bit = irq_chip_irqn_to_bit(irq);

	writel(chip, NVIC_ICER(offset), bit);
}

static void irq_chip_mark_spurious(struct irq_desc *desc, int irq)
{
	if (desc->spurious++ > IRQ_TOO_MANY_SPURIOUS)
		irq_chip_disable_irq(irq);
}

static int irq_desc_has_handler(struct irq_desc *desc)
{
	return !!desc->handler;
}

static int irq_chip_setup_irq(int irq, unsigned int flags)
{
	u32 offset = irq_chip_irqn_to_reg(irq);
	u32 bit = irq_chip_irqn_to_bit(irq);

	if (!flags)
		return -EINVAL;

	/* Check what to do with `flags' */
	writel(chip, NVIC_ISER(offset), bit);

	return 0;
}

static void irq_chip_teardown_irq(int irq)
{
	u32 offset = irq_chip_irqn_to_reg(irq);
	u32 bit = irq_chip_irqn_to_bit(irq);

	writel(chip, NVIC_ICER(offset), bit);
}

void irq_generic_handler(int irq)
{
	struct irq_desc *desc = &irq_all_descs[irq];
	irqreturn_t ret;

	/* Trigger fault? */
	if (!irq_desc_has_handler(desc)) {
		irq_chip_mark_spurious(desc, irq);
		return;
	}

	ret = desc->handler(irq, desc->cookie);
	if (ret != IRQ_HANDLED)
		irq_chip_mark_spurious(desc, irq);
}

int request_irq(unsigned int irq, irq_handler_t handler,
		unsigned int flags, void *cookie)
{
	struct irq_desc *desc = &irq_all_descs[irq];

	if (desc->handler)
		return -EBUSY;

	desc->handler = handler;
	desc->cookie = cookie;
	desc->flags = flags;

	return irq_chip_setup_irq(irq, flags);
}

void release_irq(unsigned int irq, void *cookie)
{
	struct irq_desc *desc = &irq_all_descs[irq];

	if (!desc->handler)
		return;

	/* Do we print an error? */
	if (desc->cookie != cookie)
		return;

	irq_chip_teardown_irq(irq);

	desc->handler = NULL;
	desc->cookie = NULL;
	desc->flags = 0;
	desc->spurious = 0;
}

static int irq_chip_init(void)
{
	chip = ioremap(NVIC_BASE);
	if (!chip)
		return -ENOMEM;

	return 0;
}
postcore_init(irq_chip_init);
