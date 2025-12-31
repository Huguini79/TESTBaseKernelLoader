// KEYBOARD IMPLEMENTATION FROM SCRATCH FOR THE "BaseKernel" X86 OPERATING SYSTEM FROM SCRATCH - https://github.com/Huguini79/BaseKernel

// IMPORT THE LIBRARIES THAT WE NEED

#include "keyboard.h"
#include "kernel.h"
#include "vga.h"
#include "io.h"

#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/string.h"

#include <stdbool.h>

// RESET COMMAND PARAMETERS
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define KBRD_INTRFC 0x64
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */
#define KBRD_IO 0x60 /* keyboard IO port */
#define KBRD_RESET 0xFE /* reset CPU command */
#define bit(n) (1<<(n)) /* Set bit n to 1 */
#define check_flag(flags, n) ((flags) & bit(n))
/////////////////////////////////////////////////////////////////////////////////////////////////////////

char buffer[512];
int pos = 0;

bool nano_style = false;

void anadir_caracter(char c) {
    buffer[pos++] = c;
    buffer[pos] = '\0';
}

void reboot() {
			uint8_t temp;

                        asm volatile ("cli"); /* disable all interrupts */
                    
                        /* Clear all keyboard buffers (output and command buffers) */
                        do
                        {
                            temp = insb(KBRD_INTRFC);
                            if (check_flag(temp, KBRD_BIT_KDATA) != 0)
                                insb(KBRD_IO);
                        } while (check_flag(temp, KBRD_BIT_UDATA) != 0);
                    
                        outb(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */
                        loop:
                            asm volatile ("hlt"); /* if that didn't work, halt the CPU */
                            goto loop; /* if a NMI is received, halt again */
}

void returntocommandline() {
                        overwrite();
        				row_plus();
        				printb("root@BaseKernel$");
                        go_right();
}

// DEFINE THE INIT_KEYBOARD FUNCTION
void init_keyboard() {
	// INFINITE LOOP
	while(1) {
		// MANUAL POLLING
		uint8_t status = insb(0x64); // READ THE STATUS OF THE KEYBOARD

		// THE KEYBOARD HAS BEEN PRESSED
		if(status & 0x01) {
			uint8_t scancode = insb(0x60); // READ THE SCANCODE (read the key that we have pressed in our keyboard)

			// TEST
			if(scancode == 0x01) { // ESC SCANCODE
				printb("ESC HAS BEEN PRESSED");
			}

			if(scancode == 0x0E) { // BACKSPACE SCANCODE
				if(pos > 0) {
                    buffer[--pos] = '\0';
                }
                backspace_vga();
			}

			if(scancode == 0x4B) { // LEFT ARROW
				if(nano_style != false) {
					go_left();
				}
			}

			if(scancode == 0x4D) { // RIGHT ARROW
				if(nano_style != false) {
					go_right();
				}
			}

			if(scancode == 0x48) { // UP ARROW
				if(nano_style != false) {
					go_up();
				}
			}

			if(scancode == 0x50) { // DOWN ARROW
				if(nano_style != false) {
					go_down();
				}
			}


			if(scancode == 0x1C) {
                if(strncmp(buffer, "test", 4) == 0) {
                    overwrite();
                    row_plus();
                    printb("TEST EXECUTED WITH SUCCESS");
                    returntocommandline();
                
                } else if(strncmp(buffer, "", 1) == 0) {
                        overwrite();
        				row_plus();
        				printb("root@BaseKernel$");
                        go_right();
                    }
                else if(strncmp(buffer, "exit", 4) == 0) {
                        outw(0xB004, 0x2000);
                        outw(0x604, 0x2000);
                        outw(0x4004, 0x3400);
                        outw(0x600, 0x34);
                }
                    
                else if(strncmp(buffer, "help", 4) == 0) {
                            overwrite();
                            row_plus();
                            printb("Commands:\ntest - Test command\nclear - Clear the screen\nhelp - See the available commands\nexit - Shutdown the system(this only works on QEMU, Bochs and VirtualBox)\nreboot - Reboots the systems(this works also in real hardware)\nenablenanostyle - Enables the nano style(you can move the cursor with the arrow keys)\nrandomnum - Prints a random number\nhello - Hello command using the printf function of the libc implementation");
                            returntocommandline();
                }
                else if(strncmp(buffer, "clear", 5) == 0) {
                        clear();
                        returntocommandline();
                }

		else if(strncmp(buffer, "enablenanostyle", 15) == 0) {
			nano_style = true;
		}
		
		else if(strncmp(buffer, "randomnum", 9) == 0) {
			int random_value = rand();
			
			char random_value_buffer[1024];

			itoa(random_value, random_value_buffer);

			overwrite();
			row_plus();
			printb(random_value_buffer);
			returntocommandline();


		}

		else if(strncmp(buffer, "hello", 5) == 0) {
			printf("\nHELLO");
			exit(0);
			returntocommandline();
		}

                    else if(strncmp(buffer, "reboot", 6) == 0) {
                        reboot();
                }
                    else if(strncmp(buffer, ";", 1) == 0) {
			overwrite();
			row_plus();
			returntocommandline();
			}

            else {
                    overwrite();
                    row_plus();
                    panic("**KERNEL PANIC - THE COMMAND WASN'T INTERPRETED**"); 
                    returntocommandline();
                }
				// overwrite();
				// row_plus();
				// printb("root@BaseKernel$");
				// go_right();
                pos = 0;
                buffer[pos] = '\0';
			}

		if(scancode == 0x33) { // , SCANCODE
			perfectchar2(',', 0x2F);
			anadir_caracter(',');
		}

		if(scancode == 0x35) {
			perfectchar2('/', 0x2F);
			anadir_caracter('/');
		}

		if(scancode == 0x34) {
			perfectchar2('.', 0x2F);
			anadir_caracter('.');
		}

		if(scancode == 0x0D) {
			 perfectchar2('=', 0x2F);
			 anadir_caracter('=');
		}

			if(scancode == 0x1E) { // A SCANCODE
				perfectchar2('a', 0x2F);
                anadir_caracter('a');
			}
            if(scancode == 0x30) { // B SCANCODE
				perfectchar2('b', 0x2F);
                anadir_caracter('b');
			}
            if(scancode == 0x2E) { // C SCANCODE
				perfectchar2('c', 0x2F);
                anadir_caracter('c');
			}
            if(scancode == 0x20) { // D SCANCODE
				perfectchar2('d', 0x2F);
                anadir_caracter('d');
			}
            if(scancode == 0x12) { // E SCANCODE
				perfectchar2('e', 0x2F);
                anadir_caracter('e');
			}
            if(scancode == 0x21) { // F SCANCODE
				perfectchar2('f', 0x2F);
                anadir_caracter('f');
			}
            if(scancode == 0x22) { // G SCANCODE
				perfectchar2('g', 0x2F);
                anadir_caracter('g');
			}
            if(scancode == 0x23) { // H SCANCODE
				perfectchar2('h', 0x2F);
                anadir_caracter('h');
			}
            if(scancode == 0x17) { // I SCANCODE
				perfectchar2('i', 0x2F);
                anadir_caracter('i');
			}
            if(scancode == 0x24) { // J SCANCODE
				perfectchar2('j', 0x2F);
                anadir_caracter('j');
			}
            if(scancode == 0x25) { // K SCANCODE
				perfectchar2('k', 0x2F);
                anadir_caracter('k');
			}
            if(scancode == 0x26) { // L SCANCODE
				perfectchar2('l', 0x2F);
                anadir_caracter('l');
			}
            if(scancode == 0x32) { // M SCANCODE
				perfectchar2('m', 0x2F);
                anadir_caracter('m');
			}
            if(scancode == 0x31) { // N SCANCODE
				perfectchar2('n', 0x2F);
                anadir_caracter('n');
			}
            if(scancode == 0x18) { // O SCANCODE
				perfectchar2('o', 0x2F);
                anadir_caracter('o');
			}
            if(scancode == 0x19) { // P SCANCODE
				perfectchar2('p', 0x2F);
                anadir_caracter('p');
			}
            if(scancode == 0x10) { // Q SCANCODE
				perfectchar2('q', 0x2F);
                anadir_caracter('q');
			}
            if(scancode == 0x13) { // R SCANCODE
				perfectchar2('r', 0x2F);
                anadir_caracter('r');
			}
            if(scancode == 0x1F) { // S SCANCODE
				perfectchar2('s', 0x2F);
                anadir_caracter('s');
			}
            if(scancode == 0x14) { // T SCANCODE
				perfectchar2('t', 0x2F);
                anadir_caracter('t');
			}
            if(scancode == 0x16) { // U SCANCODE
				perfectchar2('u', 0x2F);
                anadir_caracter('u');
			}
            if(scancode == 0x2F) { // V SCANCODE
				perfectchar2('v', 0x2F);
                anadir_caracter('v');
			}
            if(scancode == 0x11) { // W SCANCODE
				perfectchar2('w', 0x2F);
                anadir_caracter('w');
			}
            if(scancode == 0x2D) { // X SCANCODE
				perfectchar2('x', 0x2F);
                anadir_caracter('x');
			}
            if(scancode == 0x15) { // Y SCANCODE
				perfectchar2('y', 0x2F);
                anadir_caracter('y');
			}
            if(scancode == 0x2C) { // Z SCANCODE
				perfectchar2('z', 0x2F);
                anadir_caracter('z');
			}
            if(scancode == 0x39) { // SPACE SCANCODE
				perfectchar2(' ', 0x2F);
                anadir_caracter(' ');
			}
            if(scancode == 0x27) { // ; SCANCODE
                perfectchar2(';', 0x2F);
                anadir_caracter(';');
            }

		}

	}
}
