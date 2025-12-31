#ifndef STDLIB_H
#define STDLIB_H

#include "vga.h"

#include "libc/stdio.h"

static unsigned long int next = 1;

int rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
    next = seed;
}

void reverse(char str[], int length)
{
    int start;
    int end = length -1;
    for(start = 0; start < end; ++start, --end)
    {
        const char ch = str[start];
        str[start] = str[end];
        str[end] = ch;
    }
}

void itoa(int n, char* str) {
    int i = 0;
    int isNegative = 0;
    
    if (n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (n < 0) {
        isNegative = 1;
        n = -n;
    }

    while (n != 0) {
        int rem = n % 10;
        str[i++] = rem + '0';
        n = n / 10;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str, i);
}

void exit(uint8_t status) {
    if(status == 0) {
        printf("\n*PROGRAM EXITED WITH STATUS 0*");
    
    } else {
        panic("\n\nKERNEL PANIC - PROGRAM EXITED WITH STATUS 1");
    }
}

#endif