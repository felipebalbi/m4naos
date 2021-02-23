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

static LIST_HEAD(task_list);
struct task *current;

static __always_inline void save_context(void)
{
	u32 scratch;

	asm("mrs %0, psp\n"
	    "stmdb %0!, {r4-r11}\n"
	    "msr psp, %0\n"
	    : "=r" (scratch));
}

static __always_inline void restore_context(void)
{
	u32 scratch;

	asm("mrs %0, psp\n"
	    "ldmia %0!, {r4-r11}\n"
	    "msr psp, %0\n"
	    : "=r" (scratch));
}

static __always_inline void switch_context(void)
{
	if (current) {
		current->sp = __get_psp();
		current = list_first_entry(current->list.prev, struct task,
				list);
	} else {
		current = list_first_entry(&task_list, struct task, list);
	}

	__set_psp(current->sp);
	__isb();
	__dsb();
}

static void task_destroy(void)
{
	list_del(&current->list);
	free(current);
	current = NULL;
}

struct task *task_create(int (*handler)(void *context), void *context)
{
	struct task *new;

	new = malloc(sizeof(*new));
	if (!new)
		goto err0;

	new->handler = handler;
	new->context = context;
	new->stack_frame.hw.r0 = (u32) context;
	new->stack_frame.hw.r1 = 0;
	new->stack_frame.hw.r2 = 0;
	new->stack_frame.hw.r3 = 0;
	new->stack_frame.hw.r12 = 0;
	new->stack_frame.hw.lr = (u32) task_destroy;
	new->stack_frame.hw.pc = (u32) handler;
	new->stack_frame.hw.psr = 0x01000000;

	new->sp = (u32) &new->stack_frame.sw.r11;

	return new;

err0:
	return NULL;
}

void task_enqueue(struct task *t)
{
	list_add_tail(&t->list, &task_list);
}

void task_run(struct task *t)
{
	__set_psp(t->sp);
	__isb();
	__set_control(0x03);
	__isb();

	/* force current to t */
	__svc();
	current = t;
	t->handler(t->context);
}

void __schedule(void)
{
	writel(SCB_BASE, SCB_ICSR, SCB_ICSR_PENDSVSET);
}

void schedule(void)
{
	local_irq_disable();
	__schedule();
	local_irq_enable();
}

void svc_handler(void)
{
}

void pendsv_handler(void)
{
	save_context();
	switch_context();
	restore_context();

	/* Erratum: 838869 */
	asm volatile ("dsb 0xf":::"memory");
}

