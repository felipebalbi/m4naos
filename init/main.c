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

static int task_handler(void *context)
{
	char str[8];

	snprintf(str, 8, "TASK%d\n", current->id);

	while (true)
		uart_puts(str);

	return 0;
}

int main(void)
{
	struct task *t0;
	struct task *t1;
	int i;

	t0 = task_create(heartbeat_handler, NULL, 1);
	task_enqueue(t0);

	for (i = 0; i < 16; i++) {
		t1 = task_create(task_handler, NULL, 1);
		task_enqueue(t1);
	}

	task_run(t0);

	return 0;
}
