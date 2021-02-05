ENTRY(reset_handler);

MEMORY {
       flash(rx) : ORIGIN = 0x08000000, LENGTH = 1024K
       sram(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
       ccm(rwx)  : ORIGIN = 0x10000000, LENGTH = 64K
}

STACK_SIZE = 0x2000; /* 8K */

SECTIONS {
	. = ORIGIN(flash);

	.vectors : {
		 __start_vectors__ = .;
		 KEEP(*(.vectors))
		 __end_vectors__ = .;
	} >flash

	.text : {
		__start_text__ = .;
		*(.text* .gnu.linkonce.t.*)
		*(.glue_7t) *(.glue_7)
		*(.rodata* .gnu.linkonce.r.*)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		__end_text__ = .;
	} >flash

	.data : {
		__start_data__ = .;
		*(.data*)
		__end_data__ = .;
	} >sram AT >flash

	. = ALIGN(4);

	.bss : {
		__start_bss__ = .;
		*(.bss*)
		__end_bss__ = .;
	} >sram

	. = ALIGN(4);
}

PROVIDE(__start_stack = ORIGIN(sram));
PROVIDE(__end_stack__ = ORIGIN(sram) + LENGTH(sram));
