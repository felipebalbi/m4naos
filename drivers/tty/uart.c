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

static void __uart_putch(char c)
{
	while (!(readl(APB2_USART1, USART_SR) & BIT(6)));
	writeb(APB2_USART1, USART_DR, c);
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
	__uart_puts(str);
}

static int uart_probe(struct device *dev)
{
	u32 reg;

	clk_enable(RCC_AHB1ENR, BIT(0));
	clk_enable(dev->clk->offset, BIT(dev->clk->bit));

	reg = readl(AHB1_GPIOA, 0x00);
	reg |= (2 << 18);
	writel(AHB1_GPIOA, 0x00, reg);

	reg = readl(AHB1_GPIOA, 0x24);
	reg |= (7 << 4);
	writel(AHB1_GPIOA, 0x24, reg);

	reg = readl(APB2_USART1, USART_CR1);
	reg |= 	BIT(13); /* UE */
	reg &= ~BIT(12); /* M */
	writel(APB2_USART1, USART_CR1, reg);

	reg = readl(APB2_USART1, USART_CR2);
	reg &= ~(3 << 12); /* 1 stop bit */
	writel(APB2_USART1, USART_CR2, reg);

	/*
	 * According to Table 137, page 982 on STM32F405 reference manual, the
	 * following results in a baud rate of 10.5Mbps with an error of 0%.
	 */
	reg = 0x10; /* 1.0 */
	writel(APB2_USART1, USART_BRR, reg);

	reg = readl(APB2_USART1, USART_CR1);
	reg |= 	BIT(15) | BIT(3); /* OVER8 | TE */
	writel(APB2_USART1, USART_CR1, reg);

	return 0;
}

static struct driver uart_driver = {
	.name		= "usart",
	.probe		= uart_probe,
};

static int uart_init(void)
{
	return register_driver(&uart_driver);
}
postcore_init(uart_init);
