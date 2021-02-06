ENTRY(reset_handler);

MEMORY {
       flash(rx) : ORIGIN = 0x08000000, LENGTH = 1024K
       sram(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS {
	.text : {
		__start_text__ = .;
		__start_vectors__ = .;
		KEEP(*(.vectors))
		__end_vectors__ = .;
		*(.text)
		*(.rodata)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		__end_text__ = .;
	} >flash

	. = ALIGN(4);

	.data : {
		__start_data__ = .;
		KEEP(*(.data))
		PROVIDE(__start_stack__ = ORIGIN(sram));
		PROVIDE(__end_stack__ = ORIGIN(sram) + LENGTH(sram));
		__end_data__ = .;
	} >sram AT >flash

	. = ALIGN(4);

	.bss : {
		__start_bss__ = .;
		*(.bss)
		__end_bss__ = .;
	} >sram

	. = ALIGN(4);
}

