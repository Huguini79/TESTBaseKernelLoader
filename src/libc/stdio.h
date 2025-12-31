#ifndef STDIO_H
#define STDIO_H

#include "vga.h"

#include "libc/string.h"

void printf(const char* str) {
    overwrite();

    size_t len = strlen(str);

    for(int i = 0; i < len; i++) {
        if(str[i] == '\n') {
            row_plus();
        }
    }

    printb(str);
}

#endif