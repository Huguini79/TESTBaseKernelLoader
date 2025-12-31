// VGA IMPLEMENTATION FROM SCRATCH FOR THE "BaseKernel" X86 OPERATING SYSTEM FROM SCRATCH - https://github.com/Huguini79/BaseKernel

// IMPORT THE LIBRARIES THAT WE NEED
#include "vga.h"

#include "libc/string.h"

#include <stdint.h>
#include <stddef.h>

// INITIALIZE OUR VGA STRUCT
struct vga* vga;

// DEFINE PANIC FUNCTION
void panic(const char* error) {
	size_t len = strlen(error);

	for(int i = 0; i < len; i++) {
		perfectchar(error[i], 0x4F);
	}

}

// DEFINE ROWPLUS FUNCTION
void row_plus() {
	vga->row += 1;
	vga->col = 0;
	return;
}

// DEFINE OVERWRITE FUNCTION
void overwrite() {
	xychar(vga->col, vga->row, ' ', 0x2F);
}

// DEFINE THE INIT_SCREEN FUNCTION
void init_screen() {
	vga->video_mem = (uint16_t*)(0xB8000); // WE INITIALIZE THE SCREEN IN THE 0xB8000 ADDRESS

	clear(); // WE CLEAR THE SCREEN TO PREPARE OUR SCREEN TO WRITE PERFECTLY

}

// DEFINE GO_LEFT FUNCTION
void go_left() {
	xychar(vga->col, vga->row, vga->video_mem[(vga->row * VGA_WIDTH) + vga->col], 0x2F);
	vga->col -= 1;
	xychar(vga->col, vga->row, vga->video_mem[(vga->row * VGA_WIDTH) + vga->col], 0x4F);
}

// DEFINE GO_RIGHT FUNCTION
void go_right() {
        xychar(vga->col, vga->row, vga->video_mem[(vga->row * VGA_WIDTH) + vga->col], 0x2F);
	vga->col += 1;
        xychar(vga->col, vga->row, vga->video_mem[(vga->row * VGA_WIDTH) + vga->col], 0x4F);
}

// DEFINE GO_UP FUNCTION
void go_up() {
        xychar(vga->col, vga->row, vga->video_mem[(vga->row * VGA_WIDTH) + vga->col], 0x2F);
	vga->row -= 1;
        xychar(vga->col, vga->row, vga->video_mem[(vga->row * VGA_WIDTH) + vga->col], 0x4F);
}

// DEFINE GO_DOWN FUNCTION
void go_down() {
        xychar(vga->col, vga->row, vga->video_mem[(vga->row * VGA_WIDTH) + vga->col], 0x2F);
	vga->row += 1;
	xychar(vga->col, vga->row, vga->video_mem[(vga->row * VGA_WIDTH) + vga->col], 0x4F);
}

// DEFINE THE BACKSPACE_VGA FUNCTION
void backspace_vga() {
	/*
	// CHECK IF WE DO NOT HAVE TEXT IN THE X COLUMN
	if(vga->col == 0) {
		vga->col = VGA_WIDTH; // PUT OUR X POSITION IN THE VGA_WIDTH(80) POSITION TO GO TO THE FINAL POSITION OF THE X COLUMN
		vga->row -= 1; // DECREASE OUR Y POSITION (WE GO 1 POSITION LESS OF THE Y COLUMN)

		xychar(vga->col, vga->row, ' ', 0x22); // OVERWRITE THE NEW X AND Y POSITIONS WITH AN SPACE (WE DELETE THE CHARACTER OF THAT POSITION)

	} else {
	*/
		// WE CAN CONTINUE NORMALLY DELETING A CHARACTER FROM THE X COLUMN

		// vga->col -= 1; // DECREASE OUR X POSITION (WE GO 1 POSITION LESS OF THE X COLUMN)

		if(vga->col > 17) {
			go_left();

                	xychar(vga->col, vga->row, ' ', 0x4F); // OVERWRITE THE NEW X AND Y POSITIONS WITH AN SPACE (WE DELETE THE CHARACTER OF THAT POSITION)
		}
		/*
		go_left();

		xychar(vga->col, vga->row, ' ', 0x4F); // OVERWRITE THE NEW X AND Y POSITIONS WITH AN SPACE (WE DELETE THE CHARACTER OF THAT POSITION)
		*/
}

