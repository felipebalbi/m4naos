EXTERN(vector_table);
ENTRY(reset_handler);

__heap_min_size__	= 0x200;
__stack_min_size__	= 0x400;

MEMORY {
       flash(rx) : ORIGIN = 0x08000000, LENGTH = 1024K
       sram(rw)  : ORIGIN = 0x20000000, LENGTH = 128K
       ccm(rw)   : ORIGIN = 0x10000000, LENGTH = 64K
}

SECTIONS {
	 .text : {
	       /* Vector table */
	       KEEP(*(.vectors))

	       /* Program code */
	       . = ALIGN(4);
	       KEEP(*(.text*))
	       *(.init)
	       *(.fini)

	       /* All our initcall levels */
	       . = ALIGN(4);
	       __start_early__ = .;
	       *(.initcall0)
	       __end_early__ = .;

	       . = ALIGN(4);
	       __start_core__ = .;
	       *(.initcall1)
	       __end_core__ = .;

	       . = ALIGN(4);
	       __start_postcore__ = .;
	       *(.initcall2)
	       __end_postcore__ = .;

	       . = ALIGN(4);
	       __start_subsys__ = .;
	       *(.initcall3)
	       __end_subsys__ = .;

	       . = ALIGN(4);
	       __start_module__ = .;
	       *(.initcall4)
	       __end_module__ = .;

	       . = ALIGN(4);
	       __start_late__ = .;
	       *(.initcall5)
	       __end_late__ = .;
	
		/* Read-only data */
	       . = ALIGN(4);
	       *(.rodata*)

	       . = ALIGN(4);
	} >flash

	.data : {
	      __start_data__ = .;
	      *(.data*)
	      . = ALIGN(4);
	      __end_data__ = .;
	} >sram AT >flash
	__load_data__ = LOADADDR(.data);

	.ccm : {
	      __start_ccm__ = .;
	      KEEP(*(.ccm))
	      __end_ccm__ = .;
	} >ccm AT >flash
	__load_ccm__ = LOADADDR(.ccm);

	.bss : {
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
		. = ALIGN(4);
	} >sram

	/* User_heap_stack section, used to check that there is enough RAM left */
	._user_heap_stack :
	{
		. = ALIGN(8);
		PROVIDE ( _end = . );
		. = . + __heap_min_size__;
		. = . + __stack_min_size__;
		. = ALIGN(8);
	} >sram

	/* Remove unnecessary lib info */
	/DISCARD/ :
	{
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}

	.ARM.attributes 0 : {
		*(.ARM.attributes)
	}
}

PROVIDE(__end_stack__ = ORIGIN(sram) + LENGTH(sram));
