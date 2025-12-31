# BUILD FILE FOR THE "BaseKernel" X86 OPERATING SYSTEM FROM SCRATCH - https://github.com/Huguini79/BaseKernel

# CLEAR THE SCREEN
##################
clear            #
##################

# CREATE ALL THE BUILD DIRECTORIES FOR THE OBJECT FILES (*.o)(*.asm.o)
##############################
mkdir build/vga              #
mkdir build/io               #
mkdir build/io/keyboard      #
mkdir build/pci              #
mkdir build/kernel           #
mkdir build/gdt              #
mkdir build/task             #
mkdir build/task/tss         #
mkdir build/memory           #
mkdir build/memory/heap      #
mkdir build/memory/kheap     #
mkdir build/memory/paging    #
##############################

# CHECK THE TOOLCHAIN(BE CAREFULL WITH GRUB IN CROSTINI ENVIROMENTS OR LINUX VIRTUAL ENVIROMENTS)
####################################################################################################
# sudo apt-get install gcc nasm xorriso qemu-system-x86 grub-pc grub2-common                         #
####################################################################################################

# BUILD NASM(X86 ASSEMBLY PROGRAMMING LANGUAGE) FILES
####################################################################
nasm -f elf32 src/kernel/kernel.asm -o build/kernel/kernel.asm.o   #
nasm -f elf32 src/io/io.asm -o build/io/io.asm.o                   #
####################################################################

# BUILD GCC(C PROGRAMMING LANGUAGE) FILES
#########################################################################################################
gcc -I./src -m32 -ffreestanding -nostdlib -c src/kernel/kernel.c -o build/kernel/kernel.o               #
gcc -I./src -m32 -ffreestanding -nostdlib -c src/vga/vga.c -o build/vga/vga.o                           #
gcc -I./src -m32 -ffreestanding -nostdlib -c src/io/keyboard/keyboard.c -o build/io/keyboard/keyboard.o #
#########################################################################################################

# CREATE THE ELF32-I386 FILE OF THE KERNEL WITH THE OBJECT FILES USING THE LINKER
###########################################################################################################################################################################################################################
ld -m elf_i386 -T src/linker/linker.ld -o iso/boot/kernel build/kernel/kernel.asm.o build/io/io.asm.o build/kernel/kernel.o build/vga/vga.o build/io/keyboard/keyboard.o						  #
###########################################################################################################################################################################################################################

# USE GRUB-MKRESCUE TO CREATE THE ISO FILE WITH THE GRUB BOOTLOADER
####################################################################################
grub-mkrescue -o bin/BaseKernel.iso iso                                            #
####################################################################################

# RUN THE ISO WITH QEMU(ALSO YOU CAN RUN THE ISO WITH VIRTUALBOX, VMWARE, BOCHS OR IN REAL HARDWARE)
# THE FIRMWARE OF THE EMULATOR/HARDWARE HAS TO BE BIOS, NOT UEFI, ONLY BIOS
####################################################################################################
qemu-system-x86_64 bin/BaseKernel.iso                                                              #
####################################################################################################
