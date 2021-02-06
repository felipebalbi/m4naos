EXTERN(vector_table);
ENTRY(reset_handler);

MEMORY {
       flash(rx) : ORIGIN = 0x08000000, LENGTH = 1024K
       sram(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
       ccm(rwx)  : ORIGIN = 0x10000000, LENGTH = 64K
}

SECTIONS {
	 .text : {
	       KEEP(*(.vectors))	/* Vector table */
	       *(.text*)	/* Program code */
	       . = ALIGN(4);
	       *(.rodata*)	/* Read-only data */
	       . = ALIGN(4);
	} >flash

	. = ALIGN(4);
	__end_text__ = .;

	.data : {
	      __start_data__ = .;
	      *(.data*)
	      . = ALIGN(4);
	      __end_data__ = .;
	} >sram AT >flash
	__load_data__ = LOADADDR(.data);

	.bss : {
		__start_bss__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__end_bss__ = .;
	} >sram
}

PROVIDE(__end_stack__ = ORIGIN(sram) + LENGTH(sram));
