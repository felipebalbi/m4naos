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
#include <stdio.h>
#include <m4naos/kernel.h>
#include <m4naos/device.h>
#include <m4naos/driver.h>
#include <m4naos/irq.h>
#include <m4naos/io.h>
#include <m4naos/uart.h>
#include <m4naos/rcc.h>

#define USART_SR	0x00
#define USART_DR	0x04
#define USART_BRR	0x08
#define USART_CR1	0x0c
#define USART_CR2	0x10

static void __iomem *base;

static void __uart_putch(char c)
{
	if (c == '\n') {
		writeb(base, USART_DR, '\r');
		while (!(readl(base, USART_SR) & BIT(6)));
	}

	writeb(base, USART_DR, c);
	while (!(readl(base, USART_SR) & BIT(6)));
}

static void __uart_puts(const char *str)
{
	while (*str)
		uart_putch(*str++);
}

void uart_putch(char c)
{
	__uart_putch(c);
}

void uart_puts(const char *str)
{
	local_irq_disable();
	__uart_puts(str);
	local_irq_enable();
}

static int uart_probe(struct device *dev)
{
	const struct resource *res;
	u32 reg;
	int ret;

	res = device_get_resource(dev, RESOURCE_TYPE_CLK, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err0;
	}

	clk_enable(res->start, BIT(res->flags));

	res = device_get_resource(dev, RESOURCE_TYPE_IO_MEM, 0);
	if (!res) {
		ret = -ENOMEM;
		goto err0;
	}

	base = ioremap(res->start);
	if (!base) {
		ret = -ENOMEM;
		goto err0;
	}

	reg = readl(base, USART_CR1);
	reg |= BIT(15) | BIT(13); /* OVER8 | UE */
	reg &= ~BIT(12); /* M */
	writel(base, USART_CR1, reg);

	reg = readl(base, USART_CR2);
	reg &= ~(3 << 12); /* 1 stop bit */
	writel(base, USART_CR2, reg);

	/*
	 * We're running with Pclk = 84MHz and want to achieve a Baudrate of
	 * 115200bps. This means that we have to solve the equation:
	 *
	 *	baud = fclk / (8 * (2 - OVER8) * USARTDIV)
	 *
	 * Where baud is 2Mbps and fclk is 84MHz. Isolating USARTDIV we have:
	 *
	 *	USARTDIV = 84000000 / (8 * (2 - 1) * 2000000)
	 *		 = 84000000 / 16000000
	 *		 = 5.25
	 *
	 * Thus, we have mantissa = 5 and fraction = 0.25.
	 *
	 * Converting to hex we end up with:
	 *
	 *	MANTISSA = 0x5
	 *	FRACTION = 0x4
	 *
	 * Which results in:
	 *
	 *	BRR = 0x54
	 */
	reg = 0x54; /* 5.25 */
	writel(base, USART_BRR, reg);

	reg = readl(base, USART_CR1);
	reg |= BIT(3); /* TE */
	writel(base, USART_CR1, reg);

	return 0;

err0:
	return ret;
}

static struct driver uart_driver = {
	.name		= "usart",
	.probe		= uart_probe,
};

postcore_driver_register(uart_driver);
