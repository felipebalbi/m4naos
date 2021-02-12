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
#include <m4naos/irq.h>
#include <m4naos/io.h>
#include <m4naos/uart.h>
#include <m4naos/rcc.h>

#define USART_SR	0x00
#define USART_DR	0x04

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

static int uart_init(void)
{
	printf("module: %s\n", __func__);

	return 0;
}
module_init(uart_init);
