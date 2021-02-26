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
#include <m4naos/hardware.h>
#include <m4naos/irq.h>
#include <m4naos/kernel.h>
#include <m4naos/string.h>
#include <m4naos/io.h>
#include <m4naos/uart.h>
#include <m4naos/sched.h>

static int task_handler(void *context __unused)
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

	t0 = task_create(task_handler, NULL, 0);
	task_enqueue(t0);

	for (i = 0; i < 16; i++) {
		t1 = task_create(task_handler, NULL, i & 1);
		task_enqueue(t1);
	}

	task_run(t0);

	return 0;
}
