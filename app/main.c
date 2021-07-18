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
#include <m4naos/delay.h>
#include <m4naos/gpio.h>
#include <m4naos/hardware.h>
#include <m4naos/irq.h>
#include <m4naos/kernel.h>
#include <m4naos/string.h>
#include <m4naos/io.h>
#include <m4naos/uart.h>
#include <m4naos/sched.h>

#define PAJE_PROMPT "user> "

static int heartbeat_handler(void *_gpio)
{
	int ret;

	/* PC12, note that GPIOB is off */
	ret = gpio_request(28);
	if (ret)
		goto err0;

	ret = gpio_set_direction(28, GPIO_MODE_OUTPUT);
	if (ret)
		goto err1;

	ret = gpio_set_bias(28, GPIO_PULL_DOWN);
	if (ret)
		goto err1;

	while (true) {
		gpio_set_value(28, 1);
		mdelay(100);
		gpio_set_value(28, 0);
		mdelay(100);

		gpio_set_value(28, 1);
		mdelay(100);
		gpio_set_value(28, 0);
		mdelay(500);
	}

	return 0;

err1:
	gpio_release(28);

err0:
	return ret;
}

static char *read_repl(char *str)
{
	return str;
}

static char *eval_repl(char *str)
{
	return str;
}

static int print_repl(char *str)
{
	return printf("%s\n", str);
}

static void rep(char *str)
{
	int ret;

	ret = print_repl(eval_repl(read_repl(str)));
	if (ret < 0)
		printf("Failed to process input\n");
}

static char *readline(char *str)
{
	return str;
}

static void paje_print_banner(void)
{
	printf("\n\nPaje Scheme v%d.%d.%x\n",
			M4NAOS_VERSION_MAJOR,
			M4NAOS_VERSION_MINOR,
			M4NAOS_VERSION_PATCH);
}

static int paje_handler(void *context)
{
	paje_print_banner();

	while (true) {
		char *input = readline(PAJE_PROMPT);

		rep(input);
	}

	return 0;
}

int main(void)
{
	struct task *t0;
	struct task *t1;

	t0 = task_create(heartbeat_handler, NULL, 1);
	task_enqueue(t0);

	t1 = task_create(paje_handler, NULL, 1);
	task_enqueue(t1);

	task_run(t0);

	return 0;
}
