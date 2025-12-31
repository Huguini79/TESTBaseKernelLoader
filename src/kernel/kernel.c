// MAIN FILE OF THE C KERNEL OF THE "BaseKernel" X86 OPERATING SYSTEM FROM SCRATCH - https://github.com/Huguini79/BaseKernel

// IMPORT OUR LOCAL LIBRARIES
#include "kernel.h"
#include "vga.h"
#include "io.h"
#include "keyboard.h"

// LIBC
#include "libc/string.h"

// #include "pci.h"
// #include "memory.h"
// #include "heap.h"
// #include "kheap.h"
// #include "paging.h"
// #include "gdt.h"
// #include "tss.h"

unsigned char src_kernel_programtest_bin[] = {
  0xbf, 0x00, 0x80, 0x0b, 0x00, 0xb4, 0x0f, 0xb0, 0x48, 0x66, 0x89, 0x07,
  0x83, 0xc7, 0x02, 0xb0, 0x6f, 0x66, 0x89, 0x07, 0x83, 0xc7, 0x02, 0xb0,
  0x6c, 0x66, 0x89, 0x07, 0x83, 0xc7, 0x02, 0xb0, 0x61, 0x66, 0x89, 0x07,
  0x83, 0xc7, 0x02, 0xc3
};
unsigned int src_kernel_programtest_bin_len = 40;

// DEFINE THE KERNEL_MAIN FUNCTION (THE START OF OUR C KERNEL)
void kernel_main() {

	static unsigned char exec_buffer[256];

	memcpy(exec_buffer, src_kernel_programtest_bin, src_kernel_programtest_bin_len);

	void (*entry)(void) = (void (*)(void))exec_buffer;

	entry();

	for(;;) {}

	/*
	// INIT OUR VGA DRIVER
	init_screen();
	
	*/
	/*

	// PUT AN EXAMPLE INTO THE SCREEN
	printb("BaseKernel - github.com/Huguini79/BaseKernel");
	row_plus();
	printb("YOUTUBE: youtube.com/@ProgramandoconHuguini");

	
	// go_down();
	// go_down();
	row_plus();
	row_plus();
	printb("root@BaseKernel$");
	go_right();

	// INIT THE KEYBOARD
	/*
	init_keyboard();
	*/

}
