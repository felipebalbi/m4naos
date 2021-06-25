/* SPDX-License-Identifier: GPL-3.0-or-later */

#include <m4naos/asm.h>

	.syntax	unified
	.thumb

PROC(reset_handler)
	ldr	r0, =__start_ccm__
	ldr	r1, =__load_ccm__
	ldr	r3, =__end_ccm__

copy_ccm:
	ldr	r4, [r1]
	str	r4, [r0]
	adds	r0, #4
	adds	r1, #4
	cmp	r3, r0
	bne	copy_ccm

	ldr	r0, =__start_data__
	ldr	r1, =__load_data__
	ldr	r3, =__end_data__
copy_data:
	ldr	r4, [r1]
	str	r4, [r0]
	adds	r0, #4
	adds	r1, #4
	cmp	r3, r0
	bne	copy_data

	ldr	r3, =__bss_end__
zero_bss:
	mov	r1, #0
	str	r1, [r0]
	adds	r0, #4
	cmp	r0, r3
	bne	zero_bss

	bl	__libc_init_array
	bl	kernel_init
	ldr	r0, =main
	bx	r0

	/* should never get here */
	b	.
ENDPROC(reset_handler)	

PROC(pendsv_handler)
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
	ldr	r0,  [r1, #4]

	/* CONTROL - choose Thread's privilege level */
	ldr	r2, [r1, #8]
	msr	control, r2
	isb

	/* Enable interrupts: */
	cpsie	i

	bx	r0
ENDPROC(pendsv_handler)

PROC(default_handler)
0:
	wfi
	b	0b
ENDPROC(default_handler)

PROC(asm_do_irq)
	ldr	r0, =irq_generic_handler
	bx	r0
ENDPROC(asm_do_irq)


	/* Vector Table */
	.section .vectors
	.word	__end_stack__
	.word	reset_handler
	.word	nmi_handler
	.word	hard_fault_handler
	.word	mmu_fault_handler
	.word	bus_fault_handler
	.word	usage_fault_handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	svc_handler
	.word	dbgmon_handler
	.word	0
	.word	pendsv_handler
	.word	sys_tick_handler
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq
	.word	asm_do_irq

	.weakref nmi_handler, default_handler
	.weakref hard_fault_handler, default_handler
	.weakref mmu_fault_handler, default_handler
	.weakref bus_fault_handler, default_handler
	.weakref usage_fault_handler, default_handler
	.weakref svc_handler, default_handler
	.weakref dbgmon_handler, default_handler