// DEFINE THE XYCHAR FUNCTION
void xychar(int x, int y, char c, char color) {
	vga->video_mem[(y * VGA_WIDTH) + x] = (uint16_t)(color << 8) | c; // PUT THE CHARACTER WITH THE COLOR IN THE VIDEO MEM
}

// DEFINE THE PERFECTCHAR FUNCTION
void perfectchar(char c, char color) {
	// CHECK IF WE PUT IN THE TEXT THE '\n' TO INCREASE OUR VGA->ROW POSITION
	if(c == '\n') {
		vga->row += 1; // INCREASE THE Y POSITION (GO DOWN)
		vga->col = 0; // START FROM THE POSITION 0 IN THE X COLUMN
		return;
	}

	xychar(vga->col, vga->row, c, color); // WRITE THE CHARACTER AUTOMATICALLY USING THE XYCHAR POSITION
	vga->col += 1; // INCREASE THE X POSITION (THIS SIMULATES WRITING)

	// 80x25

	// CHECK IF OUR TEXT IS LONGER THAN THE VGA WIDTH (80)
	if(vga->col >= VGA_WIDTH) {
		vga->row += 1; // INCREASE THE Y POSITION (GO DOWN)
		vga->col = 0; // START FROM THE POSITION 0 IN THE X COLUMN
	}

	// CHECK IF OUR TEXT IS LONGER THAN THE VGA HEIGHT (25)
	if(vga->row >= VGA_HEIGHT) {
		clear(); // WE CLEAR THE SCREEN
	}

}

// DEFINE THE PERFECTCHAR2 FUNCTION
void perfectchar2(char c, char color) {
        // CHECK IF WE PUT IN THE TEXT THE '\n' TO INCREASE OUR VGA->ROW POSITION
        if(c == '\n') {
                vga->row += 1; // INCREASE THE Y POSITION (GO DOWN)
                vga->col = 0; // START FROM THE POSITION 0 IN THE X COLUMN
				return;
        }

        xychar(vga->col, vga->row, c, color); // WRITE THE CHARACTER AUTOMATICALLY USING THE XYCHAR POSITION
        go_right(); // INCREASE THE X POSITION (THIS SIMULATES WRITING)

        // 80x25

        // CHECK IF OUR TEXT IS LONGER THAN THE VGA WIDTH (80)
        if(vga->col >= VGA_WIDTH) {
                vga->row += 1; // INCREASE THE Y POSITION (GO DOWN)
                vga->col = 0; // START FROM THE POSITION 0 IN THE X COLUMN
        }

        // CHECK IF OUR TEXT IS LONGER THAN THE VGA HEIGHT (25)
        if(vga->row >= VGA_HEIGHT) {
                clear(); // WE CLEAR THE SCREEN
        }

}

// DEFINE THE PRINTB FUNCTION
void printb(const char* str) {
	// CALCULATE THE LEN OF THE STR THAT WE PUT IN THE FUNCTION
	size_t len = strlen(str);

	// WE INITIALIZE A LOOP
	for(int i = 0; i < len; i++) {
		perfectchar(str[i], 0x2F); // WE PUT ONE CHARACTER, THE NUMBER OF THE TIMES OF THE LOOP IS THE LEN OF OUR STR
	}

}

// DEFINE THE CLEAR FUNCTION
void clear() {
	// SET ALL THE POSITIONS TO 0
	vga->row = 0;
	vga->col = 0;

	// WE INITIALIZE A LOOP
	for(int y = 0; y < VGA_HEIGHT; y++) {
		for(int x = 0; x < VGA_WIDTH; x++) {
			xychar(x, y, ' ', 0x2F); // FILL THE SCREEN WITH SPACES
		}
	}

}
