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

#ifndef __M4NAOS_SCHED_H
#define __M4NAOS_SCHED_H

#include <m4naos/kernel.h>
#include <m4naos/list.h>

#define TASK_STATE_IDLE		0
#define TASK_STATE_RUNNABLE	1
#define TASK_STATE_RUNNING	2

#define TASK_STACK_SIZE		(4096 - \
	(sizeof(struct sw_stack_frame)- \
	 sizeof(struct hw_stack_frame)))

#define TASK_RETURN_HANDLER	0xfffffff1
#define TASK_RETURN_THREAD_MSP	0xfffffff9
#define TASK_RETURN_THREAD_PSP	0xfffffffd 

struct sw_stack_frame {
	u32	r4;
	u32	r5;
	u32	r6;
	u32	r7;
	u32	r8;
	u32	r9;
	u32	r10;
	u32	r11;
};

struct hw_stack_frame {
	u32	r0;
	u32	r1;
	u32	r2;
	u32	r3;
	u32	r12;
	u32	lr;
	u32	pc;
	u32	psr;
};

struct task_stack_frame {
	u8			stack[TASK_STACK_SIZE];
	struct sw_stack_frame	sw;
	struct hw_stack_frame	hw;
};

struct task {
	struct list_head list;
	struct task_stack_frame stack_frame;
	int (*handler)(void);
	u32 state;
	u32 sp;
};

struct task *task_create(int (*handler)(void));
void task_enqueue(struct task *t);
void task_run(struct task *t);
void __schedule(void);
void schedule(void);

#endif /* __M4NAOS_SCHED_H */
