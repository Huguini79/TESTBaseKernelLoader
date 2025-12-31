// I/O HEADER FILE FOR THE "BaseKernel" X86 OPERATING SYSTEM FROM SCRATCH - https://github.com/Huguini79/BaseKernel

#ifndef IO_H
#define IO_H

// DEFINE THE INSB/INSW FUNCTIONS
unsigned short insb(unsigned short port);
unsigned short insw(unsigned short port);

// DEFINE THE OUTB/OUTW FUNCTIONS
void outb(unsigned short port, unsigned short val);
void outw(uint16_t port, uint16_t val);

#endif
