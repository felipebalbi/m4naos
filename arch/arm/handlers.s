/* SPDX-License-Identifier: GPL-3.0-or-later */

	.syntax unified
	.thumb

	.section .text
	.extern choose_task
	.global pendsv_handler
	.type pendsv_handler, %function

pendsv_handler:
	/* Disable interrupts: */
	cpsid	i

	/* Save current task's context */
	mrs	r0,  psp
	subs	r0,  #32
	stmia	r0!, {r4-r11}
	subs	r0,  #32

	/* Save current task's SP: */
	ldr	r2,  =current
	ldr	r1,  [r2]
	str	r0,  [r1]

	/* choose another task */
	bl	choose_task
	
	/* Load next task's SP: */
	ldr	r2,  =current
	ldr	r1,  [r2]
	ldr	r0,  [r1]

	/* Restore new task's context */
	ldmia	r0!, {r4-r11}
	msr	psp, r0

	/* EXC_RETURN - Thread mode with PSP */
	ldr	r0,  =0xfffffffd

	/* Enable interrupts: */
	cpsie	i

	bx	r0

.size pendsv_handler, . - pendsv_handler
