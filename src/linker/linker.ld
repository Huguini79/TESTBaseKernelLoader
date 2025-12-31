OUTPUT_FORMAT(elf32-i386)
ENTRY(START)

SECTIONS {
	. = 0x100000;

	.text : {
		*(.multiboot)
		*(.text)}
	.data : {*(.data)}
	.bss : {*(.bss)}

}
